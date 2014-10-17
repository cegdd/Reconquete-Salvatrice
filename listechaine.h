#ifndef LISTECHAINEH
#define LISTECHAINEH

typedef struct EMPLACEMENT EMPLACEMENT;
typedef struct PACKobjet PACKobjet;
typedef struct CHOSE CHOSE;
typedef struct DIVERSui DIVERSui;

void insertionsac(PACKobjet *packobjet, int id);
void insertionnumero(int oldcase, EMPLACEMENT *sac, int lacase, EMPLACEMENT *objetenmain, CHOSE *objet);
void prendreenmain(EMPLACEMENT lacase, EMPLACEMENT *objetenmain);
void videemplacement(EMPLACEMENT *objetenmain);
int searchIDsac(EMPLACEMENT *sac, int id);
void effacerID(PACKobjet *packobjet, int id);
int searchcaseID(PACKobjet *packobjet, int id);
void equipestuff(PACKobjet *packobjet, DIVERSui *ui, int bodypartui, int id);

#endif
