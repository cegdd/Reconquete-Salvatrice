#include "main.h"

typedef struct typeFORevent typeFORevent;

void intputtexte(typeFORevent *FORevent)
{

	int typeclavier = FORevent->systeme->typeclavier;

	switch (FORevent->systeme->evenement.key.keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		FORevent->systeme->echap = 1;
		break;
	case SDL_SCANCODE_DOWN:
		FORevent->deplacement->direction.bas = 1;
		FORevent->deplacement->persobouge = 1;
		break;
	case SDL_SCANCODE_UP:
		FORevent->deplacement->direction.haut = 1;
		FORevent->deplacement->persobouge = 1;
		break;
	case SDL_SCANCODE_LEFT:
		FORevent->deplacement->direction.gauche = 1;
		FORevent->deplacement->persobouge = 1;
		break;
	case SDL_SCANCODE_RIGHT:
		FORevent->deplacement->direction.droite = 1;
		FORevent->deplacement->persobouge = 1;
		break;
	case SDL_SCANCODE_A:
		if (FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'q';
			}
			else if (typeclavier == '2')
			{
				FORevent->chat->lettre = 'a';
			}
			else if (typeclavier == '3')
			{
				FORevent->chat->lettre = 'a';
			}
		}
		else
		{
			FORevent->deplacement->direction.gauche = 1;
			FORevent->deplacement->persobouge = 1;
		}
		break;
	case SDL_SCANCODE_B:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'b';
		}
		break;
	case SDL_SCANCODE_C:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'c';
		}
		break;
	case SDL_SCANCODE_D:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'd';
		}
		else
		{
			FORevent->deplacement->direction.droite = 1;
			FORevent->deplacement->persobouge = 1;
		}
		break;
	case SDL_SCANCODE_E:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'e';
		}
		break;
	case SDL_SCANCODE_F:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'f';
		}
		break;
	case SDL_SCANCODE_G:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'g';
		}
		break;
	case SDL_SCANCODE_H:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'h';
		}
		break;
	case SDL_SCANCODE_I:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'i';
		}
		break;
	case SDL_SCANCODE_J:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'j';
		}
		break;
	case SDL_SCANCODE_K:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'k';
		}
		break;
	case SDL_SCANCODE_L:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'l';
		}
		break;
	case SDL_SCANCODE_M:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '?';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '\0';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = ',';
			}
		}
		break;
	case SDL_SCANCODE_SEMICOLON:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'm';
		}
		break;
	case SDL_SCANCODE_N:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'n';
		}
		break;
	case SDL_SCANCODE_O:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'o';
		}
		break;
	case SDL_SCANCODE_P:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'p';
		}
		break;
	case SDL_SCANCODE_Q:
		if (FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'a';
			}
			else if (typeclavier == '2')
			{
				FORevent->chat->lettre = 'q';
			}
			else if (typeclavier == '3')
			{
				FORevent->chat->lettre = 'q';
			}
		}
		break;
	case SDL_SCANCODE_R:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'r';
		}
		break;
	case SDL_SCANCODE_S:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 's';
		}
		else
		{
			FORevent->deplacement->direction.bas = 1;
			FORevent->deplacement->persobouge = 1;
		}
		break;
	case SDL_SCANCODE_T:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 't';
		}
		break;
	case SDL_SCANCODE_U:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'u';
		}
		break;
	case SDL_SCANCODE_V:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'v';
		}
		break;
	case SDL_SCANCODE_W:
		if (FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'z';
			}
			else if (typeclavier == '2')
			{
				FORevent->chat->lettre = 'w';
			}
			else if (typeclavier == '3')
			{
				FORevent->chat->lettre = 'w';
			}
		}
		else
		{
			FORevent->deplacement->direction.haut = 1;
			FORevent->deplacement->persobouge = 1;
		}
		break;
	case SDL_SCANCODE_X:
		if (FORevent->chat->saisiechat == 1)
		{
			FORevent->chat->lettre = 'x';
		}
		break;
	case SDL_SCANCODE_Y:
		if (FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'y';
			}
			else if (typeclavier == '2')
			{
				FORevent->chat->lettre = 'y';
			}
			else if (typeclavier == '3')
			{
				FORevent->chat->lettre = 'z';
			}
		}
		break;
	case SDL_SCANCODE_Z:
		if (FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'w';
			}
			else if (typeclavier == '2')
			{
				FORevent->chat->lettre = 'z';
			}
			else if (typeclavier == '3')
			{
				FORevent->chat->lettre = 'y';
			}
		}
		break;
	case SDL_SCANCODE_0:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '0';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '@';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'à';
			}
		}
		break;
	case SDL_SCANCODE_1:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '1';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '\0';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = '&';
			}
		}
		break;
	case SDL_SCANCODE_2:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '2';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '~';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'é';
			}
		}
		break;
	case SDL_SCANCODE_3:
		if (FORevent->chat->saisiechat == 1)
			{
				if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
				{
					FORevent->chat->lettre = '3';
				}
				else if (typeclavier == '1' && FORevent->systeme->altactif == true)
				{
					FORevent->chat->lettre = '#';
				}
				else if (typeclavier == '1')
				{
					FORevent->chat->lettre = '"';
				}
			}
		break;
	case SDL_SCANCODE_4:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '4';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '{';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = '\'';
			}
		}
		break;
	case SDL_SCANCODE_5:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '5';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '[';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = '(';
			}
		}
		break;
	case SDL_SCANCODE_6:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '6';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '|';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = '-';
			}
		}
		break;
	case SDL_SCANCODE_7:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '7';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '`';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'è';
			}
		}
		break;
	case SDL_SCANCODE_8:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '8';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '\\';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = '_';
			}
		}
		break;
	case SDL_SCANCODE_9:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '9';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '^';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = 'ç';
			}
		}
		break;
	case SDL_SCANCODE_MINUS:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '°';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = ']';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = ')';
			}
		}
		break;
	case SDL_SCANCODE_EQUALS:
		if(FORevent->chat->saisiechat == 1)
		{
			if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
			{
				FORevent->chat->lettre = '+';
			}
			else if (typeclavier == '1' && FORevent->systeme->altactif == true)
			{
				FORevent->chat->lettre = '}';
			}
			else if (typeclavier == '1')
			{
				FORevent->chat->lettre = '=';
			}
			break;
		case SDL_SCANCODE_LEFTBRACKET:
		if(FORevent->chat->saisiechat == 1)
			{
				if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
				{
					FORevent->chat->lettre = '¨';
				}
				else if (typeclavier == '1' && FORevent->systeme->altactif == true)
				{
					FORevent->chat->lettre = '\0';
				}
				else if (typeclavier == '1')
				{
					FORevent->chat->lettre = '^';
				}

			}
			break;
		case SDL_SCANCODE_RIGHTBRACKET:
			if(FORevent->chat->saisiechat == 1)
			{
				if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
				{
					FORevent->chat->lettre = '£';
				}
				else if (typeclavier == '1' && FORevent->systeme->altactif == true)
				{
					FORevent->chat->lettre = '¤';
				}
				else if (typeclavier == '1')
				{
					FORevent->chat->lettre = '$';
				}

			}
			break;
		case SDL_SCANCODE_APOSTROPHE:
			if(FORevent->chat->saisiechat == 1)
			{
				if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
				{
					FORevent->chat->lettre = '%';
				}
				else if (typeclavier == '1' && FORevent->systeme->altactif == true)
				{
					FORevent->chat->lettre = '\0';
				}
				else if (typeclavier == '1')
				{
					FORevent->chat->lettre = 'ù';
				}

			}
			break;
		case SDL_SCANCODE_COMMA:
			if(FORevent->chat->saisiechat == 1)
			{
				if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
				{
					FORevent->chat->lettre = '.';
				}
				else if (typeclavier == '1' && FORevent->systeme->altactif == true)
				{
					FORevent->chat->lettre = '\0';
				}
				else if (typeclavier == '1')
				{
					FORevent->chat->lettre = ';';
				}

			}
			break;
		case SDL_SCANCODE_PERIOD:
			if(FORevent->chat->saisiechat == 1)
			{
				if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
				{
					FORevent->chat->lettre = '/';
				}
				else if (typeclavier == '1' && FORevent->systeme->altactif == true)
				{
					FORevent->chat->lettre = '\0';
				}
				else if (typeclavier == '1')
				{
					FORevent->chat->lettre = ':';
				}

			}
			break;
		case SDL_SCANCODE_SLASH:
			if(FORevent->chat->saisiechat == 1)
			{
				if (typeclavier == '1' && FORevent->systeme->shiftactif == true)
				{
					FORevent->chat->lettre = '§';
				}
				else if (typeclavier == '1' && FORevent->systeme->altactif == true)
				{
					FORevent->chat->lettre = '\0';
				}
				else if (typeclavier == '1')
				{
					FORevent->chat->lettre = '!';
				}

			}
			break;
		case SDL_SCANCODE_KP_0:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '0';
			}
			break;
		case SDL_SCANCODE_KP_1:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '1';
			}
			break;
		case SDL_SCANCODE_KP_2:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '2';
			}
			break;
		case SDL_SCANCODE_KP_3:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '3';
			}
			break;
		case SDL_SCANCODE_KP_4:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '4';
			}
			break;
		case SDL_SCANCODE_KP_5:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '5';
			}
			break;
		case SDL_SCANCODE_KP_6:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '6';
			}
			break;
		case SDL_SCANCODE_KP_7:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '7';
			}
			break;
		case SDL_SCANCODE_KP_8:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '8';
			}
			break;
		case SDL_SCANCODE_KP_9:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '9';
			}
			break;
		case SDL_SCANCODE_SPACE:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = ' ';
			}
			break;
		case SDL_SCANCODE_BACKSPACE:
			if (FORevent->chat->saisiechat == 1)
			{
				FORevent->chat->lettre = '*';
			}
			break;
		case SDL_SCANCODE_LSHIFT:
			FORevent->systeme->shiftactif = true;
			break;
		case SDL_SCANCODE_RSHIFT:
			FORevent->systeme->shiftactif = true;
			break;
		case SDL_SCANCODE_LALT:
			FORevent->systeme->altactif = true;
			break;
		case SDL_SCANCODE_RALT:
			FORevent->systeme->altactif = true;
			break;

		default:
			break;
		}
	}
}

