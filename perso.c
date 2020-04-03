#include "deplacement.h"
#include "image.h"
#include "perso.h"
#include "tool.h"
#include "donjon.h"
#include "colision.h"

#include <LIBcegdd_ui.h>

extern int screenh, screenw;

int directionperso(struct DIRECTION *direction)
{
    if      (direction->haut == 1 && direction->droite == 0 && direction->gauche == 0 && direction->bas == 0) {return UP;}
	else if (direction->haut == 1 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 0) {return UPRIGHT;}
	else if (direction->haut == 1 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 0) {return LEFTUP;}
	else if (direction->haut == 0 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 0) {return RIGHT;}
	else if (direction->haut == 0 && direction->droite == 1 && direction->gauche == 0 && direction->bas == 1) {return RIGHTDOWN;}
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 1) {return DOWNLEFT;}
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 1 && direction->bas == 0) {return LEFT;}
	else if (direction->haut == 0 && direction->droite == 0 && direction->gauche == 0 && direction->bas == 1) {return DOWN;}
	else
	{
		if (direction->direction != -1)
		{
			direction->olddirection = direction->direction;
		}
		return -1;
	}
}


void initperso(struct PERSO *perso,struct DIVERSsysteme *systeme)
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

	CEGDD_UI_setPos4(&perso->perso.pict.pos, (screenw/2)-(perso->perso.pict.pos.w/2), (screenh/2)-(perso->perso.pict.pos.h/2), 68, 51);

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

    CEGDD_UI_setPos4(&perso->tlife.pos, screenw*0.11, screenh*0.8, screenw*0.28, screenh*0.05);
	CEGDD_UI_setPos4(&perso->tdefense.pos, screenw*0.11, screenh*0.74, screenw*0.28, screenh*0.05);
	CEGDD_UI_setPos4(&perso->tregenlife.pos, screenw*0.11, screenh*0.68, screenw*0.28, screenh*0.05);
	CEGDD_UI_setPos4(&perso->tforce.pos, screenw*0.11, screenh*0.62, screenw*0.28, screenh*0.05);
	CEGDD_UI_setPos4(&perso->tportee.pos, screenw*0.11, screenh*0.56, screenw*0.28, screenh*0.05);

	perso->BarreDeVie = AddLifeBar(100, perso->perso.pict.pos.w);

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

void hitboxplayer (struct DONJON *donjon, struct PERSO *perso, struct DIVERSsysteme *systeme)
{
    int ret = playeristouched(donjon, perso);
    while (ret != -1)
    {
        donjon->mob[ret].atkDone = true;
        TakeDamage(ret, donjon, perso, systeme);
        donjon->mob[ret].TimeSinceAtk = SDL_GetTicks();

        ret = playeristouched(donjon, perso);
    }
}
void TakeDamage (int index, struct DONJON *donjon, struct PERSO *perso, struct DIVERSsysteme *systeme)
{
    perso->life -= donjon->creature[donjon->mob[index].ID].dps;
    if (perso->life <= 0)
    {

    initdonjon(donjon, systeme);
    systeme->djisloaded = false;
    LoadDonjon(donjon, "dj0");
    systeme->djisloaded = true;
    perso->life = perso->lifemax;

    }
}
