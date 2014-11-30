#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "colision.h"
#include "ui.h"
#include "listechaine.h"
#include "main.h"
#include "image.h"
#include "evenement.h"
#include "tableau.h"
#include "systeme.h"
#include "login.h"
#include "jeux.h"
#include "clavier.h"

void boucleevent (bool *lancermessage, typeFORevent *FORevent)
{
	while(SDL_PollEvent(&FORevent->systeme->evenement) == 1)
	{
		switch(FORevent->systeme->evenement.type)
		{
		case SDL_KEYDOWN:
			intputtexte(FORevent);
			eventmapclavierdown(FORevent);
			break;
		case SDL_KEYUP:
			eventmapclavierup(lancermessage, FORevent);
			break;
		case SDL_MOUSEBUTTONUP:
			if(FORevent->systeme->evenement.button.button == SDL_BUTTON_LEFT)
			{
				eventmapsourisgaucheup(FORevent);
			}
			else if (FORevent->systeme->evenement.button.button == SDL_BUTTON_RIGHT)
			{
				eventmapsourisdroiteup(FORevent);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if( FORevent->systeme->evenement.button.button == SDL_BUTTON_LEFT )
			{
				eventmapsourisgauchedown(FORevent);
				sourisactionzone(FORevent);
			}
			else if (FORevent->systeme->evenement.button.button == SDL_BUTTON_RIGHT)
			{
				eventmapsourisdroitedown(FORevent);
			}
			break;
		default:
			break;
		}
	}
}

int boucleeventcombat (typecombat *BTLstr, DIVERSsysteme *systeme, DIRECTION *direction, DIVERSui *ui)
{
	while(SDL_PollEvent(&systeme->evenement) == 1)
	{
		switch(systeme->evenement.type)
		{
			case SDL_KEYUP:
				switch (systeme->evenement.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						if (BTLstr->echap == 1)
						{
							if (BTLstr->alive <= 0)
							{
								return BTL_WON;
							}
							else
							{
								return BTL_LEAVED;
							}
						}
						else {}
						break;
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT:
                        direction->droite = 0;
                        break;
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT:
						direction->gauche = 0;
						break;
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_UP:
						direction->haut = 0;
						break;
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_DOWN:
						direction->bas = 0;
						break;
					default:
						break;
				}
				if (direction->droite == 0 && direction->gauche == 0 && direction->haut == 0 && direction->bas == 0)
				{
					BTLstr->persobouge = 0;
				}
				break;
			case SDL_KEYDOWN:
				switch (systeme->evenement.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						BTLstr->echap = 1;
						break;
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT:
						direction->gauche = 1;
						BTLstr->persobouge = 1;
						break;
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT:
						direction->droite = 1;
						BTLstr->persobouge = 1;
						break;
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_UP:
						direction->haut = 1;
						BTLstr->persobouge = 1;
						break;
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_DOWN:
						direction->bas = 1;
						BTLstr->persobouge = 1;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if( systeme->evenement.button.button == SDL_BUTTON_LEFT )
				{
					BTLstr->letirdemander = false;
					if (ui->casestuff[ARME].IDobjet == -1)
                    {
                        BTLstr->poing_tendu = false;
                    }
				}
				break;
            case SDL_MOUSEBUTTONDOWN:
				if( systeme->evenement.button.button == SDL_BUTTON_LEFT )
				{
					BTLstr->letirdemander = true;
					if (ui->casestuff[ARME].IDobjet == -1)
                    {
                        BTLstr->poing_tendu = true;
                    }
				}
				break;
			default:
				break;
		}
	}
	return -1;
}

int boucleeventlogin (struct typelogin *loginstore, DIVERSsysteme *systeme)
{
	int x = loginstore->ppointeur.x;
	int y = loginstore->ppointeur.y;

	if (x >= systeme->screenw/11 && x <= (systeme->screenw/11)+(systeme->screenw/11) &&
		y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12) &&
		loginstore->etatoption != 2 && loginstore->optionactif == 0)//													option
	{
		loginstore->etatoption = 1;
		loginstore->etatjouer = 0;
		loginstore->etatcreer = 0;
		loginstore->etatquitter = 0;
		loginstore->etatarcade = 0;
	}
	else if (x >= (systeme->screenw/11)*3 && x <= ((systeme->screenw/11)*3)+(systeme->screenw/11) &&
			y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12) &&
			loginstore->etatjouer != 2 && loginstore->optionactif == 0)//												jouer
	{
		loginstore->etatoption = 0;
		loginstore->etatjouer = 1;
		loginstore->etatcreer = 0;
		loginstore->etatquitter = 0;
		loginstore->etatarcade = 0;
	}
	else if (x >= (systeme->screenw/11)*5 && x <= ((systeme->screenw/11)*5)+(systeme->screenw/11) &&
			y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12) &&
			loginstore->etatcreer != 2 && loginstore->optionactif == 0)//												creer
	{
		loginstore->etatoption = 0;
		loginstore->etatjouer = 0;
		loginstore->etatcreer = 1;
		loginstore->etatquitter = 0;
		loginstore->etatarcade = 0;
	}
	else if (x >= (systeme->screenw/11)*7 && x <= ((systeme->screenw/11)*7)+(systeme->screenw/11) &&
			y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12) &&
			loginstore->etatquitter != 2 && loginstore->optionactif == 0)//												quitter
	{
		loginstore->etatoption = 0;
		loginstore->etatjouer = 0;
		loginstore->etatcreer = 0;
		loginstore->etatquitter = 1;
		loginstore->etatarcade = 0;
	}
	else if (x >= (systeme->screenw/11)*9 && x <= ((systeme->screenw/11)*9)+(systeme->screenw/11) &&
			y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12) &&
			loginstore->etatarcade != 2 && loginstore->optionactif == 0)//												arcade
	{
		loginstore->etatoption = 0;
		loginstore->etatjouer = 0;
		loginstore->etatcreer = 0;
		loginstore->etatquitter = 0;
		loginstore->etatarcade = 1;
	}
	else if ( loginstore->etatoption != 2 && loginstore->etatjouer != 2 && loginstore->etatcreer != 2 &&
			loginstore->etatquitter != 2 && loginstore->optionactif == 0 && loginstore->etatarcade != 2)
	{
		loginstore->etatoption = 0;
		loginstore->etatjouer = 0;
		loginstore->etatcreer = 0;
		loginstore->etatquitter = 0;
		loginstore->etatarcade = 0;
	}
	else if ( loginstore->optionactif == 1 &&
			x >= (systeme->screenw/11)*4 && x <= ((systeme->screenw/11)*4)+(systeme->screenw/11) &&
			y >= (systeme->screenh/30)*14 && y <= ((systeme->screenh/30)*14)+(systeme->screenh/18) &&
			loginstore->etatazerty != 2)
	{
		loginstore->etatazerty = 1;
		if (loginstore->etatqwerty != 2) {loginstore->etatqwerty = 0;}
		if (loginstore->etatqwerty != 2) {loginstore->etatqwertz = 0;}
	}
	else if ( loginstore->optionactif == 1 &&
			x >= (systeme->screenw/11)*6 && x <= ((systeme->screenw/11)*6)+(systeme->screenw/11) &&
			y >= (systeme->screenh/30)*14 && y <= ((systeme->screenh/30)*14)+(systeme->screenh/18) &&
			loginstore->etatqwerty != 2)
	{
		loginstore->etatqwerty = 1;
		if (loginstore->etatazerty != 2) {loginstore->etatazerty = 0;}
		if (loginstore->etatqwertz != 2) {loginstore->etatqwertz = 0;}
	}
	else if ( loginstore->optionactif == 1 &&
			x >= (systeme->screenw/11)*8 && x <= ((systeme->screenw/11)*8)+(systeme->screenw/11) &&
			y >= (systeme->screenh/30)*14 && y <= ((systeme->screenh/30)*14)+(systeme->screenh/18) &&
			loginstore->etatqwertz != 2)
	{
		loginstore->etatqwertz = 1;
		if (loginstore->etatazerty != 2) {loginstore->etatazerty = 0;}
		if (loginstore->etatqwerty != 2) {loginstore->etatqwerty = 0;}
	}
	else if ( loginstore->optionactif == 1)
	{
		if (loginstore->etatqwertz != 2){loginstore->etatqwertz = 0;}
		if (loginstore->etatazerty != 2){loginstore->etatazerty = 0;}
		if (loginstore->etatqwerty != 2){loginstore->etatqwerty = 0;}
	}

	while(SDL_PollEvent(&loginstore->evenement) == 1)
	{
		switch(loginstore->evenement.type)
		{
			case SDL_KEYUP:
				switch (loginstore->evenement.key.keysym.scancode)
				{
					case SDL_SCANCODE_RETURN:
						if (loginstore->diall == 1)
						{
							loginstore->diall = 0;
							loginstore->optionactif = 0;
							return 1;
						}
						return 2;
						break;
					case SDL_SCANCODE_KP_ENTER:
						if (loginstore->diall == 1)
						{
							loginstore->diall = 0;
							loginstore->optionactif = 0;
							return 1;
						}
						return 2;
						break;
					case SDL_SCANCODE_BACKSPACE:
						if (loginstore->longpseudo > 0 && loginstore->saisiepseudo == 1)
						{
							loginstore->longpseudo = loginstore->longpseudo - 1;
						}
						else if (loginstore->longmdp > 0 && loginstore->saisiemdp == 1)
						{
							loginstore->longmdp = loginstore->longmdp - 1;
						}
						break;
					case SDL_SCANCODE_ESCAPE:
						if (loginstore->diall == 1)
						{
							loginstore->diall = 0;
							loginstore->optionactif = 0;
							return 1;
						}
						return 0;
						break;
					case SDL_SCANCODE_A: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'q';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'a';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'a';}}break;
					case SDL_SCANCODE_B: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'b';}	break;
					case SDL_SCANCODE_C: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'c';}	break;
					case SDL_SCANCODE_D: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'd';}	break;
					case SDL_SCANCODE_E: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'e';}	break;
					case SDL_SCANCODE_F: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'f';}	break;
					case SDL_SCANCODE_G: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'g';}	break;
					case SDL_SCANCODE_H: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'h';}	break;
					case SDL_SCANCODE_I: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'i';}	break;
					case SDL_SCANCODE_J: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'j';}	break;
					case SDL_SCANCODE_K: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'k';}	break;
					case SDL_SCANCODE_L: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'l';}	break;
					case SDL_SCANCODE_SEMICOLON: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'm';}}break;
					case SDL_SCANCODE_M: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1)
						{if (systeme->typeclavier == '2') {loginstore->lettre = 'm';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'm';}}break;
					case SDL_SCANCODE_N: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'n';}	break;
					case SDL_SCANCODE_O: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'o';}	break;
					case SDL_SCANCODE_P: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'p';}	break;
					case SDL_SCANCODE_Q: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'a';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'q';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'q';}}break;
					case SDL_SCANCODE_R: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'r';}	break;
					case SDL_SCANCODE_S: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 's';}	break;
					case SDL_SCANCODE_T: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 't';}	break;
					case SDL_SCANCODE_U: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'u';}	break;
					case SDL_SCANCODE_V: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'v';}	break;
					case SDL_SCANCODE_W: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'z';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'w';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'w';}}break;
					case SDL_SCANCODE_X: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = 'x';}	break;
					case SDL_SCANCODE_Y: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'y';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'y';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'z';}}break;
					case SDL_SCANCODE_Z: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'w';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'z';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'z';}}break;
					case SDL_SCANCODE_0: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '0';}	break;
					case SDL_SCANCODE_1: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '1';}	break;
					case SDL_SCANCODE_2: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '2';}	break;
					case SDL_SCANCODE_3: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '3';}	break;
					case SDL_SCANCODE_4: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '4';}	break;
					case SDL_SCANCODE_5: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '5';}	break;
					case SDL_SCANCODE_6: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '6';}	break;
					case SDL_SCANCODE_7: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '7';}	break;
					case SDL_SCANCODE_8: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '8';}	break;
					case SDL_SCANCODE_9: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '9';}	break;
					case SDL_SCANCODE_KP_0: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '0';}	break;
					case SDL_SCANCODE_KP_1: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '1';}	break;
					case SDL_SCANCODE_KP_2: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '2';}	break;
					case SDL_SCANCODE_KP_3: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '3';}	break;
					case SDL_SCANCODE_KP_4: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '4';}	break;
					case SDL_SCANCODE_KP_5: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '5';}	break;
					case SDL_SCANCODE_KP_6: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '6';}	break;
					case SDL_SCANCODE_KP_7: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '7';}	break;
					case SDL_SCANCODE_KP_8: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '8';}	break;
					case SDL_SCANCODE_KP_9: if (loginstore->saisiepseudo == 1 || loginstore->saisiemdp == 1){ loginstore->lettre = '9';}	break;
					case SDL_SCANCODE_TAB:
						if (loginstore->saisiepseudo == 1) {	loginstore->saisiepseudo = 0;	loginstore->saisiemdp = 1;}
						else if (loginstore->saisiemdp == 1) {	loginstore->saisiepseudo = 1;	loginstore->saisiemdp = 0;}
						else { 							loginstore->saisiepseudo = 1;	loginstore->saisiemdp = 0;}
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (x >= systeme->screenw/11 && x <= (systeme->screenw/11)+(systeme->screenw/11) &&
				y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//							option
				{
					loginstore->etatoption = 2;
				}
				else if (x >= (systeme->screenw/11)*3 && x <= ((systeme->screenw/11)*3)+(systeme->screenw/11) &&
				y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						jouer
				{
					loginstore->etatjouer = 2;
				}
				else if (x >= (systeme->screenw/11)*5 && x <= ((systeme->screenw/11)*5)+(systeme->screenw/11) &&
				y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						creer
				{
					loginstore->etatcreer = 2;
				}
				else if (x >= (systeme->screenw/11)*7 && x <= ((systeme->screenw/11)*7)+(systeme->screenw/11) &&
				y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						quitter
				{
					loginstore->etatquitter = 2;
				}
				else if (x >= (systeme->screenw/11)*9 && x <= ((systeme->screenw/11)*7)+(systeme->screenw/11) &&
				y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						arcade
				{
					loginstore->etatarcade = 2;
				}

				if ( loginstore->optionactif == 1 &&
				x >= (systeme->screenw/11)*4 && x <= ((systeme->screenw/11)*4)+(systeme->screenw/11) &&
				y >= (systeme->screenh/30)*14 && y <= ((systeme->screenh/30)*14)+(systeme->screenh/18))
				{
					//azerty
					loginstore->etatazerty = 2;
					loginstore->etatqwerty = 0;
					loginstore->etatqwertz = 0;
					systeme->typeclavier = '1';
				}
				else if ( loginstore->optionactif == 1 &&
				x >= (systeme->screenw/11)*6 && x <= ((systeme->screenw/11)*6)+(systeme->screenw/11) &&
				y >= (systeme->screenh/30)*14 && y <= ((systeme->screenh/30)*14)+(systeme->screenh/18))
				{
					//qwerty
					loginstore->etatqwertz = 0;
					loginstore->etatazerty = 0;
					loginstore->etatqwerty = 2;
					systeme->typeclavier = '3';
				}
				else if ( loginstore->optionactif == 1 &&
				x >= (systeme->screenw/11)*8 && x <= ((systeme->screenw/11)*8)+(systeme->screenw/11) &&
				y >= (systeme->screenh/30)*14 && y <= ((systeme->screenh/30)*14)+(systeme->screenh/18))
				{
					//qwertz
					loginstore->etatqwerty = 0;
					loginstore->etatazerty = 0;
					loginstore->etatqwertz = 2;
					systeme->typeclavier = '2';
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if( loginstore->evenement.button.button == SDL_BUTTON_LEFT )
					{
					if (loginstore->etatoption == 2){loginstore->etatoption = 0;}
					else if (loginstore->etatjouer == 2){loginstore->etatjouer = 0;}
					else if (loginstore->etatcreer == 2){loginstore->etatcreer = 0;}
					else if (loginstore->etatquitter == 2){loginstore->etatquitter = 0;}

					if (loginstore->diall == 1 && loginstore->optionactif == 0)
							{loginstore->diall = 0;
								return 1;
							}

					if (x >= (systeme->screenw-loginstore->pcase.w)/2 && x <= ((systeme->screenw-loginstore->pcase.w)/2)+(systeme->screenw/4) &&
						y >= systeme->screenh/2 && y <= (systeme->screenh/2)+(systeme->screenh/20))
					{
							loginstore->saisiepseudo = 1;
						loginstore->saisiemdp = 0;
					}
					else if (x >= (systeme->screenw-loginstore->pcase.w)/2 && x <= (((systeme->screenw-loginstore->pcase.w)/2)+(systeme->screenw/4)) &&
							y >= (systeme->screenh/2)+(systeme->screenh/8) && y <= ((systeme->screenh/2)+(systeme->screenh/8)+(systeme->screenh/20)))
					{
						loginstore->saisiemdp = 1;
						loginstore->saisiepseudo = 0;
					}
					else if (x >= (systeme->screenw/8)*6 && x <= ((systeme->screenw/8)*6)+(systeme->screenw/6) &&
							y >= (systeme->screenh/8)*5 && y <= ((systeme->screenh/8)*5)+(systeme->screenh/12))
					{
						if (loginstore->mdpcacher == 1)		{loginstore->mdpcacher = 0;}
						else	{loginstore->mdpcacher = 1;}
					}
					else
					{loginstore->saisiepseudo = 0;
						loginstore->saisiemdp = 0;
					}


					if (x >= systeme->screenw/11 && x <= (systeme->screenw/11)+(systeme->screenw/11) &&
					y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						option
					{return 4;}
					else if (x >= (systeme->screenw/11)*3 && x <= ((systeme->screenw/11)*3)+(systeme->screenw/11) &&
					y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						jouer
					{return 2;}
					else if (x >= (systeme->screenw/11)*5 && x <= ((systeme->screenw/11)*5)+(systeme->screenw/11) &&
					y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						creer
					{return 3;}
					else if (x >= (systeme->screenw/11)*7 && x <= ((systeme->screenw/11)*7)+(systeme->screenw/11) &&
					y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						quitter
					{return 0;}
					else if (x >= (systeme->screenw/11)*9 && x <= ((systeme->screenw/11)*9)+(systeme->screenw/11) &&
					y >= (systeme->screenh/6)*5 && y <= ((systeme->screenh/6)*5)+(systeme->screenh/12))//						arcade
					{return 0;}
					}
				break;
			default:
				break;
		}
	}
	return 1;
}

void eventmapclavierdown(typeFORevent *FORevent)
{
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
	default:
		break;
	}
}

void eventmapclavierup(bool *lancermessage, typeFORevent *FORevent)
{
	switch (FORevent->systeme->evenement.key.keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		if (FORevent->ui->dialogueactif == 1 || FORevent->ui->dialogueactif == 2)
		{
			FORevent->ui->dialogueactif = 0;
		}
		else if (FORevent->craft->actif == true)
		{
			FORevent->craft->actif = false;
		}
		break;

	case SDL_SCANCODE_RETURN:
	case SDL_SCANCODE_KP_ENTER:
		if (FORevent->ui->dialogueactif == 1 || FORevent->ui->dialogueactif == 2)
		{
			FORevent->ui->dialogueactif = 0;
		}
		else if (FORevent->chat->saisiechat == 1)
		{
			*lancermessage = true;
		}
		break;

	case SDL_SCANCODE_DOWN:
	case SDL_SCANCODE_S:
		FORevent->deplacement->direction.bas = 0;
		break;

	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_W:
		FORevent->deplacement->direction.haut = 0;
		break;

	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_A:
		FORevent->deplacement->direction.gauche = 0;
		break;

	case SDL_SCANCODE_RIGHT:
	case SDL_SCANCODE_D:
		FORevent->deplacement->direction.droite = 0;
		break;

	case SDL_SCANCODE_LSHIFT:
	case SDL_SCANCODE_RSHIFT:
		FORevent->systeme->shiftactif = false;
		break;

	case SDL_SCANCODE_LALT:
	case SDL_SCANCODE_RALT:
		FORevent->systeme->altactif = false;
		break;

	default:
		break;
	}

	if (FORevent->deplacement->direction.haut == 0 &&
		FORevent->deplacement->direction.gauche == 0 &&
		FORevent->deplacement->direction.droite == 0 &&
		FORevent->deplacement->direction.bas == 0)
	{
		FORevent->deplacement->persobouge = 0;
	}
}

void eventmapsourisgaucheup(typeFORevent *FORevent)
{
	int index, index2;
	int bodypart = FORevent->objet->objet[FORevent->objet->objetenmain.IDobjet].bodypart;
	bool outside = true;
	FORevent->bouton->crafter.etat = 0;


	//si dans le chat
	if (FORevent->ui->coinbas == 1)
	{
		if (FORevent->systeme->pp.y > FORevent->systeme->screenh-FORevent->chat->pchatactif.h)
		{
			FORevent->chat->saisiechat = 1;
		}
		else
		{
			FORevent->chat->saisiechat = 0;
		}
	}
	//si dans l'inventaire
	else if (FORevent->ui->coinbas == 2)
	{
		checkinventaire(FORevent->objet, FORevent->inventaire);
		//case sous pointeur
		FORevent->inventaire->caseupgauche = calculclicinventaire(&FORevent->systeme->pp.y, &FORevent->systeme->pp.x, FORevent->systeme);
		//si dans une case de l'inventaire
		if (FORevent->inventaire->caseupgauche  >=0 && FORevent->inventaire->caseupgauche< TAILLESAC)
		{
			insertionnumero(FORevent->inventaire->casedowngauche, FORevent->objet->sac1, FORevent->inventaire->caseupgauche, &FORevent->objet->objetenmain, FORevent->objet->objet);
			outside = false;
		}
		FORevent->inventaire->casedowngauche = -1;
	}
	//si menu est ouvert
	if (FORevent->ui->coinhaut == 1)
	{
		for (index = 0 ; index < 7 ; index++)
		{
			//si dans une case de stuff
			if (FORevent->systeme->pp.x >= FORevent->ui->pcasestuff[index].x
				&& FORevent->systeme->pp.x <= FORevent->ui->pcasestuff[index].x + FORevent->ui->pcasestuff[index].w
				&& FORevent->systeme->pp.y >= FORevent->ui->pcasestuff[index].y
				&& FORevent->systeme->pp.y <= FORevent->ui->pcasestuff[index].y + FORevent->ui->pcasestuff[index].h)
			{
				if(FORevent->ui->casestuff[bodypart].IDobjet != -1)
				{
					insertionsac(FORevent->objet, FORevent->ui->casestuff[bodypart].IDobjet);
				}
				equipestuff(FORevent->objet, FORevent->ui, index, FORevent->objet->objetenmain.IDobjet);
				videemplacement(&FORevent->objet->objetenmain);
				outside = false;
				break;
			}
		}
		//test bouton quitter
		if (FORevent->systeme->pp.x >= FORevent->systeme->screenw*0.7 && FORevent->systeme->pp.x <= (FORevent->systeme->screenw*0.7)+(FORevent->systeme->screenw*0.04) &&
			FORevent->systeme->pp.y >= FORevent->systeme->screenh*0.3 && FORevent->systeme->pp.y <= (FORevent->systeme->screenh*0.3)+(FORevent->systeme->screenw*0.04) &&
			FORevent->bouton->BoutonQuitter.etat == 2)
		{
			FORevent->systeme->continuer = 0;
		}
		else
		{
			FORevent->bouton->BoutonQuitter.etat = 0;
		}
	}
	//si inteface de craft ouvert
	else if (FORevent->craft->actif == true)
	{
		checkinventaire(FORevent->objet, FORevent->inventaire);


		//bouton du bas

		if (FORevent->systeme->pp.y >= FORevent->systeme->screenh*0.467 &&
			FORevent->systeme->pp.y <= (FORevent->systeme->screenh*0.467)+(FORevent->systeme->screenh*0.03))
		{
			for(index = 0 ; index < 7 ; index++)
			{
				if (FORevent->systeme->pp.x >= index * FORevent->bouton->bcraft[0].position.w&&
					FORevent->systeme->pp.x <= (index+1) * FORevent->bouton->bcraft[0].position.w&&
					FORevent->craft->bcraftpointer == index)
				{
					FORevent->craft->bcraftactif = index;
					FORevent->craft->planactif = 0;
				}
			}
		}


		//si souris en haut a gauche
		else if (FORevent->systeme->pp.y <= FORevent->systeme->screenh*0.5 && FORevent->systeme->pp.x <= FORevent->systeme->screenw*0.3)
		{
		    //initialisation
		    FORevent->craft->planactif = -1;

            //parcour des plans
		    for(index = 0 ; index < 10 ; index++)
            {
                if (FORevent->systeme->pp.x >= FORevent->systeme->screenw*0.007 &&
                    FORevent->systeme->pp.x <= FORevent->systeme->screenw*0.3 &&
                    FORevent->systeme->pp.y >= (FORevent->systeme->screenh*0.04)*index &&
                    FORevent->systeme->pp.y <= (FORevent->systeme->screenh*0.04)*(index+1))
                {
                    //si un plan est present a cet emplacement
                    if(FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][index].resultatID != -1)
                    {
                        //j'indique le plan actif
                        FORevent->craft->planactif = index;
                    }
                }
            }
		}
		else
		{
			if (FORevent->systeme->pp.x >= FORevent->systeme->screenw*0.622 && FORevent->systeme->pp.x <= FORevent->systeme->screenw*0.732 &&
				FORevent->systeme->pp.y >= FORevent->systeme->screenh*0.39 && FORevent->systeme->pp.y <= FORevent->systeme->screenh*0.456)
			{
				bool checkcompo = true;
				for (index = 0 ; index < FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][0].compodifferente ; index++)
				{
					if (FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][0].compodispo[index] == false)
					{
						checkcompo = false;
					}
				}
				if (checkcompo == true)
				{
					for (index = 0 ; index < FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][0].compodifferente ; index++)
					{
						for (index2 = 0 ; index2 < FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][0].compoNB[index] ; index2++)
						{
							effacerID(FORevent->objet,FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][0].compoID[index]);
						}
					}
					insertionsac(FORevent->objet, FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][0].resultatID);
					checkinventaire(FORevent->objet, FORevent->inventaire);
				}
				FORevent->bouton->crafter.etat = 1;
			}
		}
	}
	if(outside == true)
	{
		videemplacement(&FORevent->objet->objetenmain);
	}
	checkandrefreshstuff(FORevent->perso, FORevent->objet, FORevent->systeme, FORevent->ui);
}

void eventmapsourisgauchedown(typeFORevent *FORevent)
{
	int index;

	if (FORevent->ui->coinbas == 2)
	{
		if (FORevent->systeme->pp.y > (FORevent->systeme->screenh*0.526))
		{
			FORevent->inventaire->casedowngauche = calculclicinventaire(&FORevent->systeme->pp.y, &FORevent->systeme->pp.x, FORevent->systeme);
			if (FORevent->inventaire->casedowngauche < TAILLESAC)
			{
				prendreenmain(FORevent->objet->sac1[FORevent->inventaire->casedowngauche], &FORevent->objet->objetenmain);
				videemplacement(&FORevent->objet->sac1[FORevent->inventaire->casedowngauche]);
			}
		}
	}
	if (FORevent->ui->coinhaut == 1)
	{
		for (index = 0 ; index < 7 ; index++)
		{
			if (FORevent->systeme->pp.x >= FORevent->ui->pcasestuff[index].x
				&& FORevent->systeme->pp.x <= FORevent->ui->pcasestuff[index].x + FORevent->ui->pcasestuff[index].w
				&& FORevent->systeme->pp.y >= FORevent->ui->pcasestuff[index].y
				&& FORevent->systeme->pp.y <= FORevent->ui->pcasestuff[index].y + FORevent->ui->pcasestuff[index].h)
			{
				prendreenmain(FORevent->ui->casestuff[index], &FORevent->objet->objetenmain);
				videemplacement(&FORevent->ui->casestuff[index]);
				checkandrefreshstuff(FORevent->perso, FORevent->objet, FORevent->systeme, FORevent->ui);
				break;
			}
		}
		if (FORevent->systeme->pp.x >= FORevent->bouton->BoutonQuitter.position.x &&
			FORevent->systeme->pp.x <= (FORevent->bouton->BoutonQuitter.position.x)+(FORevent->bouton->BoutonQuitter.position.w) &&
			FORevent->systeme->pp.y >= FORevent->bouton->BoutonQuitter.position.y &&
			FORevent->systeme->pp.y <= (FORevent->bouton->BoutonQuitter.position.y)+(FORevent->bouton->BoutonQuitter.position.h) &&
			FORevent->bouton->BoutonQuitter.etat == 1 )
		{
			FORevent->bouton->BoutonQuitter.etat = 2;
		}
	}
	if (FORevent->ui->coinhaut == 2)
	{
		if (FORevent->systeme->pp.x >= FORevent->systeme->screenw*0.622 && FORevent->systeme->pp.x <= (FORevent->systeme->screenw*0.622)+(FORevent->systeme->screenw*0.11)
			&& FORevent->systeme->pp.y >= FORevent->systeme->screenh*0.39 && FORevent->systeme->pp.y <= (FORevent->systeme->screenh*0.39)+(FORevent->systeme->screenh*0.0651))
		{
			FORevent->bouton->crafter.etat = 2;
		}
	}
}

void eventmapsourisdroiteup(typeFORevent *FORevent)
{
	int index;

	if (FORevent->ui->coinhaut == 1)
	{
		for (index = 0 ; index < 7 ; index++)
		{
			if (FORevent->systeme->pp.x >= FORevent->ui->pcasestuff[index].x
				&& FORevent->systeme->pp.x <= FORevent->ui->pcasestuff[index].x + FORevent->ui->pcasestuff[index].w
				&& FORevent->systeme->pp.y >= FORevent->ui->pcasestuff[index].y
				&& FORevent->systeme->pp.y <= FORevent->ui->pcasestuff[index].y + FORevent->ui->pcasestuff[index].h)
			{
				insertionsac(FORevent->objet, FORevent->ui->casestuff[index].IDobjet);
				videemplacement(&FORevent->ui->casestuff[index]);
				checkandrefreshstuff(FORevent->perso, FORevent->objet, FORevent->systeme, FORevent->ui);
				break;
			}
		}
	}
	if (FORevent->ui->coinbas == 2)
	{
		FORevent->inventaire->caseupdroit = calculclicinventaire(&FORevent->systeme->pp.y, &FORevent->systeme->pp.x, FORevent->systeme);

		if (FORevent->inventaire->caseupdroit == FORevent->inventaire->casedowndroit && FORevent->inventaire->caseupdroit < TAILLESAC)
		{
			int id = FORevent->objet->sac1[FORevent->inventaire->caseupdroit].IDobjet;
			int bodypart = FORevent->objet->objet[id].bodypart;
			//si objet type equipement
			if (FORevent->objet->objet[id].type == 1)
			{
				if(FORevent->ui->casestuff[bodypart].IDobjet != -1)
				{
					insertionsac(FORevent->objet, FORevent->ui->casestuff[bodypart].IDobjet);
				}
				equipestuff(FORevent->objet, FORevent->ui, bodypart, id);
				videemplacement(&FORevent->objet->sac1[FORevent->inventaire->caseupdroit]);
				checkandrefreshstuff(FORevent->perso, FORevent->objet, FORevent->systeme, FORevent->ui);
			}
		}
	}
}

void eventmapsourisdroitedown(typeFORevent *FORevent)
{
	if (FORevent->ui->coinbas == 2)
	{
		if (FORevent->systeme->pp.y > (FORevent->systeme->screenh*0.526))
		{
			FORevent->inventaire->casedowndroit = calculclicinventaire(&FORevent->systeme->pp.y, &FORevent->systeme->pp.x, FORevent->systeme);
		}
	}
}

void sourisactionzone(typeFORevent *FORevent)
{
	//si on ne clique pas sur une UI
	if ((FORevent->ui->coinbas == 0 && FORevent->systeme->pp.y > FORevent->systeme->screenh/2) ||
			(FORevent->ui->coinhaut == 0 && FORevent->systeme->pp.y < FORevent->systeme->screenh/2) ||
			(FORevent->ui->coinbas == 0 && FORevent->ui->coinhaut == 0))
	{
		//position toumaï
		if (colisionbox(&FORevent->systeme->pp, &FORevent->pnj->toumai, 1) &&
				checkdistance(&FORevent->perso->pperso, &FORevent->pnj->toumai, 300) == -1)
		{
			FORevent->ui->lancedialogue = 2;
			FORevent->pnj->toumaiParle = true;
		}
		//position etabli
		else if (colisionbox(&FORevent->systeme->pp, &FORevent->craft->petabli, 1) &&
				checkdistance(&FORevent->perso->pperso, &FORevent->craft->petabli, 250) == -1)
		{
			FORevent->craft->actif = true;
		}
	}
}
