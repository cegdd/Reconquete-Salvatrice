#ifndef TABLEAUH
#define TABLEAUH

#include <SDL2/SDL_ttf.h>

typedef struct BARREVIE BARREVIE;
typedef struct plan plan;
typedef struct PACKobjet PACKobjet;
typedef struct PACKbouton PACKbouton;
typedef struct PACKmonstre PACKmonstre;
typedef struct DIVERSinventaire DIVERSinventaire;
typedef struct DIVERSdeplacement DIVERSdeplacement;
typedef struct DIVERStemps DIVERStemps;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct DIVERSui DIVERSui;
typedef struct DIVERSchat DIVERSchat;
typedef struct DIVERScraft DIVERScraft;
typedef struct PERSO PERSO;
typedef struct DIVERSmap DIVERSmap;
typedef struct PACKpnj PACKpnj;
typedef struct PACKrecompense PACKrecompense;
typedef struct typeFORevent typeFORevent;
typedef struct typeFORthreads typeFORthreads;

typedef struct typecombat typecombat;
typedef struct DIRECTION DIRECTION;

int TotalTableauInt(int *ptrTableau, int nbcase);
void initPLAN(int type, int index, PACKobjet *objet);
void initinventaire(DIVERSinventaire *inventaire, DIVERSsysteme *systeme);
void deplacementmap(SDL_Rect *pmap,int nombretiles, int x, int y);
void initobjet(PACKobjet *objet, DIVERSsysteme *systeme, DIVERScraft *craft);
void initbouton(PACKbouton *bouton, DIVERSsysteme *systeme);
void initmonstre(PACKmonstre *monstre, DIVERSsysteme *systeme);
void initdeplacement(DIVERSdeplacement *deplacement, DIVERSsysteme *systeme);
void inittemps(DIVERStemps *temps, DIVERSsysteme *systeme);
void initsystem(DIVERSsysteme *systeme);
void initui(DIVERSui *ui, DIVERSsysteme *systeme);
void initchat(DIVERSchat *chat, DIVERSsysteme *systeme);
void initcraft(DIVERScraft *craft, DIVERSsysteme *systeme);
void initperso(PERSO *perso, DIVERSsysteme *systeme);
void initmap (DIVERSmap *carte, DIVERSsysteme *systeme, PERSO *perso);
void initpnj (PACKpnj *pnj);
void initrecompense (PACKrecompense *recompense, DIVERSsysteme *systeme);
void initFORevent(typeFORevent *FORevent, PACKobjet *objet, PACKbouton *bouton, DIVERSinventaire *inventaire, DIVERSsysteme *systeme,
				DIVERSdeplacement *deplacement, DIVERSchat *chat, DIVERSui *ui, DIVERScraft *craft, PACKmonstre *monstre,
				PERSO *perso, PACKpnj *pnj);
void initonline(typeFORthreads *online, DIVERSsysteme *systeme);

void initcombatstore(typecombat *BTLstr, DIVERSsysteme *systeme, DIRECTION *direction, bool arcademode);

#endif
