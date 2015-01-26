#include <SDL2/SDL.h>

#include "systeme.h"
#include "main.h"
#include "tool.h"

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

void ADD_Rat(int MemoryArea, typecombat *BTLstr, DIVERSsysteme *systeme)
{
	int index;
	float randside = rand()%4;
	float randwidth = rand()%systeme->screenw;
	float randhigh = rand()%systeme->screenh;
	
	BTLstr->creature[MemoryArea].life = 30;
	BTLstr->creature[MemoryArea].life = 30;
	BTLstr->creature[MemoryArea].isdead = false;
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
