#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "main.h"
#include "image.h"
#include "objet.h"

typedef struct plan plan;
typedef struct PACKobjet PACKobjet;
typedef struct PACKbouton PACKbouton;
typedef struct PACKmonstre PACKmonstre;
typedef struct PACKpnj PACKpnj;
typedef struct DIVERSinventaire DIVERSinventaire;
typedef struct DIVERSdeplacement DIVERSdeplacement;
typedef struct DIVERStemps DIVERStemps;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct DIVERSui DIVERSui;
typedef struct DIVERSchat DIVERSchat;
typedef struct DIVERScraft DIVERScraft;
typedef struct PERSO PERSO;
typedef struct DIVERSmap DIVERSmap;
typedef struct PACKrecompense PACKrecompense;
typedef struct typeFORevent typeFORevent;
typedef struct typeFORthreads typeFORthreads;


int TotalTableauInt(int *ptrTableau, int nbcase)
{
	int total = 0, i = 0;
	for (i = 0 ; i < nbcase ; i++)
	{
		total = total + ptrTableau[i];
	}
	return total;
}

void initinventaire(DIVERSinventaire *inventaire, DIVERSsysteme *systeme)//									inventaire
{
	int index, rangerx = -1;
	for (index = 0 ; index < TAILLESAC ; index++)
	{
		rangerx++;
		if (rangerx / 24 == 1)
		{
			rangerx = 0;
		}
		inventaire->pcaseinventaire[index].x = rangerx * (systeme->screenw*0.0417);
		inventaire->pcaseinventaire[index].y = ((index / 24) * (systeme->screenw*0.0417)) +(systeme->screenh*0.526);
		inventaire->pcaseinventaire[index].w = systeme->screenw*0.0417;
		inventaire->pcaseinventaire[index].h = systeme->screenw*0.0417;

		inventaire->pnbobjet[index].x = inventaire->pcaseinventaire[index].x + inventaire->pcaseinventaire[0].h*0.7;
		inventaire->pnbobjet[index].y = inventaire->pcaseinventaire[index].y + inventaire->pcaseinventaire[0].h*0.7;
		inventaire->pnbobjet[index].w = inventaire->pcaseinventaire[0].h*0.3;
		inventaire->pnbobjet[index].h = inventaire->pcaseinventaire[0].h*0.3;
	}
	for (index = 0 ; index < 128 ; index++)
	{
		inventaire->totalID[index] = 0;
	}

	inventaire->actif = false;
	inventaire->casedowndroit = -1;
	inventaire->casedowngauche = -1;
	inventaire->caseupgauche = -1;
	inventaire->idsurvoler = -1;
	inventaire->tnbobjet = NULL;
	inventaire->Uiinventaire = LoadingImage	("rs/ui/uiinventaire.png", 0, systeme);
	inventaire->tsacinventaire = LoadingImage	("rs/ui/sac1.png", 0, systeme);
	inventaire->BGinventaire = LoadingImage	("rs/ui/BGinventaire.png", 0, systeme);
	inventaire->tcasesac = LoadingImage		("rs/ui/caseinventaire.png", 0, systeme);
	inventaire->tcasesac2 = LoadingImage		("rs/ui/caseinventaire2.png", 0, systeme);

	char nom[32];
	sprintf(nom, "clic droit : équiper");
	inventaire->taideclicdroit = imprime (nom, systeme->screenw, GRIS, systeme, NULL);
	SDL_QueryTexture(inventaire->taideclicdroit, NULL, NULL, &inventaire->LARGEURaideclicdroit, NULL);

	inventaire->puiinventaire.x = systeme->screenw-50;
	inventaire->puiinventaire.y = systeme->screenh-50;
	inventaire->puiinventaire.w = 50;
	inventaire->puiinventaire.h = 50;

	inventaire->psac.x = 0;
	inventaire->psac.y = systeme->screenh/2;
	inventaire->psac.w = systeme->screenw*0.1;
	inventaire->psac.h = systeme->screenh*0.026;

}

void deplacementmap(SDL_Rect *pmap,int nombretiles, int x, int y)
{
	int index, rangerx = 0;
	pmap[0].x = x;
	pmap[0].y = y;


	for (index = 1 ; index < nombretiles ; index++)
	{
		rangerx++;
		if (rangerx / 4 == 1)
		{
			rangerx = 0;
		}

		pmap[index].x = x + (rangerx * 2500);
		pmap[index].y = y + ((index / 4) * 2500);
	}
}

void initPLAN(int type, int index, PACKobjet *objet)
{
    objet->PLANstuff[type][index].compodifferente = 0;
	objet->PLANstuff[type][index].resultatID = -1;
	objet->PLANstuff[type][index].resultatNB = 0;
}

void initobjet(PACKobjet *objet, DIVERSsysteme *systeme, DIVERScraft *craft)//													objet
{
	char nom[128];
	int index;
	
	for(index = 0 ; index < 10 ; index++) { craft->planparonglets[index] = 0;}

//******************* ARME *************************
	objet->PLANstuff[ARME][0].compodifferente = 0;
	addcompo(ARME, 0, 7, 3, objet);
	addcompo(ARME, 0, 0, 1, objet);
	objet->PLANstuff[ARME][0].resultatID = 3;
	objet->PLANstuff[ARME][0].resultatNB = 1;

	objet->PLANstuff[ARME][1].compodifferente = 0;
	addcompo(ARME, 1, 7, 3, objet);
	addcompo(ARME, 1, 0, 1, objet);
	objet->PLANstuff[ARME][1].resultatID = 10;
	objet->PLANstuff[ARME][1].resultatNB = 1;

	objet->PLANstuff[ARME][2].compodifferente = 0;
	addcompo(ARME, 2, 7, 2, objet);
	addcompo(ARME, 2, 2, 2, objet);
	objet->PLANstuff[ARME][2].resultatID = 12;
	objet->PLANstuff[ARME][2].resultatNB = 1;

	for(index = 3 ; index < 10 ; index++)   {initPLAN(ARME, index, objet);}


//******************* TORSE *************************

	objet->PLANstuff[TORSE][0].compodifferente = 0;
	addcompo(TORSE, 0, 0, 30, objet);
	objet->PLANstuff[TORSE][0].resultatID = 4;
	objet->PLANstuff[TORSE][0].resultatNB = 1;

	for(index = 1 ; index < 10 ; index++)   {initPLAN(TORSE, index, objet);}

//******************* COU *************************

	objet->PLANstuff[COU][0].compodifferente = 0;
    addcompo(COU, 0, 0, 10, objet);
	objet->PLANstuff[COU][0].resultatID = 5;
	objet->PLANstuff[COU][0].resultatNB = 1;

	for(index = 1 ; index < 10 ; index++)   {initPLAN(COU, index, objet);}

//******************* DOS *************************

	objet->PLANstuff[DOS][0].compodifferente = 0;
    addcompo(DOS, 0, 0, 25, objet);
	objet->PLANstuff[DOS][0].resultatID = 6;
	objet->PLANstuff[DOS][0].resultatNB = 1;

	objet->PLANstuff[DOS][1].compodifferente = 0;
    addcompo(DOS, 1, 0, 30, objet);
    addcompo(DOS, 1, 2, 3, objet);
	objet->PLANstuff[DOS][1].resultatID = 11;
	objet->PLANstuff[DOS][1].resultatNB = 1;

	for(index = 2 ; index < 10 ; index++)   {initPLAN(DOS, index, objet);}

//******************* PIED *************************

	objet->PLANstuff[PIED][0].compodifferente = 0;
    addcompo(PIED, 0, 7, 4, objet);
    addcompo(PIED, 0, 0, 5, objet);
	objet->PLANstuff[PIED][0].resultatID = 1;
	objet->PLANstuff[PIED][0].resultatNB = 1;

	for(index = 1 ; index < 10 ; index++)   {initPLAN(PIED, index, objet);}

//******************* TAILLE *************************

	objet->PLANstuff[TAILLE][0].compodifferente = 0;
    addcompo(TAILLE, 0, 0, 13, objet);
    addcompo(TAILLE, 0, 2, 3, objet);
	objet->PLANstuff[TAILLE][0].resultatID = 8;
	objet->PLANstuff[TAILLE][0].resultatNB = 1;

	for(index = 1 ; index < 10 ; index++)   {initPLAN(TAILLE, index, objet);}

//******************* TETE ***********************

	objet->PLANstuff[TETE][0].compodifferente = 0;
    addcompo(TETE, 0, 0, 7, objet);
    addcompo(TETE, 0, 7, 3, objet);
	objet->PLANstuff[TETE][0].resultatID = 9;
	objet->PLANstuff[TETE][0].resultatNB = 1;

	for(index = 1 ; index < 10 ; index++)   {initPLAN(TETE, index, objet);}

    //index * nom * empilage * type * def * life * force * portee * regenlife * bodypart
    createobjet(0, "peau des rats", 99, 0, RESSOURCE, 0, 0, 0, 0, -1, objet,craft);
    createobjet(1, "sandales", 1, EQUIPEMENT, 3, 10, 0, 0, 1, PIED, objet,craft);
    createobjet(2, "silex", 5, RESSOURCE, 0, 0, 0, 0, 0, -1, objet,craft);
    createobjet(3, "lance pierre", 1, EQUIPEMENT, 1, 0, 3, 100, 0, ARME, objet,craft);
    createobjet(4, "toge en peau de rat", 1, EQUIPEMENT, 5, 10, 0, 0, 2, TORSE, objet,craft);
    createobjet(5, "echarpe en peau de rat", 1, EQUIPEMENT, 2, 0, 0, 0, 1, COU, objet,craft);
    createobjet(6, "cape en peau de rat", 1, EQUIPEMENT, 5, 5, 1, 0, 0, DOS, objet,craft);
    createobjet(7, "branche", 5, RESSOURCE, 0, 0, 0, 0, 0, -1, objet,craft);
    createobjet(8, "ceinture", 1, EQUIPEMENT, 5, 0, 5, 0, 1, TAILLE, objet,craft);
    createobjet(9, "coiffe", 1, EQUIPEMENT, 10, 20, 0, 0, 1, TETE, objet,craft);
    createobjet(11, "cape lesté de silex", 1, EQUIPEMENT, 10, 15, 2, 0, 0, DOS, objet,craft);
    createobjet(10, "hachette", 1, EQUIPEMENT, 0, 0, 5, 3, 0, ARME, objet,craft);
    createobjet(12, "baton de chamane", 1, EQUIPEMENT, 0, 20, 0, 4, 4, ARME, objet,craft);

	objet->objetenmain.IDobjet = -1;
	objet->objetenmain.NBobjet = 0;



	for (index = 0 ; index < NOMBREOBJETS ; index++)
	{
		sprintf(nom, "rs/objets/%d#0.png", index);
		objet->objet[index].texture = LoadingImage   (nom, 0, systeme);
		if(objet->objet[index].def != 0)
		{
			sprintf(nom, "défense : %d", objet->objet[index].def);
			objet->objet[index].texturedef = imprime (nom, systeme->screenw, BLANC, systeme, NULL);
			SDL_QueryTexture(objet->objet[index].texturedef, NULL, NULL, &objet->objet[index].LARGEURdef, NULL);
		}
		if(objet->objet[index].life != 0)
		{
			sprintf(nom, "santé : +%d", objet->objet[index].life);
			objet->objet[index].texturelife = imprime (nom, systeme->screenw, BLANC, systeme, NULL);
			SDL_QueryTexture(objet->objet[index].texturelife, NULL, NULL, &objet->objet[index].LARGEURlife, NULL);
		}
		if(objet->objet[index].regenlife != 0)
		{
			sprintf(nom, "régénération : %d/sec", objet->objet[index].regenlife);
			objet->objet[index].textureregenlife = imprime (nom, systeme->screenw, BLANC, systeme, NULL);
			SDL_QueryTexture(objet->objet[index].textureregenlife, NULL, NULL, &objet->objet[index].LARGEURregenlife, NULL);
		}

		if(objet->objet[index].force != 0)
		{
			sprintf(nom, "force : %d", objet->objet[index].force);
			objet->objet[index].textureforce = imprime (nom, systeme->screenw, BLANC, systeme, NULL);
			SDL_QueryTexture(objet->objet[index].textureforce, NULL, NULL, &objet->objet[index].LARGEURforce, NULL);
		}

		if(objet->objet[index].portee != 0)
		{
			sprintf(nom, "portee : +%d%%", objet->objet[index].portee);
			objet->objet[index].textureportee = imprime (nom, systeme->screenw, BLANC, systeme, NULL);
			SDL_QueryTexture(objet->objet[index].textureportee, NULL, NULL, &objet->objet[index].LARGEURportee, NULL);
		}

		sprintf(nom, "%d", objet->objet[index].empilage);
		objet->objet[index].texturenombre = imprime (nom, systeme->screenw, ROUGE, systeme, NULL);

		objet->objet[index].texturenom[0] = NULL;
		objet->objet[index].texturenom[1] = NULL;
		objet->objet[index].texturenom[2] = NULL;

		objet->objet[index].texturenom[0] = imprime (objet->objet[index].nom, systeme->screenw, BLANC, systeme, NULL);
		objet->objet[index].texturenom[1] = imprime (objet->objet[index].nom, systeme->screenw, GRIS, systeme, NULL);
		objet->objet[index].texturenom[2] = imprime (objet->objet[index].nom, systeme->screenw, ROUGE, systeme, NULL);
		SDL_QueryTexture(objet->objet[index].texturenom[0], NULL, NULL, &objet->objet[index].LARGEURnom, NULL);
	}

	for (index = 0 ; index < TAILLESAC ; index++)
	{
		objet->sac1[index].IDobjet = systeme->saveinventaire[0][index];
		objet->sac1[index].NBobjet = systeme->saveinventaire[1][index];
	}
}

void initbouton(PACKbouton *bouton, DIVERSsysteme *systeme)//												bouton
{
	bouton->bcraft[0].normal = LoadingImage	    	("rs/ui/arme.png", 0, systeme);
	bouton->bcraft[0].survoler = LoadingImage	    	("rs/ui/arme1.png", 0, systeme);
	bouton->bcraft[0].cliquer = LoadingImage	    	("rs/ui/arme2.png", 0, systeme);
	bouton->bcraft[1].normal = LoadingImage	    ("rs/ui/torse.png", 0, systeme);
	bouton->bcraft[1].survoler = LoadingImage	    ("rs/ui/torse1.png", 0, systeme);
	bouton->bcraft[1].cliquer = LoadingImage	    ("rs/ui/torse2.png", 0, systeme);
	bouton->bcraft[2].normal = LoadingImage	    		("rs/ui/cou.png", 0, systeme);
	bouton->bcraft[2].survoler = LoadingImage	    	("rs/ui/cou1.png", 0, systeme);
	bouton->bcraft[2].cliquer = LoadingImage	    	("rs/ui/cou2.png", 0, systeme);
	bouton->bcraft[3].normal = LoadingImage	    	("rs/ui/dos.png", 0, systeme);
	bouton->bcraft[3].survoler = LoadingImage	   	("rs/ui/dos1.png", 0, systeme);
	bouton->bcraft[3].cliquer = LoadingImage	    ("rs/ui/dos2.png", 0, systeme);
	bouton->bcraft[4].normal = LoadingImage	    	("rs/ui/pied.png", 0, systeme);
	bouton->bcraft[4].survoler = LoadingImage	    	("rs/ui/pied1.png", 0, systeme);
	bouton->bcraft[4].cliquer = LoadingImage	    	("rs/ui/pied2.png", 0, systeme);
	bouton->bcraft[5].normal = LoadingImage	    ("rs/ui/taille.png", 0, systeme);
	bouton->bcraft[5].survoler = LoadingImage	("rs/ui/taille1.png", 0, systeme);
	bouton->bcraft[5].cliquer = LoadingImage	    ("rs/ui/taille2.png", 0, systeme);
	bouton->bcraft[6].normal = LoadingImage	    	("rs/ui/tete.png", 0, systeme);
	bouton->bcraft[6].survoler = LoadingImage	    	("rs/ui/tete1.png", 0, systeme);
	bouton->bcraft[6].cliquer = LoadingImage	    	("rs/ui/tete2.png", 0, systeme);

	bouton->BoutonQuitter.normal = LoadingImage			("rs/ui/quitter.png", 0, systeme);
	bouton->BoutonQuitter.survoler = LoadingImage		("rs/ui/quitter1.png", 0, systeme);
	bouton->BoutonQuitter.cliquer = LoadingImage			("rs/ui/quitter2.png", 0, systeme);

	bouton->crafter.normal = LoadingImage			("rs/ui/creer.png", 0, systeme);
	bouton->crafter.survoler = LoadingImage		("rs/ui/creer2.png", 0, systeme);
	bouton->crafter.cliquer = LoadingImage			("rs/ui/creer3.png", 0, systeme);

	int index;
	for (index = 0 ; index < 7 ; index++)
	{
		bouton->bcraft[index].position.x = index*(systeme->screenw*0.143);
		bouton->bcraft[index].position.y = systeme->screenh*0.467;
		bouton->bcraft[index].position.w = systeme->screenw*0.143;
		bouton->bcraft[index].position.h = systeme->screenh*0.03;
		bouton->bcraft[index].etat = 0;
	}

	bouton->BoutonQuitter.position.x = systeme->screenw*0.7;
	bouton->BoutonQuitter.position.y = systeme->screenh*0.3;
	bouton->BoutonQuitter.position.w = systeme->screenw*0.04;
	bouton->BoutonQuitter.position.h = bouton->BoutonQuitter.position.w;
	bouton->BoutonQuitter.etat = 0;

	bouton->crafter.position.x = systeme->screenw*0.622;
	bouton->crafter.position.y = systeme->screenh*0.39;
	bouton->crafter.position.w = systeme->screenw*0.11;
	bouton->crafter.position.h = systeme->screenh*0.0651;

	bouton->crafter.etat = 0;
}

void initmonstre(PACKmonstre *monstre, DIVERSsysteme *systeme)//											monstre
{
	int index;

	monstre->rat[0].prctloot[0] = 100; //peau
	monstre->rat[0].maxloot[0] = 1; //peau
	monstre->rat[0].idloot[0] = 0; //peau
	monstre->rat[0].nombreloot = 1;


//rat
	for (index = 0 ; index < 3 ; index++)
	{
		monstre->rat[index].position.w = systeme->screenw*0.0732;
		monstre->rat[index].position.h = systeme->screenh*0.039;

		monstre->rat[index].etat = 0;
		monstre->rat[index].indexanim = 0;
		monstre->rat[index].tempsanim = 0;
		monstre->rat[index].direction = rand()%8;
		sprintf(monstre->rat[index].nom, "rat");

		monstre->rat[index].texture[0] = LoadingImage	("rs/images/mob0.0.png", 0, systeme);
		monstre->rat[index].texture[1] = LoadingImage	("rs/images/mob0.1.png", 0, systeme);
		monstre->rat[index].texture[2] = LoadingImage	("rs/images/mob0.2.png", 0, systeme);
	}
}

void initperso(PERSO *perso, DIVERSsysteme *systeme)//														perso
{
	int index;
	char string[10];

	perso->defense = 0;
	perso->pperso.x = atoi(systeme->sauvegarde[4]);
	perso->pperso.y = atoi(systeme->sauvegarde[5]);
	perso->life = atof(systeme->sauvegarde[7]);
	perso->lifemax = 100;

	sprintf(perso->slife, "vie : - /%d", perso->lifemax);

	perso->textureperso[0] = LoadingImage("rs/images/perso1.png", 0, systeme);
	perso->textureperso[1] = LoadingImage("rs/images/perso2.png", 0, systeme);
	perso->textureperso[2] = LoadingImage("rs/images/perso0.png", 0, systeme);
	perso->texture_poing[0] = LoadingImage("rs/images/perso_poing0.png", 0, systeme);
	perso->cheveuxbrun = LoadingImage("rs/images/cheveux0.png", 0, systeme);
	perso->cheveuxblanc = LoadingImage("rs/images/cheveux3.png", 0, systeme);

	perso->tpseudo = imprime (systeme->sauvegarde[0], systeme->screenw,BLANC, systeme, NULL);
	perso->tlife = imprime (perso->slife, systeme->screenw, BLANC, systeme, NULL);

	perso->pperso.w = 68;
	perso->pperso.h = 51;

	perso->pperso_poing.w = 68;
	perso->pperso_poing.h = 76;

	perso->centrecorp.x = 34;
	perso->centrecorp.y = 25;

	perso->ptpseudo.w = 100;
	perso->ptpseudo.h = 30;

	perso->pstats.x = systeme->screenw*0.11;

	perso->pstats.y = systeme->screenh*0.1;
	perso->pstats.w = systeme->screenw*0.28;
	perso->pstats.h = systeme->screenh*0.05;

	for (index = 0 ; index < 7 ; index++)//10->16
	{
		perso->stuff[index] = 0;
	}
	sprintf(string, "defense :");
	perso->tdefense = imprime (string, systeme->screenw, BLANC, systeme, NULL);
	sprintf(string, "regen vie :");
	perso->tregenlife = imprime (string, systeme->screenw, BLANC, systeme, NULL);
	sprintf(string, "force :");
	perso->tforce = imprime (string, systeme->screenw, BLANC, systeme, NULL);
	sprintf(string, "portee :");
	perso->tportee = imprime (string, systeme->screenw, BLANC, systeme, NULL);
}

void initdeplacement(DIVERSdeplacement *deplacement, DIVERSsysteme *systeme)//								deplacement
{
	int index;

	for (index = 0 ; index < MAX_JOUEURS ; index++)
	{
		deplacement->directionjoueurs[index] = 0;
	}
	deplacement->direction.bas = 0;
	deplacement->direction.haut = 0;
	deplacement->direction.droite = 0;
	deplacement->direction.gauche = 0;
	deplacement->direction.direction = 4;
	deplacement->direction.olddirection = 0;
	deplacement->persobouge = 0;
	deplacement->indexanimperso = 0;
	deplacement->x = atoi(systeme->sauvegarde[2]);
	deplacement->y = atoi(systeme->sauvegarde[3]);
}

void inittemps(DIVERStemps *temps, DIVERSsysteme *systeme)//												temps
{
	temps->i = 0;
	temps->tpact = 0;
	temps->tpap = 0;
	temps->tempsanimationjoueur = 0;
	temps->tpapr = 0;
	temps->tpspoursave= 0;
	temps->indextemps = 0;
	temps->temptotal = atoi(systeme->sauvegarde[6]);
	temps->oldipourregen = temps->temptotal;

	sprintf(temps->stringtempstotal, "age du personnage :\n - j - h - min - sec");
	sprintf(temps->StringI, "IPS => 0");

	temps->tfps = imprime (temps->StringI, systeme->screenw, BLANC, systeme, NULL);
	temps->ttemps = imprime (temps->stringtempstotal, systeme->screenw, BLANC, systeme, NULL);

	temps->ptFps.x = systeme->screenw*0.75;
	temps->ptFps.y = systeme->screenh*0.2;
	temps->ptFps.w = systeme->screenw*0.2;
	temps->ptFps.h = systeme->screenh*0.05;

	temps->pttemps.x = systeme->screenw*0.75;
	temps->pttemps.y = systeme->screenh*0.25;
	temps->pttemps.w = systeme->screenw*0.2;
	temps->pttemps.h = systeme->screenh*0.05;
}

void initsystem(DIVERSsysteme *systeme)//																	systeme
{
	int index;

	systeme->shiftactif = false;
	systeme->altactif = false;
	systeme->inbattle = false;
	systeme->continuer = 1;
	systeme->echap = 0;

	systeme->pointeur = LoadingImage				("rs/images/p.png", 0, systeme);
	systeme->BGmort = LoadingImage				("rs/fonds/mort.png", 0, systeme);
	systeme->BG = LoadingImage	("rs/ui/BG.png", 0, systeme);
	systeme->noir = LoadingImage	("rs/images/noir.png", 0, systeme);

	systeme->police = TTF_OpenFont("rs/divers/dalek.ttf", TAILLEPOLICE);
	systeme->police1 = TTF_OpenFont("rs/divers/police1.ttf", 25);

	systeme->pp.x = 0;
	systeme->pp.y = 0;
	systeme->pp.w = 20;
	systeme->pp.h = 30;


	systeme->pecran.x = 0;
	systeme->pecran.y = 0;
	systeme->pecran.w = systeme->screenw;
	systeme->pecran.h = systeme->screenh;

	systeme->ppobj.w = 50;
	systeme->ppobj.h = 50;

	systeme->oldpp.x = 0;
	systeme->oldpp.y = 0;

	index = 0;
	systeme->PixelCalque[index].x = 0;		systeme->PixelCalque[index].y = 0;		 index++;
	systeme->PixelCalque[index].x = 34;		systeme->PixelCalque[index].y = 0;		 index++;
	systeme->PixelCalque[index].x = 68;		systeme->PixelCalque[index].y = 0;		 index++;
	systeme->PixelCalque[index].x = 68;		systeme->PixelCalque[index].y = 25;		 index++;
	systeme->PixelCalque[index].x = 68;		systeme->PixelCalque[index].y = 50;		 index++;
	systeme->PixelCalque[index].x = 34;		systeme->PixelCalque[index].y = 50;		 index++;
	systeme->PixelCalque[index].x = 0;		systeme->PixelCalque[index].y = 50;		 index++;
	systeme->PixelCalque[index].x = 0;		systeme->PixelCalque[index].y = 25;
}

void initui(DIVERSui *ui, DIVERSsysteme *systeme)//															ui
{
	int index;
	ui->menuactif = false;
	ui->distanceprevenu = false;

	ui->coinhaut = 0;
	ui->coinbas = 0;
	ui->lancedialogue = 0;
	ui->dialogueactif = 0;

	sprintf(ui->designationstuff[0], "arme");
	sprintf(ui->designationstuff[1], "torse");
	sprintf(ui->designationstuff[2], "cou");
	sprintf(ui->designationstuff[3], "dos");
	sprintf(ui->designationstuff[4], "pieds");
	sprintf(ui->designationstuff[5], "taille");
	sprintf(ui->designationstuff[6], "tête");

	for(index = 0 ; index < 7 ; index++)
	{
		ui->tdesignationstuff[index] = imprime (ui->designationstuff[index], systeme->screenw, BLANC, systeme, NULL);
		ui->casestuff[index].IDobjet = atoi(systeme->sauvegarde[index+10]);
		ui->casestuff[index].NBobjet = 0;
	}

	ui->ttextedialogue = NULL;
	ui->lumiereon = LoadingImage		("rs/images/enligne.png", 0, systeme);
	ui->lumiereoff = LoadingImage		("rs/images/horsligne.png", 0, systeme);
	ui->tdialogue = LoadingImage		("rs/ui/dialogue.png", 0, systeme);
	ui->uimenu = LoadingImage		("rs/ui/uimenu.png", 0, systeme);
	ui->BGmenu = LoadingImage		("rs/ui/BGmenu.png", 0, systeme);


	ui->pUIbas.x = 0;
	ui->pUIbas.y = systeme->screenh/2;
	ui->pUIbas.w = systeme->screenw;
	ui->pUIbas.h = systeme->screenh/2;

	ui->pUIhaut.x = 0;
	ui->pUIhaut.y = 0;
	ui->pUIhaut.w = systeme->screenw;
	ui->pUIhaut.h = systeme->screenh/2;

	ui->plumiere.x = systeme->screenw*0.75;
	ui->plumiere.y = systeme->screenh*0.013;
	ui->plumiere.w = systeme->screenw*0.1;
	ui->plumiere.h = systeme->screenh*0.0325;

	ui->puimenu.x = 0;
	ui->puimenu.y = 0;
	ui->puimenu.w = 50;
	ui->puimenu.h = 50;

	ui->pcasestuff[0].x = systeme->screenw*0.225;
	ui->pcasestuff[0].y = systeme->screenh*0.35;
	ui->pcasestuff[0].w = systeme->screenh*0.1;
	ui->pcasestuff[0].h = systeme->screenh*0.1;

	ui->pcasestuff[1].x = systeme->screenw*0.05;
	ui->pcasestuff[1].y = systeme->screenh*0.05;
	ui->pcasestuff[1].w = systeme->screenh*0.1;
	ui->pcasestuff[1].h = systeme->screenh*0.1;
	ui->pcasestuff[2].x = systeme->screenw*0.05;
	ui->pcasestuff[2].y = systeme->screenh*0.15;
	ui->pcasestuff[2].w = systeme->screenh*0.1;
	ui->pcasestuff[2].h = systeme->screenh*0.1;
	ui->pcasestuff[3].x = systeme->screenw*0.05;
	ui->pcasestuff[3].y = systeme->screenh*0.25;
	ui->pcasestuff[3].w = systeme->screenh*0.1;
	ui->pcasestuff[3].h = systeme->screenh*0.1;

	ui->pcasestuff[4].x = systeme->screenw*0.4;
	ui->pcasestuff[4].y = systeme->screenh*0.05;
	ui->pcasestuff[4].w = systeme->screenh*0.1;
	ui->pcasestuff[4].h = systeme->screenh*0.1;
	ui->pcasestuff[5].x = systeme->screenw*0.4;
	ui->pcasestuff[5].y = systeme->screenh*0.15;
	ui->pcasestuff[5].w = systeme->screenh*0.1;
	ui->pcasestuff[5].h = systeme->screenh*0.1;
	ui->pcasestuff[6].x = systeme->screenw*0.4;
	ui->pcasestuff[6].y = systeme->screenh*0.25;
	ui->pcasestuff[6].w = systeme->screenh*0.1;
	ui->pcasestuff[6].h = systeme->screenh*0.1;
}

void initchat(DIVERSchat *chat, DIVERSsysteme *systeme)//													chat
{
	int index;
	chat->chatactif = false;
	chat->saisiechat = 0;

	chat->tbufferchat = NULL;
	chat->lettre = '\0';
	for (index = 0; index < 10 ; index++)
	{
		chat->tstringchat[index] = NULL;

		chat->pstringchat[index].x = 0;
		chat->pstringchat[index].y = (systeme->screenh/2)+(index*32);
		chat->pstringchat[index].w = 0;
		chat->pstringchat[index].h = TAILLEPOLICE;
	}
	chat->Uichat = LoadingImage			("rs/ui/uichat.png", 0, systeme);
	chat->BGchat = LoadingImage			("rs/ui/BGchat.png", 0, systeme);
	chat->BGchatactif = LoadingImage	("rs/ui/BGzonetextechat.png", 0, systeme);

	chat->puichat.x = 0;
	chat->puichat.y = systeme->screenh-50;
	chat->puichat.w = 50;
	chat->puichat.h = 50;

	chat->pchatactif.w = systeme->screenw;
	chat->pchatactif.h = systeme->screenh*0.03072;
	chat->pchatactif.x = 0;
	chat->pchatactif.y = systeme->screenh - chat->pchatactif.h;

	chat->pbufferchat.x = chat->pchatactif.x;
	chat->pbufferchat.y = chat->pchatactif.y;
	chat->pbufferchat.w = chat->pchatactif.w ;
	chat->pbufferchat.h = chat->pchatactif.h;
}

void initcraft(DIVERScraft *craft, DIVERSsysteme *systeme)//												craft
{
	int index;
	craft->actif = false;
	craft->bcraftactif = -1;
	craft->bcraftpointer = -1;
	craft->planactif = -1;
	craft->planpointer = -1;

	craft->Uicraft = LoadingImage			("rs/ui/uicraft.png", 0, systeme);
	craft->BGcraft = LoadingImage			("rs/ui/BGcraft.png", 0, systeme);
	craft->tetabli = LoadingImage			("rs/images/etabli.png", 0, systeme);

	craft->puicraft.x = systeme->screenw-50;
	craft->puicraft.y = 0;
	craft->puicraft.w = 50;
	craft->puicraft.h = 50;

	craft->petabli.x = 500;
	craft->petabli.y = 500;
	craft->petabli.w = 50;
	craft->petabli.h = 50;

	craft->posplan.x = systeme->screenw*0.0073;
	craft->posplan.y = systeme->screenh*0.039;
	craft->posplan.w = systeme->screenw*0.293;
	craft->posplan.h = systeme->screenh*0.065;

	craft->posimageresultatcraft.x = systeme->screenw*0.4;
	craft->posimageresultatcraft.y = systeme->screenh*0.065;
	craft->posimageresultatcraft.w = systeme->screenw*0.067;
	craft->posimageresultatcraft.h = systeme->screenh*0.12;

	craft->pstats.x = systeme->screenw*0.4;
	craft->pstats.y = systeme->screenh*0.160;
	craft->pstats.w = systeme->screenw*0.146;
	craft->pstats.h = systeme->screenh*0.04;

	for (index = 0 ; index < 10 ; index++)
	{
		craft->poscompocraft[index].x = systeme->screenw*0.512;
		craft->poscompocraft[index].y = (systeme->screenh*0.0456) +(index*(systeme->screenh*0.0599));
		craft->poscompocraft[index].w = systeme->screenw*0.366;
		craft->poscompocraft[index].h = systeme->screenh*0.0651;
		craft->posimagecompocraft[index].x = systeme->screenw*0.893;
		craft->posimagecompocraft[index].y = (systeme->screenh*0.0326) +(index*(systeme->screenh*0.0599));
		craft->posimagecompocraft[index].w = systeme->screenw*0.0337;
		craft->posimagecompocraft[index].h = systeme->screenh*0.0599;

		craft->tcomponame[index] = imprime("rien", systeme->screenw, ROUGE, systeme, NULL);
	}
}

void initmap (DIVERSmap *carte, DIVERSsysteme *systeme, PERSO *perso)//										map
{
	int index, rangerx = -1, i, j, i2, j2, noir = 0;
	Uint32 pixel = {0};
	SDL_Color couleurNoir = {0, 0, 0, 0};
	SDL_Color couleurpixel;

	carte->pmx = 0;
	carte->pmy = 0;

	for (index = 0 ; index < TILESMAP ; index++)
	{
		char nom[32];
		sprintf(nom, "rs/maps/map%d.png", index);
		carte->tilemap[index] = LoadingImage(nom, 0, systeme);
		sprintf(nom, "rs/maps/calque%d.png", index);
		carte->calque[index] = IMG_Load(nom);
	}

	for (index = 0 ; index < TILESMAP ; index++)
	{
		rangerx++;
		if (rangerx / 4 == 1)
		{
			rangerx = 0;
		}
		carte->pmap[index].x = (rangerx * 2500)+(perso->pperso.x-(systeme->screenw/2));
		carte->pmap[index].y = ((index / 4) * 2500)+(perso->pperso.y-(systeme->screenh/2));
		carte->pmap[index].w = 2500;
		carte->pmap[index].h = 2500;
		SDL_LockSurface(carte->calque[index]);
	}

	//creation de la grille de colision
	for (i = 0 ; i < 200 ; i++)
	{
		for (j = 0 ; j < 400 ; j++)
		{
			noir = 0;
			for (i2 = 0 ; i2 < 25 ; i2++)
			{
				for (j2 = 0 ; j2 < 25 ; j2++)
				{
					pixel = obtenirPixel(&carte->calque[0], (j*25)+j2, (i*25)+i2);
					SDL_GetRGB(pixel, carte->calque[2]->format, &couleurpixel.r, &couleurpixel.g, &couleurpixel.b);
					if (couleurpixel.r == couleurNoir.r)
					{
						noir++;
					}
				}
			}
			if (noir < 312)
			{
				carte->grille[i][j].value = 0;
			}
			else
			{
				carte->grille[i][j].value = 1;
			}
		}
	}

}

void initpnj (PACKpnj *pnj)//																				pnj
{
	pnj->toumai.w = 68;
	pnj->toumai.h = 48;
	pnj->toumaiParle = false;
}

void initrecompense (PACKrecompense *recompense, DIVERSsysteme *systeme)//									recompense
{
	int index;
	for (index = 0 ; index < LOOTMAX ; index++)
	{
		recompense->recompenseNB[index] = 0;
		recompense->ttextelootcombat[index] = NULL;
	}
	for (index = 0 ; index < NOMBREOBJETS ; index++)
	{
		recompense->recompenseID[index] = -1;
	}

	recompense->tvictoire = imprime("VICTOIRE", systeme->screenw, ROUGE, systeme, NULL);
	recompense->ttexterecompensecombat = imprime("vous avez gagné :", systeme->screenw, BLANC, systeme, NULL);

	recompense->pBGrecompense.x = systeme->screenw*0.333;
	recompense->pBGrecompense.y = systeme->screenh*0.044;
	recompense->pBGrecompense.w = systeme->screenw*0.333;
	recompense->pBGrecompense.h = systeme->screenh*0.911;

	recompense->precompensecombat.x = systeme->screenw*0.366;
	recompense->precompensecombat.y = systeme->screenh*0.326;
	recompense->precompensecombat.w = systeme->screenw*0.293;
	recompense->precompensecombat.h = systeme->screenh*0.039;

	recompense->ptvictoire.x = systeme->screenw*0.351;
	recompense->ptvictoire.y = systeme->screenh*0.065;
	recompense->ptvictoire.w = systeme->screenw*0.293;
	recompense->ptvictoire.h = systeme->screenh*0.13;

	recompense->ptrecompesecombat.x = systeme->screenw*0.351;
	recompense->ptrecompesecombat.y = systeme->screenh*0.26;
	recompense->ptrecompesecombat.w = systeme->screenw*0.293;
	recompense->ptrecompesecombat.h = systeme->screenh*0.065;
}

void initFORevent(typeFORevent *FORevent, PACKobjet *objet, PACKbouton *bouton, DIVERSinventaire *inventaire, DIVERSsysteme *systeme,
				DIVERSdeplacement *deplacement, DIVERSchat *chat, DIVERSui *ui, DIVERScraft *craft, PACKmonstre *monstre,
				PERSO *perso,PACKpnj *pnj)
{
	FORevent->bouton = bouton;
	FORevent->chat = chat;
	FORevent->craft = craft;
	FORevent->deplacement = deplacement;
	FORevent->inventaire = inventaire;
	FORevent->monstre = monstre;
	FORevent->objet = objet;
	FORevent->perso = perso;
	FORevent->systeme = systeme;
	FORevent->ui = ui;
	FORevent->pnj = pnj;

}

void initonline(typeFORthreads *online, DIVERSsysteme *systeme)
{
	int index;
	online->sock = -1;
	online->isonline = false;
	online->systeme = systeme;
	online->jeuxACTIF = 0;

	online->posjoueurx = 0;
	online->posjoueury = 0;

	for (index = 0; index < MAX_JOUEURS ; index++)
	{
		online->joueurs[index].posjoueurscalculer.x = -100;
		online->joueurs[index].posjoueurscalculer.y = -100;
		online->joueurs[index].posjoueurscalculer.w = 0;
		online->joueurs[index].posjoueurscalculer.h = 0;
	}

	online->chat.lenbuffer = 0;
	for (index = 0 ; index < 10 ; index++)
    {
        online->chat.poschat[index] = index;
        memset(online->chat.schat[index], '\0', 512);
    }
	online->chat.lancermessage = false;
	memset(online->chat.bufferchat, '\0', 512);

}

void initcombatstore(struct typecombat *BTLstr, DIVERSsysteme *systeme, float vie, struct DIRECTION *direction, bool arcademode)
{
	int index, index2;
	BTLstr->continuer = -1;
	BTLstr->echap = 0;
	BTLstr->doublesaut = 0;
	BTLstr->py = 0;
	BTLstr->px = 0;
	BTLstr->letirdemander = false;
	BTLstr->poing_tendu = false;
	BTLstr->canonx = 0;
	BTLstr->canony = 0;
	BTLstr->irect = 0;
	BTLstr->ResultatHitbox = 0;
	BTLstr->tableauutile = 0;
	BTLstr->indexanimperso = 0;
	BTLstr->persobouge = 0;
	BTLstr->animobjet = 1;
	BTLstr->animobjetway = 0;
	BTLstr->ennemivaincue = 0;
	BTLstr->arcadescore = 0;

	BTLstr->temps = 0;
	BTLstr->tempsaffichage = 0;
	BTLstr->tempsseconde = 0;
	BTLstr->tempscalcul = 0;
	BTLstr->tempsanimationjoueur = 0;
	BTLstr->tempsanimationobjet = 0;

	direction->bas = 0;
	direction->droite = 0;
	direction->gauche = 0;
	direction->haut = 0;
	direction->direction = 0;
	direction->olddirection = 0;

	BTLstr->NBlootsol = rand()%5;  //max déclaré 64
	if (arcademode == false)
	{
		BTLstr->NBennemi = rand()%150+5;//max déclaré 128        rand()%45+5
	}
	else
	{//valeur maximum pour tout initialisé
		BTLstr->NBennemi = LIMITEmobARCADE;
	}

	for (index = 0 ; index < BTLstr->NBlootsol ; index++)
	{
	    int tmprand  = rand()%2;
	    if (tmprand == 0)
        {BTLstr->IDlootsol[index] = 7;}
        else
        {BTLstr->IDlootsol[index] = 2;}
		BTLstr->lootsol[index] = BTL_OBJ_FLOOR;
		BTLstr->plootsol[index].w = systeme->screenw*0.0439;//60
		BTLstr->plootsol[index].h = systeme->screenh*0.130;//100
		BTLstr->plootsol[index].x = (rand()%(systeme->screenw - (BTLstr->plootsol[index].w*2)))+BTLstr->plootsol[index].w;
		BTLstr->plootsol[index].y = (rand()%(systeme->screenh - (BTLstr->plootsol[index].h*2)))+BTLstr->plootsol[index].h;
		BTLstr->oldplootsol[index].x = 0;
		BTLstr->oldplootsol[index].y = 0;
		BTLstr->oldplootsol[index].w = BTLstr->plootsol[index].w;
		BTLstr->oldplootsol[index].h = BTLstr->plootsol[index].h;
		BTLstr->lootsolDX[index] = 0;
		BTLstr->lootsolDY[index] = 0;
		BTLstr->lootsolWAYX[index] = 0;
		BTLstr->lootsolWAYY[index] = 0;
	}

	for (index = 0 ; index < BTLstr->NBennemi ; index++)
	{

		float lrand1 = rand()%systeme->screenw;
		float lrand2 = rand()%systeme->screenh;
		BTLstr->ennemi[index].vie = 10;
		BTLstr->ennemi[index].mort = false;
		BTLstr->ennemi[index].tempsanimation = 0;
		BTLstr->ennemi[index].Direction = rand()%8;
		BTLstr->ennemi[index].indexanim = 0;
		BTLstr->ennemi[index].mind = 0;
		BTLstr->ennemi[index].mindtime = 0;
		BTLstr->ennemi[index].looted = 0;
		BTLstr->ennemi[index].ontheway = 0;
		BTLstr->ennemi[index].wayx = 0;
		BTLstr->ennemi[index].wayy = 0;
		for (index2 = 0 ; index2 < 8 ; index2++)
		{
			BTLstr->ennemi[index].relevancy[index2] = 0;
		}
		BTLstr->ennemi[index].position.x = lrand1;
		BTLstr->ennemi[index].position.y = lrand2;
		BTLstr->ennemi[index].position.w = systeme->screenw*0.073206442;//100
		BTLstr->ennemi[index].position.h = systeme->screenh*0.032552083;//25
		;
		BTLstr->ennemi[index].STATICposition.w = BTLstr->ennemi[index].position.w;
		BTLstr->ennemi[index].STATICposition.h = BTLstr->ennemi[index].position.h;
	}
	
	if (arcademode == true)
	{//remise a zero du compteur pour le mode arcade
		BTLstr->NBennemi = 0;
		BTLstr->alive = BTLstr->NBennemi;
	}

	for (index = 0 ; index < 48 ; index++)
	{
		BTLstr->StringVie[index] = '\0';
	}

	for (index = 0 ; index < 128 ; index++)
	{
		BTLstr->StringCailloux[index] = '\0';
	}


	for (index = 0 ; index < NBcailloux ; index++)
	{
		printf("%d", index);
	    BTLstr->i[index] = 0;
		BTLstr->DepartBalle[index] = UNUSED;

		BTLstr->pballe[index].x = -50;
		BTLstr->pballe[index].y = -50;
		BTLstr->pballe[index].w = systeme->screenw*0.0146;
		BTLstr->pballe[index].h = systeme->screenh*0.026;
	}


	BTLstr->pecran.x = 0;
	BTLstr->pecran.y = 0;
	BTLstr->pecran.w = systeme->screenw;
	BTLstr->pecran.h = systeme->screenh;

	BTLstr->Pperso.x = systeme->screenw/2;
	BTLstr->Pperso.y = systeme->screenh*0.564;
	BTLstr->Pperso.w = systeme->screenw*0.050;
	BTLstr->Pperso.h = systeme->screenh*0.066;

	BTLstr->pcurseur.x = 0;
	BTLstr->pcurseur.y = 0;
	BTLstr->pcurseur.w = 30;
	BTLstr->pcurseur.h = 30;

	BTLstr->testcontact.x = 0;
	BTLstr->testcontact.y = 0;
	BTLstr->testcontact.w = 10;
	BTLstr->testcontact.h = 10;

	BTLstr->ptVie.x = systeme->screenw*0.015;
	BTLstr->ptVie.y = systeme->screenh*0.026;
	BTLstr->ptVie.w = systeme->screenw*0.3;
	BTLstr->ptVie.h = systeme->screenh*0.065;

	BTLstr->fond = LoadingImage				("rs/fonds/fondcombat.png", 0, systeme);
	BTLstr->curseur = LoadingImage			("rs/images/curseur.png", 0, systeme);
	BTLstr->balle = LoadingImage			("rs/images/balle.png", 0, systeme);
	BTLstr->piece = LoadingImage			("rs/images/piece.png", 0, systeme);
	BTLstr->peau = LoadingImage			    ("rs/objets/0#0.png", 0, systeme);

	sprintf(BTLstr->StringVie, "vie de %s : %.1f", systeme->sauvegarde[0], vie);
	BTLstr->tVie = imprime (BTLstr->StringVie, systeme->screenw*0.35, NOIR, systeme, NULL);
}

