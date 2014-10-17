#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#include "image.h"
#include "tableau.h"
#include "colision.h"
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

	cote[0] = etatpix[0] + etatpix[1] + etatpix[2];
	cote[1] = etatpix[1] + etatpix[2] + etatpix[3];
	cote[2] = etatpix[2] + etatpix[3] + etatpix[4];
	cote[3] = etatpix[3] + etatpix[4] + etatpix[5];
	cote[4] = etatpix[4] + etatpix[5] + etatpix[6];
	cote[5] = etatpix[5] + etatpix[6] + etatpix[7];
	cote[6] = etatpix[6] + etatpix[7] + etatpix[0];
	cote[7] = etatpix[7] + etatpix[0] + etatpix[1];

	if(autorisation == false)
	{
		//bas
		if(direction->direction == 4 && *y+perso->pperso.h >= systeme->screenh){cote[4] = 3; cote[3] = 3; cote[5] = 3;}
		//droite
		if(direction->direction == 6 && *x+perso->pperso.w >= systeme->screenw){cote[2] = 3; cote[1] = 3; cote[3] = 3;}
		//haut
		if(direction->direction == 0 && *y < 0){cote[0] = 3; cote[7] = 3; cote[1] = 3;}
		//gauche
		if(direction->direction == 2 && *x < 0){cote[6] = 3; cote[7] = 3; cote[5] = 3;}

		if(direction->direction == 5 && *y+perso->pperso.h >= systeme->screenh){cote[4] = 3; cote[3] = 3; cote[5] = 3;}
		if(direction->direction == 3 && *y+perso->pperso.h >= systeme->screenh){cote[4] = 3; cote[3] = 3; cote[5] = 3;}

		if(direction->direction == 1 && *y < 0){cote[0] = 3; cote[7] = 3; cote[1] = 3;}
		if(direction->direction == 7 && *y < 0){cote[0] = 3; cote[7] = 3; cote[1] = 3;}

		if(direction->direction == 7 && *x+perso->pperso.w >= systeme->screenw){cote[2] = 3; cote[1] = 3; cote[3] = 3;}
		if(direction->direction == 5 && *x+perso->pperso.w >= systeme->screenw){cote[2] = 3; cote[1] = 3; cote[3] = 3;}

		if(direction->direction == 3 && *x < 0){cote[6] = 3; cote[7] = 3; cote[5] = 3;}
		if(direction->direction == 1 && *x < 0){cote[6] = 3; cote[7] = 3; cote[5] = 3;}
	}


	switch (direction->direction)
	{
	case 0:
		if (cote[0] <=1)                    {haut(perso, y, systeme, enmap);}
		else if (cote[7] <= 1)              {gauchehaut(perso, x, y, systeme, enmap);}
		else if (cote[1] <= 1)              {hautdroite(perso, x, y, systeme, enmap);}
		break;
	case 7:
		if (cote[1] <=1)
		{
			hautdroite(perso, x, y, systeme, enmap);
		}
		else if (cote[0] <= 1)              {haut(perso, y, systeme, enmap);}
		else if (cote[2] <= 1)              {droite(perso, x, systeme, enmap);}
		break;
	case 6:
		if (cote[2] <=1)
		{
			droite(perso, x, systeme, enmap);
		}
		else if (cote[1] <= 1)              {hautdroite(perso, x, y, systeme, enmap);}
		else if (cote[3] <= 1)              {basdroite(perso, x, y, systeme, enmap);}
		break;
	case 5:
		if (cote[3] <=1)
		{
			basdroite(perso, x, y, systeme, enmap);
		}
		else if (cote[2] <= 1)              {droite(perso, x, systeme, enmap);}
		else if (cote[4] <= 1)              {bas(perso, y, systeme, enmap);}
		break;
	case 4:
		if (cote[4] <=1)
		{
			bas(perso, y, systeme, enmap);
		}
		else if (cote[3] <= 1)              {basdroite(perso, x, y, systeme, enmap);}
		else if (cote[5] <= 1)              {basgauche(perso, x, y, systeme, enmap);}
		break;
	case 3:
		if (cote[5] <=1)
		{
			basgauche(perso, x, y, systeme, enmap);
		}
		else if (cote[4] <= 1)              {bas(perso, y, systeme, enmap);}
		else if (cote[6] <= 1)              {gauche(perso, x, systeme, enmap);}
		break;
	case 2:
		if (cote[6] <=1)
		{
			gauche(perso, x, systeme, enmap);
		}
		else if (cote[5] <= 1)              {basgauche(perso, x, y, systeme, enmap);}
		else if (cote[7] <= 1)              {gauchehaut(perso, x, y, systeme, enmap);}
		break;
	case 1:
		if (cote[7] <=1)
		{
			gauchehaut(perso, x, y, systeme, enmap);
		}
		else if (cote[6] <= 1)              {gauche(perso, x, systeme, enmap);}
		else if (cote[0] <= 1)              {haut(perso, y, systeme, enmap);}
		break;
	}

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

