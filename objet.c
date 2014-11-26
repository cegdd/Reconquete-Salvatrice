#include "main.h"
#include <stdio.h>

typedef struct PACKobjet PACKobjet;
typedef struct DIVERSsysteme DIVERSsysteme;

void createobjet(int index, char *nom, int empilage, int type, int def, int life, int force, int portee, int regenlife,
                 int bodypart, PACKobjet *objet)
{
    sprintf(objet->objet[index].nom, "%s\n",nom);
	objet->objet[index].empilage = empilage;
	objet->objet[index].type = type;
	objet->objet[index].def = def;
	objet->objet[index].life = life;
	objet->objet[index].force = force;
	objet->objet[index].portee = portee;
	objet->objet[index].regenlife = regenlife;
	objet->objet[index].bodypart = bodypart;
}

void addcompo(int type, int index, int compoID, int compoNB, PACKobjet *objet)
{
    objet->PLANstuff[type][index].compodifferente++;
    objet->PLANstuff[type][index].compoID       [objet->PLANstuff[type][index].compodifferente - 1] = compoID;
	objet->PLANstuff[type][index].compoNB       [objet->PLANstuff[type][index].compodifferente - 1] = compoNB;
	objet->PLANstuff[type][index].compodispo    [objet->PLANstuff[type][index].compodifferente - 1] = false;
}
