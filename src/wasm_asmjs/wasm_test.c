#include <stdio.h>
#include <SDL.h>
#include <emscripten.h>

#include "../libatari800/libatari800.h"
#include "../colours.h"

const int GRAPHICS_WIDTH = 336;
const int GRAPHICS_HEIGHT = 192;

const int CANVAS_WIDTH = GRAPHICS_WIDTH;
const int CANVAS_HEIGHT = GRAPHICS_HEIGHT;

SDL_Window *window;
SDL_Renderer *renderer;

void mainloop()
{
	static int frame = 0;
	static int idx = 0;
	static unsigned char pixels[CANVAS_WIDTH * CANVAS_HEIGHT * 4];

	char msg[] = "The quick brown fox jumped over those lazy dogs who did nothing but sleep all day. 1234567890-=!@#$^&*()_+";

	frame++;

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

	SDL_Texture *texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		GRAPHICS_WIDTH, GRAPHICS_HEIGHT);


	/* print out portion of screen, assuming graphics 0 display list */
	unsigned char *screen = libatari800_get_screen_ptr();
	int x, y;

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
			pixels[offset + 0] = b;				   // b
			pixels[offset + 1] = g;				   // g
			pixels[offset + 2] = r;				   // r
			pixels[offset + 3] = SDL_ALPHA_OPAQUE; // a

		}
		screen += 384;
	}

	SDL_UpdateTexture(
		texture,
		NULL,
		&pixels[0],
		GRAPHICS_WIDTH * 4);

	SDL_RenderCopy(renderer, texture, NULL, NULL);

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
		"-basic",
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
