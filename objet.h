#ifndef OBJETH
#define OBJETH

typedef struct PACKobjet PACKobjet;
typedef struct DIVERScraft DIVERScraft;
typedef struct DIVERSsysteme DIVERSsysteme;

void createobjet(int index, char *nom, int empilage, int type, int def, int life, int force, int portee, int regenlife,
                 int bodypart, PACKobjet *objet, DIVERScraft *craft);
void addcompo(int type, int index, int compoID, int compoNB, PACKobjet *objet);

#endif
