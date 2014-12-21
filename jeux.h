#ifndef JEUXH
#define JEUXH

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

float combat (float vie, struct RAT *rat, DIVERSsysteme *systeme, PERSO *perso, DIVERSinventaire *inventaire, PACKrecompense *recompense
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
void ajoutermonstre(typecombat *BTLstr, DIVERSsysteme *systeme);
void SyncData(typecombat *BTLstr, PERSO *perso);
int CalculerBarreDeVie(int VieDeBase, int VieActuelle, int width);
void JoueurToucher(typecombat *BTLstr, DIVERSsysteme *systeme, PERSO *perso, DIVERSui *ui, int id);

#endif
