#ifndef IMAGEH
#define IMAGEH

#include <SDL2/SDL_ttf.h>

typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct TEXTE TEXTE;

SDL_Texture* LoadingImage(char* emplacement, int transparence, DIVERSsysteme *systeme);
Uint32 obtenirPixel(SDL_Surface *surface[], int pixx, int pixy);
Uint32 obtenirPixel2(SDL_Surface *surface, int pixx, int pixy);
void chargement (DIVERSsysteme *systeme);
SDL_Texture* imprime (char s[], int len, int couleur, DIVERSsysteme *systeme, int *lenghtRetour);
void ANIMmort (DIVERSsysteme *systeme);

#endif
