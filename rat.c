#include <SDL2/SDL.h>

#include "systeme.h"
#include "main.h"
#include "tool.h"
#include "image.h"

typedef struct typecombat typecombat;

int TestColision_Rat(SDL_Rect *rat, int x, int y, int direction)
{
    SDL_Rect pix = {x, y, 1, 1};
    if (checkdistance(&pix, rat, 10) == -1 )
    {
        return 1;
    }


    if (direction == UP)
    {
        pix.y += 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y += 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == DOWN)
    {
        pix.y -= 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y -= 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == LEFT)
    {
        pix.x += 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.x += 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == RIGHT)
    {
        pix.x -= 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.x -= 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == UPRIGHT)
    {
        pix.y += 10;
        pix.x -= 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y += 10;
        pix.x -= 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == LEFTUP)
    {
        pix.y += 10;
        pix.x += 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y += 10;
        pix.x += 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == RIGHTDOWN)
    {
        pix.y -= 10;
        pix.x -= 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y -= 10;
        pix.x -= 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == DOWNLEFT)
    {
        pix.y -= 10;
        pix.x += 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y -= 10;
        pix.x += 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    return 0;
}

void ADD_Rat(int type, int MemoryArea, typecombat *BTLstr, DIVERSsysteme *systeme, RAT *rat)
{
	int index;
	float randside = rand()%4;
	float randwidth = rand()%systeme->screenw;
	float randhigh = rand()%systeme->screenh;
	
	switch(type)
	{
		case RAT_BLANC:
			BTLstr->creature[MemoryArea].life = 10;
			BTLstr->creature[MemoryArea].texture[0] = rat->texture[RAT_BLANC][0];
			BTLstr->creature[MemoryArea].texture[1] = rat->texture[RAT_BLANC][1];
			BTLstr->creature[MemoryArea].texture[2] = rat->texture[RAT_BLANC][2];
			break;
		case RAT_VERT:
			BTLstr->creature[MemoryArea].life = 25;
			BTLstr->creature[MemoryArea].texture[0] = rat->texture[RAT_VERT][0];
			BTLstr->creature[MemoryArea].texture[1] = rat->texture[RAT_VERT][1];
			BTLstr->creature[MemoryArea].texture[2] = rat->texture[RAT_VERT][2];
			break;
		case RAT_JAUNE:
			BTLstr->creature[MemoryArea].life = 70;
			BTLstr->creature[MemoryArea].texture[0] = rat->texture[RAT_JAUNE][0];
			BTLstr->creature[MemoryArea].texture[1] = rat->texture[RAT_JAUNE][1];
			BTLstr->creature[MemoryArea].texture[2] = rat->texture[RAT_JAUNE][2];
			break;
		case RAT_ORANGE:
			BTLstr->creature[MemoryArea].life = 180;
			BTLstr->creature[MemoryArea].texture[0] = rat->texture[RAT_ORANGE][0];
			BTLstr->creature[MemoryArea].texture[1] = rat->texture[RAT_ORANGE][1];
			BTLstr->creature[MemoryArea].texture[2] = rat->texture[RAT_ORANGE][2];
			break;
		case RAT_ROUGE:
			BTLstr->creature[MemoryArea].life = 300;
			BTLstr->creature[MemoryArea].texture[0] = rat->texture[RAT_ROUGE][0];
			BTLstr->creature[MemoryArea].texture[1] = rat->texture[RAT_ROUGE][1];
			BTLstr->creature[MemoryArea].texture[2] = rat->texture[RAT_ROUGE][2];
			break;
		default:
			break;
	}
	BTLstr->creature[MemoryArea].lifemax = BTLstr->creature[MemoryArea].life;
	BTLstr->creature[MemoryArea].isdead = false;
	BTLstr->creature[MemoryArea].iserasable = false;
	BTLstr->creature[MemoryArea].tempsanimation = 0;
	BTLstr->creature[MemoryArea].Direction = rand()%8;
	BTLstr->creature[MemoryArea].indexanim = 0;
	BTLstr->creature[MemoryArea].mind = 0;
	BTLstr->creature[MemoryArea].mindtime = 0;
	BTLstr->creature[MemoryArea].looted = 0;
	BTLstr->creature[MemoryArea].ontheway = 0;
	BTLstr->creature[MemoryArea].wayx = 0;
	BTLstr->creature[MemoryArea].wayy = 0;
	for (index = 0 ; index < 8 ; index++)
	{
		BTLstr->creature[MemoryArea].relevancy[index] = 0;
	}
	//haut -> bas -> gauche -> droite
	if (randside == 0)
	{
		BTLstr->creature[MemoryArea].position.y = -100;
		BTLstr->creature[MemoryArea].position.x = randwidth;
	}
	else if (randside == 1)
	{
		BTLstr->creature[MemoryArea].position.y = systeme->screenh + 100;
		BTLstr->creature[MemoryArea].position.x = randwidth;
	}
	else if (randside == 2)
	{
		BTLstr->creature[MemoryArea].position.y = randhigh;
		BTLstr->creature[MemoryArea].position.x = -100;
	}
	else
	{
		BTLstr->creature[MemoryArea].position.y = randhigh;
		BTLstr->creature[MemoryArea].position.x = systeme->screenw + 100;
	}
	
	BTLstr->creature[MemoryArea].position.w = systeme->screenw*0.073206442;//100
	BTLstr->creature[MemoryArea].position.h = systeme->screenh*0.032552083;//25
	BTLstr->creature[MemoryArea].STATICposition.w = BTLstr->creature[MemoryArea].position.w;
	BTLstr->creature[MemoryArea].STATICposition.h = BTLstr->creature[MemoryArea].position.h;
	
	BTLstr->creature[MemoryArea].BarreDeVie = AddLifeBar(BTLstr->creature[MemoryArea].life,
				BTLstr->creature[MemoryArea].position.w, systeme);
}
