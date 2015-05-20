#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
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
	//initialisation des variables
	InitLoginStore(&loginstore, systeme);
	//initialisation des boutons
	Initbouton(&loginstore, systeme);

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
					loginstore.menu = true;
					loginstore.continuer = 1;
				}
				else if (loginstore.continuer == -2)
				{
					loginstore.ttextedialogue = fenetredialogue(systeme->screenw*0.3, 240, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info2, ROUGE, systeme);
					loginstore.menu = true;
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
					loginstore.menu = true;
					loginstore.continuer = 1;
				}
				else if (loginstore.continuer == -2)
				{
					loginstore.ttextedialogue = fenetredialogue(systeme->screenw*0.3, systeme->screenh*0.3, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info4, ROUGE, systeme);
					loginstore.menu = true;
					loginstore.continuer = 1;
				}
			}
			else if (loginstore.continuer == 4)
			{
				loginstore.ttextedialogue = fenetredialogue(systeme->screenw*0.7, systeme->screenh*0.15, &loginstore.pdialogue, &loginstore.ptextedialogue, " ",
                                                ROUGE, systeme);
				loginstore.menu = true;
				loginstore.continuer = 1;
				loginstore.optionactif = 1;
			}

			if (loginstore.lettre != '\0' && loginstore.longpseudo < 20 && loginstore.saisiepseudo == true)
			{
				systeme->sauvegarde[0][loginstore.longpseudo] = loginstore.lettre;
				loginstore.longpseudo++;
			}
			else if (loginstore.lettre != '\0' && loginstore.longmdp < 20 && loginstore.saisiemdp == true)
			{
				systeme->sauvegarde[1][loginstore.longmdp] = loginstore.lettre;
				loginstore.mdpshow[loginstore.longmdp] = 'X';
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
			affichageloggin(&loginstore, systeme);
		}
		else if (loginstore.tpact - loginstore.tpcurseur >= 500)
        {
            loginstore.tpcurseur = loginstore.tpact;
            if (loginstore.clignote == TRUE)
                {   loginstore.clignote = FALSE;    }
            else
                {   loginstore.clignote = TRUE;     }
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
	loginstore->police = TTF_OpenFont("rs/divers/police1.ttf", TAILLE_POLICE_LOGIN);

	loginstore->pseudo.texture = imprime ("pseudo :", systeme->screenw, BLEU, systeme, &loginstore->pseudo.lenght, NULL);
	loginstore->mdp.texture = imprime ("mot de passe :", systeme->screenw, BLEU, systeme, &loginstore->mdp.lenght, NULL);

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

	loginstore->pcurseurMDP.x = 0;
	loginstore->pcurseurMDP.y = 0;
	loginstore->pcurseurMDP.w = 3;
	loginstore->pcurseurMDP.h = TAILLE_POLICE_LOGIN;

	loginstore->pcurseurPSEUDO.x = 0;
	loginstore->pcurseurPSEUDO.y = 0;
	loginstore->pcurseurPSEUDO.w = 3;
	loginstore->pcurseurPSEUDO.h = TAILLE_POLICE_LOGIN;

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
	loginstore->LEmdp.lenght = -1;
	loginstore->LEmdp.high = -1;

	loginstore->LEpseudo.position.w = (systeme->screenw/4)-2;
	loginstore->LEpseudo.position.h = systeme->screenh/20;
	loginstore->LEpseudo.position.x = ((systeme->screenw-loginstore->LEpseudo.position.w)/2)+2;
	loginstore->LEpseudo.position.y = (systeme->screenh/2)+2;
	loginstore->LEpseudo.lenght = -1;
	loginstore->LEpseudo.high = -1;

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

    loginstore->saisiepseudo = true;
	loginstore->saisiemdp = false;
	loginstore->clignote = true;

	loginstore->continuer = 1;
	loginstore->longpseudo = 0;
	loginstore->i = 0;
	loginstore->longmdp = 0;
	loginstore->menu = false;
	loginstore->optionactif = 0;
	loginstore->mdpcacher = 1;
	loginstore->etatoption = B_NORMAL;
	loginstore->etatjouer = B_NORMAL;
	loginstore->etatcreer = B_NORMAL;
	loginstore->etatquitter = B_NORMAL;
	loginstore->etatazerty = B_NORMAL;
	loginstore->etatqwerty = B_NORMAL;
	loginstore->etatqwertz = B_NORMAL;
	loginstore->tpact = 0;
	loginstore->tpapr = 0;
	loginstore->tpcurseur = 0;
	loginstore->lettre = '0';

	//récupération du type de clavier utilisé
	loginstore->fichier = fopen("rs/options.RSsave", "r");
	systeme->typeclavier = fgetc(loginstore->fichier);
	fclose(loginstore->fichier);

	for (loginstore->i = 0 ; loginstore->i < 21 ; loginstore->i++)
	{
		loginstore->mdpshow[loginstore->i] = '\0';
	}

	if (systeme->typeclavier == '1') {loginstore->etatazerty = B_CLIQUER;}
	else if (systeme->typeclavier == '2') {loginstore->etatqwerty = B_CLIQUER;}
	else if (systeme->typeclavier == '3') {loginstore->etatqwertz = B_CLIQUER;}

	sprintf(loginstore->info, "Pseudo incorrect \n\nveuillez entrer un pseudo et un mot de passe.");
	sprintf(loginstore->info2, "Pseudo incorrect\n\nLe pseudo que vous avez entre existe deja, veuillez en choisir un autre.");
	sprintf(loginstore->info3, "Identifiants incorrects\n\nVotre personnage n'existe pas, creez en un sans attendre !");
	sprintf(loginstore->info4, "Identifiants incorrects\n\nVotre mot de passe et votre pseudo ne correspondent pas.\n\nessayer un autre mot de passe.");

	loginstore->login = LoadingImage        ("rs/fonds/login.png", 0, systeme);
	loginstore->pointeur = LoadingImage	    ("rs/images/p.png", 0, systeme);
	loginstore->blueBox = LoadingImage		("rs/images/blueBox.png", 0, systeme);
	loginstore->whiteBox = LoadingImage		("rs/images/whiteBox.png", 0, systeme);
	loginstore->tdialogue = LoadingImage	("rs/ui/fenetreinfo.png", 0, systeme);
	loginstore->cachermdp = LoadingImage	("rs/images/cachermdp.png", 0, systeme);
	loginstore->coche = LoadingImage		("rs/images/coche.png", 0, systeme);
	loginstore->curseur = systeme->noir;

	loginstore->ttextedialogue = NULL;
}


void Initbouton(typelogin *loginstore, DIVERSsysteme *systeme)
{
	loginstore->option.normal = LoadingImage		("rs/ui/options.png", 0, systeme);
	loginstore->option.survoler = LoadingImage		("rs/ui/options2.png", 0, systeme);
	loginstore->option.cliquer = LoadingImage		("rs/ui/options3.png", 0, systeme);
	loginstore->option.pos.x = systeme->screenw/11;
	loginstore->option.pos.y = (systeme->screenh/6)*5;
	loginstore->option.pos.w = systeme->screenw/11;
	loginstore->option.pos.h = systeme->screenh/12;

	loginstore->jouer.normal = LoadingImage		("rs/ui/jouer.png", 0, systeme);
	loginstore->jouer.survoler = LoadingImage		("rs/ui/jouer2.png", 0, systeme);
	loginstore->jouer.cliquer = LoadingImage		("rs/ui/jouer3.png", 0, systeme);
	loginstore->jouer.impossible = LoadingImage		("rs/ui/jouernon.png", 0, systeme);
	loginstore->jouer.pos.x = (systeme->screenw/11)*3;
	loginstore->jouer.pos.y = (systeme->screenh/6)*5;
	loginstore->jouer.pos.w = systeme->screenw/11;
	loginstore->jouer.pos.h = systeme->screenh/12;

	loginstore->creer.normal = LoadingImage		("rs/ui/creer.png", 0, systeme);
	loginstore->creer.survoler = LoadingImage		("rs/ui/creer2.png", 0, systeme);
	loginstore->creer.cliquer = LoadingImage		("rs/ui/creer3.png", 0, systeme);
	loginstore->creer.impossible = LoadingImage		("rs/ui/creernon.png", 0, systeme);
	loginstore->creer.pos.x = (systeme->screenw/11)*5;
	loginstore->creer.pos.y = (systeme->screenh/6)*5;
	loginstore->creer.pos.w = systeme->screenw/11;
	loginstore->creer.pos.h = systeme->screenh/12;

	loginstore->quitter.normal = LoadingImage		("rs/ui/logquitter.png", 0, systeme);
	loginstore->quitter.survoler = LoadingImage		("rs/ui/logquitter2.png", 0, systeme);
	loginstore->quitter.cliquer = LoadingImage		("rs/ui/logquitter3.png", 0, systeme);
	loginstore->quitter.pos.x = (systeme->screenw/11)*7;
	loginstore->quitter.pos.y = (systeme->screenh/6)*5;
	loginstore->quitter.pos.w = systeme->screenw/11;
	loginstore->quitter.pos.h = systeme->screenh/12;

    int menuw = systeme->screenw*0.7;
    int menuh = systeme->screenh*0.15;
    int gauche = systeme->screenw*0.15;
    int haut = systeme->screenh*0.425;

	loginstore->azerty.normal = LoadingImage		("rs/ui/azerty.png", 0, systeme);
	loginstore->azerty.survoler = LoadingImage		("rs/ui/azerty2.png", 0, systeme);
	loginstore->azerty.cliquer = LoadingImage		("rs/ui/azerty3.png", 0, systeme);
	loginstore->azerty.pos.w = menuw/7;
	loginstore->azerty.pos.h = menuh/3;
	loginstore->azerty.pos.x = menuw/7+gauche;
	loginstore->azerty.pos.y = menuh/3+haut;

	loginstore->qwerty.normal = LoadingImage		("rs/ui/qwerty.png", 0, systeme);
	loginstore->qwerty.survoler = LoadingImage		("rs/ui/qwerty2.png", 0, systeme);
	loginstore->qwerty.cliquer = LoadingImage		("rs/ui/qwerty3.png", 0, systeme);
	loginstore->qwerty.pos.w = menuw/7;
	loginstore->qwerty.pos.h = menuh/3;
	loginstore->qwerty.pos.x = (menuw/7)*3+gauche;
	loginstore->qwerty.pos.y = menuh/3+haut;

    loginstore->qwertz.normal = LoadingImage		("rs/ui/qwertz.png", 0, systeme);
	loginstore->qwertz.survoler = LoadingImage		("rs/ui/qwertz2.png", 0, systeme);
	loginstore->qwertz.cliquer = LoadingImage		("rs/ui/qwertz3.png", 0, systeme);
	loginstore->qwertz.pos.w = menuw/7;
	loginstore->qwertz.pos.h = menuh/3;
	loginstore->qwertz.pos.x = (menuw/7)*5+gauche;
	loginstore->qwertz.pos.y = menuh/3+haut;

	loginstore->arcade.normal = LoadingImage		("rs/ui/arcade.png", 0, systeme);
	loginstore->arcade.survoler = LoadingImage		("rs/ui/arcade.png", 0, systeme);
	loginstore->arcade.cliquer = LoadingImage		("rs/ui/arcade.png", 0, systeme);
	loginstore->arcade.pos.x = (systeme->screenw/11)*9;
	loginstore->arcade.pos.y = (systeme->screenh/6)*5;
	loginstore->arcade.pos.w = systeme->screenw/11;
	loginstore->arcade.pos.h = systeme->screenh/12;

}

void affichageloggin(typelogin *loginstore, DIVERSsysteme *systeme)
{
    SDL_RenderClear(systeme->renderer);

    SDL_RenderCopy(systeme->renderer, loginstore->login, NULL, &loginstore->pecran);//background

    if (loginstore->etatoption == B_NORMAL)
    {   SDL_RenderCopy(systeme->renderer, loginstore->option.normal, NULL, &loginstore->option.pos);}
    else if (loginstore->etatoption == B_SURVOLER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->option.survoler, NULL, &loginstore->option.pos);}
    else if (loginstore->etatoption == B_CLIQUER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->option.cliquer, NULL, &loginstore->option.pos);}

    if (loginstore->etatjouer == B_NORMAL)
    {   SDL_RenderCopy(systeme->renderer, loginstore->jouer.normal, NULL, &loginstore->jouer.pos);}
    else if (loginstore->etatjouer == B_SURVOLER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->jouer.survoler, NULL, &loginstore->jouer.pos);}
    else if (loginstore->etatjouer == B_CLIQUER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->jouer.cliquer, NULL, &loginstore->jouer.pos);}
    else if (loginstore->etatjouer == B_IMPOSSIBLE)
    {   SDL_RenderCopy(systeme->renderer, loginstore->jouer.impossible, NULL, &loginstore->jouer.pos);}

    if (loginstore->etatquitter == B_NORMAL)
    {   SDL_RenderCopy(systeme->renderer, loginstore->quitter.normal, NULL, &loginstore->quitter.pos);}
    else if (loginstore->etatquitter == B_SURVOLER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->quitter.survoler, NULL, &loginstore->quitter.pos);}
    else if (loginstore->etatquitter == B_CLIQUER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->quitter.cliquer, NULL, &loginstore->quitter.pos);}

    if (loginstore->etatcreer == B_NORMAL)
    {   SDL_RenderCopy(systeme->renderer, loginstore->creer.normal, NULL, &loginstore->creer.pos);}
    else if (loginstore->etatcreer == B_SURVOLER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->creer.survoler, NULL, &loginstore->creer.pos);}
    else if (loginstore->etatcreer == B_CLIQUER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->creer.cliquer, NULL, &loginstore->creer.pos);}
    else if (loginstore->etatcreer == B_IMPOSSIBLE)
    {   SDL_RenderCopy(systeme->renderer, loginstore->creer.impossible, NULL, &loginstore->creer.pos);}

    if (loginstore->etatarcade == B_NORMAL)
    {   SDL_RenderCopy(systeme->renderer, loginstore->arcade.normal, NULL, &loginstore->arcade.pos);}
    else if (loginstore->etatarcade == B_SURVOLER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->arcade.survoler, NULL, &loginstore->arcade.pos);}
    else if (loginstore->etatarcade == B_CLIQUER)
    {   SDL_RenderCopy(systeme->renderer, loginstore->arcade.cliquer, NULL, &loginstore->arcade.pos);}

    //mot de passe et pseudo


    if (loginstore->saisiepseudo == true)
    {   SDL_RenderCopy(systeme->renderer, loginstore->blueBox, NULL, &loginstore->pcase);     }
    else
    {   SDL_RenderCopy(systeme->renderer, loginstore->whiteBox, NULL, &loginstore->pcase);    }

    if (loginstore->saisiemdp == true)
    {   SDL_RenderCopy(systeme->renderer, loginstore->blueBox, NULL, &loginstore->pcase2);     }
    else
    {   SDL_RenderCopy(systeme->renderer, loginstore->whiteBox, NULL, &loginstore->pcase2);   }

    if(loginstore->longmdp > 0)
    {
        if (loginstore->mdpcacher == 0)
        {   loginstore->LEmdp.texture = imprime(systeme->sauvegarde[1], systeme->screenw, NOIR, systeme, &loginstore->LEmdp.lenght, NULL);}
        else
        {   loginstore->LEmdp.texture = imprime(loginstore->mdpshow, systeme->screenw, NOIR, systeme, &loginstore->LEmdp.lenght, NULL);}
        loginstore->LEmdp.position.w = loginstore->LEmdp.lenght;
        SDL_RenderCopy(systeme->renderer, loginstore->LEmdp.texture, NULL, &loginstore->LEmdp.position);//password
    }
    if(loginstore->longpseudo > 0)
    {
        loginstore->LEpseudo.texture = imprime(systeme->sauvegarde[0], systeme->screenw, NOIR, systeme, &loginstore->LEpseudo.lenght, NULL);
        loginstore->LEpseudo.position.w = loginstore->LEpseudo.lenght;
        SDL_RenderCopy(systeme->renderer, loginstore->LEpseudo.texture, NULL, &loginstore->LEpseudo.position);//login

        if (loginstore->saisiepseudo == true && loginstore->clignote == TRUE)
        {
            loginstore->pcurseurPSEUDO.x = loginstore->LEpseudo.position.x + loginstore->LEpseudo.position.w + 2;
            loginstore->pcurseurPSEUDO.y = loginstore->LEpseudo.position.y + 5;
            SDL_RenderCopy(systeme->renderer, loginstore->curseur, NULL, &loginstore->pcurseurPSEUDO);// cursor after login
        }
    }

    if (loginstore->saisiemdp == true && loginstore->clignote == true)
    {
        if (loginstore->longmdp > 0)
        {
            loginstore->pcurseurMDP.x = loginstore->LEmdp.position.x + loginstore->LEmdp.position.w + 2;
            loginstore->pcurseurMDP.y = loginstore->LEmdp.position.y + 5;
        }
        else
        {
            loginstore->pcurseurMDP.x = loginstore->pcase2.x + 5;
            loginstore->pcurseurMDP.y = loginstore->pcase2.y + 5;
        }
        SDL_RenderCopy(systeme->renderer, loginstore->curseur, NULL, &loginstore->pcurseurMDP);// cursor after password
    }
    else if (loginstore->saisiepseudo == true && loginstore->clignote == true)
    {
        if (loginstore->longpseudo > 0)
        {
            loginstore->pcurseurPSEUDO.x = loginstore->LEpseudo.position.x + loginstore->LEpseudo.position.w + 2;
            loginstore->pcurseurPSEUDO.y = loginstore->LEpseudo.position.y + 5;
        }
        else
        {
            loginstore->pcurseurPSEUDO.x = loginstore->pcase.x + 5;
            loginstore->pcurseurPSEUDO.y = loginstore->pcase.y + 5;
        }
        SDL_RenderCopy(systeme->renderer, loginstore->curseur, NULL, &loginstore->pcurseurPSEUDO);// cursor after login
    }

    SDL_RenderCopy(systeme->renderer, loginstore->pseudo.texture, NULL, &loginstore->pseudo.position);// ask login
    SDL_RenderCopy(systeme->renderer, loginstore->mdp.texture, NULL, &loginstore->mdp.position);// ask password


    SDL_RenderCopy(systeme->renderer, loginstore->cachermdp, NULL, &loginstore->pcachermdp);//tick box
    if (loginstore->mdpcacher == 1)
    {   SDL_RenderCopy(systeme->renderer, loginstore->coche, NULL, &loginstore->pcoche);}//tick


     if (loginstore->menu == true)
    {
        SDL_RenderCopy	(systeme->renderer, loginstore->tdialogue, NULL, &loginstore->pdialogue);
        SDL_RenderCopy	(systeme->renderer, loginstore->ttextedialogue, NULL, &loginstore->ptextedialogue);
    }

    if (loginstore->optionactif == 1)
    {
        if (loginstore->etatazerty == B_NORMAL)
        {   SDL_RenderCopy(systeme->renderer, loginstore->azerty.normal, NULL, &loginstore->azerty.pos);}
        else if (loginstore->etatazerty == B_SURVOLER)
        {   SDL_RenderCopy(systeme->renderer, loginstore->azerty.survoler, NULL, &loginstore->azerty.pos);}
        else if (loginstore->etatazerty == B_CLIQUER)
        {   SDL_RenderCopy(systeme->renderer, loginstore->azerty.cliquer, NULL, &loginstore->azerty.pos);}

        if (loginstore->etatqwerty == B_NORMAL)
        {   SDL_RenderCopy(systeme->renderer, loginstore->qwertz.normal, NULL, &loginstore->qwerty.pos);}
        else if (loginstore->etatqwerty == B_SURVOLER)
        {   SDL_RenderCopy(systeme->renderer, loginstore->qwertz.survoler, NULL, &loginstore->qwerty.pos);}
        else if (loginstore->etatqwerty == B_CLIQUER)
        {   SDL_RenderCopy(systeme->renderer, loginstore->qwertz.cliquer, NULL, &loginstore->qwerty.pos);}

        if (loginstore->etatqwertz == B_NORMAL)
        {   SDL_RenderCopy(systeme->renderer, loginstore->qwerty.normal, NULL, &loginstore->qwertz.pos);}
        else if (loginstore->etatqwertz == B_SURVOLER)
        {   SDL_RenderCopy(systeme->renderer, loginstore->qwerty.survoler, NULL, &loginstore->qwertz.pos);}
        else if (loginstore->etatqwertz == B_CLIQUER)
        {   SDL_RenderCopy(systeme->renderer, loginstore->qwerty.cliquer, NULL, &loginstore->qwertz.pos);}
    }

    SDL_RenderCopy(systeme->renderer, loginstore->pointeur, NULL, &loginstore->ppointeur); //souris

    SDL_RenderPresent(systeme->renderer);

    if(loginstore->longpseudo > 0)
        {SDL_DestroyTexture(loginstore->LEpseudo.texture);}
    if(loginstore->longmdp > 0)
        {SDL_DestroyTexture(loginstore->LEmdp.texture);}
}
