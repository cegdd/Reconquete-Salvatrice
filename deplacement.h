#ifndef DEPLACEMENTH
#define DEPLACEMENTH

int directionperso(struct DIRECTION *direction);
int calculdirectionjoueurs(SDL_Rect posjoueurs,SDL_Rect oldposjoueurs);

void haut           (int* y);
void hautdroite     (int* x, int* y);
void droite         (int* x);
void basdroite      (int* x, int* y);
void bas            (int* y);
void basgauche      (int* x, int* y);
void gauche         (int* x);
void gauchehaut     (int* x, int* y);

#endif
