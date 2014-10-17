#ifndef SYSTEMEH
#define SYSTEMEH

typedef struct RAT RAT;
typedef struct DIVERSui DIVERSui;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct PACKobjet PACKobjet;
typedef struct PERSO PERSO;
typedef struct DIVERSinventaire DIVERSinventaire;

void recompensecombat(RAT *rat, int *recompense);
void checkandrefreshstuff( PERSO *perso, PACKobjet *objet, DIVERSsysteme *systeme, DIVERSui *ui);
void checkinventaire( PACKobjet *objet, DIVERSinventaire *inventaire);
int checkdistance(SDL_Rect *A, SDL_Rect *B, int lenght);

#endif
