#include <SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "image.h"
#include "tableau.h"
#include "colision.h"
#include "deplacement.h"
#include "main.h"

extern int screenh, screenw;

void deplacementperso_map(struct DIVERSmap *carte,struct PERSO *perso,struct DIRECTION *direction, SDL_Point *origin)
{
    int INDEX;

    for (INDEX = 0 ; INDEX < 12 ; INDEX++)
    {
        perso->pix[INDEX].x = ((carte->cellule.pict.pos.x - perso->perso.pict.pos.x)*-1) + perso->PixelCalque[INDEX].x;
        perso->pix[INDEX].y = ((carte->cellule.pict.pos.y+carte->cellule.pict.pos.h)-(perso->perso.pict.pos.y+perso->perso.pict.pos.h)) + perso->PixelCalque[INDEX].y;

        perso->pixel[INDEX] = obtenirPixel(carte->cellule.calque, &perso->pix[INDEX]);
        if (perso->pixel[INDEX] == 255) {perso->etatpix[INDEX] = 0;}
        else{perso->etatpix[INDEX] = 1;}
    }

	perso->cote[UP] =          perso->etatpix[0] + perso->etatpix[1] + perso->etatpix[2] + perso->etatpix[3];
	perso->cote[UPRIGHT] =     perso->etatpix[1] + perso->etatpix[2] + perso->etatpix[3] + perso->etatpix[4]+ perso->etatpix[5];
	perso->cote[RIGHT] =       perso->etatpix[3] + perso->etatpix[4] + perso->etatpix[5] + perso->etatpix[6];
	perso->cote[RIGHTDOWN] =   perso->etatpix[4] + perso->etatpix[5] + perso->etatpix[6] + perso->etatpix[7]+ perso->etatpix[8];
	perso->cote[DOWN] =        perso->etatpix[6] + perso->etatpix[7] + perso->etatpix[8] + perso->etatpix[9];
	perso->cote[DOWNLEFT] =    perso->etatpix[7] + perso->etatpix[8] + perso->etatpix[9] + perso->etatpix[10]+ perso->etatpix[11];
	perso->cote[LEFT] =        perso->etatpix[9] + perso->etatpix[10]+ perso->etatpix[11]+ perso->etatpix[0];
	perso->cote[LEFTUP] =      perso->etatpix[10]+ perso->etatpix[11]+ perso->etatpix[0] + perso->etatpix[1]+ perso->etatpix[2];

	move_map(perso, direction, origin);
}

void deplacementperso_combat(struct PERSO *perso,struct DIRECTION *direction)
{
    int index;
    for (index = 0 ; index < 8 ; index++)
    {
        perso->cote[index] = 0;
    }

    if (perso->perso.pict.pos.y + perso->perso.pict.pos.h >= screenh)
    {
        perso->cote[UP] = 99;
        perso->cote[LEFTUP] = 99;
        perso->cote[UPRIGHT] = 99;
    }
    else if (perso->perso.pict.pos.y <= 0)
    {
        perso->cote[DOWN] = 99;
        perso->cote[DOWNLEFT] = 99;
        perso->cote[RIGHTDOWN] = 99;
    }

    if (perso->perso.pict.pos.x < 0)
    {
        perso->cote[LEFT] = 99;
        perso->cote[LEFTUP] = 99;
        perso->cote[DOWNLEFT] = 99;
    }
    else if (perso->perso.pict.pos.x + perso->perso.pict.pos.w >= screenw)
    {
        perso->cote[RIGHT] = 99;
        perso->cote[RIGHTDOWN] = 99;
        perso->cote[UPRIGHT] = 99;
    }
    move_combat(perso, direction);
}

void move_combat(struct PERSO *perso,struct DIRECTION *direction)
{

    int *x = &perso->perso.pict.pos.x;
    int *y = &perso->perso.pict.pos.y;

    switch (direction->direction)
	{
	case UP:
		if      (perso->cote[UP] <=1)                  {bas(y);}
		else if (perso->cote[LEFTUP] <= 1)             {basdroite(x, y);}
		else if (perso->cote[UPRIGHT] <= 1)            {basgauche(x, y);}
		break;
	case UPRIGHT:
		if      (perso->cote[UPRIGHT] <=1)             {basgauche(x, y);}
		else if (perso->cote[UP] <= 1)                 {bas(y);}
		else if (perso->cote[RIGHT] <= 1)              {gauche(x);}
		break;
	case RIGHT:
		if      (perso->cote[RIGHT] <=1)               {gauche(x);}
		else if (perso->cote[UPRIGHT] <= 1)            {basgauche(x, y);}
		else if (perso->cote[RIGHTDOWN] <= 1)          {gauchehaut(x, y);}
		break;
	case RIGHTDOWN:
		if      (perso->cote[RIGHTDOWN] <=1)           {gauchehaut(x, y);}
		else if (perso->cote[RIGHT] <= 1)              {gauche(x);}
		else if (perso->cote[DOWN] <= 1)               {haut(y);}
		break;
	case DOWN:
		if      (perso->cote[DOWN] <=1)                {haut(y);}
		else if (perso->cote[RIGHTDOWN] <= 1)          {gauchehaut(x, y);}
		else if (perso->cote[DOWNLEFT] <= 1)           {hautdroite(x, y);}
		break;
	case DOWNLEFT:
		if      (perso->cote[DOWNLEFT] <=1)            {hautdroite(x, y);}
		else if (perso->cote[DOWN] <= 1)               {haut(y);}
		else if (perso->cote[LEFT] <= 1)               {droite(x);}
		break;
	case LEFT:
		if      (perso->cote[LEFT] <=1)                {droite(x);}
		else if (perso->cote[DOWNLEFT] <= 1)           {hautdroite(x, y);}
		else if (perso->cote[LEFTUP] <= 1)             {basdroite(x, y);}
		break;
	case LEFTUP:
		if      (perso->cote[LEFTUP] <=1)              {basdroite(x, y);}
		else if (perso->cote[LEFT] <= 1)               {droite(x);}
		else if (perso->cote[UP] <= 1)                 {bas(y);}
		break;
	}
}

void move_map(struct PERSO *perso,struct DIRECTION *direction, SDL_Point *origin)
{
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

