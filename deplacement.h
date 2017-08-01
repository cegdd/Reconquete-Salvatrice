#ifndef DEPLACEMENTH
#define DEPLACEMENTH

#include "struct.h"

struct DIRECTION
{
	int bas;
    int haut;
    int droite;
    int gauche;
    int direction;
    int olddirection;
};

struct DIVERSdeplacement
{
    int directionjoueurs[MAX_JOUEURS];
    struct DIRECTION direction;
    int persobouge;
    int indexanimperso;
    SDL_Rect temp;
};

void initdeplacement(struct DIVERSdeplacement *deplacement,struct DIVERSsysteme *systeme);

void haut           (int* y);
void hautdroite     (int* x, int* y);
void droite         (int* x);
void basdroite      (int* x, int* y);
void bas            (int* y);
void basgauche      (int* x, int* y);
void gauche         (int* x);
void gauchehaut     (int* x, int* y);

#endif
