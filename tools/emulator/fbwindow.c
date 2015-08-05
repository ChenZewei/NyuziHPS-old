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

#include <SDL.h>
#include "device.h"
#include "fbwindow.h"

static SDL_Window *gWindow;
static SDL_Renderer *gRenderer;
static SDL_Texture *gFrameBuffer;
static int gFbWidth;
static SDL_Scancode gLastCode;

int initFB(int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0)
	{
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 0;
	}
	
	gWindow = SDL_CreateWindow("FrameBuffer", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!gWindow)
	{
		printf("SDL_CreateWindow error: %s\n", SDL_GetError());
		return 0;
	}
	
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!gRenderer)
	{
		printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
		return 0;
	}
	
	gFbWidth = width;
	gFrameBuffer = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!gFrameBuffer)
	{
		printf("SDL_CreateTexture error: %s\n", SDL_GetError());
		return 0;
	}
	
	return 1;
}

// PS/2 scancodes set 2
static unsigned int sdlToPs2(SDL_Scancode code)
{
	switch (code)
	{
		case SDL_SCANCODE_A:            return 0x1c; 
		case SDL_SCANCODE_B:            return 0x32; 
		case SDL_SCANCODE_C:            return 0x21; 
		case SDL_SCANCODE_D:            return 0x23; 
		case SDL_SCANCODE_E:            return 0x24; 
		case SDL_SCANCODE_F:            return 0x2b; 
		case SDL_SCANCODE_G:            return 0x34; 
		case SDL_SCANCODE_H:            return 0x33; 
		case SDL_SCANCODE_I:            return 0x43; 
		case SDL_SCANCODE_J:            return 0x3b; 
		case SDL_SCANCODE_K:            return 0x42; 
		case SDL_SCANCODE_L:            return 0x4b; 
		case SDL_SCANCODE_M:            return 0x3a; 
		case SDL_SCANCODE_N:            return 0x31; 
		case SDL_SCANCODE_O:            return 0x44; 
		case SDL_SCANCODE_P:            return 0x4d; 
		case SDL_SCANCODE_Q:            return 0x15; 
		case SDL_SCANCODE_R:            return 0x2d; 
		case SDL_SCANCODE_S:            return 0x1b; 
		case SDL_SCANCODE_T:            return 0x2c; 
		case SDL_SCANCODE_U:            return 0x3c; 
		case SDL_SCANCODE_V:            return 0x2a; 
		case SDL_SCANCODE_W:            return 0x1d; 
		case SDL_SCANCODE_X:            return 0x22; 
		case SDL_SCANCODE_Y:            return 0x35; 
		case SDL_SCANCODE_Z:            return 0x1a; 
		case SDL_SCANCODE_1:            return 0x16; 
		case SDL_SCANCODE_2:            return 0x1e; 
		case SDL_SCANCODE_3:            return 0x26; 
		case SDL_SCANCODE_4:            return 0x25; 
		case SDL_SCANCODE_5:            return 0x2e; 
		case SDL_SCANCODE_6:            return 0x36; 
		case SDL_SCANCODE_7:            return 0x3d; 
		case SDL_SCANCODE_8:            return 0x3e; 
		case SDL_SCANCODE_9:            return 0x46; 
		case SDL_SCANCODE_0:            return 0x45; 
		case SDL_SCANCODE_RETURN:       return 0x5a; 
		case SDL_SCANCODE_ESCAPE:       return 0x76; 
		case SDL_SCANCODE_BACKSPACE:    return 0x66; 
		case SDL_SCANCODE_TAB:          return 0x0d; 
		case SDL_SCANCODE_SPACE:        return 0x29; 
		case SDL_SCANCODE_MINUS:        return 0x4e; 
		case SDL_SCANCODE_EQUALS:       return 0x55; 
		case SDL_SCANCODE_LEFTBRACKET:  return 0x54; 
		case SDL_SCANCODE_RIGHTBRACKET: return 0x5b; 
		case SDL_SCANCODE_BACKSLASH:    return 0x5d; 
		case SDL_SCANCODE_SEMICOLON:    return 0x4c; 
		case SDL_SCANCODE_APOSTROPHE:   return 0x52; 
		case SDL_SCANCODE_GRAVE:        return 0x0e; 
		case SDL_SCANCODE_COMMA:        return 0x41; 
		case SDL_SCANCODE_PERIOD:       return 0x49; 
		case SDL_SCANCODE_SLASH:        return 0x4a; 
		case SDL_SCANCODE_CAPSLOCK:     return 0x58; 
		case SDL_SCANCODE_F1:           return 0x05; 
		case SDL_SCANCODE_F2:           return 0x06; 
		case SDL_SCANCODE_F3:           return 0x04; 
		case SDL_SCANCODE_F4:           return 0x0c; 
		case SDL_SCANCODE_F5:           return 0x03; 
		case SDL_SCANCODE_F6:           return 0x0b; 
		case SDL_SCANCODE_F7:           return 0x83; 
		case SDL_SCANCODE_F8:           return 0x0a; 
		case SDL_SCANCODE_F9:           return 0x01; 
		case SDL_SCANCODE_F10:          return 0x09; 
		case SDL_SCANCODE_F11:          return 0x78; 
		case SDL_SCANCODE_F12:          return 0x07; 
		case SDL_SCANCODE_PRINTSCREEN:  return 0xe012;	
		case SDL_SCANCODE_SCROLLLOCK:   return 0x7e;	
		case SDL_SCANCODE_INSERT:       return 0xe070;	
		case SDL_SCANCODE_HOME:         return 0xe06c;	
		case SDL_SCANCODE_PAGEUP:       return 0xe07d;	
		case SDL_SCANCODE_DELETE:       return 0xe071;	
		case SDL_SCANCODE_END:          return 0xe069;	
		case SDL_SCANCODE_PAGEDOWN:     return 0xe07a;	
		case SDL_SCANCODE_RIGHT:        return 0xe074;	
		case SDL_SCANCODE_LEFT:         return 0xe06b;	
		case SDL_SCANCODE_DOWN:         return 0xe072; 
		case SDL_SCANCODE_UP:           return 0xe075;	
		case SDL_SCANCODE_KP_DIVIDE:    return 0xe04a;	
		case SDL_SCANCODE_KP_MULTIPLY:  return 0x7c;	
		case SDL_SCANCODE_KP_MINUS:     return 0x7b;	
		case SDL_SCANCODE_KP_PLUS:      return 0x79; 	
		case SDL_SCANCODE_KP_ENTER:     return 0xe05a;	
		case SDL_SCANCODE_KP_1:         return 0x69;	
		case SDL_SCANCODE_KP_2:         return 0x72;	
		case SDL_SCANCODE_KP_3:         return 0x7a; 	
		case SDL_SCANCODE_KP_4:         return 0x6b; 	
		case SDL_SCANCODE_KP_5:         return 0x73;	
		case SDL_SCANCODE_KP_6:         return 0x74;	
		case SDL_SCANCODE_KP_7:         return 0x6c;	
		case SDL_SCANCODE_KP_8:         return 0x75;	
		case SDL_SCANCODE_KP_9:         return 0x7d;	
		case SDL_SCANCODE_KP_0:         return 0x70;	
		case SDL_SCANCODE_KP_PERIOD:    return 0x71;	
		case SDL_SCANCODE_LCTRL:        return 0x14;
		case SDL_SCANCODE_LSHIFT:       return 0x12;
		case SDL_SCANCODE_LALT:         return 0x11;
		case SDL_SCANCODE_LGUI:         return 0xe01f;
		case SDL_SCANCODE_RCTRL:        return 0xe014;
		case SDL_SCANCODE_RSHIFT:       return 0x59;
		case SDL_SCANCODE_RALT:         return 0xe011;
		case SDL_SCANCODE_RGUI:         return 0xe027;
		default: return -1;
	}
}

static void convertAndEnqueueScancode(SDL_Scancode code, int isRelease)
{
	int ps2Code = sdlToPs2(code);
	if (ps2Code == -1)
		return;

	if (ps2Code > 0xff)
		enqueueKey((ps2Code >> 8) & 0xff);

	if (isRelease)
		enqueueKey(0xf0);

	enqueueKey(ps2Code & 0xff);
}

void pollEvent()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
			
			case SDL_KEYDOWN:
				// Supress autorepeat, otherwise driver queue fills up
				if (gLastCode == event.key.keysym.scancode)
					return;	
	
				gLastCode = event.key.keysym.scancode;
				convertAndEnqueueScancode(event.key.keysym.scancode, 0);
				break;
				
			case SDL_KEYUP:
				gLastCode = -1;
				convertAndEnqueueScancode(event.key.keysym.scancode, 1);
				break;
		}
	}	
}

void updateFB(const void *base)
{
	SDL_UpdateTexture(gFrameBuffer, NULL, base, gFbWidth * 4);
	SDL_RenderCopy(gRenderer, gFrameBuffer, NULL, NULL);
	SDL_RenderPresent(gRenderer);
}


