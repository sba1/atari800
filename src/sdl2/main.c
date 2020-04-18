/*
 * atari_curses.c - Curses based port code
 *
 * Copyright (c) 1995-1998 David Firth
 * Copyright (c) 1998-2014 Atari800 development team (see DOC/CREDITS)

 * This file is part of the Atari800 emulator project which emulates
 * the Atari 400, 800, 800XL, 130XE, and 5200 8-bit computers.
 *
 * Atari800 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Atari800 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Atari800; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <SDL.h>

#include "config.h"
#include <string.h>

#include "screen.h"
#include "colours.h"
#include "antic.h" /* ypos */
#include "atari.h"
#include "binload.h"
#include "gtia.h" /* GTIA_COLPFx */
#include "input.h"
#include "akey.h"
#include "log.h"
#include "monitor.h"
#include "platform.h"
#include "ui.h" /* UI_alt_function */
#include "videomode.h"
#include "util.h"

#include "sdl2_input.h"
#include "sdl2_joystick.h"

#define GRAPHICS_WIDTH 336
#define GRAPHICS_HEIGHT 192

#define CANVAS_WIDTH GRAPHICS_WIDTH
#define CANVAS_HEIGHT GRAPHICS_HEIGHT

UBYTE quit = FALSE;
SDL_Window *window;
SDL_Renderer *renderer;
int last_atari_scan_code = AKEY_NONE;

#ifdef SOUND
#include "../sound.h"
#endif

void get_render_size(SDL_Window *window, int *render_width, int *render_height);
void process_input(void);
void SDL2_VIDEO_WriteConfig(FILE *fp);

int window_width = CANVAS_WIDTH;
int window_height = CANVAS_HEIGHT;
int window_x = 0;
int window_y = 0;

int PLATFORM_Configure(char *option, char *parameters)
{
	if (strcmp(option, "SDL2_WINDOW_WIDTH") == 0)
	{
		window_width = Util_sscandec(parameters);
		return TRUE;
	}

	if (strcmp(option, "SDL2_WINDOW_HEIGHT") == 0)
	{
		window_height = Util_sscandec(parameters);
		return TRUE;
	}

	if (strcmp(option, "SDL2_WINDOW_X") == 0)
	{
		window_x = Util_sscandec(parameters);
		return TRUE;
	}

	if (strcmp(option, "SDL2_WINDOW_Y") == 0)
	{
		window_y = Util_sscandec(parameters);
		return TRUE;
	}

	/*
	return SDL_VIDEO_ReadConfig(option, parameters) ||
	      SDL_INPUT_ReadConfig(option, parameters);
    */
	return FALSE;
}
void SDL2_VIDEO_WriteConfig(FILE *fp)
{
	SDL_GetWindowPosition(window, &window_x, &window_y);
	SDL_GetWindowSize(window, &window_width, &window_height);
	fprintf(fp, "SDL2_WINDOW_WIDTH=%d\n", window_width);
	fprintf(fp, "SDL2_WINDOW_HEIGHT=%d\n", window_height);
	fprintf(fp, "SDL2_WINDOW_X=%d\n", window_x);
	fprintf(fp, "SDL2_WINDOW_Y=%d\n", window_y);
}

void PLATFORM_ConfigSave(FILE *fp)
{
	printf("*** PLATFORM_CONFIG_SAVE\n");
	SDL2_VIDEO_WriteConfig(fp);
	/*
	 SDL2_VIDEO_WriteConfig(fp);
	 SDL_INPUT_WriteConfig(fp);
	 */
}

double PLATFORM_Time(void)
{
	return SDL_GetTicks() * 1e-3;
}

int PLATFORM_Initialise(int *argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return FALSE;
	}

	window = SDL_CreateWindow("SDL_ttf in SDL2",
							  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  CANVAS_WIDTH, CANVAS_HEIGHT,
							  SDL_WINDOW_RESIZABLE /* | SDL_WINDOW_OPENGL */ | SDL_WINDOW_SHOWN);

	if (window_width >= CANVAS_WIDTH && window_height >= CANVAS_HEIGHT)
	{
		SDL_SetWindowSize(window, window_width, window_height);
	}
	SDL_SetWindowPosition(window, window_x, window_y);

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return FALSE;
	}

	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return FALSE;
	}

	if (TRUE)
	{
		SDL_RendererInfo rendererInfo;
		SDL_GetRendererInfo(renderer, &rendererInfo);
		printf("Screen intialized: Using driver: %s", rendererInfo.name);
	}

	Init_SDL2_Joysticks(argc, argv);

	return TRUE;
}

int PLATFORM_Exit(int run_monitor)
{
	return FALSE;
}

/* Find the size of the window we can render into.
 * 
 * This scales to fit inside the SDL window and keep aspect ratio
 *
 *  */
void get_render_size(SDL_Window *window, int *render_width, int *render_height)
{
	int window_width, window_height;
	float canvasRatio;
	float windowRatio;

	SDL_GetWindowSize(window, &window_width, &window_height);

	canvasRatio = (float)GRAPHICS_HEIGHT / (float)GRAPHICS_WIDTH;
	windowRatio = (float)window_height / (float)window_width;

	if (windowRatio < canvasRatio)
	{
		*render_height = window_height;
		*render_width = *render_height / canvasRatio;
	}
	else
	{
		*render_width = window_width;
		*render_height = *render_width * canvasRatio;
	}
}

void process_input()
{
	SDL_Event e;

	SDL_StartTextInput();

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = TRUE;
			INPUT_key_code = AKEY_EXIT;
		}

		if (e.type == SDL_KEYDOWN)
		{
			last_atari_scan_code = sdl_keysum2scan_down(e.key.keysym.sym);
			INPUT_key_code = last_atari_scan_code;
		}

		if (e.type == SDL_KEYUP)
		{
			last_atari_scan_code = sdl_keysum2scan_up(e.key.keysym.sym);
			INPUT_key_code = last_atari_scan_code;
		}

		if (e.type == SDL_TEXTINPUT)
		{
			UBYTE khar = (UBYTE)e.text.text[0];
			last_atari_scan_code = ascii2scan(khar);
			INPUT_key_code = last_atari_scan_code;
		}
	}
}

void PLATFORM_DisplayScreen(void)
{
	int x, y;
	int render_width, render_height;
	SDL_Texture *texture;
	UBYTE *screen;
	static unsigned char pixels[CANVAS_WIDTH * CANVAS_HEIGHT * 4];

	process_input();

	get_render_size(window, &render_width, &render_height);

	SDL_RenderClear(renderer);
	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		GRAPHICS_WIDTH, GRAPHICS_HEIGHT);

	screen = (UBYTE *)Screen_atari + Screen_WIDTH;

	screen += 384 * 24 + 24;
	for (y = 0; y < GRAPHICS_HEIGHT; y++)
	{
		for (x = 0; x < GRAPHICS_WIDTH; x++)
		{
			unsigned char c = screen[x];

			unsigned char r = Colours_GetR(c);
			unsigned char b = Colours_GetB(c);
			unsigned char g = Colours_GetG(c);

			const unsigned int offset = (GRAPHICS_WIDTH * 4 * y) + x * 4;
			pixels[offset + 0] = b;
			pixels[offset + 1] = g;
			pixels[offset + 2] = r;
			pixels[offset + 3] = SDL_ALPHA_OPAQUE;
		}
		screen += 384;
	}

	SDL_UpdateTexture(
		texture,
		NULL,
		&pixels[0],
		GRAPHICS_WIDTH * 4);

	SDL_RenderSetLogicalSize(renderer, render_width, render_height);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

int PLATFORM_Keyboard(void)
{
	process_input();
	return last_atari_scan_code;
}

int PLATFORM_PORT(int num)
{
	return 0xff;
}

int PLATFORM_TRIG(int num)
{
	return 1;
}

int main(int argc, char **argv)
{
	/* initialise Atari800 core */
	if (!Atari800_Initialise(&argc, argv))
	{
		Atari800_ErrExit();
		return 3;
	}

	/* main loop */
	while (!quit)
	{
		/* INPUT_key_code = PLATFORM_Keyboard(); */
		Atari800_Frame();
		if (Atari800_display_screen)
			PLATFORM_DisplayScreen();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	Atari800_ErrExit();
	return 0;
}
