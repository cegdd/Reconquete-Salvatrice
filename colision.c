#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#include "image.h"
#include "tableau.h"
#include "colision.h"
#include "deplacement.h"
#include "main.h"

void deplacementperso(SDL_Surface *mapnb[], PERSO *perso, DIRECTION *direction, DIVERSsysteme *systeme, int *x, int *y, int enmap)
{
	int INDEX;
	static Uint32 pixel[8] = {0};
	static int pixx[8], pixy[8];
	int cote[8] = {0}, etatpix[8] = {1};
	static SDL_Color couleurpixel[8];
	static SDL_Color couleurNoir = {0, 0, 0, 0};
	bool autorisation = true;

	if (enmap == 1)
	{
		for (INDEX = 0 ; INDEX < 8 ; INDEX++)
		{
			pixx[INDEX] = (*x * -1) + perso->pperso.x + systeme->PixelCalque[INDEX].x;
			pixy[INDEX] = (*y * -1) + perso->pperso.y + systeme->PixelCalque[INDEX].y;
			pixel[INDEX] = obtenirPixel(mapnb, pixx[INDEX], pixy[INDEX]);
			SDL_GetRGB(pixel[INDEX], mapnb[2]->format, &couleurpixel[INDEX].r, &couleurpixel[INDEX].g, &couleurpixel[INDEX].b);
			if (couleurpixel[INDEX].r == couleurNoir.r) {etatpix[INDEX] = 1;}
		}
	}
	else
	{
		//si perso dans l'écran
		SDL_Rect ptemp;
		ptemp.x = 0;
		ptemp.y = 0;
		ptemp.w = 1366;
		ptemp.h = 768;
		if (colisionbox(&perso->pperso, &ptemp, 0) == 0)
		{
		}
		else
		{
			autorisation = false;
		}
	}

	cote[UP] = etatpix[UP] + etatpix[UPRIGHT] + etatpix[RIGHT];
	cote[UPRIGHT] = etatpix[UPRIGHT] + etatpix[RIGHT] + etatpix[RIGHTDOWN];
	cote[RIGHT] = etatpix[RIGHT] + etatpix[RIGHTDOWN] + etatpix[DOWN];
	cote[RIGHTDOWN] = etatpix[RIGHTDOWN] + etatpix[DOWN] + etatpix[DOWNLEFT];
	cote[DOWN] = etatpix[DOWN] + etatpix[DOWNLEFT] + etatpix[LEFT];
	cote[DOWNLEFT] = etatpix[DOWNLEFT] + etatpix[LEFT] + etatpix[LEFTUP];
	cote[LEFT] = etatpix[LEFT] + etatpix[LEFTUP] + etatpix[UP];
	cote[LEFTUP] = etatpix[LEFTUP] + etatpix[UP] + etatpix[UPRIGHT];

	if(autorisation == false)
	{
		//bas
		if(direction->direction == DOWN && *y+perso->pperso.h >= systeme->screenh){cote[DOWN] = 3; cote[RIGHTDOWN] = 3; cote[DOWNLEFT] = 3;}
		//droite
		if(direction->direction == RIGHT && *x+perso->pperso.w >= systeme->screenw){cote[RIGHT] = 3; cote[UPRIGHT] = 3; cote[RIGHTDOWN] = 3;}
		//haut
		if(direction->direction == UP && *y < 0){cote[UP] = 3; cote[LEFTUP] = 3; cote[UPRIGHT] = 3;}
		//gauche
		if(direction->direction == LEFT && *x < 0){cote[LEFT] = 3; cote[LEFTUP] = 3; cote[DOWNLEFT] = 3;}

		if(direction->direction == DOWNLEFT && *y+perso->pperso.h >= systeme->screenh){cote[DOWN] = 3; cote[RIGHTDOWN] = 3; cote[DOWNLEFT] = 3;}
		if(direction->direction == RIGHTDOWN && *y+perso->pperso.h >= systeme->screenh){cote[DOWN] = 3; cote[RIGHTDOWN] = 3; cote[DOWNLEFT] = 3;}

		if(direction->direction == UPRIGHT && *y < 0){cote[UP] = 3; cote[LEFTUP] = 3; cote[UPRIGHT] = 3;}
		if(direction->direction == LEFTUP && *y < 0){cote[UP] = 3; cote[LEFTUP] = 3; cote[UPRIGHT] = 3;}

		if(direction->direction == LEFTUP && *x+perso->pperso.w >= systeme->screenw){cote[RIGHT] = 3; cote[UPRIGHT] = 3; cote[RIGHTDOWN] = 3;}
		if(direction->direction == DOWNLEFT && *x+perso->pperso.w >= systeme->screenw){cote[RIGHT] = 3; cote[UPRIGHT] = 3; cote[RIGHTDOWN] = 3;}

		if(direction->direction == RIGHTDOWN && *x < 0){cote[LEFT] = 3; cote[LEFTUP] = 3; cote[DOWNLEFT] = 3;}
		if(direction->direction == UPRIGHT && *x < 0){cote[LEFT] = 3; cote[LEFTUP] = 3; cote[DOWNLEFT] = 3;}
	}


	switch (direction->direction)
	{
	case UP:
		if (cote[UP] <=1)                    {haut(perso, y, systeme, enmap);}
		else if (cote[LEFTUP] <= 1)              {gauchehaut(perso, x, y, systeme, enmap);}
		else if (cote[UPRIGHT] <= 1)              {hautdroite(perso, x, y, systeme, enmap);}
		break;
	case UPRIGHT:
		if (cote[UPRIGHT] <=1)
		{
			hautdroite(perso, x, y, systeme, enmap);
		}
		else if (cote[UP] <= 1)              {haut(perso, y, systeme, enmap);}
		else if (cote[RIGHT] <= 1)              {droite(perso, x, systeme, enmap);}
		break;
	case RIGHT:
		if (cote[RIGHT] <=1)
		{
			droite(perso, x, systeme, enmap);
		}
		else if (cote[UPRIGHT] <= 1)              {hautdroite(perso, x, y, systeme, enmap);}
		else if (cote[RIGHTDOWN] <= 1)              {basdroite(perso, x, y, systeme, enmap);}
		break;
	case RIGHTDOWN:
		if (cote[RIGHTDOWN] <=1)
		{
			basdroite(perso, x, y, systeme, enmap);
		}
		else if (cote[RIGHT] <= 1)              {droite(perso, x, systeme, enmap);}
		else if (cote[DOWN] <= 1)              {bas(perso, y, systeme, enmap);}
		break;
	case DOWN:
		if (cote[DOWN] <=1)
		{
			bas(perso, y, systeme, enmap);
		}
		else if (cote[RIGHTDOWN] <= 1)              {basdroite(perso, x, y, systeme, enmap);}
		else if (cote[DOWNLEFT] <= 1)              {basgauche(perso, x, y, systeme, enmap);}
		break;
	case DOWNLEFT:
		if (cote[DOWNLEFT] <=1)
		{
			basgauche(perso, x, y, systeme, enmap);
		}
		else if (cote[DOWN] <= 1)              {bas(perso, y, systeme, enmap);}
		else if (cote[LEFT] <= 1)              {gauche(perso, x, systeme, enmap);}
		break;
	case LEFT:
		if (cote[LEFT] <=1)
		{
			gauche(perso, x, systeme, enmap);
		}
		else if (cote[DOWNLEFT] <= 1)              {basgauche(perso, x, y, systeme, enmap);}
		else if (cote[LEFTUP] <= 1)              {gauchehaut(perso, x, y, systeme, enmap);}
		break;
	case LEFTUP:
		if (cote[LEFTUP] <=1)
		{
			gauchehaut(perso, x, y, systeme, enmap);
		}
		else if (cote[LEFT] <= 1)              {gauche(perso, x, systeme, enmap);}
		else if (cote[UP] <= 1)              {haut(perso, y, systeme, enmap);}
		break;
	}

}


int colisionbox(SDL_Rect *A, SDL_Rect *B, int pointeur)
{
	//si le pointeur de la souris(A) est dans la zone B
	//test sur le coin haut/gauche de la zone A
	if (pointeur == 1 &&
        A->x >= B->x && A->x <= B->x+B->w && A->y >= B->y && A->y <= B->y+B->h)
	{
		return 1;
	}
	//sinon si la zone A est dans la sone B
	else if (pointeur == 0 &&
		A->x+A->w >= B->x && A->x <= B->x+B->w && A->y+A->h >= B->y && A->y <= B->y+B->h)
	{
		return 1;
	}
	return 0;
}
bool colisionfromage(SDL_Rect *lanceur, SDL_Rect *recepteur, SDL_Rect *curseur, double marge)
{
    register double diff;

	diff = (FindAngle(lanceur, recepteur)+180) - (FindAngle(lanceur, curseur)+180);

	if (diff < 0) //si diff est négatif, on le passe en positif
    {
        diff *= -1;
    }

	if (diff <= 0 || diff >= marge/2) //si la différence est plus grande que la marge, nous retournons FAUX
    {
        return FALSE;
    }
    return TRUE;
}
double FindAngle(SDL_Rect *A, SDL_Rect *B)
{
    register int difx, dify;

    difx = (A->x + A->w/2) - (B->x + B->w/2);
    dify = (A->y + A->h/2) - (B->y + B->h/2);

    return atan2(dify, difx)* 57.296;
}

