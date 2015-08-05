// 
// Copyright 2015 Jeff Bush
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

#include "unistd.h"

// Assuming 50 Mhz system clock
#define CLOCKS_PER_US 50

int usleep(useconds_t delay)
{
	useconds_t expire = __builtin_nyuzi_read_control_reg(6) + delay * CLOCKS_PER_US;
	while (__builtin_nyuzi_read_control_reg(6) < expire)
		;

	return 0;
}