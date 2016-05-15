#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "main.h"
#include "systeme.h"

typedef struct BARREVIE BARREVIE;

#if TESTGRID == 1
void DrawTestGrid(struct typecombat *BTLstr,struct DIVERSsysteme *systeme)
{
    int k, l;
    SDL_Rect tmp = {0, 0, 5, 5};
    for (k = 0 ; k < 1365 ; k=k+6)
    {
        for (l = 0 ; l < 767 ; l=l+6)
        {
            if (BTLstr->calque[k][l] == 0)
            {
                tmp.x = k-3;
                tmp.y = l-3;
                //SDL_RenderCopy(systeme->renderer, systeme->noir, NULL, &tmp);
            }
        }
    }
}

void UnWriteSquareTestGrid(struct typecombat *BTLstr,struct SDL_Rect *area)
{
    int k, l;
    for (k = 0 ; k < 1365 ; k++)
    {
        if(k>area->x && k <= area->x+area->w)
        {
            for (l = 0 ; l < 767 ; l++)
            {
                if (l > area->y && l <= area->y+area->h)
                {
                    BTLstr->calque[k][l] = 1;
                }
            }
        }
    }
}

void UnWriteCircleTestGrid (struct typecombat *BTLstr, SDL_Point *middle, int width)
{
    int k, l;
    SDL_Rect tmp2 = {middle->x - width,
                     middle->y - width,
                     width+width,
                     width+width};

    for (k = 0 ; k < 1365 ; k++)
    {
        if(k > middle->x - width &&
           k <= middle->x + width)
        {
            for (l = 0 ; l < 767 ; l++)
            {
                if (l > middle->y - width &&
                    l <= middle->y + width)
                {
                    SDL_Rect tmp = {k, l, 0, 0};
                    if (checkdistance(&tmp, &tmp2, width) == -1)
                    {
                        BTLstr->calque[k][l] = 1;
                    }
                }
            }
        }
    }
}
#endif

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
