#include "C:\Users\antoi\Documents\programation\SDL2\SDL.h"

#include <math.h>

#include "struct.h"
#include "deplacement.h"
#include "mob.h"
#include "target.h"
#include "perso.h"
#include "creature.h"

void initdeplacement(struct DIVERSdeplacement *deplacement,struct DIVERSsysteme *systeme)
{
	int index;

	for (index = 0 ; index < MAX_JOUEURS ; index++)
	{
		deplacement->directionjoueurs[index] = 0;
	}
	deplacement->direction.bas = 0;
	deplacement->direction.haut = 0;
	deplacement->direction.droite = 0;
	deplacement->direction.gauche = 0;
	deplacement->direction.direction = 4;
	deplacement->direction.olddirection = 0;
	deplacement->persobouge = 0;
	deplacement->indexanimperso = 0;
}


void haut (int* y)
{
        *y = *y - 6;
}
void hautdroite (int* x, int* y)
{
        *y = *y - 5;
        *x = *x - 5;
}
void droite (int* x)
{
        *x = *x - 6;
}
void basdroite (int* x, int* y)
{
            *y = *y + 5;
            *x = *x - 5;
}
void bas (int* y)
{
        *y = *y + 6;
}
void basgauche (int* x, int* y)
{
        *y = *y + 5;
        *x = *x + 5;
}
void gauche (int* x)
{
            *x = *x + 6;
}
void gauchehaut (int* x, int* y)
{
        *y = *y - 5;
        *x = *x + 5;
}

void NewStraightPath(struct DONJON *donjon, SDL_Rect target_Pos)
{
    double dist;

    donjon->mob->straightpath = malloc (sizeof(struct STRAIGHTPATH));
    NewTarget(&donjon->mob->straightpath->target, target_Pos);
    donjon->mob->straightpath->StartPos.x =     donjon->mob->hookpict.translation.x;
    donjon->mob->straightpath->StartPos.y =     donjon->mob->hookpict.translation.y;
    donjon->mob->straightpath->CurrentPos.x =   donjon->mob->straightpath->StartPos.x;
    donjon->mob->straightpath->CurrentPos.y =   donjon->mob->straightpath->StartPos.y;
    donjon->mob->straightpath->speed =          donjon->creature[donjon->mob->ID].vitesse;
    donjon->mob->straightpath->vecteur_X =      donjon->mob->straightpath->target.pos.x - donjon->map.pict.pos.x -
                                                donjon->mob->hookpict.translation.x - donjon->map.pict.pos.x;
    donjon->mob->straightpath->vecteur_Y =      donjon->mob->straightpath->target.pos.y - donjon->map.pict.pos.y -
                                                donjon->mob->hookpict.translation.y - donjon->map.pict.pos.y;

    dist = pow(donjon->mob->straightpath->vecteur_X, 2)+ pow(donjon->mob->straightpath->vecteur_Y, 2);
    dist = sqrt(dist);

    donjon->mob->straightpath->vecteur_X /= dist;
    donjon->mob->straightpath->vecteur_Y /= dist;
}

