#ifndef JEUXH
#define JEUXH

//####grille de test#####//
#define TESTGRID 1
//###arret des ennemis###//
#define ARRET_MOB 1
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

float combat (float vie, struct RAT *rat, DIVERSsysteme *systeme, PERSO *perso, DIVERSinventaire *inventaire, PACKrecompense *recompense
				, PACKobjet *objet, DIVERSui *ui);

int Hitboxjoueur (SDL_Rect pmob, SDL_Rect pperso, float *ptrvie, PERSO *perso);
int HitboxBalle(typecombat *BTLstr, SDL_Rect pballe[], SDL_Rect *pennemi, int Iennemi);
int HitboxPoing(typecombat *BTLstr, SDL_Rect *pennemi);

void afficherCOMBAT(typecombat *BTLstr, DIVERSsysteme *systeme, PERSO *perso, RAT *rat,
                    DIVERSinventaire *inventaire, PACKobjet *objet);

void COMBATgestionCLICetCOLISION (typecombat *BTLstr, DIVERSui *ui);
void COMBATgestionprojectile (typecombat *BTLstr);
void COMBATgestionDEGAT (typecombat *BTLstr, DIVERSui *ui);
void COMBATgestionENNEMI(typecombat *BTLstr, struct RAT *rat, DIVERSsysteme *systeme);
void COMBATgestionOBJETsol(typecombat *BTLstr, DIVERSsysteme *systeme, PACKrecompense *recompense);

void COMBATanimationPERSO(typecombat *BTLstr);
void COMBATanimationMOB(typecombat *BTLstr);
void COMBATanimationOBJET(typecombat *BTLstr);

void ADDloot(PACKrecompense *recompense, int id, int nombre);

void gestiontir(typecombat *BTLstr);
void gestioncoup(typecombat *BTLstr);

#endif
