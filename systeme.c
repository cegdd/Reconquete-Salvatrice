#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "main.h"
#include "image.h"
#include "listechaine.h"

typedef struct RAT RAT;
typedef struct PACKobjet PACKobjet;
typedef struct PERSO PERSO;
typedef struct DIVERSinventaire DIVERSinventaire;

void recompensecombat(struct RAT *rat, int *recompense)
{
    int lerand, index, index2;

    for (index = 0 ; index < rat->nombreloot ; index++)
    {
        for(index2 = 0 ; index2 < rat->maxloot[index] ; index2++)
        {
            lerand = rand()%100;
            lerand = lerand - (20);
            if (lerand <= rat->prctloot[index])
            {
                recompense[index] += 1;
            }
        }
    }
}

void checkandrefreshstuff(PERSO *perso, PACKobjet *objet,struct DIVERSsysteme *systeme,struct DIVERSui *ui)
{
	int index;
	char string[64];

    perso->defense = 0;
    perso->lifemax = 100;
    perso->regenlife = 0;
    perso->portee = 0;
    perso->force = 0;

    for (index = 0 ; index < 7 ; index++)
    {
    	if(ui->casestuff[index].IDobjet != -1)
		{
			perso->defense += objet->objet[ui->casestuff[index].IDobjet].def;
            perso->lifemax += objet->objet[ui->casestuff[index].IDobjet].life;
            perso->regenlife += objet->objet[ui->casestuff[index].IDobjet].regenlife;
            perso->force += objet->objet[ui->casestuff[index].IDobjet].force;
            perso->portee += objet->objet[ui->casestuff[index].IDobjet].portee;
		}
    }

    if (perso->life > perso->lifemax)
	{
		perso->life = perso->lifemax;
	}

    sprintf(string, "defense : %d", (int)perso->defense);
    SDL_DestroyTexture(perso->tdefense);
    perso->tdefense = imprime (string, systeme->screenw, BLANC, systeme, NULL, NULL);

    sprintf(string, "regen vie : +%d/sec", perso->regenlife);
    SDL_DestroyTexture(perso->tregenlife);
    perso->tregenlife = imprime (string, systeme->screenw, BLANC, systeme, NULL, NULL);

    sprintf(string, "portee : +%d%%", perso->portee);
    SDL_DestroyTexture(perso->tportee);
    perso->tportee = imprime (string, systeme->screenw, BLANC, systeme, NULL, NULL);

    sprintf(string, "force : %d", perso->force);
    SDL_DestroyTexture(perso->tforce);
    perso->tforce = imprime (string, systeme->screenw, BLANC, systeme, NULL, NULL);
}

void checkinventaire(PACKobjet *objet, DIVERSinventaire *inventaire)
{
	int index;
	for (index = 0 ; index < 128 ; index++)
	{
		inventaire->totalID[index] = 0;
	}
	 for (index = 0 ; index < TAILLESAC; index++)
            {
            	if (objet->sac1[index].IDobjet != -1)
				{
					if (objet->objet[objet->sac1[index].IDobjet].type == 1)
					{
					}
					else
					{
						inventaire->totalID[objet->sac1[index].IDobjet] += objet->sac1[index].NBobjet;
					}
				}

            }
}

int checkdistance(SDL_Rect *A, SDL_Rect *B, int lenght)
{
    double resultat;
	double difx = (A->x+(A->w/2)) - (B->x+(B->w/2));
	double dify = (A->y+(A->h/2)) - (B->y+(B->h/2));

	if (difx < 0) {difx *= -1;}
	if (dify < 0) {dify *= -1;}

	resultat = sqrt((difx*difx)+(dify*dify));

	if (resultat <= lenght) {return -1;} /* dedans*/
	return 1; /* dehors*/
}

int arrondi (float flottant)
{
    return (int)(flottant+0.5);
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
