#ifndef LOGINH
#define LOGINH

#include <stdio.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

/*####     OS     ######*/
#define WINDOWS 1
/*####logging rapide ####*/
#define FASTLOG 1
/*####  battle log   ####*/
#define BATTLE_LOG 0
/*##battle log display##*/
#define BATTLE_LOG_DISPLAY 0
/*####    cheat     ####*/
#define CHEAT 1
/*#######################*/

#if WINDOWS == 1
#include <winsock2.h>
#else
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
#endif

#define LOOTMAX 50
#define NOMBREOBJETS 14
#define MAX_JOUEURS 50
#define TILESMAP 10
#define MAX_JOUEURS 50
#define NBargSAVE 17
#define TAILLESAC 80
#define C 50
#define TEMPSREPOPBATMOUTHS 10
#define TAILLE_POLICE 18
#define TAILLE_POLICE_LOGIN 25
#define NBargSAVE 17
#define IPSERVEUR "88.191.117.41"
#define BUFFER 25
#define REGEN 2.5

/*combat*/
#define NBcailloux 50
#define PRECISIONcailloux 384 /*nombre de calcul par tir*/
#define DEGATcailloux 10
#define DEGATsubitCHOC 10.0  /*6 a 10*/
#define DEGATsubitDUREE 0.3  /*0.8*/
#define VITESSE 3
#define LIMITEmobARCADE 512

#define BTL_OBJ_MOVE -1
#define BTL_OBJ_TOOK -2
#define BTL_OBJ_FLOOR 0


enum{BTL_LOST, BTL_WON, BTL_LEAVED, BTL_RESTART};/*for battle*/
enum{ARME, TORSE, COU, DOS, PIED, TAILLE, TETE};/*body area for item*/
enum{RESSOURCE, EQUIPEMENT};/*type of item*/
enum{BLANC, ROUGE, GRIS, NOIR, VERT, BLEU};/*text color*/
enum{UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT, LEFT, LEFTUP};/*direction*/
enum{UNUSED, GO, RUNNING, STOP};/*projectil*/
enum{ALIGN_RIGHT, ALIGN_LEFT, ALIGN_CENTER};/*text*/
enum{B_NORMAL, B_SURVOLER, B_CLIQUER, B_IMPOSSIBLE};/*bouton*/
enum{RAT_BLANC, RAT_VERT, RAT_JAUNE, RAT_ORANGE, RAT_ROUGE};/*creature*/
enum{ALIVE, DEAD};

struct pict
{
    SDL_Rect pos;
    GLuint texture;
};
struct TEXTE
{
    struct pict img;
	int lenght;
	int high;
};

struct moving_pict
{
    struct pict pict;
    GLuint texture[16];
    int frame;
    int current;
    int delay;
    int time;
};

struct floor
{
    struct pict pict;
    SDL_Surface *calque;
    SDL_Point translation;
};

struct hookpict
{
    struct pict pict;
    SDL_Point translation;
};

struct File
{
    struct Element *premier;
};

struct Element
{
    int nombre;
    struct Element *suivant;
};

struct BARREVIE
{
	SDL_Texture *texture;
	SDL_Texture *BGtexture;
	SDL_Rect position;
	SDL_Rect BGposition;

	int life;
	int baselife;
};
struct GRILLE
{
	unsigned int value : 1;
};

struct CHOSE
{
	char nom [48];

	GLuint texture;
	GLuint quantite;
	GLuint texturenom[3];

	int empilage;
	int type;
	int bodypart;
	int LARGEURnom;

	int def;
	int life;
	int regenlife;
	int force;
	int portee;

	struct TEXTE tdef;
	struct TEXTE tlife;
	struct TEXTE tregenlife;
	struct TEXTE tforce;
	struct TEXTE tportee;

};

struct PLAN
{
	int compodifferente;
	int compoID[NOMBREOBJETS];
	int compoNB[10];
	int craftnumber;
	bool compodispo[NOMBREOBJETS];
	int resultatID;
	int resultatNB;
	char textecompo[NOMBREOBJETS][96];
	SDL_Texture *resultattexture;
};

struct BOUTON
{
	GLuint texture;
	SDL_Rect pos;
	int etat;
};

struct EMPLACEMENT
{
	int IDobjet;
	int NBobjet;

	SDL_Rect pos;
};

struct PERSO
{
	struct BARREVIE *BarreDeVie;

	int lifemax;
	char slife[50];
	int stuff[7];

	int regenlife;
	float defense;
	float life;
	int force;
	int portee;
	int cote[8];
	int etatpix[12];

	struct moving_pict perso;

	Uint8 pixel[12] ;

	SDL_Texture *texture_poing[1];
	SDL_Texture *tpseudo;
	SDL_Texture *cheveuxbrun ;
	SDL_Texture *cheveuxblanc;

	struct pict tdefense;

	struct pict tlife;
	struct pict tregenlife;
	struct pict tforce;
	struct pict tportee;

	SDL_Rect spriteup[8];
	SDL_Rect spritehit;
	SDL_Rect pperso_poing;
	SDL_Rect ptpseudo;

	SDL_Point PixelCalque[12];
	SDL_Point centrecorp;
    SDL_Point pix;

};

struct DIRECTION
{
	int bas;
    int haut;
    int droite;
    int gauche;
    int direction;
    int olddirection;
};

struct PACKbouton
{
	struct BOUTON crafter;
	struct BOUTON bcraft[7];
};

struct PACKobjet
{
	struct PLAN PLANstuff[7][10];
	int craftnumber[7];
	struct EMPLACEMENT sac1[TAILLESAC];
	struct EMPLACEMENT objetenmain;
	struct CHOSE objet[NOMBREOBJETS];
};

struct PACKpnj
{
	struct pict toumai;
	bool toumaiParle;
};

struct DIVERSinventaire
{
	int caseupgauche;
	int caseupdroit;
	int casedowndroit;
	int casedowngauche;
	int idsurvoler;
	int totalID[128];

	SDL_Rect pnbobjet[TAILLESAC];

	struct pict fond;
	struct pict sac;
	struct pict box[TAILLESAC];
	struct pict rubbish;

	struct TEXTE aide;

	SDL_Rect pdetail;
};

struct DIVERSdeplacement
{
    int directionjoueurs[MAX_JOUEURS];
    struct DIRECTION direction;
    int persobouge;
    int indexanimperso;
    SDL_Rect temp;
};

struct DIVERStemps
{
	int i;
	int tpact;
	int tpap;
	int tpapr;
	int tempsanimationjoueur;
	int temptotal;
	int tpspoursave;
    int indextemps;
    int oldipourregen;

    char StringI[12];
    char stringtempstotal[128];

    struct pict temps;
    struct pict fps;
};

struct DIVERSsysteme
{
    bool shiftactif;
    bool altactif;
    bool inbattle;
    int continuer;
    int echap;
    int typeclavier;

    bool djisloaded;
    int djID;

    struct pict pointeur;

    SDL_Texture *BGmort;
    GLuint BG;
    SDL_Texture *BGblanc;

    SDL_Event evenement;

    SDL_Window *screen;

    TTF_Font *police;
    TTF_Font *police1;

	SDL_Rect pecran;
	SDL_Rect oldpp;
	SDL_Rect ppobj;

	char sauvegarde[NBargSAVE][C];
	int saveinventaire[2][999];
};

struct DIVERSui
{
	bool menu_open;
	bool inventaire_open;
	bool chat_open;
	bool craft_open;

	bool distanceprevenu;

	bool lancedialogue;
	int dialogueactif;

	char designationstuff[7][128];

	struct EMPLACEMENT casestuff[7];

	SDL_Texture *tdesignationstuff[7];

	struct pict dialogue_back;
	struct pict dialogue_text;
	struct pict BGmenu;

	SDL_Texture *lumiereon;
	SDL_Texture *lumiereoff;

	struct BOUTON corner_menu;
	struct BOUTON corner_chat;
	struct BOUTON corner_inventaire;
	struct BOUTON BoutonQuitter;

	SDL_Rect pUIbas;
	SDL_Rect pUIhaut;
	SDL_Rect plumiere;
};

struct DIVERSchat
{
    int saisiechat;

	SDL_Texture *tbufferchat;
	SDL_Texture *tstringchat[10];
	SDL_Texture *BGchat;
	SDL_Texture *BGchatactif;

	char lettre;

	SDL_Rect pbufferchat;
	SDL_Rect pchatactif;
	SDL_Rect pstringchat[10];
};

struct DIVERScraft
{
    int bcraftactif;
    int bcraftpointer;
    int planactif;
    int planpointer;
    int planparonglets[7];

    SDL_Texture *Uicraft;
    SDL_Texture *tetabli;
    SDL_Texture *tcomponame[10];
	SDL_Texture *BGcraft;

	SDL_Rect puicraft;
	SDL_Rect petabli;
	SDL_Rect poscompocraft[10];
	SDL_Rect posplan;
	SDL_Rect posimagecompocraft[10];
	SDL_Rect posimageresultatcraft;
	SDL_Rect pstats;
};

struct DIVERSmap
{
    SDL_Point origin;
	struct floor cellule;
};

struct DONJON
{
    char path[64];
    struct hookpict entrance;
    struct floor map;
    SDL_Point origin;
    struct hookpict monstre [512];
    int nombremonstre;
};

struct PACKrecompense
{
	int recompenseID[NOMBREOBJETS];
    int recompenseNB[LOOTMAX];

    SDL_Rect ptrecompesecombat;
    SDL_Rect pBGrecompense;
    SDL_Rect precompensecombat;
    SDL_Rect ptvictoire;

    SDL_Texture *tvictoire;
    SDL_Texture *ttexterecompensecombat;
    SDL_Texture *ttextelootcombat[LOOTMAX];
};

struct typeFORevent
    {
    	struct PACKobjet *objet;
    	struct PACKbouton *bouton;
    	struct DIVERSinventaire *inventaire;
		struct DIVERSsysteme *systeme;
		struct DIVERSdeplacement *deplacement;
		struct DIVERSchat *chat;
		struct DIVERSui *ui;
		struct DIVERScraft *craft;
        struct PACKmonstre *monstre;
        struct PERSO *perso;
        struct PACKpnj *pnj;
    };

struct typeFORthreads
{
	struct onlineplayer
	{
		SDL_Rect position;
		char pseudo[20];
		int enligne;
		SDL_Texture *tpseudo;
		SDL_Rect ppseudo;
		SDL_Rect posjoueurscalculer;
		SDL_Rect oldposjoueurs;
	}joueurs[MAX_JOUEURS];

	struct typeFORchat
	{
	    bool lancermessage;
        int lenbuffer;
        char schat[10][512];
        int poschat[10];
        char bufferchat[512];
	}chat;

	int jeuxACTIF;
	int posjoueurx;
	int posjoueury;
	SOCKET sock;
	bool isonline;

	struct DIVERSsysteme *systeme;
};

struct typelogin
{

    struct BOUTON option;
    struct BOUTON jouer;
    struct BOUTON creer;
    struct BOUTON quitter;
    struct BOUTON azerty;
    struct BOUTON qwerty;
    struct BOUTON qwertz;
    struct BOUTON arcade;

	SDL_Event evenement;
	TTF_Font *police;
	SDL_Color couleurNoir;
	SDL_Color couleurBleu;
	FILE *fichier;

	struct TEXTE pseudo;
	struct TEXTE mdp;
	struct TEXTE LEpseudo;
	struct TEXTE LEmdp;

	struct pict pointeur;
	struct pict login;
	struct pict blueBox;
	struct pict whiteBox;
	struct pict tdialogue;
	struct pict cachermdp;
	struct pict coche;
	struct pict noir;

	SDL_Rect pecran;
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
	int tpact;
	int tpapr;
	int tpcurseur;

	char lettre;
	char mdpshow[21];

	char info[1024];
	char info2[1024];
	char info3[1024];
	char info4[1024];

	GLuint ttextedialogue;
};

struct TIR
{
    char StringCailloux[128];

    bool letirdemander;
    int canonx;
    int canony;
    int DepartBalle[NBcailloux];
    int i[NBcailloux];
    int ResultatHitbox;
    int tx[NBcailloux][PRECISIONcailloux];
    int ty[NBcailloux][PRECISIONcailloux];
    int tableauutile;
	int px;
    int py;
    int indexanimperso;

    double degre;

    GLuint balle;

    SDL_Rect pballe[NBcailloux];
};

#endif
