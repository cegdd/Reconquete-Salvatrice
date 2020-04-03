#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

#include "struct.h"
#include "image.h"

#include <LIBcegdd_ui.h>

struct BARREVIE* AddLifeBar(int life, int lenght)
{
	struct BARREVIE *lifebar = malloc(sizeof(struct BARREVIE));

	lifebar->life = life;
	lifebar->baselife = life;

	CEGDD_UI_setPos4(&lifebar->pBG, 0, 0, lenght+2, 7);
    CEGDD_UI_setPos4(&lifebar->pbarre, 1, 1, lenght, 5);
	return lifebar;
}


int CalculerBarreDeVie(int VieDeBase, int VieActuelle, int width)
{
	return ((float)width / (float)VieDeBase) * (float)VieActuelle;
}
