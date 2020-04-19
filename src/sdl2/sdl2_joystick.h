#ifndef SDL2_JOYSTICK_H_
#define SDL2_JOYSTICK_H_

typedef struct SDL_INPUT_RealJSConfig_t
{
    int use_hat;
} SDL_INPUT_RealJSConfig_t;

void Init_SDL2_Joysticks(int *argc, char *argv[]);
SDL_INPUT_RealJSConfig_t *SDL_INPUT_GetRealJSConfig(int joyIndex);

#endif