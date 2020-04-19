#define _POSIX_C_SOURCE 200112L /* for snprintf */
#include <SDL.h>

#include "sdl2_joystick.h"
#include "SDL_joystick.h"
#include "input.h"
#include "ui.h"
#include "platform.h"

#include <stdio.h>


#define MAX_JOYSTICKS	4
static SDL_Joystick *joystick[MAX_JOYSTICKS] = { NULL, NULL, NULL, NULL };
static int joystick_nbuttons[MAX_JOYSTICKS];
static SDL_INPUT_RealJSConfig_t real_js_configs[MAX_JOYSTICKS];
static int joysticks_found = 0;
static struct js_state {
	unsigned int port;
	unsigned int trig;
} sdl_js_state[MAX_JOYSTICKS];

#define minjoy 10000			/* real joystick tolerancy */

static int KBD_TRIG_0 = SDLK_RCTRL;
static int KBD_STICK_0_LEFT = SDLK_KP_4;
static int KBD_STICK_0_RIGHT = SDLK_KP_6;
static int KBD_STICK_0_DOWN = SDLK_KP_5;
static int KBD_STICK_0_UP = SDLK_KP_8;

static int KBD_TRIG_1 = SDLK_LCTRL;
static int KBD_STICK_1_LEFT = SDLK_a;
static int KBD_STICK_1_RIGHT = SDLK_d;
static int KBD_STICK_1_DOWN = SDLK_s;
static int KBD_STICK_1_UP = SDLK_w;

void PLATFORM_GetJoystickKeyName(int joystick, int direction, char *buffer, int bufsize)
{
	const char *key = "";
	switch(direction) {
		case 0: key = SDL_GetKeyName((SDL_Keycode)(joystick == 0 ? KBD_STICK_0_LEFT : KBD_STICK_1_LEFT));
			break;
		case 1: key = SDL_GetKeyName((SDL_Keycode)(joystick == 0 ? KBD_STICK_0_UP : KBD_STICK_1_UP));
			break;
		case 2: key = SDL_GetKeyName((SDL_Keycode)(joystick == 0 ? KBD_STICK_0_RIGHT : KBD_STICK_1_RIGHT));
			break;
		case 3: key = SDL_GetKeyName((SDL_Keycode)(joystick == 0 ? KBD_STICK_0_DOWN : KBD_STICK_1_DOWN));
			break;
		case 4: key = SDL_GetKeyName((SDL_Keycode)(joystick == 0 ? KBD_TRIG_0 : KBD_TRIG_1));
			break;
	}
	snprintf(buffer, bufsize, "%11s", key);
}

/*Get pointer to a real joystick configuration*/
SDL_INPUT_RealJSConfig_t* SDL_INPUT_GetRealJSConfig(int joyIndex)
{
    return &real_js_configs[joyIndex];
}


void PLATFORM_SetJoystickKey(int joystick, int direction, int value)
{
	if (joystick == 0) {
		switch(direction) {
			case 0: KBD_STICK_0_LEFT = value; break;
			case 1: KBD_STICK_0_UP = value; break;
			case 2: KBD_STICK_0_RIGHT = value; break;
			case 3: KBD_STICK_0_DOWN = value; break;
			case 4: KBD_TRIG_0 = value; break;
		}
	}
	else {
		switch(direction) {
			case 0: KBD_STICK_1_LEFT = value; break;
			case 1: KBD_STICK_1_UP = value; break;
			case 2: KBD_STICK_1_RIGHT = value; break;
			case 3: KBD_STICK_1_DOWN = value; break;
			case 4: KBD_TRIG_1 = value; break;
		}
	}
}



void Init_SDL2_Joysticks(int *argc, char *argv[])
{
}
