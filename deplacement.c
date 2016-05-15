#include <SDL.h>

#include "colision.h"
#include "main.h"

int directionperso(struct DIRECTION *direction)
{
    if      (direction->haut == 1 && direction->droite == 0 && direction->gauche == 0 && direction->bas == 0) {return UP;}
	else if (direction->haut == 1 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 0) {return UPRIGHT;}
	else if (direction->haut == 1 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 0) {return LEFTUP;}
	else if (direction->haut == 0 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 0) {return RIGHT;}
	else if (direction->haut == 0 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 1) {return RIGHTDOWN;}
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 1) {return DOWNLEFT;}
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 0) {return LEFT;}
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 0 && direction->bas == 1) {return DOWN;}
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

    if (haut == 1 && droite == 0 && gauche == 0) {return UP;}
    else if (haut == 1 && droite == 1 && gauche == 0) {return UPRIGHT;}
    else if (haut == 0 && droite == 1 && bas == 0) {return RIGHT;}
    else if (haut == 0 && droite == 1 && bas == 1) {return RIGHTDOWN;}
    else if (gauche == 0 && droite == 0 && bas == 1) {return DOWN;}
    else if (gauche == 1 && droite == 0 && bas == 1) {return DOWNLEFT;}
    else if (haut == 0 && gauche == 1 && bas == 0) {return LEFT;}
    else if (haut == 1 && gauche == 1 && bas == 0) {return LEFTUP;}

    return DOWN;
}


void haut (int* y)
{
        *y = *y - 6;
}
void hautdroite (int* x, int* y)
{
        *y = *y - 5;
        *x = *x - 5;
}
void droite (int* x)
{
        *x = *x - 6;
}
void basdroite (int* x, int* y)
{
            *y = *y + 5;
            *x = *x - 5;
}
void bas (int* y)
{
        *y = *y + 6;
}
void basgauche (int* x, int* y)
{
        *y = *y + 5;
        *x = *x + 5;
}
void gauche (int* x)
{
            *x = *x + 6;
}
void gauchehaut (int* x, int* y)
{
        *y = *y - 5;
        *x = *x + 5;
}
