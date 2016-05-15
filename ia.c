#include <stdlib.h>
#include <SDL.h>

#include "main.h"
extern int screenh, screenw;

int MouvemementChauveSouris(struct typecombat *BTLstr, struct RAT *rat, struct DIVERSsysteme *systeme, int index)
{
	int index2 = 0, total = 0, lerand = 0;

	int x = BTLstr->creature[index].m_pict.pict.pos.x;
	int y = BTLstr->creature[index].m_pict.pict.pos.y;
	int w = BTLstr->creature[index].m_pict.pict.pos.w;
	int h = BTLstr->creature[index].m_pict.pict.pos.h;



	/*si l'idée a expiré*/
	BTLstr->creature[index].mindtime--;
	if (BTLstr->creature[index].mindtime <= 0)
	{
		/*génération de la durée de la prochaine idée*/
		BTLstr->creature[index].mindtime = rand()%200;

		/*toute les idées sont probables*/
		for(index2 = 0 ; index2 < 8 ; index2++)
		{
			BTLstr->creature[index].relevancy[index2] = 1;
		}

		/*total de l'interet de toutes les idées*/
		for (index2 = 0 ; index2 < 8 ; index2++)
		{
			total += BTLstr->creature[index].relevancy[index2];
		}
		/*tirage de l'idée dans se total*/
		lerand = rand()%total;

		for (index2 = 0 ; index2 < 8 ; index2++)
		{
			if(lerand >= 0 && lerand < BTLstr->creature[index].relevancy[index2])
			{
				BTLstr->creature[index].mind = index2;
				break;
			}
			else
			{
				lerand -= BTLstr->creature[index].relevancy[index2];
			}
		}
	}

	switch(BTLstr->creature[index].mind)
	{
		case 1:
			for(index2 = 0 ; index2 < BTLstr->creature[index].mindtime ; index2++)
			{
				x+=1;
				y-=1;
			}
			if (y < 0){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else if (x+w > screenw) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.x += 1;
				BTLstr->creature[index].m_pict.pict.pos.y -= 1;
				return UPRIGHT;
			}
			break;
		case 2:
			for(index2 = 0 ; index2 < BTLstr->creature[index].mindtime ; index2++)
			{
				x+=1;
			}
			if (x+w > screenw) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.x += 1;
				return RIGHT;
			}
			break;
		case 3:
			for(index2 = 0 ; index2 < BTLstr->creature[index].mindtime ; index2++)
			{
				x+=1;
				y+=1;
			}
			if (y+h > screenh){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else if (x+w > screenw) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.x += 1;
				BTLstr->creature[index].m_pict.pict.pos.y += 1;
				return RIGHTDOWN;
			}
			break;
		case 4:
			for(index2 = 0 ; index2 < BTLstr->creature[index].mindtime ; index2++)
			{
				y+=1;
			}
			if (y+h > screenh){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.y += 1;
				return DOWN;
			}
			break;
		case 5:
			for(index2 = 0 ; index2 < BTLstr->creature[index].mindtime ; index2++)
			{
				x-=1;
				y+=1;
			}
			if (y+h > screenh){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else if (x <0) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.x -= 1;
				BTLstr->creature[index].m_pict.pict.pos.y += 1;
				return DOWNLEFT;
			}
			break;
		case 6:
			for(index2 = 0 ; index2 < BTLstr->creature[index].mindtime ; index2++)
			{
				x-=1;
			}
			if (x < 0) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.x -= 1;
				return LEFT;
			}
			break;
		case 7:
			for(index2 = 0 ; index2 < BTLstr->creature[index].mindtime ; index2++)
			{
				x-=1;
				y-=1;
			}
			if (y < 0){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else if (x < 0) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.x -= 1;
				BTLstr->creature[index].m_pict.pict.pos.y -= 1;
				return LEFTUP;
			}
			break;
		default:
			for(index2 = 0 ; index2 < BTLstr->creature[index].mindtime ; index2++)
			{
				y-=1;
			}
			if (y < 0){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.y -= 1;
				return UP;
			}
			break;
	}
	return UP;
}

