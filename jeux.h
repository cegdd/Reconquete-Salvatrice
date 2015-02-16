#ifndef JEUXH
#define JEUXH

#include <stdbool.h>
#include <SDL2/SDL.h>

//####grille de test#####//
#define TESTGRID 0
//###arret des ennemis###//
#define ARRET_MOB 0
//#######################//



typedef struct DIRECTION DIRECTION;
typedef struct RAT RAT;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct PERSO PERSO;
typedef struct typecombat typecombat;
typedef struct DIVERSinventaire DIVERSinventaire;
typedef struct PACKrecompense PACKrecompense;
typedef struct PACKobjet PACKobjet;
typedef struct DIVERSui DIVERSui;
typedef struct PACKmonstre PACKmonstre;

float combat (float vie, PACKmonstre *monstre, DIVERSsysteme *systeme, PERSO *perso, DIVERSinventaire *inventaire, PACKrecompense *recompense
				, PACKobjet *objet, DIVERSui *ui, bool arcademode);
void Hitboxjoueur (typecombat *BTLstr, PERSO *perso, int id);

void afficherCOMBAT(typecombat *BTLstr, DIVERSsysteme *systeme, PERSO *perso, RAT *rat,
                    DIVERSinventaire *inventaire, PACKobjet *objet, bool arcademode);

void COMBATgestionCLICetCOLISION (typecombat *BTLstr, DIVERSui *ui);
void COMBATgestionDEGAT (typecombat *BTLstr, DIVERSui *ui);
void COMBATgestionENNEMI(typecombat *BTLstr, struct RAT *rat, DIVERSsysteme *systeme);
void COMBATgestionOBJETsol(typecombat *BTLstr, DIVERSsysteme *systeme, PACKrecompense *recompense, bool arcademode,
							DIVERSui *ui, PERSO *perso);
							
void COMBATanimationPERSO(typecombat *BTLstr);
void COMBATanimationMOB(typecombat *BTLstr);
void COMBATanimationOBJET(typecombat *BTLstr);

void ADDloot(PACKrecompense *recompense, int id, int nombre);
int FindCreatureMemoryArea(typecombat *BTLstr);
void SyncData(typecombat *BTLstr, PERSO *perso);
int CalculerBarreDeVie(int VieDeBase, int VieActuelle, int width);
void JoueurToucher(typecombat *BTLstr, DIVERSsysteme *systeme, PERSO *perso, DIVERSui *ui, int id);
int JoueurMort(typecombat *BTLstr, DIVERSsysteme *systeme, DIVERSui *ui);

int PositionOfDeathDisplay(SDL_Texture *texture[], SDL_Rect position[], char score[][20],
							typecombat *BTLstr, DIVERSsysteme *systeme);
void Hit_Creature(int index, typecombat *BTLstr);
int FindCreatureEngaged( PACKmonstre *monstre);
int FindCreatureID( PACKmonstre *monstre, int ID);

#endif
