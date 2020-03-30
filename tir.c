#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include <math.h>

#include "struct.h"
#include "donjon.h"
#include "systeme.h"
#include "image.h"
#include "perso.h"

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


void COMBATgestionprojectile (struct TIR *TIR, struct DONJON *donjon)
{
	int index, i;
	for (index = 0 ; index < NBcailloux ; index++)
	{
		if (TIR->DepartBalle[index] != UNUSED && TIR->i[index] < PRECISIONcailloux - 1 && TIR->DepartBalle[index] != STOP)
		{//running
			TIR->i[index]++;
			TIR->pballe[index].x = TIR->tx[index][TIR->i[index]];
			TIR->pballe[index].y = TIR->ty[index][TIR->i[index]];

			if (obtenirPixel_hook(donjon->map.calque, (SDL_Point*)&TIR->pballe[index]) !=  255)
            {
                TIR->DepartBalle[index] = STOP;
            }
            TIR->pballe[index].x += donjon->map.pict.pos.x;
			TIR->pballe[index].y += donjon->map.pict.pos.y;
            for( i = 0 ; i < donjon->nombremonstre ; i++)
            {
                if (donjon->mob[i].BarreDeVie->life > 0 && checkdistance(&TIR->pballe[index], &donjon->mob[i].hookpict.pict.pos, donjon->mob[i].hookpict.pict.pos.w/2) == -1)
                {
                    TIR->DepartBalle[index] = UNUSED;
                    donjon->mob[i].vie -=10;
                    donjon->mob[i].BarreDeVie->life -=10;
                }

            }
		}
		else if (TIR->i[index] >= PRECISIONcailloux-1)// fin de course
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
    int cursy = (systeme->pointeur.pos.y + systeme->pointeur.pos.h);

    tirer (systeme->pointeur.pos.x, cursy, x, y, TIR->tx, TIR->ty, TIR->tableauutile, &TIR->degre, donjon);


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
			draw(TIR->balle, &TIR->pballe[index]);
		}
	}
}
