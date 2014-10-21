#ifndef DEPLACEMENTH
#define DEPLACEMENTH

typedef struct DIVERSdeplacement DIVERSdeplacement;
typedef struct DIRECTION DIRECTION;


int directionperso(DIRECTION *direction);
int calculdirectionjoueurs(SDL_Rect posjoueurs,SDL_Rect oldposjoueurs);

void haut (PERSO *perso, int* y, DIVERSsysteme *systeme, int enmap);
void hautdroite (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap);
void droite (PERSO *perso, int* x, DIVERSsysteme *systeme, int enmap);
void basdroite (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap);
void bas (PERSO *perso, int* y, DIVERSsysteme *systeme, int enmap);
void basgauche (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap);
void gauche (PERSO *perso, int* x, DIVERSsysteme *systeme, int enmap);
void gauchehaut (PERSO *perso, int* x, int* y, DIVERSsysteme *systeme, int enmap);

#endif
