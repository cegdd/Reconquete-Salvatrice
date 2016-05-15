#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <math.h>

#include "main.h"
#include "rat.h"
#include "systeme.h"

void tirer (float px, float py, int canonx, int canony, int tx[][PRECISIONcailloux], int ty[][PRECISIONcailloux], int tableauutile, double *degre)
{
	int vitesse = VITESSE;
	float y, x;
	int difx = 0, dify = 0, i = 0, bissectrice = 0;
	int octant = calculoctant(px, py, canonx, canony, &difx, &dify);
	float ecart = 0, ecartinverse = 0;
	y = canony;
	x = canonx;

	*degre = atan2(dify, difx);
	*degre *= 57.296;
	ecart = *degre/90;
	ecartinverse = 1-ecart;

	bissectrice = *degre -45;

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

int HitboxBalle(struct typecombat *BTLstr, int index)
{/*fonction appeler pour chaque monstres*/
	int i, k = 0, l = 0;
	SDL_Rect pix = {0, 0, 1, 1};

	#if TESTGRID == 1
	SDL_Point point;
	#endif /* TESTGRID*/

	for (i = 0 ; i < NBcailloux ; i++)
	{   /*tri et degrossissage pour calcul précis*/
	    if (checkdistance(&BTLstr->creature[index].m_pict.pict.pos, &BTLstr->pballe[i], 120) == -1 && BTLstr->DepartBalle[i] == RUNNING )
        {
            #if TESTGRID == 1
            point.x = pballe[i].x;
            point.y = pballe[i].y;
            UnWriteCircleTestGrid(BTLstr, &point, 10);
            #endif /* TESTGRID*/

            for(k = BTLstr->pballe[i].x ; k <= BTLstr->pballe[i].x + BTLstr->pballe[i].w ; k++)
            {
                for(l = BTLstr->pballe[i].y ; l <= BTLstr->pballe[i].y + BTLstr->pballe[i].h; l++)
                {
                    pix.x = k;
                    pix.y = l;

                    if (checkdistance(&pix, &BTLstr->pballe[i], 10) == -1 )
                    {
                        if (TestColision_Rat(&BTLstr->creature[index].m_pict.pict.pos, pix.x, pix.y, BTLstr->creature[index].Direction) == 1)
                        {
                            #if TESTGRID == 1
                            point.x = pballe[i].x;
                            point.y = pballe[i].y;
                            UnWriteCircleTestGrid(BTLstr, &point, 10);
                            #endif /* TESTGRID*/
                            return i;
                        }
                    }
                }
            }
        }
	}
	return -1;
}

void COMBATgestionprojectile (struct typecombat *BTLstr)
{
	int index;
	for (index = 0 ; index < NBcailloux ; index++)
	{
		if (BTLstr->DepartBalle[index] != UNUSED && BTLstr->i[index] < PRECISIONcailloux - 1 && BTLstr->DepartBalle[index] != STOP)
		{
			BTLstr->i[index] = BTLstr->i[index]+1;
			BTLstr->pballe[index].x = BTLstr->tx[index][BTLstr->i[index]];
			BTLstr->pballe[index].y = BTLstr->ty[index][BTLstr->i[index]];
		}
		else if (BTLstr->i[index] >= PRECISIONcailloux-1)
		{
			BTLstr->pballe[index].x = BTLstr->tx[index][PRECISIONcailloux-1];
			BTLstr->pballe[index].y = BTLstr->ty[index][PRECISIONcailloux-1];
			BTLstr->DepartBalle[index] = STOP;
		}
		else
		{
		}
	}
}

void gestiontir(struct typecombat *BTLstr)
{
    tirer (BTLstr->curseur.pos.x, BTLstr->curseur.pos.y, BTLstr->canonx, BTLstr->canony, BTLstr->tx, BTLstr->ty, BTLstr->tableauutile, &BTLstr->degre);

    BTLstr->letirdemander = false;
    BTLstr->DepartBalle[BTLstr->tableauutile] = RUNNING;
    BTLstr->i[BTLstr->tableauutile] = 0;
    BTLstr->tableauutile++;
    if (BTLstr->tableauutile == NBcailloux)
	{
		BTLstr->tableauutile = 0;
	}
}
