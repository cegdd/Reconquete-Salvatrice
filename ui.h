#ifndef UIH
#define UIH

#include "SDL2/SDL_ttf.h"
#include <stdbool.h>

#include "struct.h"

void gestionui (struct DIVERSsysteme *systeme,struct DIVERSui *ui,struct DIVERScraft *craft,struct PACKbouton *bouton,
                struct DIVERSchat *chat,struct DIVERSinventaire *inventaire,struct PACKobjet *objet,struct PERSO *perso);
GLuint fenetredialogue(int x, int y, SDL_Rect* pdialogue, SDL_Rect* ptextedialogue, char texte[], SDL_Color *couleur,struct DIVERSsysteme *systeme);

int calculclicinventaire(SDL_Rect pointeur ,struct DIVERSsysteme *systeme);
void afficherCRAFT(struct DIVERScraft *craft,struct DIVERSui *ui,struct PACKbouton *bouton,struct PACKobjet *objet,
                   struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme);
void afficherINVENTAIRE(struct DIVERSinventaire *inventaire,struct DIVERSui *ui,struct PACKobjet *objet,struct DIVERSsysteme *systeme);
void afficherUI(bool enligne,struct DIVERSui *ui,struct PACKbouton *bouton,struct DIVERStemps *temps,struct PERSO *perso,
                struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme,
                struct PACKrecompense *recompense,struct PACKobjet *objet);
void afficherJOUEURS(struct PERSO *perso,struct DIVERSdeplacement *deplacement,struct DIVERSsysteme *systeme,
                     struct typeFORthreads *online, struct DIVERStemps *temps);
void afficherCHAT(struct DIVERSchat *chat,struct DIVERSui *ui, int lenbuffer,struct DIVERSsysteme *systeme);
void afficherPOINTEUR(struct DIVERSsysteme *systeme,struct PACKobjet *objet);
void afficherDETAIL(struct DIVERSinventaire *inventaire,struct PACKobjet *objet,struct DIVERSsysteme *systeme, int id);

#endif
