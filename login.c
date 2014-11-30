#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#include "image.h"
#include "evenement.h"
#include "login.h"
#include "fichier.h"
#include "sauvegarde.h"
#include "ui.h"
#include "main.h"


int login (DIVERSsysteme *systeme)
{
	struct typelogin loginstore;
	struct bouton option, jouer, creer, quitter, azerty, qwerty, qwertz, arcade;
	//initialisation des variables
	InitLoginStore(&loginstore, systeme);
	//initialisation des boutons
	Initbouton(&option, &jouer, &creer, &quitter, &azerty, &qwerty, &qwertz, &arcade, systeme);

	while(loginstore.continuer == 1)
	{
		loginstore.tpact = SDL_GetTicks();

        if (loginstore.tpact - loginstore.tpapr >= 16) //16   ms
        {
            loginstore.tpapr = loginstore.tpact;

			loginstore.lettre =  '\0';

			SDL_GetMouseState(&loginstore.ppointeur.x, &loginstore.ppointeur.y);
			loginstore.continuer = boucleeventlogin(&loginstore, systeme);

			if (loginstore.continuer == 3) // creer perso
			{
				loginstore.continuer = creerjoueur(systeme->sauvegarde);
				if ( loginstore.continuer == 0) {loginstore.continuer = 2;}
				else if (loginstore.continuer == -1)
				{
					loginstore.ttextedialogue = fenetredialogue(systeme->screenw*0.3, 240, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info, ROUGE, systeme);
					loginstore.diall = 1;
					loginstore.continuer = 1;
				}
				else if (loginstore.continuer == -2)
				{
					loginstore.ttextedialogue = fenetredialogue(systeme->screenw*0.3, 240, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info2, ROUGE, systeme);
					loginstore.diall = 1;
					loginstore.continuer = 1;
				}
				else {loginstore.continuer = 1;}
			}
			else if (loginstore.continuer == 2)//jouer
			{

				loginstore.continuer = auth(systeme->sauvegarde);
				if (loginstore.continuer == -1)
				{
					loginstore.ttextedialogue = fenetredialogue(systeme->screenw*0.3, systeme->screenh*0.3, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info3, ROUGE, systeme);
					loginstore.diall = 1;
					loginstore.continuer = 1;
				}
				else if (loginstore.continuer == -2)
				{
					loginstore.ttextedialogue = fenetredialogue(systeme->screenw*0.3, systeme->screenh*0.3, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info4, ROUGE, systeme);
					loginstore.diall = 1;
					loginstore.continuer = 1;
				}
			}
			else if (loginstore.continuer == 4)
			{
				loginstore.ttextedialogue = fenetredialogue(systeme->screenw*0.7, systeme->screenh*0.15, &loginstore.pdialogue, &loginstore.ptextedialogue, "Type de clavier :                                                                                      \n",
                                                ROUGE, systeme);
				loginstore.diall = 1;
				loginstore.continuer = 1;
				loginstore.optionactif = 1;
			}

			if (loginstore.lettre != '\0' && loginstore.longpseudo < 20 && loginstore.saisiepseudo == 1)
			{
				systeme->sauvegarde[0][loginstore.longpseudo] = loginstore.lettre;
				loginstore.longpseudo++;
			}
			else if (loginstore.lettre != '\0' && loginstore.longmdp < 20 && loginstore.saisiemdp == 1)
			{
				systeme->sauvegarde[1][loginstore.longmdp] = loginstore.lettre;
				loginstore.mdpshow[loginstore.longmdp] = '*';
				loginstore.longmdp++;
			}

			for ( loginstore.i = loginstore.longpseudo ; loginstore.i <=20 ; loginstore.i++)
			{
				systeme->sauvegarde[0][loginstore.i] = '\0';
			}
			for ( loginstore.i = loginstore.longmdp ; loginstore.i <=20 ; loginstore.i++)
			{
				systeme->sauvegarde[1][loginstore.i] = '\0';
				loginstore.mdpshow[loginstore.i] = '\0';
			}
			//affichage
			affichageloggin(&loginstore, systeme, &option, &jouer, &creer, &quitter, &azerty, &qwerty, &qwertz, &arcade);
		}
		else
		{
			SDL_Delay(10);
		}
	}
	loginstore.fichier = fopen ("rs/options.RSsave", "w+");
	if (loginstore.etatazerty == 2) {fputc('1', loginstore.fichier);}
	else if (loginstore.etatqwerty == 2) {fputc('2', loginstore.fichier);}
	else if (loginstore.etatqwertz == 2) {fputc('3', loginstore.fichier);}
	fclose(loginstore.fichier);
	return loginstore.continuer;
}


//#################################################################################################################################
//#################################################################################################################################
//############################################################## creer joueur #####################################################
//#################################################################################################################################
//#################################################################################################################################


int creerjoueur(char sauvegarde[][50])
{
	if (strlen(sauvegarde[0]) == 0)
	{
		return -1;
	}

	int i;
	FILE *fichier2 = NULL;
	char nomfichier[50] = {'\0'};
	sprintf(nomfichier, "rs/sauvegarde/%s.RSCryptedSave", sauvegarde[0]);

	if (fopen((const char *)nomfichier, "r") == NULL)
	{
		int taille = TAILLESAC;
		sprintf(sauvegarde[4], "350");			//perso en x
		sprintf(sauvegarde[5], "550");			//perso en y
		sprintf(sauvegarde[7], "100");			//quantité de vie
		sprintf(sauvegarde[9], "%d", taille);	//taille sac

		fichier2 = fopen((const char *)nomfichier, "w+");

		ecris(sauvegarde[0], fichier2);
		nouvelle_ligne(fichier2);

		ecris(sauvegarde[1], fichier2);
		nouvelle_ligne(fichier2);

		nouvelle_ligne(fichier2);

		nouvelle_ligne(fichier2);

		ecris(sauvegarde[4], fichier2);
		nouvelle_ligne(fichier2);

		ecris(sauvegarde[5], fichier2);
		nouvelle_ligne(fichier2);

		nouvelle_ligne(fichier2);

		ecris(sauvegarde[7], fichier2);
		nouvelle_ligne(fichier2);

		nouvelle_ligne(fichier2);

		ecris(sauvegarde[9], fichier2);
		nouvelle_ligne(fichier2);

		ecris("-1\0", fichier2);
		nouvelle_ligne(fichier2);

		ecris("-1\0", fichier2);
		nouvelle_ligne(fichier2);

		ecris("-1\0", fichier2);
		nouvelle_ligne(fichier2);

		ecris("-1\0", fichier2);
		nouvelle_ligne(fichier2);

		ecris("-1\0", fichier2);
		nouvelle_ligne(fichier2);

		ecris("-1\0", fichier2);
		nouvelle_ligne(fichier2);

		ecris("-1\0", fichier2);
		nouvelle_ligne(fichier2);

		fclose(fichier2);

		sprintf(nomfichier, "rs/sauvegarde/%s.RSsave2", sauvegarde[0]);
		fichier2 = fopen((const char *)nomfichier, "w");
		for (i = 0 ; i < TAILLESAC ; i++)
		{
			fprintf(fichier2, "-1#0#");
		}
	}
	else
	{
		return -2;
	}

	fclose(fichier2);
	return 0;
}

//#################################################################################################################################
//#################################################################################################################################
//############################################################## authentification #####################################################
//#################################################################################################################################
//#################################################################################################################################



int auth(char login[][50])
{
	FILE *fichier = NULL;
	char nomfichier[50] = {'\0'};

	sprintf(nomfichier, "rs/sauvegarde/%s.RSCryptedSave", login[0]);

	fichier = fopen ((const char *) nomfichier, "r");
	if (fichier == NULL)
	{
		 return -1;
	}

	int i2 = 0, iligne = 0, index;
	int i = 0, LenMdpLogin = 0, LenMdpSauv = 0;
	char sauvegarde[2][50] = {{'\0'},{'\0'}};
	char caractere = '\0';
	char buffer[4096] = {'\0'};
	char ret[50] = {'\0'};

	while (i2 < 2)
	{
		caractere = fgetc(fichier);
		while (caractere != '#')
		{
			buffer[iligne] = caractere;
			iligne++;
			caractere = fgetc(fichier);
		}
		lis(buffer, ret);
		strcpy(sauvegarde[i2], ret);

		for(index = 0 ; index < 4096 ; index++)
		{
			buffer[index] = '\0';
		}
		iligne = 0;
		i2++;
	}

	LenMdpLogin = strlen(login[1]);
	LenMdpSauv = strlen(sauvegarde[1]);

	if ( LenMdpLogin != LenMdpSauv)
	{
		fclose(fichier);
		return -2;
	}

	for ( i = 0 ; i < LenMdpLogin ; i++)
	{
		if (sauvegarde[1][i] == login[1][i])
		{}
		else
		{
			fclose(fichier);
			return -2;
		}
	}
	fclose(fichier);
	return 2;
}

void InitLoginStore(typelogin *loginstore, DIVERSsysteme *systeme)
{
	loginstore->police = TTF_OpenFont("rs/divers/police1.ttf", 32);

	loginstore->pseudo.texture = imprime ("pseudo :", systeme->screenw, BLEU, systeme, &loginstore->pseudo.lenght);
	loginstore->mdp.texture = imprime ("mot de passe :", systeme->screenw, BLEU, systeme, &loginstore->mdp.lenght);

	loginstore->couleurNoir.r = 0;
	loginstore->couleurNoir.g = 0;
	loginstore->couleurNoir.b = 0;
	loginstore->couleurNoir.a = 0;

	loginstore->couleurBleu.r = 0;
	loginstore->couleurBleu.g = 75;
	loginstore->couleurBleu.b = 255;
	loginstore->couleurBleu.a = 0;

	loginstore->pecran.x = 0;
	loginstore->pecran.y = 0;
	loginstore->pecran.w = systeme->screenw;
	loginstore->pecran.h = systeme->screenh;

	loginstore->ppointeur.x = 0;
	loginstore->ppointeur.y = 0;
	loginstore->ppointeur.w = 40;
	loginstore->ppointeur.h = 60;

	loginstore->pcase.w = systeme->screenw/4;
	loginstore->pcase.h = systeme->screenh/20;
	loginstore->pcase.x = (systeme->screenw-loginstore->pcase.w)/2;
	loginstore->pcase.y = systeme->screenh/2;

	loginstore->pcase2.w = systeme->screenw/4;
	loginstore->pcase2.h = systeme->screenh/20;
	loginstore->pcase2.x = (systeme->screenw-loginstore->pcase2.w)/2;
	loginstore->pcase2.y = (systeme->screenh/2)+(systeme->screenh/8);

	loginstore->LEmdp.position.w = (systeme->screenw/4)-2;
	loginstore->LEmdp.position.h = systeme->screenh/20;
	loginstore->LEmdp.position.x = ((systeme->screenw-loginstore->LEmdp.position.w)/2)+2;
	loginstore->LEmdp.position.y = (systeme->screenh/2)+(systeme->screenh/8)+2;

	loginstore->LEpseudo.position.w = (systeme->screenw/4)-2;
	loginstore->LEpseudo.position.h = systeme->screenh/20;
	loginstore->LEpseudo.position.x = ((systeme->screenw-loginstore->LEpseudo.position.w)/2)+2;
	loginstore->LEpseudo.position.y = (systeme->screenh/2)+2;

	loginstore->pseudo.position.w = loginstore->pseudo.lenght;
	loginstore->pseudo.position.h = systeme->screenh/20;
	loginstore->pseudo.position.x = (systeme->screenw-loginstore->pseudo.position.w)/2;
	loginstore->pseudo.position.y = (systeme->screenh/2)-loginstore->pseudo.position.h;

	loginstore->mdp.position.w = loginstore->mdp.lenght;
	loginstore->mdp.position.h = systeme->screenh/20;
	loginstore->mdp.position.x = (systeme->screenw-loginstore->mdp.position.w)/2;
	loginstore->mdp.position.y = (systeme->screenh/2)+(systeme->screenh/8)-loginstore->pseudo.position.h;

	loginstore->pcachermdp.w = systeme->screenw/6;
	loginstore->pcachermdp.h = systeme->screenh/12;
	loginstore->pcachermdp.x =(systeme->screenw/8)*6;
	loginstore->pcachermdp.y =(systeme->screenh/8)*5;

	loginstore->pcoche.w = loginstore->pcachermdp.w/3;
	loginstore->pcoche.h = loginstore->pcachermdp.h*1.3;
	loginstore->pcoche.x =(systeme->screenw/8)*6;
	loginstore->pcoche.y =((systeme->screenh/8)*5)-25;

	loginstore->continuer = 1;
	loginstore->saisiepseudo = false;
	loginstore->saisiemdp = false;
	loginstore->longpseudo = 0;
	loginstore->i = 0;
	loginstore->longmdp = 0;
	loginstore->diall = 0;
	loginstore->optionactif = 0;
	loginstore->mdpcacher = 1;
	loginstore->etatoption = 0;
	loginstore->etatjouer = 0;
	loginstore->etatcreer = 0;
	loginstore->etatquitter = 0;
	loginstore->etatazerty = 0;
	loginstore->etatqwerty = 0;
	loginstore->etatqwertz = 0;
	loginstore->tpact = 0;
	loginstore->tpapr = 0;
	loginstore->lettre = '0';

	//récupération du type de clavier utilisé
	loginstore->fichier = fopen("rs/options.RSsave", "r");
	systeme->typeclavier = fgetc(loginstore->fichier);
	fclose(loginstore->fichier);

	for (loginstore->i = 0 ; loginstore->i < 21 ; loginstore->i++)
	{
		loginstore->mdpshow[loginstore->i] = '\0';
	}

	if (systeme->typeclavier == '1') {loginstore->etatazerty =2;}
	else if (systeme->typeclavier == '2') {loginstore->etatqwerty =2;}
	else if (systeme->typeclavier == '3') {loginstore->etatqwertz =2;}

	sprintf(loginstore->info, "Pseudo incorrect \n\nveuillez entrer un pseudo et un mot de passe.");
	sprintf(loginstore->info2, "Pseudo incorrect\n\nLe pseudo que vous avez entre existe deja, veuillez en choisir un autre.");
	sprintf(loginstore->info3, "Identifiants incorrects\n\nVotre personnage n'existe pas, creez en un sans attendre !");
	sprintf(loginstore->info4, "Identifiants incorrects\n\nVotre mot de passe et votre pseudo ne correspondent pas.\n\nessayer un autre mot de passe.");

	loginstore->login = LoadingImage		("rs/fonds/login.png", 0, systeme);
	loginstore->pointeur = LoadingImage	("rs/images/p.png", 0, systeme);
	loginstore->lacase = LoadingImage		("rs/images/case.png", 0, systeme);
	loginstore->lacase0 = LoadingImage		("rs/images/case0.png", 0, systeme);
	loginstore->tdialogue = LoadingImage		("rs/ui/fenetreinfo.png", 0, systeme);
	loginstore->cachermdp = LoadingImage		("rs/images/cachermdp.png", 0, systeme);
	loginstore->coche = LoadingImage		("rs/images/coche.png", 0, systeme);

	loginstore->ttextedialogue = NULL;
}

void Initbouton(bouton *option, bouton *jouer, bouton *creer, bouton *quitter, bouton *azerty, bouton *qwerty, bouton *qwertz,
				bouton *arcade, DIVERSsysteme *systeme)
{
	option->normal = LoadingImage		("rs/ui/options.png", 0, systeme);
	option->survoler = LoadingImage		("rs/ui/options2.png", 0, systeme);
	option->cliquer = LoadingImage		("rs/ui/options3.png", 0, systeme);
	option->pos.x = systeme->screenw/11;
	option->pos.y = (systeme->screenh/6)*5;
	option->pos.w = systeme->screenw/11;
	option->pos.h = systeme->screenh/12;

	jouer->normal = LoadingImage		("rs/ui/jouer.png", 0, systeme);
	jouer->survoler = LoadingImage		("rs/ui/jouer2.png", 0, systeme);
	jouer->cliquer = LoadingImage		("rs/ui/jouer3.png", 0, systeme);
	jouer->pos.x = (systeme->screenw/11)*3;
	jouer->pos.y = (systeme->screenh/6)*5;
	jouer->pos.w = systeme->screenw/11;
	jouer->pos.h = systeme->screenh/12;

	creer->normal = LoadingImage		("rs/ui/creer.png", 0, systeme);
	creer->survoler = LoadingImage		("rs/ui/creer2.png", 0, systeme);
	creer->cliquer = LoadingImage		("rs/ui/creer3.png", 0, systeme);
	creer->pos.x = (systeme->screenw/11)*5;
	creer->pos.y = (systeme->screenh/6)*5;
	creer->pos.w = systeme->screenw/11;
	creer->pos.h = systeme->screenh/12;

	quitter->normal = LoadingImage		("rs/ui/logquitter.png", 0, systeme);
	quitter->survoler = LoadingImage		("rs/ui/logquitter2.png", 0, systeme);
	quitter->cliquer = LoadingImage		("rs/ui/logquitter3.png", 0, systeme);
	quitter->pos.x = (systeme->screenw/11)*7;
	quitter->pos.y = (systeme->screenh/6)*5;
	quitter->pos.w = systeme->screenw/11;
	quitter->pos.h = systeme->screenh/12;

	azerty->normal = LoadingImage		("rs/ui/azerty.png", 0, systeme);
	azerty->survoler = LoadingImage		("rs/ui/azerty2.png", 0, systeme);
	azerty->cliquer = LoadingImage		("rs/ui/azerty3.png", 0, systeme);
	azerty->pos.w = systeme->screenw/11;
	azerty->pos.h = systeme->screenh/18;
	azerty->pos.x = (systeme->screenw/11)*4;
	azerty->pos.y = (systeme->screenh/30)*14;

	qwerty->normal = LoadingImage		("rs/ui/qwerty.png", 0, systeme);
	qwerty->survoler = LoadingImage		("rs/ui/qwerty2.png", 0, systeme);
	qwerty->cliquer = LoadingImage		("rs/ui/qwerty3.png", 0, systeme);
	qwerty->pos.w = systeme->screenw/11;
	qwerty->pos.h = systeme->screenh/18;
	qwerty->pos.x = (systeme->screenw/11)*6;
	qwerty->pos.y = (systeme->screenh/30)*14;

    qwertz->normal = LoadingImage		("rs/ui/qwertz.png", 0, systeme);
	qwertz->survoler = LoadingImage		("rs/ui/qwertz2.png", 0, systeme);
	qwertz->cliquer = LoadingImage		("rs/ui/qwertz3.png", 0, systeme);
	qwertz->pos.w = systeme->screenw/11;
	qwertz->pos.h = systeme->screenh/18;
	qwertz->pos.x = (systeme->screenw/11)*8;
	qwertz->pos.y = (systeme->screenh/30)*14;
	
	arcade->normal = LoadingImage		("rs/ui/arcade.png", 0, systeme);
	arcade->survoler = LoadingImage		("rs/ui/arcade.png", 0, systeme);
	arcade->cliquer = LoadingImage		("rs/ui/arcade.png", 0, systeme);
	arcade->pos.x = (systeme->screenw/11)*9;
	arcade->pos.y = (systeme->screenh/6)*5;
	arcade->pos.w = systeme->screenw/11;
	arcade->pos.h = systeme->screenh/12;

}

void affichageloggin(typelogin *loginstore, DIVERSsysteme *systeme, bouton *option, bouton *jouer, bouton *creer, bouton *quitter,
					bouton *azerty, bouton *qwerty, bouton *qwertz, bouton *arcade)
{
    SDL_RenderClear(systeme->renderer);

    SDL_RenderCopy(systeme->renderer, loginstore->login, NULL, &loginstore->pecran);//						fond

    if (loginstore->saisiepseudo == 1)
    {
        SDL_RenderCopy(systeme->renderer, loginstore->lacase, NULL, &loginstore->pcase);//					pseudo case bleu
        SDL_RenderCopy(systeme->renderer, loginstore->lacase0, NULL, &loginstore->pcase2);
    }
    else if (loginstore->saisiemdp == 1)
    {
        SDL_RenderCopy(systeme->renderer, loginstore->lacase, NULL, &loginstore->pcase2);//					mdp case bleu
        SDL_RenderCopy(systeme->renderer, loginstore->lacase0, NULL, &loginstore->pcase);
    }
    else
    {
        SDL_RenderCopy(systeme->renderer, loginstore->lacase0, NULL, &loginstore->pcase2);
        SDL_RenderCopy(systeme->renderer, loginstore->lacase0, NULL, &loginstore->pcase);
    }

    if (loginstore->etatoption == 0)
    {   SDL_RenderCopy(systeme->renderer, option->normal, NULL, &option->pos);}
    else if (loginstore->etatoption == 1)
    {   SDL_RenderCopy(systeme->renderer, option->survoler, NULL, &option->pos);}
    else
    {   SDL_RenderCopy(systeme->renderer, option->cliquer, NULL, &option->pos);}

    if (loginstore->etatjouer == 0)
    {   SDL_RenderCopy(systeme->renderer, jouer->normal, NULL, &jouer->pos);}
    else if (loginstore->etatjouer == 1)
    {   SDL_RenderCopy(systeme->renderer, jouer->survoler, NULL, &jouer->pos);}
    else
    {   SDL_RenderCopy(systeme->renderer, jouer->cliquer, NULL, &jouer->pos);}

    if (loginstore->etatquitter == 0)
    {   SDL_RenderCopy(systeme->renderer, quitter->normal, NULL, &quitter->pos);}
    else if (loginstore->etatquitter == 1)
    {   SDL_RenderCopy(systeme->renderer, quitter->survoler, NULL, &quitter->pos);}
    else
    {   SDL_RenderCopy(systeme->renderer, quitter->cliquer, NULL, &quitter->pos);}

    if (loginstore->etatcreer == 0)
    {   SDL_RenderCopy(systeme->renderer, creer->normal, NULL, &creer->pos);}
    else if (loginstore->etatcreer == 1)
    {   SDL_RenderCopy(systeme->renderer, creer->survoler, NULL, &creer->pos);}
    else
    {   SDL_RenderCopy(systeme->renderer, creer->cliquer, NULL, &creer->pos);}
    
    if (loginstore->etatarcade == 0)
    {   SDL_RenderCopy(systeme->renderer, arcade->normal, NULL, &arcade->pos);}
    else if (loginstore->etatarcade == 1)
    {   SDL_RenderCopy(systeme->renderer, arcade->survoler, NULL, &arcade->pos);}
    else
    {   SDL_RenderCopy(systeme->renderer, arcade->cliquer, NULL, &arcade->pos);}

    //mot de passe et pseudo

    if (loginstore->mdpcacher == 0)
    {   loginstore->LEmdp.texture = imprime(systeme->sauvegarde[1], systeme->screenw, NOIR, systeme, &loginstore->LEmdp.lenght);}
    else
    {   loginstore->LEmdp.texture = imprime(loginstore->mdpshow, systeme->screenw, NOIR, systeme, &loginstore->LEmdp.lenght);}
    loginstore->LEpseudo.texture = imprime(systeme->sauvegarde[0], systeme->screenw, NOIR, systeme, &loginstore->LEpseudo.lenght);

    loginstore->LEpseudo.position.w = loginstore->LEpseudo.lenght;
    loginstore->LEmdp.position.w = loginstore->LEmdp.lenght;

    SDL_RenderCopy(systeme->renderer, loginstore->LEpseudo.texture, NULL, &loginstore->LEpseudo.position);//pseudo
    SDL_RenderCopy(systeme->renderer, loginstore->LEmdp.texture, NULL, &loginstore->LEmdp.position);//mot de passe

    SDL_RenderCopy(systeme->renderer, loginstore->pseudo.texture, NULL, &loginstore->pseudo.position);// demande pseudo
    SDL_RenderCopy(systeme->renderer, loginstore->mdp.texture, NULL, &loginstore->mdp.position);// demande mot de passe


    SDL_RenderCopy(systeme->renderer, loginstore->cachermdp, NULL, &loginstore->pcachermdp);//coche
    if (loginstore->mdpcacher == 1)
    {   SDL_RenderCopy(systeme->renderer, loginstore->coche, NULL, &loginstore->pcoche);}

    if (loginstore->diall == 1)
    {
        SDL_RenderCopy	(systeme->renderer, loginstore->tdialogue, NULL, &loginstore->pdialogue);
        SDL_RenderCopy	(systeme->renderer, loginstore->ttextedialogue, NULL, &loginstore->ptextedialogue);
    }
    if (loginstore->optionactif == 1)
    {
        if (loginstore->etatazerty == 0)
        {   SDL_RenderCopy(systeme->renderer, azerty->normal, NULL, &azerty->pos);}
        else if (loginstore->etatazerty == 1)
        {   SDL_RenderCopy(systeme->renderer, azerty->survoler, NULL, &azerty->pos);}
        else
        {   SDL_RenderCopy(systeme->renderer, azerty->cliquer, NULL, &azerty->pos);}

        if (loginstore->etatqwerty == 0)
        {   SDL_RenderCopy(systeme->renderer, qwerty->normal, NULL, &qwerty->pos);}
        else if (loginstore->etatqwerty == 1)
        {   SDL_RenderCopy(systeme->renderer, qwerty->survoler, NULL, &qwerty->pos);}
        else
        {   SDL_RenderCopy(systeme->renderer, qwerty->cliquer, NULL, &qwerty->pos);}

        if (loginstore->etatqwertz == 0)
        {   SDL_RenderCopy(systeme->renderer, qwertz->normal, NULL, &qwertz->pos);}
        else if (loginstore->etatqwertz == 1)
        {   SDL_RenderCopy(systeme->renderer, qwertz->survoler, NULL, &qwertz->pos);}
        else
        {   SDL_RenderCopy(systeme->renderer, qwertz->cliquer, NULL, &qwertz->pos);}
    }

    SDL_RenderCopy(systeme->renderer, loginstore->pointeur, NULL, &loginstore->ppointeur); //souris

    SDL_RenderPresent(systeme->renderer);

    SDL_DestroyTexture(loginstore->LEpseudo.texture);
    SDL_DestroyTexture(loginstore->LEmdp.texture);
}
