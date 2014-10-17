#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "jeux.h"
#include "tir.h"
#include "main.h"


int arrondi (float flottant)
{
    return (int)(flottant+0.5);
}

void tirer (float px, float py, int canonx, int canony, int tx[][PRECISIONcailloux], int ty[][PRECISIONcailloux], int tableauutile, double *degre)
{
	register int vitesse = VITESSE;
	register float y, x;
	int difx = 0;
	int dify = 0;
	int i = 0, octant = calculoctant(px, py, canonx, canony, &difx, &dify);

	y = canony;
	x = canonx;
	*degre = atan2(dify, difx);
	*degre *= 57.296;
	register float ecart = *degre/90;
	register float ecartinverse = 1-ecart;

	int bissectrice = *degre -45;

	if (bissectrice < 0)
	{
		bissectrice = bissectrice*-1;
	}
	bissectrice = bissectrice *2.5;

	for (i = 0; i < PRECISIONcailloux-bissectrice ; i++)
	{
		if (octant == 1)
		{
			x += ecartinverse*vitesse;
			y -= ecart*vitesse;
		}
		else if (octant == 2)
		{
			x += ecartinverse*vitesse;
			y += ecart*vitesse;
		}
		else if (octant == 3)
		{
			x -= ecartinverse*vitesse;
			y += ecart*vitesse;
		}
		else
		{
			x -= ecartinverse*vitesse;
			y -= ecart*vitesse;
		}

		tx[tableauutile][i] = arrondi(x);
		ty[tableauutile][i] = arrondi(y);
	}
	for(i = PRECISIONcailloux-bissectrice; i < PRECISIONcailloux ; i++)
	{
		tx[tableauutile][i] = tx[tableauutile][PRECISIONcailloux-1-bissectrice];
		ty[tableauutile][i] = ty[tableauutile][PRECISIONcailloux-1-bissectrice];
	}
}

int calculoctant(int x, int y, int x2, int y2, int* difx, int* dify)
{
	int octant = 0;

	if (x >= x2)
	{
		if (difx != NULL)
		{
			*difx = x - x2;
		}

		if (y >= y2)
        {
			if (difx != NULL)
			{
				*dify = y - y2;
			}
            octant = 2;
        }
        else
        {
			if (difx != NULL)
			{
				*dify = y2 - y;
			}
            octant = 1;
        }
    }
    else
    {
		if (difx != NULL)
		{
			*difx = x2 - x;
		}
		
        if (y >= y2)
        {
			if (difx != NULL)
			{
				*dify = y - y2;
			}
            octant = 3;
        }
        else
        {
			if (difx != NULL)
			{
				*dify = y2 - y;
			}
            octant = 4;
        }
    }
    
    return octant;
}
