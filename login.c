
#include "login.h"

#include "evenement.h"
#include "ui.h"
#include "sauvegarde.h"
#include "fichier.h"

extern int screenh, screenw;

int login (struct DIVERSsysteme *systeme)
{
	struct typelogin loginstore;

	/*initialisation des variables*/
	InitLoginStore(&loginstore, systeme);
	/*initialisation des boutons*/
	Initbouton(&loginstore, systeme);

	while(loginstore.continuer == 1)
	{
		loginstore.tpact = SDL_GetTicks();

        if (loginstore.tpact - loginstore.tpapr >= 16) /*16   ms*/
        {
            loginstore.tpapr = loginstore.tpact;

			loginstore.lettre =  '\0';

			SDL_GetMouseState(&loginstore.pointeur.pos.x, &loginstore.pointeur.pos.y);
			loginstore.pointeur.pos.y = (loginstore.pointeur.pos.y - screenh) * -1;
			loginstore.continuer = boucleeventlogin(&loginstore, systeme);

			if (loginstore.continuer == 3) /* creer perso*/
			{
				loginstore.continuer = creerjoueur(systeme->sauvegarde);
				if ( loginstore.continuer == 0) {loginstore.continuer = 2;}
				else if (loginstore.continuer == -1)
				{
					loginstore.ttextedialogue = fenetredialogue(screenw*0.3, 240, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info, &systeme->rouge, systeme);
					loginstore.menu = true;
					loginstore.continuer = 1;
				}
				else if (loginstore.continuer == -2)
				{
					loginstore.ttextedialogue = fenetredialogue(screenw*0.3, 240, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info2, &systeme->rouge, systeme);
					loginstore.menu = true;
					loginstore.continuer = 1;
				}
				else {loginstore.continuer = 1;}
			}
			else if (loginstore.continuer == 2)/*jouer*/
			{

				loginstore.continuer = auth(systeme->sauvegarde);
				if (loginstore.continuer == -1)
				{
					loginstore.ttextedialogue = fenetredialogue(screenw*0.3, screenh*0.3, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info3, &systeme->rouge, systeme);
					loginstore.menu = true;
					loginstore.continuer = 1;
				}
				else if (loginstore.continuer == -2)
				{
					loginstore.ttextedialogue = fenetredialogue(screenw*0.3, screenh*0.3, &loginstore.pdialogue, &loginstore.ptextedialogue, loginstore.info4, &systeme->rouge, systeme);
					loginstore.menu = true;
					loginstore.continuer = 1;
				}
			}
			else if (loginstore.continuer == 4)
			{
				loginstore.ttextedialogue = fenetredialogue(screenw*0.7, screenh*0.15, &loginstore.pdialogue, &loginstore.ptextedialogue, " ", &systeme->rouge, systeme);
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
			/*affichage*/
			affichageloggin(&loginstore, systeme);

		}
		else if (loginstore.tpact - loginstore.tpcurseur >= 500)
        {
            loginstore.tpcurseur = loginstore.tpact;
            if (loginstore.clignote == true)
                {   loginstore.clignote = false;    }
            else
                {   loginstore.clignote = true;     }
        }
		else
		{
			SDL_Delay(10);
		}
	}
	loginstore.fichier = fopen ("rs/options.RSsave", "w+");
	if      (loginstore.azerty.etat == B_CLIQUER) {fputc('1',loginstore.fichier);}
	else if (loginstore.qwerty.etat == B_CLIQUER) {fputc('2', loginstore.fichier);}
	else if (loginstore.qwertz.etat == B_CLIQUER) {fputc('3', loginstore.fichier);}
	fclose(loginstore.fichier);
	return loginstore.continuer;
}


int creerjoueur(char sauvegarde[][50])
{
    int i;
    FILE *fichier2 = NULL;
	char nomfichier[50] = {'\0'};

	if (strlen(sauvegarde[0]) == 0)
	{
		return -1;
	}

	sprintf(nomfichier, "rs/sauvegarde/%s.RSCryptedSave", sauvegarde[0]);

	if (fopen((const char *)nomfichier, "r") == NULL)
	{
		int taille = TAILLESAC;
		sprintf(sauvegarde[4], "500");			/*perso en x500*/
		sprintf(sauvegarde[5], "500");			/*perso en y500*/
		sprintf(sauvegarde[7], "100");			/*quantité de vie*/
		sprintf(sauvegarde[9], "%d", taille);	/*taille sac*/

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

	int i2 = 0, iligne = 0, index;
	int i = 0, LenMdpLogin = 0, LenMdpSauv = 0;
	char sauvegarde[2][50] = {{'\0'},{'\0'}};
	char caractere = '\0';
	char buffer[4096] = {'\0'};
	char ret[50] = {'\0'};

	sprintf(nomfichier, "rs/sauvegarde/%s.RSCryptedSave", login[0]);

	fichier = fopen ((const char *) nomfichier, "r");
	if (fichier == NULL)
	{
		 return -1;
	}

	while (i2 < 2)
	{
		caractere = fgetc(fichier);
		while (caractere != '#')
		{
			buffer[iligne] = caractere;
			iligne++;
			caractere = fgetc(fichier);
		}
		uncrypt(buffer, ret);
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


void InitLoginStore(struct typelogin *loginstore,struct DIVERSsysteme *systeme)
{
	loginstore->police = TTF_OpenFont("rs/divers/police1.ttf", TAILLE_POLICE_LOGIN);

	loginstore->pseudo.img.texture = CEGDD_UI_imprime ("pseudo :", screenw, &systeme->bleu, systeme->police1, &loginstore->pseudo.lenght, NULL);
	loginstore->mdp.img.texture = CEGDD_UI_imprime ("mot de passe :", screenw, &systeme->bleu, systeme->police1, &loginstore->mdp.lenght, NULL);

	CEGDD_UI_setPos4(&loginstore->login.pos, 0, 0, screenw, screenh);
	CEGDD_UI_setPos4(&loginstore->pointeur.pos, 0, 0, 40, 60);
	CEGDD_UI_setPos4(&loginstore->blueBox.pos, 0, 0, 0, 0);
	CEGDD_UI_setPos4(&loginstore->whiteBox.pos, 0, 0, 0, 0);
	CEGDD_UI_setPos4(&loginstore->tdialogue.pos, screenw/8, (screenh/12)*5, (screenw/8)*6, (screenh/6));
	CEGDD_UI_setPos4(&loginstore->cachermdp.pos, screenw*0.75, screenh*0.3, screenw/6, screenh/12);
	CEGDD_UI_setPos4(&loginstore->coche.pos, screenw*0.75, screenh*0.3, loginstore->cachermdp.pos.w/3, loginstore->cachermdp.pos.h*1.3);

    loginstore->login.texture =     CEGDD_UI_loadTexture("rs/fonds/login.png");
    loginstore->pointeur.texture =  CEGDD_UI_loadTexture("rs/images/p.png");
    loginstore->blueBox.texture =   CEGDD_UI_loadTexture("rs/images/blueBox.png");
    loginstore->whiteBox.texture =  CEGDD_UI_loadTexture("rs/images/whiteBox.png");
    loginstore->tdialogue.texture = CEGDD_UI_loadTexture("rs/ui/fenetreinfo.png");
    loginstore->cachermdp.texture = CEGDD_UI_loadTexture("rs/images/cachermdp.png");
    loginstore->coche.texture =     CEGDD_UI_loadTexture("rs/images/coche.png");

	loginstore->noir.texture = 0;

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
	loginstore->pecran.w = screenw;
	loginstore->pecran.h = screenh;

	loginstore->noir.pos.x = 0;
	loginstore->noir.pos.y = 0;
	loginstore->noir.pos.w = 3;
	loginstore->noir.pos.h = TAILLE_POLICE_LOGIN;
	loginstore->noir.texture = 0;

	loginstore->pcase.w = screenw*0.25;
	loginstore->pcase.h = screenh*0.05;
	loginstore->pcase.x = (screenw-loginstore->pcase.w)*0.5;
	loginstore->pcase.y = screenh/2;

	loginstore->pcase2.w = screenw*0.25;
	loginstore->pcase2.h = screenh*0.05;
	loginstore->pcase2.x = (screenw-loginstore->pcase2.w)*0.5;
	loginstore->pcase2.y = (screenh*0.5)-(screenh*0.125);

	loginstore->LEmdp.img.pos.h = screenh/20;
	loginstore->LEmdp.img.pos.x = loginstore->pcase.x + 10;
	loginstore->LEmdp.img.pos.y = (screenh*0.5)-(screenh*0.125)+2;

	loginstore->LEpseudo.img.pos.h = screenh/20;
	loginstore->LEpseudo.img.pos.x = loginstore->pcase.x + 10;
	loginstore->LEpseudo.img.pos.y = (screenh/2)+2;

	loginstore->pseudo.img.pos.w = (screenw/4)-2;
	loginstore->pseudo.img.pos.h = screenh/20;
	loginstore->pseudo.img.pos.x = (screenw-loginstore->pseudo.img.pos.w)/2;
	loginstore->pseudo.img.pos.y = (screenh/2)+(screenh/8)-loginstore->pseudo.img.pos.h;

	loginstore->mdp.img.pos.w = (screenw/4)-2;
	loginstore->mdp.img.pos.h = screenh/20;
	loginstore->mdp.img.pos.x = (screenw-loginstore->mdp.img.pos.w)/2;
	loginstore->mdp.img.pos.y = (screenh/2)-loginstore->pseudo.img.pos.h;

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
	loginstore->tpact = 0;
	loginstore->tpapr = 0;
	loginstore->tpcurseur = 0;
	loginstore->lettre = '0';

	/*récupération du type de clavier utilisé*/
	loginstore->fichier = fopen("rs/options.RSsave", "r");
	systeme->typeclavier = fgetc(loginstore->fichier);
	fclose(loginstore->fichier);

	for (loginstore->i = 0 ; loginstore->i < 21 ; loginstore->i++)
	{
		loginstore->mdpshow[loginstore->i] = '\0';
	}

	if (systeme->typeclavier == '1')        {loginstore->azerty.etat = B_CLIQUER;}
	else if (systeme->typeclavier == '2')   {loginstore->qwerty.etat = B_CLIQUER;}
	else if (systeme->typeclavier == '3')   {loginstore->qwertz.etat = B_CLIQUER;}

	sprintf(loginstore->info, "Pseudo incorrect \n\nveuillez entrer un pseudo et un mot de passe.");
	sprintf(loginstore->info2, "Pseudo incorrect\n\nLe pseudo que vous avez entre existe deja, veuillez en choisir un autre.");
	sprintf(loginstore->info3, "Identifiants incorrects\n\nVotre personnage n'existe pas, creez en un sans attendre !");
	sprintf(loginstore->info4, "Identifiants incorrects\n\nVotre mot de passe et votre pseudo ne correspondent pas.\n\nessayer un autre mot de passe.");

	loginstore->ttextedialogue = -1;
}


void Initbouton(struct typelogin *loginstore,struct DIVERSsysteme *systeme)
{
     int menuw = screenw*0.7;
    int menuh = screenh*0.15;
    int gauche = screenw*0.15;
    int haut = screenh*0.425;

    loginstore->option.texture = CEGDD_UI_loadTexture("rs/ui/options.png");
    CEGDD_UI_setPos4(&loginstore->option.pos,  screenw/11, screenh/7, screenw/11, screenh/12);
    loginstore->option.etat = B_NORMAL;

	loginstore->jouer.texture = CEGDD_UI_loadTexture("rs/ui/jouer.png");
	CEGDD_UI_setPos4(&loginstore->jouer.pos,  (screenw/11)*3, screenh/7, screenw/11, screenh/12);
    loginstore->jouer.etat = B_NORMAL;

	loginstore->creer.texture = CEGDD_UI_loadTexture("rs/ui/creer.png");
	CEGDD_UI_setPos4(&loginstore->creer.pos,  (screenw/11)*5, screenh/7, screenw/11, screenh/12);
    loginstore->creer.etat = B_NORMAL;

	loginstore->quitter.texture = CEGDD_UI_loadTexture("rs/ui/logquitter.png");
	CEGDD_UI_setPos4(&loginstore->quitter.pos,  (screenw/11)*7, screenh/7, screenw/11, screenh/12);
    loginstore->quitter.etat = B_NORMAL;

	loginstore->arcade.texture = CEGDD_UI_loadTexture("rs/ui/arcade.png");
	CEGDD_UI_setPos4(&loginstore->arcade.pos,  (screenw/11)*9, screenh/7, screenw/11, screenh/12);
    loginstore->arcade.etat = B_NORMAL;

	loginstore->azerty.texture = CEGDD_UI_loadTexture("rs/ui/azerty.png");
	CEGDD_UI_setPos4(&loginstore->azerty.pos,  menuw/7+gauche, menuh/3+haut, menuw/7, menuh/3);
    loginstore->azerty.etat = B_NORMAL;

	loginstore->qwerty.texture = CEGDD_UI_loadTexture("rs/ui/qwerty.png");
	CEGDD_UI_setPos4(&loginstore->qwerty.pos,  (menuw/7)*5+gauche, menuh/3+haut, menuw/7, menuh/3);
    loginstore->qwerty.etat = B_NORMAL;

    loginstore->qwertz.texture = CEGDD_UI_loadTexture("rs/ui/qwertz.png");
    CEGDD_UI_setPos4(&loginstore->qwertz.pos,  (menuw/7)*3+gauche, menuh/3+haut, menuw/7, menuh/3);
    loginstore->qwertz.etat = B_NORMAL;
}

void affichageloggin(struct typelogin *loginstore,struct DIVERSsysteme *systeme)
{

    CEGDD_UI_draw_pict(&loginstore->login);

    CEGDD_UI_draw_button(&loginstore->option);
    CEGDD_UI_draw_button(&loginstore->jouer);
    CEGDD_UI_draw_button(&loginstore->quitter);
    CEGDD_UI_draw_button(&loginstore->creer);
    CEGDD_UI_draw_button(&loginstore->arcade);

    if (loginstore->saisiepseudo == true)
    {   CEGDD_UI_setPos4(&loginstore->blueBox.pos, loginstore->pcase.x, loginstore->pcase.y, loginstore->pcase.w, loginstore->pcase.h);
        CEGDD_UI_draw_pict(&loginstore->blueBox);     }
    else
    {   CEGDD_UI_setPos4(&loginstore->whiteBox.pos, loginstore->pcase.x, loginstore->pcase.y, loginstore->pcase.w, loginstore->pcase.h);
        CEGDD_UI_draw_pict(&loginstore->whiteBox);     }

    if (loginstore->saisiemdp == true)
    {   CEGDD_UI_setPos4(&loginstore->blueBox.pos, loginstore->pcase2.x, loginstore->pcase2.y, loginstore->pcase2.w, loginstore->pcase2.h);
        CEGDD_UI_draw_pict(&loginstore->blueBox);     }
    else
    {   CEGDD_UI_setPos4(&loginstore->whiteBox.pos, loginstore->pcase2.x, loginstore->pcase2.y, loginstore->pcase2.w, loginstore->pcase2.h);
        CEGDD_UI_draw_pict(&loginstore->whiteBox);     }

    if(loginstore->longmdp > 0)
    {
        if (loginstore->mdpcacher == 0)
        {
            loginstore->LEmdp.img.texture = CEGDD_UI_imprime(systeme->sauvegarde[1], screenw, &systeme->noir, systeme->police1, &loginstore->LEmdp.img.pos.w, NULL);
        }
        else
        {
            loginstore->LEmdp.img.texture = CEGDD_UI_imprime(loginstore->mdpshow, screenw, &systeme->noir, systeme->police1, &loginstore->LEmdp.img.pos.w, NULL);
        }
        CEGDD_UI_draw_pict(&loginstore->LEmdp.img);
    }
    if(loginstore->longpseudo > 0)
    {
        loginstore->LEpseudo.img.texture = CEGDD_UI_imprime(systeme->sauvegarde[0], screenw, &systeme->noir, systeme->police1, &loginstore->LEpseudo.img.pos.w, NULL);
        CEGDD_UI_draw_pict(&loginstore->LEpseudo.img);
    }

    if (loginstore->saisiemdp == true && loginstore->clignote == true)
    {
        if (loginstore->longmdp > 0)
        {
            loginstore->noir.pos.x = loginstore->LEmdp.img.pos.x + loginstore->LEmdp.img.pos.w + 2;
            loginstore->noir.pos.y = loginstore->LEmdp.img.pos.y + 5;
        }
        else
        {
            loginstore->noir.pos.x = loginstore->pcase2.x + 5;
            loginstore->noir.pos.y = loginstore->pcase2.y + 5;
        }
        CEGDD_UI_draw_color_black(&loginstore->noir.pos);
    }
    else if (loginstore->saisiepseudo == true && loginstore->clignote == true)
    {
        if (loginstore->longpseudo > 0)
        {
            loginstore->noir.pos.x = loginstore->LEpseudo.img.pos.x + loginstore->LEpseudo.img.pos.w + 2;
            loginstore->noir.pos.y = loginstore->LEpseudo.img.pos.y + 5;
        }
        else
        {
            loginstore->noir.pos.x = loginstore->pcase.x + 5;
            loginstore->noir.pos.y = loginstore->pcase.y + 5;
        }
        CEGDD_UI_draw_color_black(&loginstore->noir.pos);
    }

    CEGDD_UI_draw_pict(&loginstore->pseudo.img);
    CEGDD_UI_draw_pict(&loginstore->mdp.img);

    CEGDD_UI_draw_pict(&loginstore->cachermdp);
    if (loginstore->mdpcacher == 1)
    {   CEGDD_UI_draw_pict(&loginstore->coche);   }


     if (loginstore->menu == true)
    {
        CEGDD_UI_draw_pict(&loginstore->tdialogue);
        //draw(&loginstore->ttextedialogue);
    }

    if (loginstore->optionactif == 1)
    {
        if (loginstore->azerty.etat == B_NORMAL)
        {   CEGDD_UI_draw_button(&loginstore->azerty);}

        if (loginstore->qwerty.etat == B_NORMAL)
        {   CEGDD_UI_draw_button(&loginstore->qwertz);}

        if (loginstore->qwertz.etat == B_NORMAL)
        {   CEGDD_UI_draw_button(&loginstore->qwerty);}
    }
    CEGDD_UI_draw_pict(&loginstore->pointeur);

    glFlush();
    SDL_GL_SwapWindow(systeme->screen);
}

