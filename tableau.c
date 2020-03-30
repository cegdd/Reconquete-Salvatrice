#include "SDL2/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "struct.h"
#include "image.h"
#include "objet.h"
#include "tool.h"
#include "perso.h"

extern int screenh, screenw;

int TotalTableauInt(int *ptrTableau, int nbcase)
{
	int total = 0, i = 0;
	for (i = 0 ; i < nbcase ; i++)
	{
		total = total + ptrTableau[i];
	}
	return total;
}

void initinventaire(struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme)
{
	int index, rangerx = -1;
	char nom[32];

	inventaire->box[0].texture = loadTexture		("rs/ui/caseinventaire.png");

	for (index = 0 ; index < TAILLESAC ; index++)
	{
		rangerx++;
		if (rangerx / 24 == 1)
		{
			rangerx = 0;
		}
		inventaire->box[index].pos.x = rangerx * (screenw*0.0417);
		inventaire->box[index].pos.y = (screenh*0.4) -((index / 24) * screenw*0.0417);
		inventaire->box[index].pos.w = screenw*0.0417+1;
		inventaire->box[index].pos.h = screenw*0.0417+1;
		inventaire->box[index].texture = inventaire->box[0].texture;

		inventaire->pnbobjet[index].x = inventaire->box[index].pos.x + inventaire->box[0].pos.h*0.7;
		inventaire->pnbobjet[index].y = inventaire->box[index].pos.y + inventaire->box[0].pos.h*0.7;
		inventaire->pnbobjet[index].w = inventaire->box[0].pos.h*0.3;
		inventaire->pnbobjet[index].h = inventaire->box[0].pos.h*0.3;
	}
	for (index = 0 ; index < 128 ; index++)
	{
		inventaire->totalID[index] = 0;
	}

	inventaire->casedowndroit = -1;
	inventaire->casedowngauche = -1;
	inventaire->caseupgauche = -1;
	inventaire->idsurvoler = -1;
	inventaire->sac.texture = loadTexture   ("rs/ui/sac1.png");
	inventaire->fond.texture = loadTexture	("rs/ui/BGinventaire.png");
	inventaire->rubbish.texture = loadTexture("rs/images/rubbish.png");

	sprintf(nom, "clic droit : equiper");
	inventaire->aide.img.texture = imprime (nom, screenw, GRIS, systeme, &inventaire->aide.lenght, NULL);

	setPos4(&inventaire->sac.pos, 0, screenh/2 - screenh*0.026, screenw*0.1, screenh*0.026);
	setPos4(&inventaire->fond.pos, 0, 0, screenw, screenh/2);
	setPos4(&inventaire->rubbish.pos, screenw*0.9, 0, screenw*0.073, screenh*0.13);
}


void initPLAN(struct PACKobjet *objet)
{
    int i, j;

    for(i = 0 ; i <= 7 ; i++)
    {
        objet->craftnumber[i] = 0;
        for(j = 0 ; j <= 10 ; j++)
        {
            objet->PLANstuff[i][j].compodifferente = 0;
            objet->PLANstuff[i][j].resultatID = -1;
            objet->PLANstuff[i][j].resultatNB = 0;
        }
    }
}

void initobjet(struct PACKobjet *objet,struct DIVERSsysteme *systeme,struct DIVERScraft *craft)/*													objet*/
{
	char nom[128];
	int index;

	for(index = 10 ; index >= 0 ; index--) { craft->planparonglets[index] = 0;}
	initPLAN(objet);

/****************** ressources **********************/

	    /*index * nom * empilage * type * def * life * force * portee * regenlife * bodypart*/
    createobjet(0, "peau des rats",         99, RESSOURCE,  0,  0,  0, 0,   0, -1,      objet,craft);
    createobjet(2, "silex",                 5,  RESSOURCE,  0,  0,  0, 0,   0, -1,      objet,craft);
    createobjet(7, "branche",               5,  RESSOURCE,  0,  0,  0, 0,   0, -1,      objet,craft);

/******************** ARME **************************/

    createobjet(3, "lance pierre",          1,  EQUIPEMENT, 1,  0,  3, 100, 0, ARME,    objet,craft);
    CreateCraft(3 , 1, objet, 2 /**/, 7, 3,/**/ 0, 1);
    createobjet(10, "hachette",             1,  EQUIPEMENT, 0,  0,  5, 3,   0, ARME,    objet,craft);
    CreateCraft(10, 1, objet, 2 /**/, 7, 3,/**/ 0, 1);
    createobjet(12, "baton de chamane",     1,  EQUIPEMENT, 0,  20, 0, 4,   4, ARME,    objet,craft);
    CreateCraft(12, 1, objet, 2 /**/, 7, 2,/**/ 2, 2);
    createobjet(13, "gros lance pierre",    1,  EQUIPEMENT, 2,  0,  5, 150, 0, ARME,    objet,craft);
	CreateCraft(13, 1, objet, 2 /**/, 7, 5,/**/ 2, 6);

/******************** TORSE **************************/

    createobjet(4, "toge en peau de rat",   1,  EQUIPEMENT, 5,  10, 0, 0,   2, TORSE,   objet,craft);
    CreateCraft(4 , 1, objet, 1 /**/, 0, 30);

/******************** COU *************************/

    createobjet(5, "echarpe en peau de rat",1,  EQUIPEMENT, 2,  0,  0, 0,   1, COU,     objet,craft);
    CreateCraft(5 , 1, objet, 1 /**/, 0, 25);

/******************** DOS *************************/

    createobjet(6, "cape en peau de rat",   1,  EQUIPEMENT, 5,  5,  1, 0,   0, DOS,     objet,craft);
    CreateCraft(6 , 1, objet, 1 /**/, 0, 25);
    createobjet(11, "cape lestee de silex",  1,  EQUIPEMENT, 10, 15, 2, 0,   0, DOS,     objet,craft);
    CreateCraft(11 , 1, objet, 2 /**/, 0, 30,/**/ 2, 3);

/******************** PIED *************************/

    createobjet(1, "sandales", 1, EQUIPEMENT, 3, 10, 0, 0, 1,PIED, objet,craft);
    CreateCraft(1 , 1, objet, 2 /**/, 7, 4,/**/ 0, 5);

/******************** TAILLE *************************/

    createobjet(8, "ceinture",              1,  EQUIPEMENT, 5,  0,  5, 0,   1, TAILLE,  objet,craft);
    CreateCraft(8 , 1, objet, 2 /**/, 0, 13,/**/ 2, 3);

/******************** TETE ***********************/

    createobjet(9, "coiffe",                1,  EQUIPEMENT, 10, 20, 0, 0,   1, TETE,    objet,craft);
    CreateCraft(9 , 1, objet, 2 /**/, 0, 17,/**/ 7, 3);



	objet->objetenmain.IDobjet = -1;
	objet->objetenmain.NBobjet = 0;

	for (index = 0 ; index < NOMBREOBJETS ; index++)
	{
		sprintf(nom, "rs/objets/%d#0.png", index);
        objet->objet[index].texture = loadTexture   (nom);
		if(objet->objet[index].def != 0)
		{
			sprintf(nom, "defense : %d", objet->objet[index].def);
			objet->objet[index].tdef.img.texture = imprime (nom, screenw, BLANC, systeme, &objet->objet[index].tdef.lenght, NULL);
		}
		if(objet->objet[index].life != 0)
		{
			sprintf(nom, "sante : +%d", objet->objet[index].life);
			objet->objet[index].tlife.img.texture = imprime (nom, screenw, BLANC, systeme, &objet->objet[index].tlife.lenght, NULL);
		}
		if(objet->objet[index].regenlife != 0)
		{
			sprintf(nom, "regeneration : %d/sec", objet->objet[index].regenlife);
			objet->objet[index].tregenlife.img.texture = imprime (nom, screenw, BLANC, systeme, &objet->objet[index].tregenlife.lenght, NULL);
		}

		if(objet->objet[index].force != 0)
		{
			sprintf(nom, "force : %d", objet->objet[index].force);
			objet->objet[index].tforce.img.texture = imprime (nom, screenw, BLANC, systeme, &objet->objet[index].tforce.lenght, NULL);
		}

		if(objet->objet[index].portee != 0)
		{
			sprintf(nom, "portee : +%d%%", objet->objet[index].portee);
			objet->objet[index].tportee.img.texture = imprime (nom, screenw, BLANC, systeme, &objet->objet[index].tportee.lenght, NULL);
		}

		sprintf(nom, "%d", objet->objet[index].empilage);
		objet->objet[index].quantite = imprime (nom, screenw, ROUGE, systeme, NULL, NULL);

		objet->objet[index].texturenom[0] = imprime (objet->objet[index].nom, screenw, BLANC, systeme, &objet->objet[index].LARGEURnom, NULL);
		objet->objet[index].texturenom[1] = imprime (objet->objet[index].nom, screenw, GRIS, systeme, &objet->objet[index].LARGEURnom, NULL);
		objet->objet[index].texturenom[2] = imprime (objet->objet[index].nom, screenw, ROUGE, systeme, &objet->objet[index].LARGEURnom, NULL);
	}

	for (index = 0 ; index < TAILLESAC ; index++)
	{
		objet->sac1[index].IDobjet = systeme->saveinventaire[0][index];
		objet->sac1[index].NBobjet = systeme->saveinventaire[1][index];
	}
}

void initbouton(struct PACKbouton *bouton,struct DIVERSsysteme *systeme)/*												bouton*/
{
    int index;
/*
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

	bouton->crafter.normal = LoadingImage			("rs/ui/creer.png", 0, systeme);
	bouton->crafter.survoler = LoadingImage		("rs/ui/creer2.png", 0, systeme);
	bouton->crafter.cliquer = LoadingImage			("rs/ui/creer3.png", 0, systeme);*/

	for (index = 0 ; index < 7 ; index++)
	{
		bouton->bcraft[index].pos.x = index*(screenw*0.143);
		bouton->bcraft[index].pos.y = screenh*0.467;
		bouton->bcraft[index].pos.w = screenw*0.143;
		bouton->bcraft[index].pos.h = screenh*0.03;
		bouton->bcraft[index].etat = 0;
	}

	bouton->crafter.pos.x = screenw*0.622;
	bouton->crafter.pos.y = screenh*0.39;
	bouton->crafter.pos.w = screenw*0.11;
	bouton->crafter.pos.h = screenh*0.0651;

	bouton->crafter.etat = 0;
}

void inittemps(struct DIVERStemps *temps,struct DIVERSsysteme *systeme)/*												temps*/
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

	temps->fps.texture = imprime (temps->StringI, screenw, BLANC, systeme, NULL, NULL);
	temps->temps.texture = imprime (temps->stringtempstotal, screenw, BLANC, systeme, NULL, NULL);

	setPos4(&temps->fps.pos, screenw*0.75, screenh*0.8, screenw*0.2, screenh*0.05);
	setPos4(&temps->temps.pos, screenw*0.75, screenh*0.75, screenw*0.2, screenh*0.05);
}

void initsystem(struct DIVERSsysteme *systeme)/*																	systeme*/
{
	systeme->shiftactif = false;
	systeme->altactif = false;
	systeme->inbattle = false;
	systeme->djisloaded = false;
	systeme->djID = 0;
	systeme->continuer = 1;
	systeme->echap = 0;

	systeme->pointeur.texture = loadTexture("rs/images/p.png");
	//systeme->BGmort = LoadingImage				("rs/fonds/mort.png", 0, systeme);
	systeme->BGnoir =               loadTexture	("rs/ui/BG.png");
	systeme->BGblanc =              loadTexture	("rs/ui/bgb.png");

	systeme->police = TTF_OpenFont("rs/divers/dalek.ttf", TAILLE_POLICE);
	systeme->police1 = TTF_OpenFont("rs/divers/police1.ttf", TAILLE_POLICE);
	if (systeme->police == NULL ||
        systeme->police1 == NULL)
    {
        printf("police not load2\n");
    }

    setPos4(&systeme->pointeur.pos, 0, 0, 20, 30);

	systeme->pecran.x = 0;
	systeme->pecran.y = 0;
	systeme->pecran.w = screenw;
	systeme->pecran.h = screenh;

	systeme->ppobj.w = 50;
	systeme->ppobj.h = 50;

	systeme->oldpp.x = 0;
	systeme->oldpp.y = 0;
}

void initui(struct DIVERSui *ui,struct DIVERSsysteme *systeme)/*															ui*/
{
	int index;
	ui->menu_open =         false;
	ui->inventaire_open =   false;
	ui->chat_open =         false;
	ui->craft_open =        false;
	ui->distanceprevenu =   false;

	ui->lancedialogue = false;
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
//		ui->tdesignationstuff[index] = imprime (ui->designationstuff[index], screenw, BLANC, systeme, NULL, NULL);
		ui->casestuff[index].IDobjet = atoi(systeme->sauvegarde[index+10]);
		ui->casestuff[index].NBobjet = 0;
	}

	ui->dialogue_text.texture = 0;
	ui->dialogue_back.texture = loadTexture		("rs/ui/dialogue.png");

    //ui->lumiereon = LoadingImage		("rs/images/enligne.png", 0, systeme);
	//ui->lumiereoff = LoadingImage		("rs/images/horsligne.png", 0, systeme);

	ui->corner_menu.texture = loadTexture       ("rs/ui/uimenu.png");
	ui->corner_inventaire.texture = loadTexture ("rs/ui/uiinventaire.png");
	ui->corner_chat.texture = loadTexture       ("rs/ui/uichat.png");
	ui->BGmenu.texture = loadTexture            ("rs/ui/BGmenu.png");
	ui->BoutonQuitter.texture = loadTexture		("rs/ui/quitter.png");

	ui->pUIbas.x = 0;
	ui->pUIbas.y = screenh/2;
	ui->pUIbas.w = screenw;
	ui->pUIbas.h = screenh/2;

	ui->pUIhaut.x = 0;
	ui->pUIhaut.y = 0;
	ui->pUIhaut.w = screenw;
	ui->pUIhaut.h = screenh/2;

	ui->plumiere.x = screenw*0.75;
	ui->plumiere.y = screenh*0.013;
	ui->plumiere.w = screenw*0.1;
	ui->plumiere.h = screenh*0.0325;

	setPos4 (&ui->corner_menu.pos, 0, screenh-screenh*0.063, screenw*0.036, screenh*0.065);
	setPos4 (&ui->corner_inventaire.pos, screenw-screenw*0.036, 0, screenw*0.036, screenh*0.065);
	setPos4 (&ui->corner_chat.pos, 0, 0, screenw*0.036, screenh*0.065);
	setPos4 (&ui->BGmenu.pos, 0, screenh/2, screenw, screenh/2);
	setPos4 (&ui->BoutonQuitter.pos, screenw*0.96, screenh-screenw*0.04, screenw*0.04, screenw*0.04);

	ui->BoutonQuitter.etat = B_NORMAL;

	ui->corner_menu.etat =          B_NORMAL;
	ui->corner_inventaire.etat =    B_NORMAL;
	ui->corner_chat.etat =          B_NORMAL;

	setPos4 (&ui->casestuff[0].pos, screenw*0.225, screenh*0.85, screenh*0.1, screenh*0.1);
	setPos4 (&ui->casestuff[1].pos, screenw*0.05, screenh*0.55, screenh*0.1, screenh*0.1);
	setPos4 (&ui->casestuff[2].pos, screenw*0.05, screenh*0.65, screenh*0.1, screenh*0.1);
	setPos4 (&ui->casestuff[3].pos, screenw*0.05, screenh*0.75, screenh*0.1, screenh*0.1);
	setPos4 (&ui->casestuff[4].pos, screenw*0.4, screenh*0.55, screenh*0.1, screenh*0.1);
	setPos4 (&ui->casestuff[5].pos, screenw*0.4, screenh*0.65, screenh*0.1, screenh*0.1);
	setPos4 (&ui->casestuff[6].pos, screenw*0.4, screenh*0.75, screenh*0.1, screenh*0.1);


}

void initchat(struct DIVERSchat *chat,struct DIVERSsysteme *systeme)/*													chat*/
{
	int index;
	chat->saisiechat = 0;

	chat->tbufferchat = NULL;
	chat->lettre = '\0';
	for (index = 0; index < 10 ; index++)
	{
		chat->tstringchat[index] = NULL;

		chat->pstringchat[index].x = 0;
		chat->pstringchat[index].y = (screenh/2)+(index*32);
		chat->pstringchat[index].w = 0;
		chat->pstringchat[index].h = TAILLE_POLICE;
	}
/*	chat->BGchat = LoadingImage			("rs/ui/BGchat.png", 0, systeme);
	chat->BGchatactif = LoadingImage	("rs/ui/BGzonetextechat.png", 0, systeme);*/

	chat->pchatactif.w = screenw;
	chat->pchatactif.h = screenh*0.03072;
	chat->pchatactif.x = 0;
	chat->pchatactif.y = screenh - chat->pchatactif.h;

	chat->pbufferchat.x = chat->pchatactif.x;
	chat->pbufferchat.y = chat->pchatactif.y;
	chat->pbufferchat.w = chat->pchatactif.w ;
	chat->pbufferchat.h = chat->pchatactif.h;
}

void initcraft(struct DIVERScraft *craft,struct DIVERSsysteme *systeme)/*												craft*/
{
	int index;
	craft->bcraftactif = -1;
	craft->bcraftpointer = -1;
	craft->planactif = -1;
	craft->planpointer = -1;

	craft->puicraft.x = screenw-50;
	craft->puicraft.y = 0;
	craft->puicraft.w = 50;
	craft->puicraft.h = 50;

	craft->petabli.x = 500;
	craft->petabli.y = 500;
	craft->petabli.w = 50;
	craft->petabli.h = 50;

	craft->posplan.x = screenw*0.0073;
	craft->posplan.y = screenh*0.039;
	craft->posplan.w = screenw*0.293;
	craft->posplan.h = screenh*0.065;

	craft->posimageresultatcraft.x = screenw*0.4;
	craft->posimageresultatcraft.y = screenh*0.065;
	craft->posimageresultatcraft.w = screenw*0.067;
	craft->posimageresultatcraft.h = screenh*0.12;

	craft->pstats.x = screenw*0.4;
	craft->pstats.y = screenh*0.160;
	craft->pstats.w = screenw*0.146;
	craft->pstats.h = screenh*0.04;

	for (index = 0 ; index < 10 ; index++)
	{
		craft->poscompocraft[index].x = screenw*0.512;
		craft->poscompocraft[index].y = (screenh*0.0456) +(index*(screenh*0.0599));
		craft->poscompocraft[index].w = screenw*0.366;
		craft->poscompocraft[index].h = screenh*0.0651;
		craft->posimagecompocraft[index].x = screenw*0.893;
		craft->posimagecompocraft[index].y = (screenh*0.0326) +(index*(screenh*0.0599));
		craft->posimagecompocraft[index].w = screenw*0.0337;
		craft->posimagecompocraft[index].h = screenh*0.0599;

//		craft->tcomponame[index] = imprime("rien", screenw, ROUGE, systeme, NULL, NULL);
	}
/*
	craft->Uicraft = LoadingImage			("rs/ui/uicraft.png", 0, systeme);
	craft->BGcraft = LoadingImage			("rs/ui/BGcraft.png", 0, systeme);
	craft->tetabli = LoadingImage			("rs/images/etabli.png", 0, systeme);*/
}

void initrecompense (struct PACKrecompense *recompense,struct DIVERSsysteme *systeme)/*									recompense*/
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

//	recompense->tvictoire = imprime("VICTOIRE", screenw, ROUGE, systeme, NULL, NULL);
//	recompense->ttexterecompensecombat = imprime("vous avez gagné :", screenw, BLANC, systeme, NULL, NULL);

	recompense->pBGrecompense.x = screenw*0.333;
	recompense->pBGrecompense.y = screenh*0.044;
	recompense->pBGrecompense.w = screenw*0.333;
	recompense->pBGrecompense.h = screenh*0.911;

	recompense->precompensecombat.x = screenw*0.366;
	recompense->precompensecombat.y = screenh*0.326;
	recompense->precompensecombat.w = screenw*0.293;
	recompense->precompensecombat.h = screenh*0.039;

	recompense->ptvictoire.x = screenw*0.351;
	recompense->ptvictoire.y = screenh*0.065;
	recompense->ptvictoire.w = screenw*0.293;
	recompense->ptvictoire.h = screenh*0.13;

	recompense->ptrecompesecombat.x = screenw*0.351;
	recompense->ptrecompesecombat.y = screenh*0.26;
	recompense->ptrecompesecombat.w = screenw*0.293;
	recompense->ptrecompesecombat.h = screenh*0.065;
}

void initFORevent(struct typeFORevent *FORevent,struct PACKobjet *objet,struct PACKbouton *bouton,struct DIVERSinventaire *inventaire,
                  struct DIVERSsysteme *systeme,struct DIVERSdeplacement *deplacement,struct DIVERSchat *chat,struct DIVERSui *ui,
                  struct DIVERScraft *craft,struct PERSO *perso)
{
	FORevent->bouton = bouton;
	FORevent->chat = chat;
	FORevent->craft = craft;
	FORevent->deplacement = deplacement;
	FORevent->inventaire = inventaire;
	FORevent->objet = objet;
	FORevent->perso = perso;
	FORevent->systeme = systeme;
	FORevent->ui = ui;

}

void initonline(struct typeFORthreads *online,struct DIVERSsysteme *systeme)
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

        sprintf(online->chat.schat[index]," The chat is not working, no server founded.");
    }
	online->chat.lancermessage = false;
	memset(online->chat.bufferchat, '\0', 512);

}

void initTIR(struct TIR *TIR)
{
    int index = 0;

    TIR->canonx = 0;
	TIR->canony = 0;
	TIR->tableauutile = 0;

	for (index = 0 ; index < 128 ; index++)
	{
		TIR->StringCailloux[index] = '\0';
	}

	for (index = 0 ; index < NBcailloux ; index++)
	{
	    TIR->i[index] = 0;
		TIR->DepartBalle[index] = UNUSED;

		setPos4(&TIR->pballe[index], -50, -50, screenw*0.0146, screenh*0.026);
	}

	TIR->balle = loadTexture ("rs/images/balle.png");
}
