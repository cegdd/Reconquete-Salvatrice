#ifndef COLISIONH
#define COLISIONH
#include<stdbool.h>

typedef struct PERSO PERSO;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct DIRECTION DIRECTION;

void deplacementperso(SDL_Surface *mapnb[], PERSO *perso, DIRECTION *direction, DIVERSsysteme *systeme, int *x, int *y, int enmap);

int colisionbox(SDL_Rect *A, SDL_Rect *B, bool pointeur);
bool colisionfromage(SDL_Rect *lanceur, SDL_Rect *recepteur, SDL_Rect *curseur, double marge);
double FindAngle(SDL_Rect *A, SDL_Rect *B);

#endif
