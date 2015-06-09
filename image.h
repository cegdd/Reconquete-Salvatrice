#ifndef IMAGEH
#define IMAGEH

#include <SDL_ttf.h>
#include "main.h"

SDL_Texture* LoadingImage(char* emplacement, int transparence,struct DIVERSsysteme *systeme);
Uint32 obtenirPixel(SDL_Surface *surface[], int pixx, int pixy);
Uint32 obtenirPixel2(SDL_Surface *surface, int pixx, int pixy);
void chargement (struct DIVERSsysteme *systeme);
SDL_Texture* imprime (char s[], int len, int couleur,struct DIVERSsysteme *systeme, int *LenghtReturn, int *HighReturn);
void ANIMmort (struct DIVERSsysteme *systeme);
void InitPicture(struct Picture *picture, char* emplacement, int x, int y, int w, int h, int transparance, struct DIVERSsysteme *systeme);

#endif
