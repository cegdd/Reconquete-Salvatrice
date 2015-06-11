#ifndef OBJETH
#define OBJETH

void createobjet(int index, char *nom, int empilage, int type, int def, int life, int force, int portee, int regenlife,
                 int bodypart,struct PACKobjet *objet,struct DIVERScraft *craft);
void addcompo(int type, int index, int compoID, int compoNB,struct PACKobjet *objet);
void CreateCraft(int index, int exemplaire, struct PACKobjet *objet, int compo, ...);

#endif
