#ifndef DEPLACEMENTH
#define DEPLACEMENTH

typedef struct DIVERSdeplacement DIVERSdeplacement;
typedef struct DIRECTION DIRECTION;


int directionperso(DIRECTION *direction);
int calculdirectionjoueurs(SDL_Rect posjoueurs,SDL_Rect oldposjoueurs);

#endif
