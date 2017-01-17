#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <math.h>

#include "main.h"
#include "rat.h"
#include "systeme.h"
#include "struct.h"
#include "image.h"

void tirer (float px, float py, int canonx, int canony, int tx[][PRECISIONcailloux], int ty[][PRECISIONcailloux],
            int tableauutile, double *degre, struct DONJON *donjon)
{
	int vitesse = VITESSE;
	float y, x;
	int difx = 0, dify = 0, i = 0, bissectrice = 0;
	int octant = calculoctant(px, py, canonx, canony, &difx, &dify);
	float ecart = 0, ecartinverse = 0;
	x = canonx;
	y = canony;

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

		tx[tableauutile][i] = arrondi(x)- donjon->map.pict.pos.x;
		ty[tableauutile][i] = arrondi(y)- donjon->map.pict.pos.y;


	}
	for(i = PRECISIONcailloux-bissectrice; i < PRECISIONcailloux ; i++)
	{
		tx[tableauutile][i] = tx[tableauutile][PRECISIONcailloux-1-bissectrice];
		ty[tableauutile][i] = ty[tableauutile][PRECISIONcailloux-1-bissectrice];
	}
}
/*
int HitboxBalle(int index)
{//fonction appeler pour chaque monstres
	int i, k = 0, l = 0;
	SDL_Rect pix = {0, 0, 1, 1};

	for (i = 0 ; i < NBcailloux ; i++)
	{   //tri et degrossissage pour calcul précis
	    if (checkdistance(&BTLstr->creature[index].m_pict.pict.pos, &BTLstr->pballe[i], 120) == -1 && BTLstr->DepartBalle[i] == RUNNING )
        {
            #if TESTGRID == 1
            point.x = pballe[i].x;
            point.y = pballe[i].y;
            UnWriteCircleTestGrid(BTLstr, &point, 10);
            #endif // TESTGRID

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
                            #endif // TESTGRID
                            return i;
                        }
                    }
                }
            }
        }
	}
	return -1;
}*/



void COMBATgestionprojectile (struct TIR *TIR, struct DONJON *donjon)
{
	int index;
	for (index = 0 ; index < NBcailloux ; index++)
	{
		if (TIR->DepartBalle[index] != UNUSED && TIR->i[index] < PRECISIONcailloux - 1 && TIR->DepartBalle[index] != STOP)
		{
			TIR->i[index]++;
			TIR->pballe[index].x = TIR->tx[index][TIR->i[index]];
			TIR->pballe[index].y = TIR->ty[index][TIR->i[index]];
			if (obtenirPixel_middle(donjon->map.calque, &TIR->pballe[index]) !=  255)
            {
                TIR->DepartBalle[index] = STOP;
            }
		}
		else if (TIR->i[index] >= PRECISIONcailloux-1)
		{
			TIR->pballe[index].x = TIR->tx[index][PRECISIONcailloux-1];
			TIR->pballe[index].y = TIR->ty[index][PRECISIONcailloux-1];
			TIR->DepartBalle[index] = STOP;
		}
	}
}

void gestiontir(struct TIR *TIR, struct DIVERSsysteme *systeme, struct PERSO *perso, struct DONJON *donjon)
{
    //pos du perso a l'ecran
    int x = (perso->perso.pict.pos.x + perso->perso.pict.pos.w/2);
    int y = (perso->perso.pict.pos.y + perso->perso.pict.pos.h/2);

    tirer (systeme->pointeur.pos.x, systeme->pointeur.pos.y, x, y, TIR->tx, TIR->ty, TIR->tableauutile, &TIR->degre, donjon);


    TIR->letirdemander = false;
    TIR->DepartBalle[TIR->tableauutile] = RUNNING;
    TIR->i[TIR->tableauutile] = 0;
    TIR->tableauutile++;
    if (TIR->tableauutile == NBcailloux)
	{
		TIR->tableauutile = 0;
	}
}

void BattleDraw_Projectile(struct TIR *TIR, struct DONJON *donjon)
{
    int index;
    for(index = 0 ; index < NBcailloux ; index++)
	{
		if (TIR->DepartBalle[index] == RUNNING)
		{
			draw_hook(TIR->balle, &TIR->pballe[index], &donjon->map.pict.pos);
		}
	}
}
