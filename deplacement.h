#ifndef DEPLACEMENTH
#define DEPLACEMENTH

#include "struct.h"
#include "target.h"
#include "mob.h"
#include "creature.h"

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

struct STRAIGHTPATH
{
    struct TARGET target;
    double vecteur_X;
    double vecteur_Y;
    SDL_Point StartPos;
    SDL_Point CurrentPos;
    int speed;
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

void NewStraightPath(struct DONJON *donjon, SDL_Rect target_Pos);

#endif
