#ifndef LOGINH
#define LOGINH

#include "main.h"

struct bouton
{
	SDL_Texture *alpha100;
	SDL_Texture *normal;
	SDL_Texture *survoler;
	SDL_Texture *cliquer;
	SDL_Texture *impossible;
	SDL_Rect pos;
};

struct typelogin
{

    struct bouton option;
    struct bouton jouer;
    struct bouton creer;
    struct bouton quitter;
    struct bouton azerty;
    struct bouton qwerty;
    struct bouton qwertz;
    struct bouton arcade;
	SDL_Event evenement;
	TTF_Font *police;
	SDL_Color couleurNoir;
	SDL_Color couleurBleu;
	FILE *fichier;

	struct TEXTE pseudo;
	struct TEXTE mdp;
	struct TEXTE LEpseudo;
	struct TEXTE LEmdp;

	SDL_Rect pecran;
	SDL_Rect ppointeur;
	SDL_Rect pcase;
	SDL_Rect pcase2;
	SDL_Rect pdialogue;
	SDL_Rect ptextedialogue;
	SDL_Rect pcachermdp;
	SDL_Rect pcoche;
	SDL_Rect pcurseurMDP;
	SDL_Rect pcurseurPSEUDO;

	bool saisiepseudo;
	bool saisiemdp;
	bool clignote;
	bool menu;

	int continuer;
	int longpseudo;
	int i;
	int longmdp;
	int optionactif;
	int mdpcacher;
	int etatoption;
	int etatjouer;
	int etatcreer;
	int etatquitter;
	int etatarcade;
	int etatazerty;
	int etatqwerty;
	int etatqwertz;
	int tpact;
	int tpapr;
	int tpcurseur;

	char lettre;
	char mdpshow[21];

	char info[1024];
	char info2[1024];
	char info3[1024];
	char info4[1024];

	SDL_Texture *login;
	SDL_Texture *curseur;
	SDL_Texture *pointeur;
	SDL_Texture *blueBox;
	SDL_Texture *whiteBox;
	SDL_Texture *tdialogue;
	SDL_Texture *cachermdp;
	SDL_Texture *coche;
	SDL_Texture *ttextedialogue;
};

typedef struct bouton bouton;

int auth (char sauvegarde[][50]);
int login (struct DIVERSsysteme *systeme);
int creerjoueur(char sauvegarde[][50]);

void InitLoginStore (struct typelogin *loginstore,struct DIVERSsysteme *systeme);
void Initbouton     (struct typelogin *loginstore,struct DIVERSsysteme *systeme);
void affichageloggin(struct typelogin *loginstore,struct DIVERSsysteme *systeme);

#endif
