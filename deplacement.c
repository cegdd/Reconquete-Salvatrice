#include <SDL.h>

#include "struct.h"
#include "deplacement.h"



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
