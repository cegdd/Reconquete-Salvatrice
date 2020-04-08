#ifndef DEPLACEMENTH
#define DEPLACEMENTH

#include "struct.h"

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
