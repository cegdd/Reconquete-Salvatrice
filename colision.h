#ifndef COLISIONH
#define COLISIONH
#include<stdbool.h>

typedef struct PERSO PERSO;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct DIRECTION DIRECTION;

void deplacementperso(SDL_Surface *mapnb[], PERSO *perso, DIRECTION *direction, DIVERSsysteme *systeme, int *x, int *y, int enmap);

void haut (PERSO *perso, int* y, DIVERSsysteme *systeme, int enmap);
void hautdroite (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap);
void droite (PERSO *perso, int* x, DIVERSsysteme *systeme, int enmap);
void basdroite (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap);
void bas (PERSO *perso, int* y, DIVERSsysteme *systeme, int enmap);
void basgauche (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap);
void gauche (PERSO *perso, int* x, DIVERSsysteme *systeme, int enmap);
void gauchehaut (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap);
int colisionbox(SDL_Rect *A, SDL_Rect *B, int pointeur);
bool colisionfromage(SDL_Rect *lanceur, SDL_Rect *recepteur, SDL_Rect *curseur, double marge);
double FindAngle(SDL_Rect *A, SDL_Rect *B);

#endif
