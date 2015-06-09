#ifndef JEUXH
#define JEUXH

#include <stdbool.h>
#include <SDL.h>

#include "main.h"

/*####grille de test#####*/
#define TESTGRID 0
/*###arret des ennemis###*/
#define ARRET_MOB 0
/*#######################*/


float combat (float vie,struct PACKmonstre *monstre,struct DIVERSsysteme *systeme,struct PERSO *perso,
              struct PACKrecompense *recompense,struct PACKobjet *objet,
              struct DIVERSui *ui, bool arcademode);
void Hitboxjoueur (struct typecombat *BTLstr,struct PERSO *perso, int id);

void afficherCOMBAT(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct PERSO *perso,
                    struct DIVERSui *ui, struct PACKobjet *objet, bool arcademode);

void COMBATgestionCLICetCOLISION (struct typecombat *BTLstr,struct DIVERSui *ui);
void COMBATgestionDEGAT (struct typecombat *BTLstr,struct DIVERSui *ui);
void COMBATgestionENNEMI(struct typecombat *BTLstr, struct RAT *rat,struct DIVERSsysteme *systeme);
void COMBATgestionOBJETsol(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct PACKrecompense *recompense,struct PERSO *perso);

void COMBATanimationPERSO(struct typecombat *BTLstr);
void COMBATanimationMOB(struct typecombat *BTLstr);
void COMBATanimationOBJET(struct typecombat *BTLstr);

void ADDloot(struct PACKrecompense *recompense, int id, int nombre);
int FindCreatureMemoryArea(struct typecombat *BTLstr);
void SyncData(struct typecombat *BTLstr,struct PERSO *perso);
int CalculerBarreDeVie(int VieDeBase, int VieActuelle, int width);
void JoueurToucher(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct PERSO *perso,struct DIVERSui *ui, int id);
void DrawDeathDisplay(struct typecombat *BTLstr,struct DIVERSsysteme *systeme, SDL_Texture *texture[], SDL_Rect position[], int ret);
int PositionOfDeathDisplay(SDL_Texture *texture[], SDL_Rect position[], char score[][20],
                            struct DIVERSsysteme *systeme);
void Hit_Creature(int index,struct typecombat *BTLstr);
int FindCreatureEngaged(struct PACKmonstre *monstre);
int FindCreatureID(struct PACKmonstre *monstre, int ID);
void JoueurMort(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct DIVERSui *ui,struct PERSO *perso,
				struct PACKobjet *objet, bool arcademode);

#endif
