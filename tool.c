#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "main.h"
#include "image.h"

typedef struct BARREVIE BARREVIE;


BARREVIE* AddLifeBar(int life, int lenght)
{
	BARREVIE *lifebar = malloc(sizeof(BARREVIE));

	lifebar->life = life;
	lifebar->baselife = life;

	setPos4(&lifebar->pBG, 0, 0, lenght+2, 7);
    setPos4(&lifebar->pbarre, 1, 1, lenght, 5);
	return lifebar;
}


int CalculerBarreDeVie(int VieDeBase, int VieActuelle, int width)
{
	return ((float)width / (float)VieDeBase) * (float)VieActuelle;
}
