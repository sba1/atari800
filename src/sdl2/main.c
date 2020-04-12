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

#ifdef SOUND
#include "../sound.h"
#endif

double PLATFORM_Time(void)
{
	return SDL_GetTicks() * 1e-3;
}

int PLATFORM_Initialise(int *argc, char *argv[])
{
	return TRUE;
}

int PLATFORM_Exit(int run_monitor)
{
	return FALSE;
}

void PLATFORM_DisplayScreen(void)
{
}

int PLATFORM_Keyboard(void)
{
	/* int keycode = getch(); */
	int keycode = 33;

	INPUT_key_consol = INPUT_CONSOL_NONE;

	switch (keycode)
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
		keycode = AKEY_CTRL_e;
		break;
	case 0x06:
		keycode = AKEY_CTRL_f;
		break;
	case 0x07:
		keycode = AKEY_CTRL_g;
		break;
		/*
	case 0x08:
		keycode = AKEY_CTRL_h;
		break;
 */
	case 0x09:
		keycode = AKEY_TAB;
		break;
		/*
	case 0x0a:
		keycode = AKEY_CTRL_j;
		break;
 */
	case 0x0b:
		keycode = AKEY_CTRL_k;
		break;
	case 0x0c:
		keycode = AKEY_CTRL_l;
		break;
		/*
	case 0x0d:
		keycode = AKEY_CTRL_m;
		break;
 */
	case 0x0e:
		keycode = AKEY_CTRL_n;
		break;
	case 0x0f:
		keycode = AKEY_CTRL_o;
		break;
	case 0x10:
		keycode = AKEY_CTRL_p;
		break;
	case 0x11:
		keycode = AKEY_CTRL_q;
		break;
	case 0x12:
		keycode = AKEY_CTRL_r;
		break;
	case 0x13:
		keycode = AKEY_CTRL_s;
		break;
	case 0x14:
		keycode = AKEY_CTRL_t;
		break;
	case 0x15:
		keycode = AKEY_CTRL_u;
		break;
	case 0x16:
		keycode = AKEY_CTRL_v;
		break;
	case 0x17:
		keycode = AKEY_CTRL_w;
		break;
	case 0x18:
		keycode = AKEY_CTRL_x;
		break;
	case 0x19:
		keycode = AKEY_CTRL_y;
		break;
	case 0x1a:
		keycode = AKEY_CTRL_z;
		break;
	case '`':
		keycode = AKEY_CAPSTOGGLE;
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
	case '[':
		keycode = AKEY_BRACKETLEFT;
		break;
	case ']':
		keycode = AKEY_BRACKETRIGHT;
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
#ifdef PADMINUS
	case PADMINUS:
#endif
	case '-':
		keycode = AKEY_MINUS;
		break;
#ifdef PADPLUS
	case PADPLUS:
#endif
	case '+':
		keycode = AKEY_PLUS;
		break;
#ifdef PADSTAR
	case PADSTAR:
#endif
	case '*':
		keycode = AKEY_ASTERISK;
		break;
#ifdef PADSLASH
	case PADSLASH:
#endif
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
	case '^':
		keycode = AKEY_CIRCUMFLEX;
		break;
	case '\\':
		keycode = AKEY_BACKSLASH;
		break;
	case '|':
		keycode = AKEY_BAR;
		break;
	case ' ':
		keycode = AKEY_SPACE;
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
	case 'a':
		keycode = AKEY_a;
		break;
	case 'b':
		keycode = AKEY_b;
		break;
	case 'c':
		keycode = AKEY_c;
		break;
	case 'd':
		keycode = AKEY_d;
		break;
	case 'e':
		keycode = AKEY_e;
		break;
	case 'f':
		keycode = AKEY_f;
		break;
	case 'g':
		keycode = AKEY_g;
		break;
	case 'h':
		keycode = AKEY_h;
		break;
	case 'i':
		keycode = AKEY_i;
		break;
	case 'j':
		keycode = AKEY_j;
		break;
	case 'k':
		keycode = AKEY_k;
		break;
	case 'l':
		keycode = AKEY_l;
		break;
	case 'm':
		keycode = AKEY_m;
		break;
	case 'n':
		keycode = AKEY_n;
		break;
	case 'o':
		keycode = AKEY_o;
		break;
	case 'p':
		keycode = AKEY_p;
		break;
	case 'q':
		keycode = AKEY_q;
		break;
	case 'r':
		keycode = AKEY_r;
		break;
	case 's':
		keycode = AKEY_s;
		break;
	case 't':
		keycode = AKEY_t;
		break;
	case 'u':
		keycode = AKEY_u;
		break;
	case 'v':
		keycode = AKEY_v;
		break;
	case 'w':
		keycode = AKEY_w;
		break;
	case 'x':
		keycode = AKEY_x;
		break;
	case 'y':
		keycode = AKEY_y;
		break;
	case 'z':
		keycode = AKEY_z;
		break;
	case 'A':
		keycode = AKEY_A;
		break;
	case 'B':
		keycode = AKEY_B;
		break;
	case 'C':
		keycode = AKEY_C;
		break;
	case 'D':
		keycode = AKEY_D;
		break;
	case 'E':
		keycode = AKEY_E;
		break;
	case 'F':
		keycode = AKEY_F;
		break;
	case 'G':
		keycode = AKEY_G;
		break;
	case 'H':
		keycode = AKEY_H;
		break;
	case 'I':
		keycode = AKEY_I;
		break;
	case 'J':
		keycode = AKEY_J;
		break;
	case 'K':
		keycode = AKEY_K;
		break;
	case 'L':
		keycode = AKEY_L;
		break;
	case 'M':
		keycode = AKEY_M;
		break;
	case 'N':
		keycode = AKEY_N;
		break;
	case 'O':
		keycode = AKEY_O;
		break;
	case 'P':
		keycode = AKEY_P;
		break;
	case 'Q':
		keycode = AKEY_Q;
		break;
	case 'R':
		keycode = AKEY_R;
		break;
	case 'S':
		keycode = AKEY_S;
		break;
	case 'T':
		keycode = AKEY_T;
		break;
	case 'U':
		keycode = AKEY_U;
		break;
	case 'V':
		keycode = AKEY_V;
		break;
	case 'W':
		keycode = AKEY_W;
		break;
	case 'X':
		keycode = AKEY_X;
		break;
	case 'Y':
		keycode = AKEY_Y;
		break;
	case 'Z':
		keycode = AKEY_Z;
		break;
	case 0x1b:
		keycode = AKEY_ESCAPE;
		break;
	case 8:
	case 127:
#ifdef KEY_BACKSPACE
#if KEY_BACKSPACE != 8 && KEY_BACKSPACE != 127
	case KEY_BACKSPACE:
#endif
#endif
		keycode = AKEY_BACKSPACE;
		break;
	case '\n':
		keycode = AKEY_RETURN;
		break;
	default:
		keycode = AKEY_NONE;
		break;
	}
	return keycode;
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
		return 3;

	/* main loop */
	for (;;)
	{
		INPUT_key_code = PLATFORM_Keyboard();
		Atari800_Frame();
		if (Atari800_display_screen)
			PLATFORM_DisplayScreen();
	}
}
