#ifndef LISTECHAINEH
#define LISTECHAINEH

typedef struct EMPLACEMENT EMPLACEMENT;
typedef struct CHOSE CHOSE;

void insertionsac(struct PACKobjet *packobjet, int id);
void insertionnumero(int oldcase, EMPLACEMENT *sac, int lacase, EMPLACEMENT *objetenmain, CHOSE *objet);
void prendreenmain(EMPLACEMENT lacase, EMPLACEMENT *objetenmain);
void videemplacement(EMPLACEMENT *objetenmain);
int searchIDsac(EMPLACEMENT *sac, int id);
void effacerID(struct PACKobjet *packobjet, int id);
int searchcaseID(struct PACKobjet *packobjet, int id);
void equipestuff(struct PACKobjet *packobjet,struct DIVERSui *ui, int bodypartui, int id);

#endif
