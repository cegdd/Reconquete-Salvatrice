#include "C:\Users\antoi\Documents\programation\SDL2\SDL.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "struct.h"
#include "perso.h"
#include "colision.h"
#include "image.h"
#include "deplacement.h"
#include "donjon.h"

extern int screenh, screenw;

void checkPixel(struct floor *carte,struct PERSO *perso,struct DIVERSsysteme *systeme)
{
    int INDEX;
    for (INDEX = 0 ; INDEX < 12 ; INDEX++)
    {
        perso->pix.x = ((carte->pict.pos.x - perso->perso.pict.pos.x)*-1) + perso->PixelCalque[INDEX].x;
        perso->pix.y = ((carte->pict.pos.y+carte->pict.pos.h)-(perso->perso.pict.pos.y+perso->perso.pict.pos.h)) + perso->PixelCalque[INDEX].y;


        if (obtenirPixel(carte->calque, &perso->pix) == 255) {perso->etatpix[INDEX] = 0;}
        else{perso->etatpix[INDEX] = 1;}
    }
}

void move_map(struct PERSO *perso,struct DIRECTION *direction, SDL_Point *origin)
{
    perso->cote[UP] =          perso->etatpix[0] + perso->etatpix[1] + perso->etatpix[2] + perso->etatpix[3];
	perso->cote[UPRIGHT] =     perso->etatpix[1] + perso->etatpix[2] + perso->etatpix[3] + perso->etatpix[4]+ perso->etatpix[5];
	perso->cote[RIGHT] =       perso->etatpix[3] + perso->etatpix[4] + perso->etatpix[5] + perso->etatpix[6];
	perso->cote[RIGHTDOWN] =   perso->etatpix[4] + perso->etatpix[5] + perso->etatpix[6] + perso->etatpix[7]+ perso->etatpix[8];
	perso->cote[DOWN] =        perso->etatpix[6] + perso->etatpix[7] + perso->etatpix[8] + perso->etatpix[9];
	perso->cote[DOWNLEFT] =    perso->etatpix[7] + perso->etatpix[8] + perso->etatpix[9] + perso->etatpix[10]+ perso->etatpix[11];
	perso->cote[LEFT] =        perso->etatpix[9] + perso->etatpix[10]+ perso->etatpix[11]+ perso->etatpix[0];
	perso->cote[LEFTUP] =      perso->etatpix[10]+ perso->etatpix[11]+ perso->etatpix[0] + perso->etatpix[1]+ perso->etatpix[2];

    switch (direction->direction)
	{
	case UP:
		if      (perso->cote[UP] <=1)                  {haut(&origin->y);}
		else if (perso->cote[LEFTUP] <= 1)             {gauchehaut(&origin->x, &origin->y);}
		else if (perso->cote[UPRIGHT] <= 1)            {hautdroite(&origin->x, &origin->y);}
		break;
	case UPRIGHT:
		if      (perso->cote[UPRIGHT] <=1)             {hautdroite(&origin->x, &origin->y);}
		else if (perso->cote[UP] <= 1)                 {haut(&origin->y);}
		else if (perso->cote[RIGHT] <= 1)              {droite(&origin->x);}
		break;
	case RIGHT:
		if      (perso->cote[RIGHT] <=1)               {droite(&origin->x);}
		else if (perso->cote[UPRIGHT] <= 1)            {hautdroite(&origin->x, &origin->y);}
		else if (perso->cote[RIGHTDOWN] <= 1)          {basdroite(&origin->x, &origin->y);}
		break;
	case RIGHTDOWN:
		if      (perso->cote[RIGHTDOWN] <=1)           {basdroite(&origin->x, &origin->y);}
		else if (perso->cote[RIGHT] <= 1)              {droite(&origin->x);}
		else if (perso->cote[DOWN] <= 1)               {bas(&origin->y);}
		break;
	case DOWN:
		if      (perso->cote[DOWN] <=1)                {bas(&origin->y);}
		else if (perso->cote[RIGHTDOWN] <= 1)          {basdroite(&origin->x, &origin->y);}
		else if (perso->cote[DOWNLEFT] <= 1)           {basgauche(&origin->x, &origin->y);}
		break;
	case DOWNLEFT:
		if      (perso->cote[DOWNLEFT] <=1)            {basgauche(&origin->x, &origin->y);}
		else if (perso->cote[DOWN] <= 1)               {bas(&origin->y);}
		else if (perso->cote[LEFT] <= 1)               {gauche(&origin->x);}
		break;
	case LEFT:
		if      (perso->cote[LEFT] <=1)                {gauche(&origin->x);}
		else if (perso->cote[DOWNLEFT] <= 1)           {basgauche(&origin->x, &origin->y);}
		else if (perso->cote[LEFTUP] <= 1)             {gauchehaut(&origin->x, &origin->y);}
		break;
	case LEFTUP:
		if      (perso->cote[LEFTUP] <=1)              {gauchehaut(&origin->x, &origin->y);}
		else if (perso->cote[LEFT] <= 1)               {gauche(&origin->x);}
		else if (perso->cote[UP] <= 1)                 {haut(&origin->y);}
		break;
	}
}

int colisionbox(SDL_Rect *A, SDL_Rect *B, bool pointeur)
{
	/*if cursor of the mouse(A) is inside zone B
	test on the upleft of zone A*/
	if (pointeur == true &&
        A->x >= B->x && A->x <= B->x+B->w && A->y+A->h >= B->y && A->y+A->h <= B->y+B->h)
	{
		return 1;
	}
	/*else if zone A is inside B*/
	else if (pointeur == false &&
		A->x+A->w >= B->x && A->x <= B->x+B->w && A->y+A->h >= B->y && A->y <= B->y+B->h)
	{
		return 1;
	}
	return 0;
}
bool colisionfromage(SDL_Rect *lanceur, SDL_Rect *recepteur, SDL_Rect *pixeltest, double marge)
{
    double diff;

	diff = (FindAngle(lanceur, recepteur)+180) - (FindAngle(lanceur, pixeltest)+180);

	if (diff < 0) /*if "diff" is negative, we switch him to positive*/
    {
        diff *= -1;
    }

	if (diff <= 0 || diff >= marge/2) /*if the difference is bigger than the gap, we return FALSE*/
    {
        return false;
    }
    return true;
}
double FindAngle(SDL_Rect *A, SDL_Rect *B)
{
    register int difx, dify;

    difx = (A->x + A->w/2) - (B->x + B->w/2);
    dify = (A->y + A->h/2) - (B->y + B->h/2);

    return atan2(dify, difx)* 57.296;
}

int playeristouched(struct DONJON *donjon, struct PERSO *perso)
{
    int i = 0;

    for (i = 0 ; i < donjon->nombremonstre ; i++)
    {
        if (colisionbox(&perso->perso.pict.pos, &donjon->mob[i].hookpict.pict.pos, false) == true &&
            donjon->mob[i].atkDone == false)
        {
            return i;
        }
    }
        return -1;
}

