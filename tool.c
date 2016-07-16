#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "main.h"
#include "systeme.h"

typedef struct BARREVIE BARREVIE;


BARREVIE* AddLifeBar(int life, int lenght,struct DIVERSsysteme *systeme)
{
	BARREVIE *new = malloc(sizeof(BARREVIE));

	new->life = life;
	new->BGtexture = systeme->BGblanc;
	new->position.x = -1;
	new->position.y = -1;
	new->position.w = lenght;
	new->position.h = 5;
	new->BGposition.w = lenght+2;
	new->BGposition.h = 7;
	return new;
}
