#include "SDL_keyboard.h"
#include "sdl2_input.h"
#include "input.h"
#include "akey.h"
#include "ui.h"

#define FALSE 0

static Uint8 is_shift = 0;
static Uint8 is_ctrl = 0;

int SHIFTED(int a);

int sdl_keysum2scan_up(SDL_Keycode sym)
{
    int keycode = AKEY_NONE;
    switch (sym)
    {
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
        is_shift = FALSE;
        break;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
        is_ctrl = FALSE;
        break;
    case SDLK_F2:
        INPUT_key_consol |= INPUT_CONSOL_OPTION;
        break;

    case SDLK_F3:
        INPUT_key_consol |= INPUT_CONSOL_SELECT;
        break;

    case SDLK_F4:
        INPUT_key_consol |= INPUT_CONSOL_START;
        break;

    default:
        break;
    }

    /*printf("(up) %d is_shift=%d  && is_ctrl=%d\n", INPUT_key_consol, is_shift, is_ctrl); */

    return keycode;
}

int SHIFTED(int a)
{
    if (is_ctrl)
    {
        return (a + (64 * is_shift) + (128 * is_ctrl));
    }
    return AKEY_NONE;
}

int sdl_keysum2scan_down(SDL_Keycode sym)
{
    int keycode = AKEY_NONE;

    printf("(down) UI: %d %d is_shift=%d  && is_ctrl=%d\n", UI_is_active, INPUT_key_consol, is_shift, is_ctrl);

    switch (sym)
    {
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
        is_shift = TRUE;
        break;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
        is_ctrl = TRUE;
        break;
    case SDLK_RETURN:
        keycode = AKEY_RETURN;
        break;
    case SDLK_LEFT:
        keycode = AKEY_LEFT;
        break;
    case SDLK_RIGHT:
        keycode = AKEY_RIGHT;
        break;
    case SDLK_UP:
        keycode = AKEY_UP;
        break;
    case SDLK_DOWN:
        keycode = AKEY_DOWN;
        break;

    case SDLK_F1:
        keycode = AKEY_UI;
        break;

    case SDLK_F2:
        INPUT_key_consol &= ~INPUT_CONSOL_OPTION;
        keycode = AKEY_OPTION;
        break;

    case SDLK_F3:
        INPUT_key_consol &= ~INPUT_CONSOL_SELECT;
        keycode = AKEY_SELECT;
        break;

    case SDLK_F4:
        INPUT_key_consol &= ~INPUT_CONSOL_START;
        keycode = AKEY_START;
        break;

    case SDLK_F5:
        keycode = is_shift ? AKEY_COLDSTART : AKEY_WARMSTART;
        break;

    case SDLK_END:
    case SDLK_F6:
        keycode = AKEY_HELP;

    case SDLK_F7:
        keycode = AKEY_BREAK;
        break;

    case SDLK_F8:
        UI_alt_function = UI_MENU_MONITOR;
        break;

    case SDLK_F9:
        keycode = AKEY_EXIT;
        break;

    case SDLK_F10:
        keycode = is_shift ? AKEY_SCREENSHOT_INTERLACE : AKEY_SCREENSHOT;
        break;

    case SDLK_F12:
        keycode = AKEY_TURBO;
        break;

    case SDLK_PAGEDOWN:
        keycode = AKEY_F2 | AKEY_SHFT;
        break;

    case SDLK_PAGEUP:
        keycode = AKEY_F1 | AKEY_SHFT;
        break;

    case SDLK_HOME:
        keycode = is_ctrl ? AKEY_LESS : AKEY_CLEAR;
        break;

    case SDLK_DELETE:
        keycode = is_shift ? AKEY_DELETE_LINE : AKEY_DELETE_CHAR;
        break;

    case SDLK_INSERT:
        keycode = is_shift ? AKEY_INSERT_LINE : AKEY_INSERT_CHAR;
        break;

    case SDLK_CAPSLOCK:
        keycode = is_shift ? AKEY_CAPSTOGGLE : AKEY_CAPSTOGGLE;
        break;

        /* work-around for windows */
    case SDLK_BACKSLASH:
        keycode = AKEY_ESCAPE;
        break;

    case SDLK_TAB:
        keycode = AKEY_TAB;
        break;

    case SDLK_BACKSPACE:
        keycode = AKEY_BACKSPACE;
        break;

    case SDLK_a:
        keycode = SHIFTED(AKEY_a);
        break;
    case SDLK_b:
        keycode = SHIFTED(AKEY_b);
        break;
    case SDLK_c:
        keycode = SHIFTED(AKEY_c);
        break;
    case SDLK_d:
        keycode = SHIFTED(AKEY_d);
        break;
    case SDLK_e:
        keycode = SHIFTED(AKEY_e);
        break;
    case SDLK_f:
        keycode = SHIFTED(AKEY_f);
        break;
    case SDLK_g:
        keycode = SHIFTED(AKEY_g);
        break;
    case SDLK_h:
        keycode = SHIFTED(AKEY_h);
        break;
    case SDLK_i:
        keycode = SHIFTED(AKEY_i);
        break;
    case SDLK_j:
        keycode = SHIFTED(AKEY_j);
        break;
    case SDLK_k:
        keycode = SHIFTED(AKEY_k);
        break;
    case SDLK_l:
        keycode = SHIFTED(AKEY_l);
        break;
    case SDLK_m:
        keycode = SHIFTED(AKEY_m);
        break;
    case SDLK_n:
        keycode = SHIFTED(AKEY_n);
        break;
    case SDLK_o:
        keycode = SHIFTED(AKEY_o);
        break;
    case SDLK_p:
        keycode = SHIFTED(AKEY_p);
        break;
    case SDLK_q:
        keycode = SHIFTED(AKEY_q);
        break;
    case SDLK_r:
        keycode = SHIFTED(AKEY_r);
        break;
    case SDLK_s:
        keycode = SHIFTED(AKEY_s);
        break;
    case SDLK_t:
        keycode = SHIFTED(AKEY_t);
        break;
    case SDLK_u:
        keycode = SHIFTED(AKEY_u);
        break;
    case SDLK_v:
        keycode = SHIFTED(AKEY_v);
        break;
    case SDLK_w:
        keycode = SHIFTED(AKEY_w);
        break;
    case SDLK_x:
        keycode = SHIFTED(AKEY_x);
        break;
    case SDLK_y:
        keycode = SHIFTED(AKEY_y);
        break;
    case SDLK_z:
        keycode = SHIFTED(AKEY_z);
        break;
    case SDLK_ESCAPE:
        keycode = AKEY_ESCAPE;
        break;
    case SDLK_BACKQUOTE:
    /* Fallthrough */
    case SDLK_LGUI:
        keycode = AKEY_ATARI;
        break;
    case SDLK_RGUI:
        keycode = is_shift ? AKEY_CAPSLOCK : AKEY_CAPSTOGGLE;
        break;
    }

    return keycode;
}

int ascii2scan(int code)
{

    int keycode;

    switch (code)
    {
    case '0':
        keycode = AKEY_0;
        break;
    case '1':
        keycode = AKEY_1;
        break;
    case '2':
        keycode = AKEY_2;
        break;
    case '3':
        keycode = AKEY_3;
        break;
    case '4':
        keycode = AKEY_4;
        break;
    case '5':
        keycode = AKEY_5;
        break;
    case '6':
        keycode = AKEY_6;
        break;
    case '7':
        keycode = AKEY_7;
        break;
    case '8':
        keycode = AKEY_8;
        break;
    case '9':
        keycode = AKEY_9;
        break;
    case 'A':
    case 'a':
        keycode = AKEY_a;
        break;
    case 'B':
    case 'b':
        keycode = AKEY_b;
        break;
    case 'C':
    case 'c':
        keycode = AKEY_c;
        break;
    case 'D':
    case 'd':
        keycode = AKEY_d;
        break;
    case 'E':
    case 'e':
        keycode = AKEY_e;
        break;
    case 'F':
    case 'f':
        keycode = AKEY_f;
        break;
    case 'G':
    case 'g':
        keycode = AKEY_g;
        break;
    case 'H':
    case 'h':
        keycode = AKEY_h;
        break;
    case 'I':
    case 'i':
        keycode = AKEY_i;
        break;
    case 'J':
    case 'j':
        keycode = AKEY_j;
        break;
    case 'K':
    case 'k':
        keycode = AKEY_k;
        break;
    case 'L':
    case 'l':
        keycode = AKEY_l;
        break;
    case 'M':
    case 'm':
        keycode = AKEY_m;
        break;
    case 'N':
    case 'n':
        keycode = AKEY_n;
        break;
    case 'O':
    case 'o':
        keycode = AKEY_o;
        break;
    case 'P':
    case 'p':
        keycode = AKEY_p;
        break;
    case 'Q':
    case 'q':
        keycode = AKEY_q;
        break;
    case 'R':
    case 'r':
        keycode = AKEY_r;
        break;
    case 'S':
    case 's':
        keycode = AKEY_s;
        break;
    case 'T':
    case 't':
        keycode = AKEY_t;
        break;
    case 'U':
    case 'u':
        keycode = AKEY_u;
        break;
    case 'V':
    case 'v':
        keycode = AKEY_v;
        break;
    case 'W':
    case 'w':
        keycode = AKEY_w;
        break;
    case 'X':
    case 'x':
        keycode = AKEY_x;
        break;
    case 'Y':
    case 'y':
        keycode = AKEY_y;
        break;
    case 'Z':
    case 'z':
        keycode = AKEY_z;
        break;
    case ' ':
        keycode = AKEY_SPACE;
        break;
    case '\t':
        keycode = AKEY_TAB;
        break;
    case '!':
        keycode = AKEY_EXCLAMATION;
        break;
    case '"':
        keycode = AKEY_DBLQUOTE;
        break;
    case '#':
        keycode = AKEY_HASH;
        break;
    case '$':
        keycode = AKEY_DOLLAR;
        break;
    case '%':
        keycode = AKEY_PERCENT;
        break;
    case '&':
        keycode = AKEY_AMPERSAND;
        break;
    case '\'':
        keycode = AKEY_QUOTE;
        break;
    case '@':
        keycode = AKEY_AT;
        break;
    case '(':
        keycode = AKEY_PARENLEFT;
        break;
    case ')':
        keycode = AKEY_PARENRIGHT;
        break;
    case '<':
        keycode = AKEY_LESS;
        break;
    case '>':
        keycode = AKEY_GREATER;
        break;
    case '=':
        keycode = AKEY_EQUAL;
        break;
    case '?':
        keycode = AKEY_QUESTION;
        break;
    case '-':
        keycode = AKEY_MINUS;
        break;
    case '+':
        keycode = AKEY_PLUS;
        break;
    case '*':
        keycode = AKEY_ASTERISK;
        break;
    case '/':
        keycode = AKEY_SLASH;
        break;
    case ':':
        keycode = AKEY_COLON;
        break;
    case ';':
        keycode = AKEY_SEMICOLON;
        break;
    case ',':
        keycode = AKEY_COMMA;
        break;
    case '.':
        keycode = AKEY_FULLSTOP;
        break;
    case '_':
        keycode = AKEY_UNDERSCORE;
        break;
    case '[':
        keycode = AKEY_BRACKETLEFT;
        break;
    case ']':
        keycode = AKEY_BRACKETRIGHT;
        break;
    case '^':
        keycode = AKEY_CIRCUMFLEX;
        break;
    case '\\':
        keycode = AKEY_BACKSLASH;
        break;
    case '|':
        keycode = AKEY_BAR;
        break;
    default:
        keycode = AKEY_NONE;
        break;
    }

    printf("keycode of %c %d\n", code, keycode);

    return keycode;
}
