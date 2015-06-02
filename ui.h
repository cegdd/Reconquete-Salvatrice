#ifndef UIH
#define UIH

#include <SDL_ttf.h>
#include <stdbool.h>

typedef struct PACKbouton PACKbouton;
typedef struct DIVERSui DIVERSui;
typedef struct DIVERScraft DIVERScraft;
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

void gestionui (struct DIVERSsysteme *systeme, DIVERSui *ui, DIVERScraft *craft, PACKbouton *bouton, DIVERSchat *chat,
			DIVERSinventaire *inventaire, PACKobjet *objet, PERSO *perso, PACKpnj *pnj);
SDL_Texture *fenetredialogue(int x, int y, SDL_Rect* pdialogue, SDL_Rect* ptextedialogue, char texte[],
							int couleur,struct DIVERSsysteme *systeme);
SDL_Texture *DrawSDLText(SDL_Rect* ptextedialogue, char texte[], int color, int ALIGN,struct DIVERSsysteme *systeme);

void testcoin(struct DIVERSsysteme *systeme, DIVERSui *ui, DIVERSchat *chat, DIVERSinventaire *inventaire);
int calculclicinventaire(int *ptrpy, int *ptrpx,struct DIVERSsysteme *systeme);
void afficherCRAFT(DIVERScraft *craft, DIVERSui *ui, PACKbouton *bouton, PACKobjet *objet, DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme);
void afficherINVENTAIRE(DIVERSinventaire *inventaire, DIVERSui *ui, PACKobjet *objet,struct DIVERSsysteme *systeme);
void afficherUI(bool enligne, DIVERSui *ui, PACKbouton *bouton, DIVERStemps *temps, PERSO *perso, DIVERSchat *chat, DIVERSinventaire *inventaire,
                struct DIVERSsysteme *systeme, PACKrecompense *recompense, PACKobjet *objet);
void afficherMAP(DIVERSmap *carte,struct DIVERSsysteme *systeme,DIVERScraft *craft);
void afficherPNJ(PERSO *perso, PACKpnj *pnj,struct DIVERSsysteme *systeme);
void afficherMOB(PACKmonstre *monstre,struct DIVERSsysteme *systeme);
void afficherJOUEURS(PERSO *perso, DIVERSdeplacement *deplacement,struct DIVERSsysteme *systeme, typeFORthreads *online);
void afficherCHAT(DIVERSchat *chat, DIVERSui *ui, int lenbuffer,struct DIVERSsysteme *systeme);
void afficherPOINTEUR(struct DIVERSsysteme *systeme, PACKobjet *objet);
void afficherDETAIL(DIVERSinventaire *inventaire, PACKobjet *objet,struct DIVERSsysteme *systeme, int id);

#endif
