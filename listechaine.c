#include <stdlib.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "listechaine.h"


typedef struct EMPLACEMENT EMPLACEMENT;
typedef struct CHOSE CHOSE;
typedef struct PACKobjet PACKobjet;


void insertionsac(PACKobjet *packobjet, int id)
{
	int retoursearch = searchcaseID(packobjet, id);
	if (retoursearch != -1)
	{
		packobjet->sac1[retoursearch].NBobjet++;
	}
	else
	{
		int index = 0, stop = 0;
		while (index < TAILLESAC && stop == 0)
		{
			if (packobjet->sac1[index].IDobjet == -1)
			{
				packobjet->sac1[index].IDobjet = id;
				packobjet->sac1[index].NBobjet = 1;
				stop = 1;
			}
				index++;
		}
	}
}

void insertionnumero(int oldcase, EMPLACEMENT *sac, int lacase, EMPLACEMENT *objetenmain, CHOSE *objet)
{
	//si le m�me objet est d�j� pr�sent a cet emplacement
	if (sac[lacase].NBobjet > 0 && sac[lacase].IDobjet == objetenmain->IDobjet && sac[lacase].NBobjet < objet[objetenmain->IDobjet].empilage)
	{
		if (sac[lacase].NBobjet + objetenmain->NBobjet <= objet[objetenmain->IDobjet].empilage)
		{
			sac[lacase].NBobjet = sac[lacase].NBobjet + objetenmain->NBobjet;
			videemplacement(objetenmain);
		}
		else
		{
			int dif = objet[objetenmain->IDobjet].empilage - sac[lacase].NBobjet;
			sac[lacase].NBobjet += dif;
			objetenmain->NBobjet = objetenmain->NBobjet - dif;
		}
	}
	//sinon si un objet diff�rent est d�j� pr�sent a cet emplcement
	else if (sac[lacase].NBobjet > 0 && objetenmain->NBobjet > 0)
	{
		if (oldcase != -1)
		{
			insertionnumero(-1, sac, oldcase, &sac[lacase], objet);
		}
		sac[lacase].IDobjet = objetenmain->IDobjet;
		sac[lacase].NBobjet = sac[lacase].NBobjet + objetenmain->NBobjet;
		videemplacement(objetenmain);
	}
	else if (objetenmain->NBobjet > 0)
	{
		sac[lacase].IDobjet = objetenmain->IDobjet;
		sac[lacase].NBobjet = objetenmain->NBobjet;
		videemplacement(objetenmain);
	}
}

void prendreenmain(EMPLACEMENT lacase, EMPLACEMENT *objetenmain)
{
	if (objetenmain->NBobjet == 0)
	{
		objetenmain->IDobjet = lacase.IDobjet;
		objetenmain->NBobjet = lacase.NBobjet;
		if (lacase.NBobjet <= 0)
		{
			objetenmain->NBobjet = 1;
		}
	}
}

void videemplacement(EMPLACEMENT *emplacement)
{
	emplacement->IDobjet = -1;
	emplacement->NBobjet = 0;
}

int searchIDsac(EMPLACEMENT *sac, int id)
{
	register int index, resultat = 0;
	for (index = 0 ; index < TAILLESAC ; index++)
	{
		if (sac[index].IDobjet == id)
		{
			resultat += sac[index].NBobjet;
		}
	}
	return resultat;
}

void effacerID(PACKobjet *packobjet, int id)
{
	int index;
	for (index = 0 ; index < TAILLESAC ; index++)
	{
		if (packobjet->sac1[index].IDobjet == id)
		{
			packobjet->sac1[index].NBobjet--;

			if (packobjet->sac1[index].NBobjet <= 0)
			{
				packobjet->sac1[index].IDobjet = -1;
			}

			index = TAILLESAC;
		}
	}
}

int searchcaseID(PACKobjet *packobjet, int id)
{
	int index;
	for (index = 0 ; index < TAILLESAC ; index++)
	{
		if (packobjet->sac1[index].IDobjet == id && packobjet->sac1[index].NBobjet < packobjet->objet[id].empilage)
		{
			return index;
		}
	}
	return -1;
}

void equipestuff(PACKobjet *objet, DIVERSui *ui, int bodypartui,int id)
{
	int bodypart = objet->objet[id].bodypart;

	if (objet->objet[id].type == 1)
	{
		if (bodypart == bodypartui)
		{
			ui->casestuff[bodypart].IDobjet = id;
		}
	}
}
