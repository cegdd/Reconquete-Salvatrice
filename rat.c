#include <SDL.h>

#include "systeme.h"
#include "main.h"
#include "tool.h"
#include "image.h"

extern int screenh, screenw;

int TestColision_Rat(SDL_Rect *rat, int x, int y, int direction)
{
    SDL_Rect pix = {0, 0, 1, 1};
    pix.x = x;
    pix.y = y;

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

void ADD_Rat(int type, int MemoryArea,struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct MOB *mob)
{

	int index;
	float randside = rand()%4;
	float randwidth = rand()%screenw;
	float randhigh = rand()%screenh;

	switch(type)
	{
		case RAT_BLANC:
			BTLstr->creature[MemoryArea].life = 10;
			break;
		case RAT_VERT:
			BTLstr->creature[MemoryArea].life = 25;
			break;
		case RAT_JAUNE:
			BTLstr->creature[MemoryArea].life = 70;
			break;
		case RAT_ORANGE:
			BTLstr->creature[MemoryArea].life = 180;
			break;
		case RAT_ROUGE:
			BTLstr->creature[MemoryArea].life = 300;
			break;
		default:
			break;
	}
	BTLstr->creature[MemoryArea].lifemax = BTLstr->creature[MemoryArea].life;
	BTLstr->creature[MemoryArea].isdead = false;
	BTLstr->creature[MemoryArea].iserasable = false;
	BTLstr->creature[MemoryArea].Direction = rand()%8;
	BTLstr->creature[MemoryArea].mind = 0;
	BTLstr->creature[MemoryArea].mindtime = 0;
	BTLstr->creature[MemoryArea].looted = false;
	BTLstr->creature[MemoryArea].ontheway = 0;
	BTLstr->creature[MemoryArea].wayx = 0;
	BTLstr->creature[MemoryArea].wayy = 0;
	for (index = 0 ; index < 8 ; index++)
	{
		BTLstr->creature[MemoryArea].relevancy[index] = 0;
	}
	/*haut -> bas -> gauche -> droite*/
	if (randside == 0)
	{
		BTLstr->creature[MemoryArea].m_pict.pict.pos.y = -100;
		BTLstr->creature[MemoryArea].m_pict.pict.pos.x = randwidth;
	}
	else if (randside == 1)
	{
		BTLstr->creature[MemoryArea].m_pict.pict.pos.y = screenh + 100;
		BTLstr->creature[MemoryArea].m_pict.pict.pos.x = randwidth;
	}
	else if (randside == 2)
	{
		BTLstr->creature[MemoryArea].m_pict.pict.pos.y = randhigh;
		BTLstr->creature[MemoryArea].m_pict.pict.pos.x = -100;
	}
	else
	{
		BTLstr->creature[MemoryArea].m_pict.pict.pos.y = randhigh;
		BTLstr->creature[MemoryArea].m_pict.pict.pos.x = screenw + 100;
	}

	BTLstr->creature[MemoryArea].m_pict.pict.pos.w = screenw*0.073206442;/*100*/
	BTLstr->creature[MemoryArea].m_pict.pict.pos.h = screenh*0.032552083;/*25*/
	BTLstr->creature[MemoryArea].STATICposition.w = BTLstr->creature[MemoryArea].m_pict.pict.pos.w;
	BTLstr->creature[MemoryArea].STATICposition.h = BTLstr->creature[MemoryArea].m_pict.pict.pos.h;

	BTLstr->creature[MemoryArea].BarreDeVie = AddLifeBar(BTLstr->creature[MemoryArea].life,
				BTLstr->creature[MemoryArea].m_pict.pict.pos.w, systeme);
}
