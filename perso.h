#ifndef PERSOH
#define PERSOH

#include "deplacement.h"
#include "donjon.h"

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
void initperso(struct PERSO *perso,struct DIVERSsysteme *systeme);

int directionperso(struct DIRECTION *direction);

void hitboxplayer (struct DONJON *donjon, struct PERSO *perso);
void TakeDamage (int index, struct DONJON *donjon, struct PERSO *perso);

#endif
