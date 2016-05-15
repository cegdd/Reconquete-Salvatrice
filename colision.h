#ifndef COLISIONH
#define COLISIONH

#include <stdbool.h>
#include "struct.h"

void deplacementperso_map(struct DIVERSmap *carte,struct PERSO *perso,struct DIRECTION *direction, SDL_Point *origin);
void deplacementperso_combat(struct PERSO *perso,struct DIRECTION *direction);
void move_map(struct PERSO *perso,struct DIRECTION *direction, SDL_Point *origin);
void move_combat(struct PERSO *perso,struct DIRECTION *direction);

int colisionbox(SDL_Rect *A, SDL_Rect *B, bool pointeur);
bool colisionfromage(SDL_Rect *lanceur, SDL_Rect *recepteur, SDL_Rect *curseur, double marge);
double FindAngle(SDL_Rect *A, SDL_Rect *B);

#endif
