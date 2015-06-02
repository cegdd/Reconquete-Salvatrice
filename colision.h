#ifndef COLISIONH
#define COLISIONH

#include <stdbool.h>
#include "main.h"

void deplacementperso(SDL_Surface *mapnb[],struct PERSO *perso,struct DIRECTION *direction,struct DIVERSsysteme *systeme, int *x, int *y, int enmap);

int colisionbox(SDL_Rect *A, SDL_Rect *B, bool pointeur);
bool colisionfromage(SDL_Rect *lanceur, SDL_Rect *recepteur, SDL_Rect *curseur, double marge);
double FindAngle(SDL_Rect *A, SDL_Rect *B);

#endif
