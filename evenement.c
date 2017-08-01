#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "struct.h"
#include "perso.h"
#include "clavier.h"
#include "evenement.h"
#include "colision.h"
#include "systeme.h"
#include "ui.h"
#include "listechaine.h"

extern int screenh, screenw;

void boucleevent (bool *lancermessage,struct typeFORevent *FORevent, struct TIR *TIR)
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

		    TIR->letirdemander = true;

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
int boucleeventlogin (struct typelogin *loginstore,struct DIVERSsysteme *systeme)
{
	if (colisionbox(&loginstore->pointeur.pos, &loginstore->option.pos, true) &&
		loginstore->option.etat != B_CLIQUER && loginstore->optionactif == 0)								/*option*/
	{
		loginstore->option.etat = B_SURVOLER;
		loginstore->jouer.etat = B_NORMAL;
		loginstore->creer.etat = B_NORMAL;
		loginstore->quitter.etat = B_NORMAL;
		loginstore->arcade.etat = B_NORMAL;
	}
	else if (colisionbox(&loginstore->pointeur.pos, &loginstore->jouer.pos, true) &&
			loginstore->jouer.etat != B_CLIQUER && loginstore->optionactif == 0)							/*play*/
	{
		loginstore->option.etat = B_NORMAL;
		loginstore->jouer.etat = B_SURVOLER;
		loginstore->creer.etat = B_NORMAL;
		loginstore->quitter.etat = B_NORMAL;
		loginstore->arcade.etat = B_NORMAL;
	}
	else if (colisionbox(&loginstore->pointeur.pos, &loginstore->creer.pos, true) &&
			loginstore->creer.etat != B_CLIQUER && loginstore->optionactif == 0)							/*create*/
	{
		loginstore->option.etat = B_NORMAL;
		loginstore->jouer.etat = B_NORMAL;
		loginstore->creer.etat = B_SURVOLER;
		loginstore->quitter.etat = B_NORMAL;
		loginstore->arcade.etat = B_NORMAL;
	}
	else if (colisionbox(&loginstore->pointeur.pos, &loginstore->quitter.pos, true) &&
			loginstore->quitter.etat != B_CLIQUER && loginstore->optionactif == 0)                          /*quit*/
	{
		loginstore->option.etat = B_NORMAL;
		loginstore->jouer.etat = B_NORMAL;
		loginstore->creer.etat = B_NORMAL;
		loginstore->quitter.etat = B_SURVOLER;
		loginstore->arcade.etat = B_NORMAL;
	}
	else if (colisionbox(&loginstore->pointeur.pos, &loginstore->arcade.pos, true) &&
			loginstore->arcade.etat != B_CLIQUER && loginstore->optionactif == 0)							/*arcade*/
	{
		loginstore->option.etat = B_NORMAL;
		loginstore->jouer.etat = B_NORMAL;
		loginstore->creer.etat = B_NORMAL;
		loginstore->quitter.etat = B_NORMAL;
		loginstore->arcade.etat = B_SURVOLER;
	}
	else if ( loginstore->option.etat != B_CLIQUER && loginstore->jouer.etat != B_CLIQUER && loginstore->creer.etat != B_CLIQUER &&
			loginstore->quitter.etat != B_CLIQUER && loginstore->optionactif == 0 && loginstore->arcade.etat != B_CLIQUER)
	{
		loginstore->option.etat = B_NORMAL;
		loginstore->jouer.etat = B_NORMAL;
		loginstore->creer.etat = B_NORMAL;
		loginstore->quitter.etat = B_NORMAL;
		loginstore->arcade.etat = B_NORMAL;
	}
	else if ( loginstore->optionactif == 1 && colisionbox(&loginstore->pointeur.pos, &loginstore->azerty.pos, true) &&
			loginstore->azerty.etat != B_CLIQUER)
	{
            loginstore->azerty.etat = B_SURVOLER;
		if (loginstore->qwerty.etat != B_CLIQUER) {loginstore->qwerty.etat = B_NORMAL;}
		if (loginstore->qwerty.etat != B_CLIQUER) {loginstore->qwertz.etat = B_NORMAL;}
	}
	else if ( loginstore->optionactif == 1 && colisionbox(&loginstore->pointeur.pos, &loginstore->qwerty.pos, true) &&
			loginstore->qwerty.etat != B_CLIQUER)
	{
            loginstore->qwerty.etat = B_SURVOLER;
		if (loginstore->azerty.etat != B_CLIQUER) {loginstore->azerty.etat = B_NORMAL;}
		if (loginstore->qwertz.etat != B_CLIQUER) {loginstore->qwertz.etat = B_NORMAL;}
	}
	else if ( loginstore->optionactif == 1 && colisionbox(&loginstore->pointeur.pos, &loginstore->qwertz.pos, true) &&
			loginstore->qwertz.etat != B_CLIQUER)
	{
            loginstore->qwertz.etat = B_SURVOLER;
		if (loginstore->azerty.etat != B_CLIQUER) {loginstore->azerty.etat = B_NORMAL;}
		if (loginstore->qwerty.etat != B_CLIQUER) {loginstore->qwerty.etat = B_NORMAL;}
	}
	else if ( loginstore->optionactif == 1)
	{
		if (loginstore->qwertz.etat != B_CLIQUER){loginstore->qwertz.etat = B_NORMAL;}
		if (loginstore->azerty.etat != B_CLIQUER){loginstore->azerty.etat = B_NORMAL;}
		if (loginstore->qwerty.etat != B_CLIQUER){loginstore->qwerty.etat = B_NORMAL;}
	}

	/*blocking impossible button*/
	if(loginstore->longpseudo <= 0 || loginstore->longmdp <= 0)
	{
		loginstore->jouer.etat = B_IMPOSSIBLE;
		loginstore->creer.etat = B_IMPOSSIBLE;
	}

	while(SDL_PollEvent(&loginstore->evenement) == 1)
	{
		switch(loginstore->evenement.type)
		{
			case SDL_KEYUP:
				switch (loginstore->evenement.key.keysym.scancode)
				{
					case SDL_SCANCODE_RETURN:
						if (loginstore->menu == true)
						{
							loginstore->menu = false;
							loginstore->optionactif = 0;
							return 1;
						}
						return 2;
						break;
					case SDL_SCANCODE_KP_ENTER:
						if (loginstore->menu == true)
						{
							loginstore->menu = false;
							loginstore->optionactif = 0;
							return 1;
						}
						return 2;
						break;
					case SDL_SCANCODE_BACKSPACE:
						if (loginstore->longpseudo > false && loginstore->saisiepseudo == true)
						{
							loginstore->longpseudo = loginstore->longpseudo - 1;
						}
						else if (loginstore->longmdp > 0 && loginstore->saisiemdp == true)
						{
							loginstore->longmdp = loginstore->longmdp - 1;
						}
						break;
					case SDL_SCANCODE_ESCAPE:
						if (loginstore->menu == true)
						{
							loginstore->menu = false;
							loginstore->optionactif = 0;
							return 1;
						}
						return 0;
						break;
					case SDL_SCANCODE_A: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'q';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'a';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'a';}}break;
					case SDL_SCANCODE_B: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'b';}	break;
					case SDL_SCANCODE_C: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'c';}	break;
					case SDL_SCANCODE_D: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'd';}	break;
					case SDL_SCANCODE_E: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'e';}	break;
					case SDL_SCANCODE_F: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'f';}	break;
					case SDL_SCANCODE_G: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'g';}	break;
					case SDL_SCANCODE_H: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'h';}	break;
					case SDL_SCANCODE_I: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'i';}	break;
					case SDL_SCANCODE_J: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'j';}	break;
					case SDL_SCANCODE_K: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'k';}	break;
					case SDL_SCANCODE_L: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'l';}	break;
					case SDL_SCANCODE_SEMICOLON: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'm';}}break;
					case SDL_SCANCODE_M: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true)
						{if (systeme->typeclavier == '2') {loginstore->lettre = 'm';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'm';}}break;
					case SDL_SCANCODE_N: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'n';}	break;
					case SDL_SCANCODE_O: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'o';}	break;
					case SDL_SCANCODE_P: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'p';}	break;
					case SDL_SCANCODE_Q: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'a';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'q';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'q';}}break;
					case SDL_SCANCODE_R: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'r';}	break;
					case SDL_SCANCODE_S: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 's';}	break;
					case SDL_SCANCODE_T: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 't';}	break;
					case SDL_SCANCODE_U: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'u';}	break;
					case SDL_SCANCODE_V: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'v';}	break;
					case SDL_SCANCODE_W: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'z';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'w';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'w';}}break;
					case SDL_SCANCODE_X: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = 'x';}	break;
					case SDL_SCANCODE_Y: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'y';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'y';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'z';}}break;
					case SDL_SCANCODE_Z: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true)
						{if (systeme->typeclavier == '1') {loginstore->lettre = 'w';}
						else if (systeme->typeclavier == '2') {loginstore->lettre = 'z';}
						else if (systeme->typeclavier == '3') {loginstore->lettre = 'z';}}break;
					case SDL_SCANCODE_0:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '0';}	break;
					case SDL_SCANCODE_1:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '1';}	break;
					case SDL_SCANCODE_2:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '2';}	break;
					case SDL_SCANCODE_3:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '3';}	break;
					case SDL_SCANCODE_4:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '4';}	break;
					case SDL_SCANCODE_5:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '5';}	break;
					case SDL_SCANCODE_6:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '6';}	break;
					case SDL_SCANCODE_7:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '7';}	break;
					case SDL_SCANCODE_8:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '8';}	break;
					case SDL_SCANCODE_9:    if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '9';}	break;
					case SDL_SCANCODE_KP_0: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '0';}	break;
					case SDL_SCANCODE_KP_1: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '1';}	break;
					case SDL_SCANCODE_KP_2: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '2';}	break;
					case SDL_SCANCODE_KP_3: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '3';}	break;
					case SDL_SCANCODE_KP_4: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '4';}	break;
					case SDL_SCANCODE_KP_5: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '5';}	break;
					case SDL_SCANCODE_KP_6: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '6';}	break;
					case SDL_SCANCODE_KP_7: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '7';}	break;
					case SDL_SCANCODE_KP_8: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '8';}	break;
					case SDL_SCANCODE_KP_9: if (loginstore->saisiepseudo == true || loginstore->saisiemdp == true){ loginstore->lettre = '9';}	break;
					case SDL_SCANCODE_TAB:
						if (loginstore->saisiepseudo == true) {	loginstore->saisiepseudo = false;	loginstore->saisiemdp = true;}
						else if (loginstore->saisiemdp == true) {	loginstore->saisiepseudo = true;	loginstore->saisiemdp = false;}
						else { 							loginstore->saisiepseudo = true;	loginstore->saisiemdp = false;}
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (colisionbox(&loginstore->pointeur.pos, &loginstore->option.pos, true))					/*option*/
				{
					loginstore->option.etat = B_CLIQUER;
				}
				else if (colisionbox(&loginstore->pointeur.pos, &loginstore->jouer.pos, true))						/*play*/
				{
					/*blocking impossible button*/
					if(loginstore->longpseudo > 0 && loginstore->longmdp > 0)
					{
						loginstore->jouer.etat = B_CLIQUER;
					}
				}
				else if (colisionbox(&loginstore->pointeur.pos, &loginstore->creer.pos, true))						/*create*/
				{
					/*blocking impossible button*/
					if(loginstore->longpseudo > 0 && loginstore->longmdp > 0)
					{
						loginstore->creer.etat = B_CLIQUER;
					}
				}
				else if (colisionbox(&loginstore->pointeur.pos, &loginstore->quitter.pos, true))						/*quit*/
				{
					loginstore->quitter.etat = B_CLIQUER;
				}
				else if (colisionbox(&loginstore->pointeur.pos, &loginstore->arcade.pos, true))						/*arcade*/
				{
					loginstore->arcade.etat = B_CLIQUER;
				}

				if ( loginstore->optionactif == 1 && colisionbox(&loginstore->pointeur.pos, &loginstore->azerty.pos, true))
				{
					/*azerty*/
					loginstore->azerty.etat = B_CLIQUER;
					loginstore->qwerty.etat = B_NORMAL;
					loginstore->qwertz.etat = B_NORMAL;
					systeme->typeclavier = '1';
				}
				else if ( loginstore->optionactif == 1 && colisionbox(&loginstore->pointeur.pos, &loginstore->qwerty.pos, true))
				{
					/*qwerty*/
					loginstore->qwertz.etat = B_NORMAL;
					loginstore->azerty.etat = B_NORMAL;
					loginstore->qwerty.etat = B_CLIQUER;
					systeme->typeclavier = '3';
				}
				else if ( loginstore->optionactif == 1 && colisionbox(&loginstore->pointeur.pos, &loginstore->qwertz.pos, true))
				{
					/*qwertz*/
					loginstore->qwerty.etat = B_NORMAL;
					loginstore->azerty.etat = B_NORMAL;
					loginstore->qwertz.etat = B_CLIQUER;
					systeme->typeclavier = '2';
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if( loginstore->evenement.button.button == SDL_BUTTON_LEFT )
					{
					if      (loginstore->option.etat == B_CLIQUER)  {loginstore->option.etat = B_NORMAL;}
					else if (loginstore->jouer.etat == B_CLIQUER)   {loginstore->jouer.etat = B_NORMAL;}
					else if (loginstore->creer.etat == B_CLIQUER)   {loginstore->creer.etat = B_NORMAL;}
					else if (loginstore->quitter.etat == B_CLIQUER) {loginstore->quitter.etat = B_NORMAL;}

					if (loginstore->menu == true && loginstore->optionactif == 0)
							{
							    loginstore->menu = false;
								return 1;
							}

					if  (colisionbox(&loginstore->pointeur.pos, &loginstore->pcase, true))
					{
							loginstore->saisiepseudo = true;
						loginstore->saisiemdp = false;
					}
					else if  (colisionbox(&loginstore->pointeur.pos, &loginstore->pcase2, true))
					{
						loginstore->saisiemdp = true;
						loginstore->saisiepseudo = false;
					}
					else if (colisionbox(&loginstore->pointeur.pos, &loginstore->coche.pos, true))
					{
						if (loginstore->mdpcacher == 1)		{loginstore->mdpcacher = 0;}
						else	{loginstore->mdpcacher = 1;}
					}
					else
					{loginstore->saisiepseudo = false;
						loginstore->saisiemdp = false;
					}

					/*CAUTION DON'T USE "1"*/
					if (colisionbox(&loginstore->pointeur.pos, &loginstore->option.pos, true)) 			/*option*/
					{return 4;}
					else if (colisionbox(&loginstore->pointeur.pos, &loginstore->jouer.pos, true) &&
                        loginstore->longpseudo > 0 && loginstore->longmdp > 0)				            /*play*/
					{return 2;}
					else if (colisionbox(&loginstore->pointeur.pos, &loginstore->creer.pos, true) &&
                        loginstore->longpseudo > 0 && loginstore->longmdp > 0)					        /*create*/
					{return 3;}
					else if (colisionbox(&loginstore->pointeur.pos, &loginstore->quitter.pos, true))		/*quit*/
					{return 0;}
					else if (colisionbox(&loginstore->pointeur.pos, &loginstore->arcade.pos, true))		/*arcade*/
					{return 5;}
					}
				break;
			default:
				break;
		}
	}
	return 1;
}

void eventmapclavierdown(struct typeFORevent *FORevent)
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

void eventmapclavierup(bool *lancermessage,struct typeFORevent *FORevent)
{
	switch (FORevent->systeme->evenement.key.keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		if (FORevent->ui->dialogueactif == 1 || FORevent->ui->dialogueactif == 2)
		{
			FORevent->ui->dialogueactif = 0;
		}
		else if (FORevent->ui->craft_open == true)
		{
			FORevent->ui->craft_open = false;
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

void eventmapsourisgaucheup(struct typeFORevent *FORevent)
{
	int index, index2;
	FORevent->bouton->crafter.etat = 0;



	/*if inside the inventory*/
	if (FORevent->ui->inventaire_open)
	{
		checkinventaire(FORevent->objet, FORevent->inventaire);
		/*box under cursor*/
		FORevent->inventaire->caseupgauche = calculclicinventaire(FORevent->systeme->pointeur.pos, FORevent->systeme);
		/*if inside a box of the inventory*/
		if (FORevent->inventaire->caseupgauche  >=0 && FORevent->inventaire->caseupgauche< TAILLESAC)
		{
			insertionnumero(FORevent->inventaire->casedowngauche, FORevent->objet->sac1, FORevent->inventaire->caseupgauche, &FORevent->objet->objetenmain, FORevent->objet->objet);
		}
		FORevent->inventaire->casedowngauche = -1;
	}
	/*if menu open*/
	if (FORevent->ui->menu_open)
	{
		for (index = 0 ; index < 7 ; index++)
		{
			/*if inside a box of the stuff*/
			/*and is an equipment*/
			/*and is in the right box*/
			if (colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->casestuff[index].pos, true) &&
				FORevent->objet->objet[FORevent->objet->objetenmain.IDobjet].type == EQUIPEMENT &&
				FORevent->objet->objet[FORevent->objet->objetenmain.IDobjet].bodypart == index)
			{
				equipestuff(FORevent->objet, FORevent->ui, index, FORevent->objet->objetenmain.IDobjet);
				videemplacement(&FORevent->objet->objetenmain);
				break;
			}
		}
		/*test quit button*/
		if (colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->BoutonQuitter.pos, true) &&
            FORevent->ui->BoutonQuitter.etat == B_CLIQUER)
		{
			FORevent->systeme->continuer = 0;
		}
		else
		{
			FORevent->ui->BoutonQuitter.etat = B_NORMAL;
		}
	}
	/*if craft menu open*/
	else if (FORevent->ui->craft_open == true)
	{
		checkinventaire(FORevent->objet, FORevent->inventaire);


		/*bottom button*/

		if (FORevent->systeme->pointeur.pos.y >= screenh*0.467 &&
			FORevent->systeme->pointeur.pos.y <= (screenh*0.467)+(screenh*0.03))
		{
			for(index = 0 ; index < 7 ; index++)
			{
				if (FORevent->systeme->pointeur.pos.x >= index * FORevent->bouton->bcraft[0].pos.w&&
					FORevent->systeme->pointeur.pos.x <= (index+1) * FORevent->bouton->bcraft[0].pos.w&&
					FORevent->craft->bcraftpointer == index)
				{
					FORevent->craft->bcraftactif = index;
					FORevent->craft->planactif = 0;
				}
			}
		}


		/*si souris en haut a gauche*/
		else if (FORevent->systeme->pointeur.pos.y <= screenh*0.5 && FORevent->systeme->pointeur.pos.x <= screenw*0.3)
		{
		    /*initialisation*/
		    FORevent->craft->planactif = -1;

            /*parcour des plans*/
		    for(index = 0 ; index < 10 ; index++)
            {
                if (FORevent->systeme->pointeur.pos.x >= screenw*0.007 &&
                    FORevent->systeme->pointeur.pos.x <= screenw*0.3 &&
                    FORevent->systeme->pointeur.pos.y >= (screenh*0.04)*index &&
                    FORevent->systeme->pointeur.pos.y <= (screenh*0.04)*(index+1))
                {
                    /*si un plan est present a cet emplacement*/
                    if(FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][index].resultatID != -1)
                    {
                        /*j'indique le plan actif*/
                        FORevent->craft->planactif = index;
                    }
                }
            }
		}
		else/*souris en haut a droite*/
		{
			if (FORevent->systeme->pointeur.pos.x >= screenw*0.622 && FORevent->systeme->pointeur.pos.x <= screenw*0.732 &&
				FORevent->systeme->pointeur.pos.y >= screenh*0.39 && FORevent->systeme->pointeur.pos.y <= screenh*0.456)
			{
				bool checkcompo = true;
				for (index = 0 ; index < FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][FORevent->craft->planactif].compodifferente ; index++)
				{
					if (FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][FORevent->craft->planactif].compodispo[index] == false)
					{
						checkcompo = false;
					}
				}
				if (checkcompo == true)
				{
					for (index = 0 ; index < FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][FORevent->craft->planactif].compodifferente ; index++)
					{
						for (index2 = 0 ; index2 < FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][FORevent->craft->planactif].compoNB[index] ; index2++)
						{
							effacerID(FORevent->objet,FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][FORevent->craft->planactif].compoID[index]);
						}
					}
					insertionsac(FORevent->objet, FORevent->objet->PLANstuff[FORevent->craft->bcraftactif][FORevent->craft->planactif].resultatID);
					checkinventaire(FORevent->objet, FORevent->inventaire);
				}
				FORevent->bouton->crafter.etat = 1;
			}
		}
	}
	if(colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->inventaire->rubbish.pos, true))
	{
		videemplacement(&FORevent->objet->objetenmain);
	}
	else
    {
        for(index = 0 ; index < FORevent->objet->objetenmain.NBobjet ; index++)
        {
            insertionsac(FORevent->objet, FORevent->objet->objetenmain.IDobjet);
        }
        videemplacement(&FORevent->objet->objetenmain);
    }
	checkandrefreshstuff(FORevent->perso, FORevent->objet, FORevent->systeme, FORevent->ui);



	if(colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->corner_inventaire.pos, true) &&
        FORevent->ui->corner_inventaire.etat == B_CLIQUER)
	{
	    FORevent->ui->corner_inventaire.etat = B_NORMAL;
        if(!FORevent->ui->inventaire_open)
        {
            FORevent->ui->inventaire_open = true;
        }
        else
        {
            FORevent->ui->inventaire_open = false;
        }
	}
	else if(colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->corner_chat.pos, true) &&
            FORevent->ui->corner_chat.etat == B_CLIQUER)
	{
	    FORevent->ui->corner_chat.etat = B_NORMAL;
	}
	else if(colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->corner_menu.pos, true) &&
            FORevent->ui->corner_menu.etat == B_CLIQUER)
	{
	    FORevent->ui->corner_menu.etat = B_NORMAL;
        if(!FORevent->ui->menu_open)
        {
            FORevent->ui->menu_open = true;
        }
        else
        {
            FORevent->ui->menu_open = false;
        }
	}
}

void eventmapsourisgauchedown(struct typeFORevent *FORevent)
{
	int index;

	if(colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->corner_inventaire.pos, true))
	{
	    FORevent->ui->corner_inventaire.etat = B_CLIQUER;
	}
	else if(colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->corner_chat.pos, true))
	{
	    FORevent->ui->corner_chat.etat = B_CLIQUER;
	}
	else if(colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->corner_menu.pos, true))
	{
	    FORevent->ui->corner_menu.etat = B_CLIQUER;
	}

	if (FORevent->ui->inventaire_open)
	{
		if (FORevent->systeme->pointeur.pos.y < (screenh*0.43))
		{
			FORevent->inventaire->casedowngauche = calculclicinventaire(FORevent->systeme->pointeur.pos, FORevent->systeme);
			if (FORevent->inventaire->casedowngauche < TAILLESAC && FORevent->inventaire->casedowngauche >= 0)
			{
				prendreenmain(FORevent->objet->sac1[FORevent->inventaire->casedowngauche], &FORevent->objet->objetenmain);
				videemplacement(&FORevent->objet->sac1[FORevent->inventaire->casedowngauche]);
			}
		}
	}
	if (FORevent->ui->menu_open)
	{
		for (index = 0 ; index < 7 ; index++)
		{
			if (colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->casestuff[index].pos, true))
			{
				prendreenmain(FORevent->ui->casestuff[index], &FORevent->objet->objetenmain);
				videemplacement(&FORevent->ui->casestuff[index]);
				checkandrefreshstuff(FORevent->perso, FORevent->objet, FORevent->systeme, FORevent->ui);
				break;
			}
		}

		if (colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->BoutonQuitter.pos, true) &&
			FORevent->ui->BoutonQuitter.etat == B_SURVOLER )
		{
			FORevent->ui->BoutonQuitter.etat = B_CLIQUER;
		}
	}/*
	if (FORevent->ui->coinhaut == 2)
	{
		if (FORevent->systeme->pointeur.pos.x >= screenw*0.622 && FORevent->systeme->pointeur.pos.x <= (screenw*0.622)+(screenw*0.11)
			&& FORevent->systeme->pointeur.pos.y >= screenh*0.39 && FORevent->systeme->pointeur.pos.y <= (screenh*0.39)+(screenh*0.0651))
		{
			FORevent->bouton->crafter.etat = 2;
		}
	}*/
}

void eventmapsourisdroiteup(struct typeFORevent *FORevent)
{
	int index;

	if (FORevent->ui->menu_open)
	{
		for (index = 0 ; index < 7 ; index++)
		{
			if (colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->ui->casestuff[index].pos, true))
			{
				insertionsac(FORevent->objet, FORevent->ui->casestuff[index].IDobjet);
				videemplacement(&FORevent->ui->casestuff[index]);
				checkandrefreshstuff(FORevent->perso, FORevent->objet, FORevent->systeme, FORevent->ui);
				break;
			}
		}
	}
	if (FORevent->ui->inventaire_open)
	{
		FORevent->inventaire->caseupdroit = calculclicinventaire(FORevent->systeme->pointeur.pos, FORevent->systeme);

		if (FORevent->inventaire->caseupdroit == FORevent->inventaire->casedowndroit &&
            FORevent->inventaire->caseupdroit < TAILLESAC)
		{
			int id = FORevent->objet->sac1[FORevent->inventaire->caseupdroit].IDobjet;
			int bodypart = FORevent->objet->objet[id].bodypart;
			/*si objet type equipement*/
			if (FORevent->objet->objet[id].type == EQUIPEMENT)
			{
                //if an object is already in use, put it in the bag
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

void eventmapsourisdroitedown(struct typeFORevent *FORevent)
{
	if (FORevent->ui->inventaire_open)
	{
		if (FORevent->systeme->pointeur.pos.y < screenh*0.43)
		{
			FORevent->inventaire->casedowndroit = calculclicinventaire(FORevent->systeme->pointeur.pos, FORevent->systeme);
		}
	}
}

void sourisactionzone(struct typeFORevent *FORevent)
{
    /*position etabli*/
    if (colisionbox(&FORevent->systeme->pointeur.pos, &FORevent->craft->petabli, true) &&
            checkdistance(&FORevent->perso->perso.pict.pos, &FORevent->craft->petabli, 250) == -1)
    {
        FORevent->ui->craft_open = true;
        FORevent->ui->menu_open = false;
    }
}
