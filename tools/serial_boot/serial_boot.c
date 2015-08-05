// 
// Copyright 2011-2015 Jeff Bush
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 

//
// Loads file over the serial port into memory on the FPGA board.  This 
// communicates with the first stage bootloader in software/bootloader.
// This expects the memory file to be in the format used by the Verilog 
// system task $readmemh: each line is a 32 bit hexadecimal value.
// This may optionally also take a binary ramdisk image to load at 0x4000000.
// This checks for transfer errors, but does not attempt to recover or 
// retransmit. If it fails, the user can reset the board and try again.
// Errors are very rare in my experience.
//

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

#define RAMDISK_BASE 0x4000000
#define BLOCK_SIZE 1024
#define PROGRESS_BAR_WIDTH 40

// This must match the enum in software/bootloader/boot.c
enum Command
{
	kLoadMemoryReq = 0xc0,
	kLoadMemoryAck,
	kExecuteReq,
	kExecuteAck,
	kPingReq,
	kPingAck,
	kClearMemoryReq,
	kClearMemoryAck
};

int open_serial_port(const char *path)
{
	struct termios serialopts;
	int serial_fd;

	serial_fd = open(path, O_RDWR | O_NOCTTY);
	if (serial_fd < 0)
	{
		perror("couldn't open serial port");
		return -1;
	}
	
	// Configure serial options
	memset(&serialopts, 0, sizeof(serialopts));
	serialopts.c_cflag = CS8 | CLOCAL | CREAD;
	cfsetspeed(&serialopts, B115200);
	if (tcsetattr(serial_fd, TCSANOW, &serialopts) != 0)
	{
		perror("Unable to initialize serial port");
		return -1;
	}
	
	// Clear out any junk that may already be buffered in the 
	// serial driver (otherwise the ping sequence may fail)
	tcflush(serial_fd, TCIOFLUSH);

	return serial_fd;
}

// Returns 1 if the byte was read successfully, 0 if a timeout
// or other error occurred.
int read_serial_byte(int serial_fd, unsigned char *ch, int timeout_ms)
{	
	fd_set set;
	struct timeval tv;
	int ready_fds;

	FD_ZERO(&set);
	FD_SET(serial_fd, &set);

	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;

	do 
	{
		ready_fds = select(FD_SETSIZE, &set, NULL, NULL, &tv);
	} 
	while (ready_fds < 0 && errno == EINTR);

	if (ready_fds == 0)
		return 0;
	
	if (read(serial_fd, ch, 1) != 1)
	{
		perror("read");
		return 0;
	}
	
	return 1;
}

int read_serial_long(int serial_fd, unsigned int *out, int timeout)
{
	unsigned int result = 0;
	unsigned char ch;
	int i;
	
	for (i = 0; i < 4; i++)
	{
		if (!read_serial_byte(serial_fd, &ch, timeout))
			return 0;

		result = (result >> 8) | (ch << 24);
	}
	
	*out = result;
	return 1;
}

int write_serial_byte(int serial_fd, unsigned int ch)
{
	if (write(serial_fd, &ch, 1) != 1)
	{
		perror("write");
		return 0;
	}

	return 1;
}

int write_serial_long(int serial_fd, unsigned int value)
{
	char out[4] = { value & 0xff, (value >> 8) & 0xff, (value >> 16) & 0xff,
		(value >> 24) & 0xff };
	
	if (write(serial_fd, out, 4) != 4)
	{
		perror("write");
		return 0;
	}

	return 1;
}

int fill_memory(int serial_fd, unsigned int address, const unsigned char *buffer, int length)
{
	unsigned int target_checksum;
	unsigned int local_checksum;
	int cksuma;
	int cksumb;
	unsigned char ch;
	int i;

	if (!write_serial_byte(serial_fd, kLoadMemoryReq))
		return 0;
	
	if (!write_serial_long(serial_fd, address))
		return 0;
	
	if (!write_serial_long(serial_fd, length))
		return 0;
	
	local_checksum = 0;
	cksuma = 0;
	cksumb = 0;

	if (write(serial_fd, buffer, length) != length)
	{
		fprintf(stderr, "\nError writing to serial port\n");
		return 0;
	}

	// wait for ack
	if (!read_serial_byte(serial_fd, &ch, 15000) || ch != kLoadMemoryAck)
	{
		fprintf(stderr, "\n%08x Did not get ack for load memory\n", address);
		return 0;
	}

	for (i = 0; i < length; i++)
	{
		cksuma += buffer[i];
		cksumb += cksuma;
	}

	local_checksum = (cksuma & 0xffff) | ((cksumb & 0xffff) << 16);

	if (!read_serial_long(serial_fd, &target_checksum, 5000))
	{
		fprintf(stderr, "\n%08x timed out reading checksum\n", address);
		return 0;
	}

	if (target_checksum != local_checksum)
	{
		fprintf(stderr, "\n%08x checksum mismatch want %08x got %08x\n",
			address, local_checksum, target_checksum);
		return 0;
	}

	return 1;
}

int clear_memory(int serial_fd, unsigned int address, int length)
{
	unsigned char ch;

	if (!write_serial_byte(serial_fd, kClearMemoryReq))
		return 0;
	
	if (!write_serial_long(serial_fd, address))
		return 0;
	
	if (!write_serial_long(serial_fd, length))
		return 0;
	
	// wait for ack
	if (!read_serial_byte(serial_fd, &ch, 15000) || ch != kClearMemoryAck)
	{
		fprintf(stderr, "\n%08x Did not get ack for clear memory\n", address);
		return 0;
	}

	return 1;
}

int ping_target(int serial_fd)
{
	int retry;
	unsigned char ch;
	
	printf("ping target");

	int target_ready = 0;
	for (retry = 0; retry < 20; retry++)
	{
		printf(".");
		fflush(stdout);
		write_serial_byte(serial_fd, kPingReq);
		if (read_serial_byte(serial_fd, &ch, 250) && ch == kPingAck) 
		{
			target_ready = 1;
			break;
		}
	}
	
	if (!target_ready) 
	{ 
		printf("target is not responding\n");
		return 0;
	}
	
	printf("\n");
	
	return 1;
}

int send_execute_command(int serial_fd)
{
	unsigned char ch;
	
	write_serial_byte(serial_fd, kExecuteReq);
	if (!read_serial_byte(serial_fd, &ch, 15000) || ch != kExecuteAck)
	{
		fprintf(stderr, "Target returned error starting execution\n");
		return 0;
	}
	
	return 1;
}

void do_console_mode(int serial_fd)
{
	fd_set set;
	int ready_fds;
	char read_buffer[256];
	int got;

	while (1)
	{
		FD_ZERO(&set);
		FD_SET(serial_fd, &set);
		FD_SET(STDIN_FILENO, &set);	// stdin

		do 
		{
			ready_fds = select(FD_SETSIZE, &set, NULL, NULL, NULL);
		} 
		while (ready_fds < 0 && errno == EINTR);

		if (FD_ISSET(serial_fd, &set))
		{
			// Serial -> Terminal
			got = read(serial_fd, read_buffer, sizeof(read_buffer));
			if (got <= 0)
			{
				perror("read");
				return;
			}
			
			if (write(STDIN_FILENO, read_buffer, got) < got)
			{
				perror("write");
				return;
			}
		}
		
		if (FD_ISSET(STDIN_FILENO, &set))
		{
			// Terminal -> Serial
			got = read(STDIN_FILENO, read_buffer, sizeof(read_buffer));
			if (got <= 0)
			{
				perror("read");
				return;
			}
			
			if (write(serial_fd, read_buffer, got) != got)
			{
				perror("write");
				return;
			}
		}	
	}
}

int read_hex_file(const char *filename, unsigned char **out_ptr, int *out_length)
{
	FILE *input_file;
	char line[16];
	int offset = 0;
	unsigned char *data;
	int file_length;

	input_file = fopen(filename, "r");
	if (!input_file) 
	{
		perror("Error opening input file\n");
		return 0;
	}

	fseek(input_file, 0, SEEK_END);
	file_length = ftell(input_file);
	fseek(input_file, 0, SEEK_SET);
	
	// This may overestimate the size a bit, which is fine.
	data = malloc(file_length / 2);
	while (fgets(line, sizeof(line), input_file)) 
	{
		unsigned int value = strtoul(line, NULL, 16);
		data[offset++] = (value >> 24) & 0xff;
		data[offset++] = (value >> 16) & 0xff;
		data[offset++] = (value >> 8) & 0xff;
		data[offset++] = value & 0xff;
	}
	
	*out_ptr = data;
	*out_length = offset;
	fclose(input_file);
	
	return 1;
}

int read_binary_file(const char *filename, unsigned char **out_ptr, int *out_length)
{
	FILE *input_file;
	unsigned char *data;
	int file_length;

	input_file = fopen(filename, "r");
	if (!input_file) 
	{
		perror("Error opening input file");
		return 0;
	}

	fseek(input_file, 0, SEEK_END);
	file_length = ftell(input_file);
	fseek(input_file, 0, SEEK_SET);
	
	data = malloc(file_length);
	if (fread(data, file_length, 1, input_file) != 1)
	{
		perror("Error reading file");
		return 0;
	}
	
	*out_ptr = data;
	*out_length = file_length;
	fclose(input_file);
	
	return 1;
}

void print_progress_bar(int current, int total)
{
	int numTicks = current * PROGRESS_BAR_WIDTH / total;
	int i;

	printf("\rLoading [");
	for (i = 0; i < numTicks; i++)
		printf("=");

	for (; i < PROGRESS_BAR_WIDTH; i++)
		printf(" ");
	
	printf("] (%d%%)", current * 100 / total);
	fflush(stdout);
}

static int is_empty(unsigned char *data, int length)
{
	int empty;
	int i;

	empty = 1;
	for (i = 0; i < length; i++)
	{
		if (data[i] != 0)
		{
			empty = 0;
			break;
		}
	}

	return empty;
}

int send_file(int serial_fd, unsigned int address, unsigned char *data, int data_length)
{
	int offset = 0;
	
	print_progress_bar(0, data_length);
	while (offset < data_length)
	{
		int this_slice = data_length - offset;
		if (this_slice > BLOCK_SIZE)
			this_slice = BLOCK_SIZE;

		if (is_empty(data + offset, this_slice))
		{
			if (!clear_memory(serial_fd, address + offset, this_slice))
				return 0;
		}
		else
		{
			if (!fill_memory(serial_fd, address + offset, data + offset, this_slice))
				return 0;
		}

		offset += this_slice;
		print_progress_bar(offset, data_length);
	}
	
	return 1;
}

int main(int argc, const char *argv[])
{
	unsigned char *program_data;
	int program_length;
	unsigned char *ramdisk_data = NULL;
	int ramdisk_length;
	int serial_fd;
	
	if (argc < 3)
	{
		fprintf(stderr, "USAGE:\n    serial_boot <serial port name> <hex file> [<ramdisk image>]\n");
		return 1;
	}

	if (!read_hex_file(argv[2], &program_data, &program_length))
		return 1;

	if (argc == 4)
	{
		// Load binary ramdisk image
		if (!read_binary_file(argv[3], &ramdisk_data, &ramdisk_length))
			return 1;
	}

	serial_fd = open_serial_port(argv[1]);
	if (serial_fd < 0)
		return 1;

	if (!ping_target(serial_fd))
		return 1;

	printf("Program is %d bytes\n", program_length);
	if (!send_file(serial_fd, 0, program_data, program_length))
		return 1;
	
	if (ramdisk_data)
	{
		printf("\nRamdisk is %d bytes\n", ramdisk_length);
		if (!send_file(serial_fd, RAMDISK_BASE, ramdisk_data, ramdisk_length))
			return 1;
	}
	
	if (!send_execute_command(serial_fd))
		return 1;
	
	printf("\nProgram running, entering console mode\n");
	
	do_console_mode(serial_fd);
	
	return 0;
}
