#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "main.h"
#include "image.h"
#include "objet.h"
#include "tool.h"
#include "queue.h"

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

	setPos(&inventaire->sac.pos, 0, screenh/2 - screenh*0.026, screenw*0.1, screenh*0.026);
	setPos(&inventaire->fond.pos, 0, 0, screenw, screenh/2);
	setPos(&inventaire->rubbish.pos, screenw*0.9, 0, screenw*0.073, screenh*0.13);
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

void initmonstre(struct PACKmonstre *monstre,struct DIVERSsysteme *systeme)/*											monstre*/
{
	int index;
	monstre->rat[0].ID = 0;
	monstre->rat[1].ID = 1;
	monstre->rat[2].ID = 2;

	monstre->rat[0].prctloot[0] = 100; /*peau*/
	monstre->rat[0].maxloot[0] = 1; /*peau*/
	monstre->rat[0].idloot[0] = 0; /*peau*/
	monstre->rat[0].nombreloot = 1;

	initqueue(&monstre->rat[0].queue, 0);
	initqueue(&monstre->rat[1].queue, 1);
	initqueue(&monstre->rat[2].queue, 2);


	monstre->rat[0].m_pict.texture[0] =     loadTexture	("rs/images/mob0.0.png");
    monstre->rat[0].m_pict.texture[1] =     loadTexture	("rs/images/mob0.1.png");
    monstre->rat[0].m_pict.texture[2] =     loadTexture	("rs/images/mob0.2.png");


/*rat*/
	for (index = 0 ; index < 3 ; index++)
	{
		monstre->rat[index].m_pict.pict.pos.w = screenw*0.0732;
		monstre->rat[index].m_pict.pict.pos.h = screenh*0.039;

		monstre->rat[index].etat = ALIVE;
		monstre->rat[index].Engaged = false;
		monstre->rat[index].indexanim = 0;
		monstre->rat[index].tempsanim = 0;
		monstre->rat[index].direction = rand()%8;
		sprintf(monstre->rat[index].nom, "rat");
		monstre->rat[index].m_pict.texture[0] = monstre->rat[0].m_pict.texture[0];
        monstre->rat[index].m_pict.texture[1] = monstre->rat[0].m_pict.texture[1];
        monstre->rat[index].m_pict.texture[2] = monstre->rat[0].m_pict.texture[2];
		monstre->rat[index].m_pict.pict.texture = monstre->rat[0].m_pict.texture[0];
		monstre->rat[index].m_pict.current = 0;
		monstre->rat[index].m_pict.delay = 200;
		monstre->rat[index].m_pict.frame = 2;
		monstre->rat[index].m_pict.time = 0;
	}
}

void initperso(struct PERSO *perso,struct DIVERSsysteme *systeme)/*														perso*/
{
	int index;
	char string[16];
	perso->perso.texture[0] = loadTexture("rs/images/perso0.png");
	perso->perso.texture[1] = loadTexture("rs/images/perso1.png");
	perso->perso.texture[2] = loadTexture("rs/images/perso2.png");
	perso->perso.frame = 3;
	perso->perso.pict.texture = perso->perso.texture[0];
	perso->perso.current = 0;
	perso->perso.delay = 123;
	perso->perso.time = 0;

	setPos (&perso->perso.pict.pos, (screenw/2)-(perso->perso.pict.pos.w/2), (screenh/2)-(perso->perso.pict.pos.h/2), 68, 51);

	for(index = 0 ; index < 8 ; index++)
    {
        perso->cote[index] = 0;
    }
    for(index = 0 ; index < 12 ; index++)
    {
        perso->etatpix[index] = 1;
        perso->pixel[index] = 0;
    }




	perso->defense = 0;
	perso->life = atof(systeme->sauvegarde[7]);
	perso->lifemax = 100;

	sprintf(perso->slife, "vie : - /%d", perso->lifemax);

	//perso->cheveuxbrun = loadTexture("rs/images/cheveux0.png");
	//perso->cheveuxblanc = loadTexture("rs/images/cheveux3.png");

	//perso->tpseudo = imprime (systeme->sauvegarde[0], screenw,BLANC, systeme, NULL, NULL);

	perso->pperso_poing.w = 48;
	perso->pperso_poing.h = 48;
	perso->pperso_poing.x = 96;
	perso->pperso_poing.y = 288;

	perso->centrecorp.x = 34;
	perso->centrecorp.y = 25;

	perso->ptpseudo.w = 100;
	perso->ptpseudo.h = 30;

	for (index = 0 ; index < 7 ; index++)/*10->16*/
	{
		perso->stuff[index] = 0;
	}
	sprintf(string, "defense :");
	sprintf(string, "regen vie :");
	sprintf(string, "force :");
	sprintf(string, "portee :");

    perso->tlife.texture = imprime (perso->slife, screenw, BLANC, systeme, NULL, NULL);
	perso->tportee.texture = imprime (string, screenw, BLANC, systeme, NULL, NULL);
	perso->tforce.texture = imprime (string, screenw, BLANC, systeme, NULL, NULL);
	perso->tregenlife.texture = imprime (string, screenw, BLANC, systeme, NULL, NULL);
	perso->tdefense.texture = imprime (string, screenw, BLANC, systeme, NULL, NULL);

    setPos(&perso->tlife.pos, screenw*0.11, screenh*0.8, screenw*0.28, screenh*0.05);
	setPos(&perso->tdefense.pos, screenw*0.11, screenh*0.74, screenw*0.28, screenh*0.05);
	setPos(&perso->tregenlife.pos, screenw*0.11, screenh*0.68, screenw*0.28, screenh*0.05);
	setPos(&perso->tforce.pos, screenw*0.11, screenh*0.62, screenw*0.28, screenh*0.05);
	setPos(&perso->tportee.pos, screenw*0.11, screenh*0.56, screenw*0.28, screenh*0.05);

	perso->BarreDeVie = AddLifeBar(100, perso->perso.pict.pos.w, systeme);

	index = 0;
	perso->PixelCalque[index].x = 0;		perso->PixelCalque[index].y = 0;		 index++;
	perso->PixelCalque[index].x = 22;		perso->PixelCalque[index].y = 0;		 index++;
	perso->PixelCalque[index].x = 44;		perso->PixelCalque[index].y = 0;		 index++;
	perso->PixelCalque[index].x = 68;		perso->PixelCalque[index].y = 0;		 index++;
	perso->PixelCalque[index].x = 68;		perso->PixelCalque[index].y = 16;		 index++;
	perso->PixelCalque[index].x = 68;		perso->PixelCalque[index].y = 32;		 index++;
	perso->PixelCalque[index].x = 68;		perso->PixelCalque[index].y = 50;		 index++;
	perso->PixelCalque[index].x = 22;		perso->PixelCalque[index].y = 50;		 index++;
	perso->PixelCalque[index].x = 44;		perso->PixelCalque[index].y = 50;		 index++;
	perso->PixelCalque[index].x = 0;		perso->PixelCalque[index].y = 50;		 index++;
	perso->PixelCalque[index].x = 0;		perso->PixelCalque[index].y = 16;		 index++;
	perso->PixelCalque[index].x = 0;		perso->PixelCalque[index].y = 32;
}

void initdeplacement(struct DIVERSdeplacement *deplacement,struct DIVERSsysteme *systeme)/*								deplacement*/
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
	//deplacement->x = atoi(systeme->sauvegarde[2]);
	//deplacement->y = atoi(systeme->sauvegarde[3]);
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

	setPos (&temps->fps.pos, screenw*0.75, screenh*0.8, screenw*0.2, screenh*0.05);
	setPos (&temps->temps.pos, screenw*0.75, screenh*0.75, screenw*0.2, screenh*0.05);
}

void initsystem(struct DIVERSsysteme *systeme)/*																	systeme*/
{
	int index;

	systeme->shiftactif = false;
	systeme->altactif = false;
	systeme->inbattle = false;
	systeme->continuer = 1;
	systeme->echap = 0;

	systeme->pointeur.texture = loadTexture("rs/images/p.png");
	//systeme->BGmort = LoadingImage				("rs/fonds/mort.png", 0, systeme);
	systeme->BG =               loadTexture	("rs/ui/BG.png");
	//systeme->BGblanc = LoadingImage	("rs/ui/bgb.png", 0, systeme);

	systeme->police = TTF_OpenFont("rs/divers/dalek.ttf", TAILLE_POLICE);
	systeme->police1 = TTF_OpenFont("rs/divers/police1.ttf", TAILLE_POLICE);
	if (systeme->police == NULL ||
        systeme->police1 == NULL)
    {
        printf("police not load2\n");
    }

    setPos(&systeme->pointeur.pos, 0, 0, 20, 30);

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
	sprintf(ui->designationstuff[6], "t�te");

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

	setPos (&ui->corner_menu.pos, 0, screenh-screenh*0.063, screenw*0.036, screenh*0.065);
	setPos (&ui->corner_inventaire.pos, screenw-screenw*0.036, 0, screenw*0.036, screenh*0.065);
	setPos (&ui->corner_chat.pos, 0, 0, screenw*0.036, screenh*0.065);
	setPos (&ui->BGmenu.pos, 0, screenh/2, screenw, screenh/2);
	setPos (&ui->BoutonQuitter.pos, screenw*0.96, screenh-screenw*0.04, screenw*0.04, screenw*0.04);

	ui->BoutonQuitter.etat = B_NORMAL;

	ui->corner_menu.etat =          B_NORMAL;
	ui->corner_inventaire.etat =    B_NORMAL;
	ui->corner_chat.etat =          B_NORMAL;

	setPos (&ui->casestuff[0].pos, screenw*0.225, screenh*0.85, screenh*0.1, screenh*0.1);
	setPos (&ui->casestuff[1].pos, screenw*0.05, screenh*0.55, screenh*0.1, screenh*0.1);
	setPos (&ui->casestuff[2].pos, screenw*0.05, screenh*0.65, screenh*0.1, screenh*0.1);
	setPos (&ui->casestuff[3].pos, screenw*0.05, screenh*0.75, screenh*0.1, screenh*0.1);
	setPos (&ui->casestuff[4].pos, screenw*0.4, screenh*0.55, screenh*0.1, screenh*0.1);
	setPos (&ui->casestuff[5].pos, screenw*0.4, screenh*0.65, screenh*0.1, screenh*0.1);
	setPos (&ui->casestuff[6].pos, screenw*0.4, screenh*0.75, screenh*0.1, screenh*0.1);


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

void initmap (struct DIVERSmap *carte,struct DIVERSsysteme *systeme)/*										map*/
{
	carte->origin.x = screenw/2;
	carte->origin.y = screenh/2;

	carte->cellule.translation.x = -500;
	carte->cellule.translation.y = -1000;

    carte->cellule.pict.texture = loadTexture("rs/maps/cellule2.png");
    setPos(&carte->cellule.pict.pos, 0, 0 ,2258, 1376);
    carte->cellule.calque = IMG_Load("rs/maps/cellule2nb.png");
}

void initpnj (struct PACKpnj *pnj)/*																				pnj*/
{
    pnj->toumai.pos.x = 0;
	pnj->toumai.pos.y = 0;
	pnj->toumai.pos.w = 68;
	pnj->toumai.pos.h = 48;
	pnj->toumai.texture = loadTexture("rs/images/perso0.png");
	pnj->toumaiParle = false;
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
//	recompense->ttexterecompensecombat = imprime("vous avez gagn� :", screenw, BLANC, systeme, NULL, NULL);

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
                  struct DIVERScraft *craft,struct PACKmonstre *monstre,struct PERSO *perso,struct PACKpnj *pnj)
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

void initcombatstore(struct typecombat *BTLstr,struct DIVERSsysteme *systeme, struct DIRECTION *direction,struct PACKmonstre *monstre)
{
    #if BATTLE_LOG == 1
	printf("initialising memory for battle :\n");
	#endif
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
	BTLstr->persobouge = false;
	BTLstr->animobjet = 1;
	BTLstr->animobjetway = 0;
	BTLstr->ennemivaincue = 0;
	BTLstr->arcadescore = 0;
	BTLstr->IndexCreature = -1;

	BTLstr->temps = 0;
	BTLstr->tempsaffichage = 0;
	BTLstr->tempsseconde = 0;
	BTLstr->tempscalcul = 0;
	BTLstr->tempsanimationjoueur = 0;
	BTLstr->tempsanimationobjet = 0;
	BTLstr->TimeAddEnnemy = 0;

	direction->bas = 0;
	direction->droite = 0;
	direction->gauche = 0;
	direction->haut = 0;
	direction->direction = 0;
	direction->olddirection = 0;

	BTLstr->NBlootsol = rand()%5;  /*max declared 64*/
    #if BATTLE_LOG == 1
	printf("20%%\n");
	#endif

	for (index = 0 ; index < BTLstr->NBlootsol ; index++)
	{
	    int tmprand  = rand()%2;
	    if (tmprand == 0)
        {BTLstr->IDlootsol[index] = 7;}
        else
        {BTLstr->IDlootsol[index] = 2;}
		BTLstr->lootsol[index] = BTL_OBJ_FLOOR;
		BTLstr->plootsol[index].w = screenw*0.0439;/*60*/
		BTLstr->plootsol[index].h = screenh*0.130;/*100*/
		BTLstr->plootsol[index].x = (rand()%(screenw - (BTLstr->plootsol[index].w*2)))+BTLstr->plootsol[index].w;
		BTLstr->plootsol[index].y = (rand()%(screenh - (BTLstr->plootsol[index].h*2)))+BTLstr->plootsol[index].h;
		BTLstr->oldplootsol[index].x = 0;
		BTLstr->oldplootsol[index].y = 0;
		BTLstr->oldplootsol[index].w = BTLstr->plootsol[index].w;
		BTLstr->oldplootsol[index].h = BTLstr->plootsol[index].h;
		BTLstr->lootsolDX[index] = 0;
		BTLstr->lootsolDY[index] = 0;
		BTLstr->lootsolWAYX[index] = 0;
		BTLstr->lootsolWAYY[index] = 0;
	}
	#if BATTLE_LOG == 1
	printf("40%%\n");
	#endif

	for (index = 0 ; index < LIMITEmobARCADE ; index++)/*adapt� pour le mode arcade*/
	{

		BTLstr->premiercoup[index] = 0;
		BTLstr->creature[index].isdead = true;
		BTLstr->creature[index].iserasable = true;
		BTLstr->creature[index].Direction = 0;
		BTLstr->creature[index].mind = 0;
		BTLstr->creature[index].mindtime = 0;
		BTLstr->creature[index].looted = false;
		BTLstr->creature[index].ontheway = 0;
		BTLstr->creature[index].wayx = 0;
		BTLstr->creature[index].wayy = 0;
		for (index2 = 0 ; index2 < 8 ; index2++)
		{
			BTLstr->creature[index].relevancy[index2] = 0;
		}
		BTLstr->creature[index].m_pict.delay = 120;
		BTLstr->creature[index].m_pict.frame = 2;
		BTLstr->creature[index].m_pict.current = 0;
		for (index2 = 0 ; index2 < 3 ; index2++)
		{
            BTLstr->creature[index].m_pict.texture[index2] = monstre->rat[0].m_pict.texture[index2];
		}

		BTLstr->creature[index].STATICposition.w = 0;
		BTLstr->creature[index].STATICposition.h = 0;
	}
	#if BATTLE_LOG == 1
	printf("60%%\n");
	#endif

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
	    BTLstr->i[index] = 0;
		BTLstr->DepartBalle[index] = UNUSED;

		BTLstr->pballe[index].x = -50;
		BTLstr->pballe[index].y = -50;
		BTLstr->pballe[index].w = screenw*0.0146;
		BTLstr->pballe[index].h = screenh*0.026;
	}
	#if BATTLE_LOG == 1
	printf("80%%\n");
	#endif

	BTLstr->Pperso.x = screenw/2;
	BTLstr->Pperso.y = screenh*0.564;
	BTLstr->Pperso.w = screenw*0.050;
	BTLstr->Pperso.h = screenh*0.066;

	setPos(&BTLstr->curseur.pos, 0, 0, 30, 30);
	setPos(&BTLstr->fond.pos, 0, 0, screenw, screenh);

	BTLstr->ptVie.x = 0;
	BTLstr->ptVie.y = 0;
	BTLstr->ptVie.w = screenw*0.073;/*100*/
	BTLstr->ptVie.h = screenh*0.05;/*32*/
//	BTLstr->tVie = imprime ("0", screenw*0.3, NOIR, systeme, NULL, NULL);

	BTLstr->fond.texture = loadTexture			("rs/fonds/fondcombat.png");
	BTLstr->balle = loadTexture                 ("rs/images/balle.png");
	BTLstr->curseur.texture = loadTexture		("rs/images/curseur.png");
//	BTLstr->piece = LoadingImage			("rs/images/piece.png", 0, systeme);
	//BTLstr->peau = LoadingImage			    ("rs/objets/0#0.png", 0, systeme);

	#if BATTLE_LOG == 1
	printf("90%%\n");
	#endif

	/*bouton rejouer*/
/*	BTLstr->rejouer.normal = LoadingImage				("rs/ui/jouer.png", 0, systeme);
	BTLstr->rejouer.survoler = LoadingImage				("rs/ui/jouer2.png", 0, systeme);
	BTLstr->rejouer.cliquer = LoadingImage				("rs/ui/jouer3.png", 0, systeme);*/
	BTLstr->rejouer.pos.x = 460;
	BTLstr->rejouer.pos.y = 650;
	BTLstr->rejouer.pos.w = screenw * 0.1464;
	BTLstr->rejouer.pos.h = screenh * 0.065;
	BTLstr->rejouer.etat = B_NORMAL;
	/*bouton quitter*/
/*	BTLstr->quitter.normal = LoadingImage				("rs/ui/logquitter.png", 0, systeme);
	BTLstr->quitter.survoler = LoadingImage				("rs/ui/logquitter2.png", 0, systeme);
	BTLstr->quitter.cliquer = LoadingImage				("rs/ui/logquitter3.png", 0, systeme);*/
	BTLstr->quitter.pos.x = 700;
	BTLstr->quitter.pos.y = 650;
	BTLstr->quitter.pos.w = screenw * 0.1464;
	BTLstr->quitter.pos.h = screenh * 0.065;
	BTLstr->quitter.etat = B_NORMAL;
	#if BATTLE_LOG == 1
	printf("100%%\n");
	#endif
}

