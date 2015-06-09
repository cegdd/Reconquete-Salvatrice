#ifndef SYSTEMEH
#define SYSTEMEH

#include "main.h"

void recompensecombat(struct RAT *rat, int *recompense);
void checkandrefreshstuff(struct PERSO *perso,struct PACKobjet *objet,struct DIVERSsysteme *systeme,struct DIVERSui *ui);
void checkinventaire(struct PACKobjet *objet,struct DIVERSinventaire *inventaire);
int checkdistance(SDL_Rect *A, SDL_Rect *B, int lenght);
int calculoctant(int px, int py, int canonx, int canony, int* difx, int* dify);
int arrondi (float flottant);


#endif
