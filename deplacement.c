#include <SDL2/SDL.h>

#include "colision.h"
#include "main.h"

typedef struct DIVERSdeplacement DIVERSdeplacement;
typedef struct DIRECTION DIRECTION;

int directionperso(DIRECTION *direction)
{
	if (direction->haut == 1 && direction->droite == 0 && direction->gauche == 0 && direction->bas == 0) {return 0;}//haut
	else if (direction->haut == 1 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 0) {return 7;}//haut droite
	else if (direction->haut == 1 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 0) {return 1;}//haut gauche
	else if (direction->haut == 0 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 0) {return 6;}//droite
	else if (direction->haut == 0 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 1) {return 5;}//bas droite
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 1) {return 3;}//bas gauche
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 0) {return 2;}//gauche
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 0 && direction->bas == 1) {return 4;}//bas
	else
	{
		if (direction->direction != -1)
		{
			direction->olddirection = direction->direction;
		}
		return -1;
	}
}

int calculdirectionjoueurs(SDL_Rect posjoueurs,SDL_Rect oldposjoueurs)
{
    int bas = 0, haut = 0, gauche = 0, droite = 0;

    if ( oldposjoueurs.x < posjoueurs.x ){droite = 1;}
    else if ( oldposjoueurs.x > posjoueurs.x ){gauche = 1;}

    if ( oldposjoueurs.y < posjoueurs.y ){haut = 1;}
    else if ( oldposjoueurs.y > posjoueurs.y ){bas = 1;}

    if (haut == 1 && droite == 0 && gauche == 0) {return 0;}//haut
    else if (haut == 1 && droite == 1 && gauche == 0) {return 7;}//hautdroite
    else if (haut == 0 && droite == 1 && bas == 0) {return 6;}//droite
    else if (haut == 0 && droite == 1 && bas == 1) {return 5;}//basdroite
    else if (gauche == 0 && droite == 0 && bas == 1) {return 4;}//bas
    else if (gauche == 1 && droite == 0 && bas == 1) {return 3;}//basgauche
    else if (haut == 0 && gauche == 1 && bas == 0) {return 2;}//gauche
    else if (haut == 1 && gauche == 1 && bas == 0) {return 1;}//hautgauche

    return 4;
}
