#include "SDL_keyboard.h"
#include "sdl2_input.h"
#include "akey.h"

int sdl_keysum2scan(SDL_Keycode sym)
{
    int keycode = AKEY_NONE;
    switch (sym)
    {

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
    }

    return keycode;
}

int ascii2scan(int code)
{

    int keycode;

    switch (code)
    {
    case 0x01:
        keycode = AKEY_CTRL_a;
        break;
    case 0x02:
        keycode = AKEY_CTRL_b;
        break;
    case 0x03:
        keycode = AKEY_CTRL_c;
        break;
    case 0x04:
        keycode = AKEY_CTRL_d;
        break;
    case 0x05:
        keycode = AKEY_CTRL_E;
        break;
    case 0x06:
        keycode = AKEY_CTRL_F;
        break;
    case 0x07:
        keycode = AKEY_CTRL_G;
        break;

    /*
							case 0x08 :
								keycode = AKEY_CTRL_H;
								break;
		*/
    /* TAB - see case '\t' :
							case 0x09 :
								keycode = AKEY_CTRL_I;
								break;
		*/
    case 0x0a:
        keycode = AKEY_CTRL_J;
        break;
    case 0x0b:
        keycode = AKEY_CTRL_K;
        break;
    case 0x0c:
        keycode = AKEY_CTRL_L;
        break;

    /*
							case 0x0d :
								keycode = AKEY_CTRL_M;
								break;
		*/
    case 0x0e:
        keycode = AKEY_CTRL_N;
        break;
    case 0x0f:
        keycode = AKEY_CTRL_O;
        break;
    case 0x10:
        keycode = AKEY_CTRL_P;
        break;
    case 0x11:
        keycode = AKEY_CTRL_Q;
        break;
    case 0x12:
        keycode = AKEY_CTRL_R;
        break;
    case 0x13:
        keycode = AKEY_CTRL_S;
        break;
    case 0x14:
        keycode = AKEY_CTRL_T;
        break;
    case 0x15:
        keycode = AKEY_CTRL_U;
        break;
    case 0x16:
        keycode = AKEY_CTRL_V;
        break;
    case 0x17:
        keycode = AKEY_CTRL_W;
        break;
    case 0x18:
        keycode = AKEY_CTRL_X;
        break;
    case 0x19:
        keycode = AKEY_CTRL_Y;
        break;
    case 0x1a:
        keycode = AKEY_CTRL_Z;
        break;
    case 8:
        keycode = AKEY_BACKSPACE;
        break;
    case 13:
        keycode = AKEY_RETURN;
        break;
    case 0x1b:
        keycode = AKEY_ESCAPE;
        break;
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
