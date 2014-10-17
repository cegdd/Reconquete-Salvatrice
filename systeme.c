#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "main.h"
#include "image.h"
#include "listechaine.h"

typedef struct RAT RAT;
typedef struct PACKobjet PACKobjet;
typedef struct PERSO PERSO;
typedef struct DIVERSsysteme DIVERSsysteme;
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

void checkandrefreshstuff(PERSO *perso, PACKobjet *objet, DIVERSsysteme *systeme, DIVERSui *ui)
{
	int index;

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
    char string[64];
    sprintf(string, "defense : %d", perso->defense);
    SDL_DestroyTexture(perso->tdefense);
    perso->tdefense = imprime (string, systeme->screenw, BLANC, systeme, NULL);

    sprintf(string, "regen vie : +%d/sec", perso->regenlife);
    SDL_DestroyTexture(perso->tregenlife);
    perso->tregenlife = imprime (string, systeme->screenw, BLANC, systeme, NULL);

    sprintf(string, "portee : +%d%%", perso->portee);
    SDL_DestroyTexture(perso->tportee);
    perso->tportee = imprime (string, systeme->screenw, BLANC, systeme, NULL);

    sprintf(string, "force : %d", perso->force);
    SDL_DestroyTexture(perso->tforce);
    perso->tforce = imprime (string, systeme->screenw, BLANC, systeme, NULL);
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

	double difx = (A->x+(A->w/2)) - (B->x+(B->w/2));
	double dify = (A->y+(A->h/2)) - (B->y+(B->h/2));

	if (difx < 0) {difx *= -1;}
	if (dify < 0) {dify *= -1;}

	double resultat = sqrt((difx*difx)+(dify*dify));

	if (resultat <= lenght) {return -1;} // dedans
	return 1; // dehors
}
