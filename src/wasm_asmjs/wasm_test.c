#include <stdio.h>
#include <SDL.h>
#include <emscripten.h>

#include "../libatari800/libatari800.h"

const int PIXEL_WIDTH = 2;
const int PIXEL_HEIGHT = 2;
const int GRAPHICS_HEIGHT = 192;
const int GRAPHICS_WIDTH = 320;

const int CANVAS_WIDTH = PIXEL_WIDTH * GRAPHICS_WIDTH;
const int CANVAS_HEIGHT = PIXEL_HEIGHT * GRAPHICS_HEIGHT;
const int BYTES_PER_PIXEL = 4;

SDL_Window *window;
SDL_Renderer *renderer;

void z()
{
	SDL_RenderClear(renderer);

	SDL_Rect rect;
	rect.x = 20;
	rect.y = 20;
	rect.w = 200;
	rect.h = 200;

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderPresent(renderer);
}

void drawLines()
{
	static int r = 255, g = 0, b = 0;
	r += 10;
	g += 27;
	b += 1;

	r = r % 255;
	g = g % 255;
	b = b % 255;

	SDL_Surface *surface = SDL_CreateRGBSurface(0, CANVAS_WIDTH, CANVAS_HEIGHT, 32, 0, 0, 0, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
	SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
	SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
	SDL_RenderPresent(renderer);
	SDL_FreeSurface(surface);
}

void mainloop()
{
	static int frame = 0;
	static int idx = 0;

	char msg[] = "The quick brown fox jumped over those lazy dogs who did nothing but sleep all day.";

	frame++;

	SDL_Rect rect;

	input_template_t input;

	input.keychar = 0;
	if (frame >= 200 && idx < strlen(msg))
	{
		if (frame % 4 == 0)
		{
			input.keychar = msg[idx];
			idx++;
		}
	}
	libatari800_next_frame(&input);

	if (frame % 60 != 0)
	{
		return;
	}

	/* print out portion of screen, assuming graphics 0 display list */
	unsigned char *screen = libatari800_get_screen_ptr();
	int x, y;

	screen += 384 * 24 + 24;
	for (y = 0; y < 192; y++)
	{
		for (x = 0; x < 320; x++)
		{
			unsigned char c = screen[x];
			if (c == 0)
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			else if (c == 0x94)
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			else if (c == 0x9a)
				SDL_SetRenderDrawColor(renderer, 127, 127, 127, SDL_ALPHA_OPAQUE);
			else
				SDL_SetRenderDrawColor(renderer, 127, 255, 127, SDL_ALPHA_OPAQUE);

			rect.x = x * PIXEL_WIDTH;
			rect.y = y * PIXEL_HEIGHT;
			rect.w = PIXEL_WIDTH;
			rect.h = PIXEL_HEIGHT;
			SDL_RenderFillRect(renderer, &rect);
		}
		screen += 384;
	}

	SDL_RenderPresent(renderer);
}

int init_system()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("SDL_ttf in SDL2",
							  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  CANVAS_WIDTH, CANVAS_HEIGHT,
							  0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}

static void debug_screen()
{
	/* print out portion of screen, assuming graphics 0 display list */
	unsigned char *screen = libatari800_get_screen_ptr();
	int x, y;

	screen += 384 * 24 + 24;
	for (y = 0; y < 32; y++)
	{
		for (x = 8; x < 88; x++)
		{
			unsigned char c = screen[x];
			if (c == 0)
				printf(" ");
			else if (c == 0x94)
				printf(".");
			else if (c == 0x9a)
				printf("X");
			else
				printf("?");
		}
		printf("\n");
		screen += 384;
	}
}

int main(int argc, char **argv)
{
	printf("SYSTEM IS STARTING\n");
	int frame;
	input_template_t input;

	/* force the 400/800 OS to get the Memo Pad */
	char *test_args[] = {
		"atari800",
		"-atari",
	};
	libatari800_init(sizeof(test_args) / sizeof(test_args[0]), test_args);

	libatari800_clear_input_array(&input);

	emulator_state_t state;
	cpu_state_t *cpu;
	unsigned char *pc;

	init_system();
	printf("SYSTEM IS READY TO GO\n");

	emscripten_set_main_loop(mainloop, 60, 1);

	frame = 0;
	while (frame < 200)
	{
		libatari800_get_current_state(&state);
		cpu = (cpu_state_t *)&state.state[state.tags.cpu]; /* order: A,SR,SP,X,Y */
		pc = &state.state[state.tags.pc];
		printf("frame %d: A=%02x X=%02x Y=%02x SP=%02x SR=%02x PC=%04x\n", frame, cpu->A, cpu->X, cpu->Y, cpu->P, cpu->S, pc[0] + 256 * pc[1]);
		libatari800_next_frame(&input);
		if (frame > 100)
		{
			debug_screen();
			input.keychar = 'A';
		}
		frame++;
	}
}
