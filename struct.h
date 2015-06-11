#ifndef LOGINH
#define LOGINH

#include <stdio.h>
#include <stdbool.h>
#include <SDL_ttf.h>

/*####     OS     ######*/
#define WINDOWS 1
/*####logging rapide ####*/
#define FASTLOG 0
/*####  battle log   ####*/
#define BATTLE_LOG 0
/*##battle log display##*/
#define BATTLE_LOG_DISPLAY 0
/*####    cheat     ####*/
#define CHEAT 0
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

struct Picture
{
    SDL_Texture *texture;
    SDL_Surface *surface;
    SDL_Rect pos;
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

	SDL_Texture *texture;
	SDL_Texture *texturenombre;
	SDL_Texture *texturenom[3];

	int empilage;
	int type;
	int bodypart;
	int LARGEURnom;

	int def;
	int life;
	int regenlife;
	int force;
	int portee;

	int LARGEURdef;
	int LARGEURlife;
	int LARGEURregenlife;
	int LARGEURforce;
	int LARGEURportee;

	SDL_Texture *texturedef;
	SDL_Texture *texturelife;
	SDL_Texture *textureregenlife;
	SDL_Texture *textureforce;
	SDL_Texture *textureportee;

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
	SDL_Texture *normal;
	SDL_Texture *survoler;
	SDL_Texture *cliquer;
	SDL_Rect position;
	int etat;
};
struct CREATURE
{
	SDL_Texture *texture[3];
	SDL_Rect position;
	SDL_Rect STATICposition;
	struct BARREVIE *BarreDeVie;

	char name [48];
	bool isdead;
	bool iserasable;
	float life;
	float lifemax;
	int ID;

	int tempsanimation;
	int Direction;
	int indexanim;
	int mind;
	int mindtime;
	int relevancy[8];
	int looted;
	int ontheway;
	float wayx;
	float wayy;
	int oldposx;
    int oldposy;
    float dx;
    float dy;
};
struct RAT
{
	/*graphic*/
	SDL_Texture *texture[5][3];
	SDL_Rect position;

	/*general*/
	char nom [48];
	int etat;
	bool Engaged;
	struct File queue;
	int ID;

	/*animation*/
	int indexanim;
	int tempsanim;
	int direction;

	/*loot*/
	int prctloot[LOOTMAX];
	int maxloot[LOOTMAX];
	int nombreloot;
	int idloot[LOOTMAX];
};
struct PACKmonstre
{
	struct RAT rat[3];
};

struct EMPLACEMENT
{
	int IDobjet;
	int NBobjet;
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

	SDL_Texture *tperso;
	SDL_Texture *texture_poing[1];
	SDL_Texture *tpseudo;
	SDL_Texture *cheveuxbrun ;
	SDL_Texture *cheveuxblanc;

	SDL_Texture *tdefense;
	SDL_Texture *tlife;
	SDL_Texture *tregenlife;
	SDL_Texture *tforce;
	SDL_Texture *tportee;

	SDL_Rect spriteup[8];
	SDL_Rect spritehit;

	SDL_Rect pperso;
	SDL_Rect pperso_poing;
	SDL_Rect ptpseudo;
	SDL_Point centrecorp;

	SDL_Rect pstats;
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
	struct BOUTON BoutonQuitter;
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
	SDL_Rect toumai;
	bool toumaiParle;
};

struct DIVERSinventaire
{
	int caseupgauche;
	int caseupdroit;
	int casedowndroit;
	int casedowngauche;
	int idsurvoler;
	int LARGEURaideclicdroit;
	int totalID[128];

	SDL_Rect pcaseinventaire[TAILLESAC];
	SDL_Rect  pnbobjet[TAILLESAC];
	SDL_Texture *tnbobjet;

	SDL_Texture *tsacinventaire;
	SDL_Texture *BGinventaire;
	SDL_Texture *tcasesac;
	SDL_Texture *tcasesac2;
	SDL_Texture *taideclicdroit;

	SDL_Rect psac;
	SDL_Rect pdetail;
};

struct DIVERSdeplacement
{
	int x;
	int y;
    int directionjoueurs[MAX_JOUEURS];
    struct DIRECTION direction;
    int persobouge;
    int indexanimperso;
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

    SDL_Texture *tfps;
    SDL_Texture *ttemps;

	SDL_Rect pttemps;
    SDL_Rect ptFps;
};

struct DIVERSsysteme
{
    bool shiftactif;
    bool altactif;
    bool inbattle;
    int continuer;
    int echap;
    int screenw;
    int screenh;
    int typeclavier;

    SDL_Texture *pointeur;
    SDL_Texture *BGmort;
    SDL_Texture *BG;
    SDL_Texture *BGblanc;
    SDL_Texture *noir;

    SDL_Event evenement;

    SDL_Window *screen;

    SDL_Renderer *renderer;

    TTF_Font *police;
    TTF_Font *police1;

	SDL_Rect pp;
	SDL_Rect pecran;
	SDL_Rect oldpp;
	SDL_Rect ppobj;
	SDL_Rect PixelCalque[8];

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
	bool OnLeftUp;
	bool OnRightUp;
	bool OnRightDown;
	bool OnLeftDown;

	int coinhaut;
	int coinbas;
	int lancedialogue;
	int dialogueactif;
	int PointedCorner;
	int CornerTime;
	int OldCornerTime;

	char designationstuff[7][128];

	struct EMPLACEMENT casestuff[7];

	SDL_Texture *tdesignationstuff[7];
	SDL_Texture *ttextedialogue;
	SDL_Texture *lumiereon;
	SDL_Texture *lumiereoff;
	SDL_Texture *tdialogue;
	SDL_Texture *uimenu;
	SDL_Texture *Uiinventaire;
	SDL_Texture *Uichat;
	SDL_Texture *BGmenu;

	SDL_Rect pUIbas;
	SDL_Rect pUIhaut;
	SDL_Rect puimenu;
	SDL_Rect puiinventaire;
	SDL_Rect puichat;
	SDL_Rect plumiere;
	SDL_Rect ptextedialogue;
	SDL_Rect pdialogue;
	SDL_Rect pcasestuff[7];
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
	int pmx;
	int pmy;
	struct GRILLE grille[400][400];

	SDL_Texture *tilemap[TILESMAP];
	SDL_Surface *calque[TILESMAP];

	SDL_Rect pmap[TILESMAP];
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

struct typecombat
{
	struct BOUTON rejouer;
	struct BOUTON quitter;
    /*char calque[1366][768];*/
	struct CREATURE creature[LIMITEmobARCADE];
	int premiercoup[LIMITEmobARCADE];

    char StringVie[48];
    char StringCailloux[128];

    int continuer;
    int echap;
    int doublesaut;
    bool letirdemander;
    bool poing_tendu;
    int canonx;
    int canony;
    int DepartBalle[NBcailloux];
    int i[NBcailloux];
    int irect;
    int ResultatHitbox;
    int tx[NBcailloux][PRECISIONcailloux];
    int ty[NBcailloux][PRECISIONcailloux];
    int tableauutile;
	int px;
    int py;
    int indexanimperso;
    int persobouge;
    int alive;
    int ennemivaincue;
    int arcadescore;
    int IndexCreature;

    int animobjetway;
    int NBlootsol;
    int IDlootsol[64];
    int lootsol[64];
    float lootsolDX[64];
    float lootsolDY[64];
    float lootsolWAYX[64];
    float lootsolWAYY[64];

    long temps;
    long tempscalcul;
    long tempsaffichage;
    long tempsseconde;
    long tempsanimationjoueur;
    long tempsanimationobjet;
    long TimeAddEnnemy;

    double degre;

    float animobjet;

    SDL_Texture *tVie;
    SDL_Texture *fond;
    SDL_Texture *curseur;
    SDL_Texture *balle;
    SDL_Texture *peau;
    SDL_Texture *piece;

    SDL_Rect Pperso;
    SDL_Rect pcurseur;
    SDL_Rect pballe[NBcailloux];
    SDL_Rect ptVie;
    SDL_Rect plootsol[64];
    SDL_Rect oldplootsol[64];
};

struct bouton
{
	SDL_Texture *alpha100;
	SDL_Texture *normal;
	SDL_Texture *survoler;
	SDL_Texture *cliquer;
	SDL_Texture *impossible;
	SDL_Rect pos;
};

struct TEXTE
{
	SDL_Texture *texture;
	SDL_Rect position;
	int lenght;
	int high;
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

	struct Picture pointeur;
	struct Picture login;
	struct Picture blueBox;
	struct Picture whiteBox;
	struct Picture tdialogue;
	struct Picture cachermdp;
	struct Picture coche;

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

	SDL_Texture *curseur;
	SDL_Texture *ttextedialogue;
};

#endif
