#include <SDL2/SDL.h>

#include "colision.h"
#include "main.h"

typedef struct DIVERSdeplacement DIVERSdeplacement;
typedef struct DIRECTION DIRECTION;

int directionperso(DIRECTION *direction)
{
	if (direction->haut == 1 && direction->droite == 0 && direction->gauche == 0 && direction->bas == 0) {return UP;}
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


void haut (PERSO *perso, int* y, DIVERSsysteme *systeme, int enmap)
{
    if (enmap == 1)
    {
        if (perso->pperso.y >= (systeme->screenh-perso->pperso.h)/2)
        {
            perso->pperso.y = perso->pperso.y - 6;
        }
        else if (*y >= 0 && perso->pperso.y >= 10)
        {
            perso->pperso.y = perso->pperso.y - 6;
        }
        else if (*y <= 0)
        {
            *y = *y + 6;
        }
    }
    else
	{
		*y = *y - 3;
	}
}
void hautdroite (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap)
{
    if (enmap == 1)
    {
        if (perso->pperso.y >= (systeme->screenh-perso->pperso.h)/2)
        {
            perso->pperso.y = perso->pperso.y - 5;
        }
        else if (*y >= 0 && perso->pperso.y >= 10)
        {
            perso->pperso.y = perso->pperso.y - 5;
        }
        else if (*y <= 0)
        {
            *y = *y + 5;
        }

        if (perso->pperso.x <= (systeme->screenw-perso->pperso.w)/2)
        {
            perso->pperso.x = perso->pperso.x + 5;
        }
        else if (*x <= -8640 && perso->pperso.x <= systeme->screenw-perso->pperso.w)
        {
            perso->pperso.x = perso->pperso.x + 5;
        }
        else if (*x >= -8640)
        {
            *x = *x - 5;
        }
    }
    else
	{
		*x = *x + 2;
		*y = *y - 2;
	}
}
void droite (PERSO *perso, int* x, DIVERSsysteme *systeme, int enmap)
{
    if (enmap == 1)
    {
        if (perso->pperso.x <= (systeme->screenw-perso->pperso.w)/2)
        {
            perso->pperso.x = perso->pperso.x + 6;
        }
        else if (*x <= -8640 && perso->pperso.x <= systeme->screenw-perso->pperso.w)
        {
            perso->pperso.x = perso->pperso.x + 6;
        }
        else if (*x >= -8640)
        {
            *x = *x - 6;
        }
    }
    else
	{
		*x = *x + 3;
	}
}
void basdroite (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap)
{
    if (enmap == 1)
    {
        if (perso->pperso.y <= (systeme->screenh-perso->pperso.h)/2)
        {
            perso->pperso.y = perso->pperso.y + 5;
        }
        else if (*y <= -9222 && perso->pperso.y <= systeme->screenh-perso->pperso.h)
        {
            perso->pperso.y = perso->pperso.y + 5;
        }
        else if (*y >= -9222)
        {
            *y = *y - 5;
        }

        if (perso->pperso.x <= (systeme->screenw-perso->pperso.w)/2)
        {
            perso->pperso.x = perso->pperso.x + 5;
        }
        else if (*x <= -8640 && perso->pperso.x <= systeme->screenw-perso->pperso.w)
        {
            perso->pperso.x = perso->pperso.x + 5;
        }
        else if (*x >= -8640)
        {
            *x = *x - 5;
        }
    }
    else
	{
		*y = *y + 2;
		*x = *x + 2;
	}
}
void bas (PERSO *perso, int* y, DIVERSsysteme *systeme, int enmap)
{
    if (enmap == 1)
    {
        if (perso->pperso.y <= (systeme->screenh-perso->pperso.h)/2)
        {
            perso->pperso.y = perso->pperso.y + 6;
        }
        else if (*y <= -9222 && perso->pperso.y <= systeme->screenh-perso->pperso.h)
        {
            perso->pperso.y = perso->pperso.y + 6;
        }
        else if (*y >= -9222)
        {
            *y = *y - 6;
        }
    }
    else
	{
		*y = *y + 3;
	}
}
void basgauche (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap)
{
    if (enmap == 1)
    {
        if (perso->pperso.y <= (systeme->screenh-perso->pperso.h)/2)
        {
            perso->pperso.y = perso->pperso.y + 5;   //bas
        }
        else if (*y <= -9222 && perso->pperso.y <= systeme->screenh-perso->pperso.h)
        {
            perso->pperso.y = perso->pperso.y + 5;
        }
        else if (*y >= -9222)
        {
            *y = *y - 5;
        }

        if (perso->pperso.x >= (systeme->screenw-perso->pperso.w)/2)
        {
            perso->pperso.x = perso->pperso.x - 5;   //gauche
        }
        else if (*x >= 0 && perso->pperso.x >= -10)
        {
            perso->pperso.x = perso->pperso.x - 5;
        }
        else if (*x <= 0)
        {
            *x = *x + 5;
        }
    }
    else
	{
		*y = *y + 2;
		*x = *x - 2;
	}
}
void gauche (PERSO *perso, int* x, DIVERSsysteme *systeme, int enmap)
{
    if (enmap == 1)
    {
        if (perso->pperso.x >= (systeme->screenw-perso->pperso.w)/2)
        {
            perso->pperso.x = perso->pperso.x - 6;
        }
        else if (*x >= 0 && perso->pperso.x >= -10)
        {
            perso->pperso.x = perso->pperso.x - 6;
        }
        else if (*x <= 0)
        {
            *x = *x + 6;
        }
    }
    else
	{
		*x = *x - 3;
	}
}
void gauchehaut (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap)
{
    if (enmap == 1)
    {
        if (perso->pperso.y >= (systeme->screenh-perso->pperso.h)/2)
        {
            perso->pperso.y = perso->pperso.y - 5;   //haut
        }
        else if (*y >= 0 && perso->pperso.y >= 10)
        {
            perso->pperso.y = perso->pperso.y - 5;
        }
        else if (*y <= 0)
        {
            *y = *y + 5;
        }

        if (perso->pperso.x >= (systeme->screenw-perso->pperso.w)/2)
        {
            perso->pperso.x = perso->pperso.x - 5;   //gauche
        }
        else if (*x >= 0 && perso->pperso.x >= -10)
        {
            perso->pperso.x = perso->pperso.x - 5;
        }
        else if (*x <= 0)
        {
            *x = *x + 5;
        }
    }
    else
	{
		*y = *y - 2;
		*x = *x - 2;
	}
}
