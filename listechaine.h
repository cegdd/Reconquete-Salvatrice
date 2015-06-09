#ifndef LISTECHAINEH
#define LISTECHAINEH

void insertionsac(struct PACKobjet *packobjet, int id);
void insertionnumero(int oldcase,struct EMPLACEMENT *sac, int lacase,struct EMPLACEMENT *objetenmain,struct CHOSE *objet);
void prendreenmain(struct EMPLACEMENT lacase,struct EMPLACEMENT *objetenmain);
void videemplacement(struct EMPLACEMENT *objetenmain);
int searchIDsac(struct EMPLACEMENT *sac, int id);
void effacerID(struct PACKobjet *packobjet, int id);
int searchcaseID(struct PACKobjet *packobjet, int id);
void equipestuff(struct PACKobjet *packobjet,struct DIVERSui *ui, int bodypartui, int id);

#endif
