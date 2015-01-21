#ifndef UIH
#define UIH

#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct PACKbouton PACKbouton;
typedef struct DIVERSui DIVERSui;
typedef struct DIVERScraft DIVERScraft;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct DIVERSchat DIVERSchat;
typedef struct DIVERSinventaire DIVERSinventaire;
typedef struct PACKobjet PACKobjet;
typedef struct PACKmonstre PACKmonstre;
typedef struct DIVERStemps DIVERStemps;
typedef struct PERSO PERSO;
typedef struct PACKrecompense PACKrecompense;
typedef struct DIVERSmap DIVERSmap;
typedef struct PACKpnj PACKpnj;
typedef struct DIVERSdeplacement DIVERSdeplacement;
typedef struct typeFORthreads typeFORthreads;

void gestionui (DIVERSsysteme *systeme, DIVERSui *ui, DIVERScraft *craft, PACKbouton *bouton, DIVERSchat *chat,
			DIVERSinventaire *inventaire, PACKobjet *objet, PERSO *perso, PACKpnj *pnj);
SDL_Texture *fenetredialogue(int x, int y, SDL_Rect* pdialogue, SDL_Rect* ptextedialogue, char texte[],
							int couleur, DIVERSsysteme *systeme);
SDL_Texture *DrawText(SDL_Rect* ptextedialogue, char texte[], int color, DIVERSsysteme *systeme);

void testcoin(DIVERSsysteme *systeme, DIVERSui *ui, DIVERSchat *chat, DIVERSinventaire *inventaire);
int calculclicinventaire(int *ptrpy, int *ptrpx, DIVERSsysteme *systeme);
void afficherCRAFT(DIVERScraft *craft, DIVERSui *ui, PACKbouton *bouton, PACKobjet *objet, DIVERSinventaire *inventaire, DIVERSsysteme *systeme);
void afficherINVENTAIRE(DIVERSinventaire *inventaire, DIVERSui *ui, PACKobjet *objet, DIVERSsysteme *systeme);
void afficherUI(bool enligne, DIVERSui *ui, PACKbouton *bouton, DIVERStemps *temps, PERSO *perso, DIVERSchat *chat, DIVERSinventaire *inventaire,
                DIVERSsysteme *systeme, PACKrecompense *recompense, PACKobjet *objet);
void afficherMAP(DIVERSmap *carte, DIVERSsysteme *systeme,DIVERScraft *craft);
void afficherPNJ(PERSO *perso, PACKpnj *pnj, DIVERSsysteme *systeme);
void afficherMOB(PACKmonstre *monstre, DIVERSsysteme *systeme);
void afficherJOUEURS(PERSO *perso, DIVERSdeplacement *deplacement, DIVERSsysteme *systeme, typeFORthreads *online);
void afficherCHAT(DIVERSchat *chat, DIVERSui *ui, int lenbuffer, DIVERSsysteme *systeme);
void afficherPOINTEUR(DIVERSsysteme *systeme, PACKobjet *objet);
void afficherDETAIL(DIVERSinventaire *inventaire, PACKobjet *objet, DIVERSsysteme *systeme, int id);

#endif
