#ifndef DEPLACEMENTH
#define DEPLACEMENTH

int directionperso(struct DIRECTION *direction);
int calculdirectionjoueurs(SDL_Rect posjoueurs,SDL_Rect oldposjoueurs);

void haut (struct PERSO *perso, int* y,struct DIVERSsysteme *systeme, int enmap);
void hautdroite (struct PERSO *perso, int* x, int* y,struct DIVERSsysteme *systeme, int enmap);
void droite (struct PERSO *perso, int* x,struct DIVERSsysteme *systeme, int enmap);
void basdroite (struct PERSO *perso, int* x, int* y,struct DIVERSsysteme *systeme, int enmap);
void bas (struct PERSO *perso, int* y,struct DIVERSsysteme *systeme, int enmap);
void basgauche (struct PERSO *perso, int* x, int* y,struct DIVERSsysteme *systeme, int enmap);
void gauche (struct PERSO *perso, int* x,struct DIVERSsysteme *systeme, int enmap);
void gauchehaut (struct PERSO *perso, int* x, int* y,struct DIVERSsysteme *systeme, int enmap);

#endif
