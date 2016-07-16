#ifndef TABLEAUH
#define TABLEAUH

#include <SDL_ttf.h>

#include "main.h"

int TotalTableauInt(int *ptrTableau, int nbcase);
void initPLAN(struct PACKobjet *objet);
void initinventaire(struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme);
void initobjet(struct PACKobjet *objet,struct DIVERSsysteme *systeme,struct DIVERScraft *craft);
void initbouton(struct PACKbouton *bouton,struct DIVERSsysteme *systeme);
void initmonstre(struct PACKmonstre *monstre,struct DIVERSsysteme *systeme);
void initdeplacement(struct DIVERSdeplacement *deplacement,struct DIVERSsysteme *systeme);
void inittemps(struct DIVERStemps *temps,struct DIVERSsysteme *systeme);
void initsystem(struct DIVERSsysteme *systeme);
void initui(struct DIVERSui *ui,struct DIVERSsysteme *systeme);
void initchat(struct DIVERSchat *chat,struct DIVERSsysteme *systeme);
void initcraft(struct DIVERScraft *craft,struct DIVERSsysteme *systeme);
void initperso(struct PERSO *perso,struct DIVERSsysteme *systeme);
void initmap (struct DIVERSmap *carte,struct DIVERSsysteme *systeme);
void initpnj (struct PACKpnj *pnj);
void initrecompense (struct PACKrecompense *recompense,struct DIVERSsysteme *systeme);
void initFORevent(struct typeFORevent *FORevent,struct PACKobjet *objet,struct PACKbouton *bouton,struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme,
				struct DIVERSdeplacement *deplacement,struct DIVERSchat *chat,struct DIVERSui *ui,struct DIVERScraft *craft,
				struct PERSO *perso,struct PACKpnj *pnj);
void initonline(struct typeFORthreads *online,struct DIVERSsysteme *systeme);

#endif
