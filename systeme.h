#ifndef SYSTEMEH
#define SYSTEMEH

typedef struct RAT RAT;

void recompensecombat(RAT *rat, int *recompense);
void checkandrefreshstuff(struct PERSO *perso, struct PACKobjet *objet, struct DIVERSsysteme *systeme, struct DIVERSui *ui);
void checkinventaire( struct PACKobjet *objet, struct DIVERSinventaire *inventaire);
int checkdistance(SDL_Rect *A, SDL_Rect *B, int lenght);

#endif
