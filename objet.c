#include <stdio.h>
#include <stdarg.h>

#include "main.h"

void createobjet(int index, char *nom, int empilage, int type, int def, int life, int force, int portee, int regenlife,
                 int bodypart,struct PACKobjet *objet,struct DIVERScraft *craft)
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
	if (bodypart != -1) {craft->planparonglets[bodypart]++;}
}

void addcompo(int type, int index, int compoID, int compoNB,struct PACKobjet *objet)
{
    objet->PLANstuff[type][index].compoID       [objet->PLANstuff[type][index].compodifferente] = compoID;
	objet->PLANstuff[type][index].compoNB       [objet->PLANstuff[type][index].compodifferente] = compoNB;
	objet->PLANstuff[type][index].compodispo    [objet->PLANstuff[type][index].compodifferente] = false;

	objet->PLANstuff[type][index].compodifferente++;
}

void CreateCraft(int index, int exemplaire, struct PACKobjet *objet, int compo, ...)
{
    int type = objet->objet[index].bodypart;
    int i;

    va_list ap;
    va_start(ap, compo);

    objet->PLANstuff[type][objet->craftnumber[type]].resultatID = index;
	objet->PLANstuff[type][objet->craftnumber[type]].resultatNB = exemplaire;
    for(i = 0 ; i < compo ; i++)
    {
        int id =  va_arg(ap, int);
        int nb =  va_arg(ap, int);

        addcompo(type, objet->craftnumber[type], id, nb, objet);
    }

    objet->craftnumber[type]++;
}
