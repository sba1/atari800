#ifndef SDL2_INPUT_H_
#define SLD2_INPUT_H_

#include <SDL.h>

int ascii2scan(int code);
int sdl_keysum2scan_up(SDL_Keycode sym);
int sdl_keysum2scan_down(SDL_Keycode sym);
#endif
