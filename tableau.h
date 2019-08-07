#ifndef TABLEAUH
#define TABLEAUH

#include "C:\Users\antoi\Documents\programation\SDL2\SDL_ttf.h"


int TotalTableauInt(int *ptrTableau, int nbcase);
void initPLAN(struct PACKobjet *objet);
void initinventaire(struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme);
void initobjet(struct PACKobjet *objet,struct DIVERSsysteme *systeme,struct DIVERScraft *craft);
void initbouton(struct PACKbouton *bouton,struct DIVERSsysteme *systeme);
void inittemps(struct DIVERStemps *temps,struct DIVERSsysteme *systeme);
void initsystem(struct DIVERSsysteme *systeme);
void initui(struct DIVERSui *ui,struct DIVERSsysteme *systeme);
void initchat(struct DIVERSchat *chat,struct DIVERSsysteme *systeme);
void initcraft(struct DIVERScraft *craft,struct DIVERSsysteme *systeme);
void initrecompense (struct PACKrecompense *recompense,struct DIVERSsysteme *systeme);
void initFORevent(struct typeFORevent *FORevent,struct PACKobjet *objet,struct PACKbouton *bouton,struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme,
				struct DIVERSdeplacement *deplacement,struct DIVERSchat *chat,struct DIVERSui *ui,struct DIVERScraft *craft,
				struct PERSO *perso);
void initonline(struct typeFORthreads *online,struct DIVERSsysteme *systeme);
void initTIR(struct TIR *TIR);

#endif
