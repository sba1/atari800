#ifndef SDL2_JOYSTICK_H_
#define SDL2_JOYSTICK_H_

typedef struct SDL_INPUT_RealJSConfig_t
{
    int use_hat;
} SDL_INPUT_RealJSConfig_t;

int Init_SDL2_Joysticks(int *argc, char *argv[]);
SDL_INPUT_RealJSConfig_t *SDL_INPUT_GetRealJSConfig(int joyIndex);
int SDL2_INPUT_ReadConfig(char *option, char *parameters);
void SDL2_INPUT_WriteConfig(FILE *fp);

#endif