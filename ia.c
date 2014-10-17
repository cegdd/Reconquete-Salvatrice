#include <stdlib.h>
#include <SDL2/SDL.h>

#include "main.h"

typedef struct typecombat typecombat;

int MouvemementChauveSouris(typecombat *BTLstr, struct RAT *rat, struct DIVERSsysteme *systeme, int index)
{
	int index2, total = 0;

	int x = BTLstr->ennemi[index].position.x;
	int y = BTLstr->ennemi[index].position.y;
	int w = BTLstr->ennemi[index].position.w;
	int h = BTLstr->ennemi[index].position.h;



	//si l'idée a expiré
	BTLstr->ennemi[index].mindtime--;
	if (BTLstr->ennemi[index].mindtime <= 0)
	{
		//génération de la durée de la prochaine idée
		BTLstr->ennemi[index].mindtime = rand()%200;

		//toute les idées sont probables
		for(index2 = 0 ; index2 < 8 ; index2++)
		{
			BTLstr->ennemi[index].relevancy[index2] = 1;
		}

		//total de l'interet de toutes les idées
		for (index2 = 0 ; index2 < 8 ; index2++)
		{
			total += BTLstr->ennemi[index].relevancy[index2];
		}
		//tirage de l'idée dans se total
		int lerand = rand()%total;

		for (index2 = 0 ; index2 < 8 ; index2++)
		{
			if(lerand >= 0 && lerand < BTLstr->ennemi[index].relevancy[index2])
			{
				BTLstr->ennemi[index].mind = index2;
				break;
			}
			else
			{
				lerand -= BTLstr->ennemi[index].relevancy[index2];
			}
		}
	}

	switch(BTLstr->ennemi[index].mind)
	{
		case 1:
			for(index2 = 0 ; index2 < BTLstr->ennemi[index].mindtime ; index2++)
			{
				x+=1;
				y-=1;
			}
			if (y < 0){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else if (x+w > systeme->screenw) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->ennemi[index].position.x += 1;
				BTLstr->ennemi[index].position.y -= 1;
				return 1;
			}
			break;
		case 2:
			for(index2 = 0 ; index2 < BTLstr->ennemi[index].mindtime ; index2++)
			{
				x+=1;
			}
			if (x+w > systeme->screenw) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->ennemi[index].position.x += 1;
				return 2;
			}
			break;
		case 3:
			for(index2 = 0 ; index2 < BTLstr->ennemi[index].mindtime ; index2++)
			{
				x+=1;
				y+=1;
			}
			if (y+h > systeme->screenh){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else if (x+w > systeme->screenw) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->ennemi[index].position.x += 1;
				BTLstr->ennemi[index].position.y += 1;
				return 3;
			}
			break;
		case 4:
			for(index2 = 0 ; index2 < BTLstr->ennemi[index].mindtime ; index2++)
			{
				y+=1;
			}
			if (y+h > systeme->screenh){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->ennemi[index].position.y += 1;
				return 4;
			}
			break;
		case 5:
			for(index2 = 0 ; index2 < BTLstr->ennemi[index].mindtime ; index2++)
			{
				x-=1;
				y+=1;
			}
			if (y+h > systeme->screenh){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else if (x <0) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->ennemi[index].position.x -= 1;
				BTLstr->ennemi[index].position.y += 1;
				return 5;
			}
			break;
		case 6:
			for(index2 = 0 ; index2 < BTLstr->ennemi[index].mindtime ; index2++)
			{
				x-=1;
			}
			if (x < 0) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->ennemi[index].position.x -= 1;
				return 6;
			}
			break;
		case 7:
			for(index2 = 0 ; index2 < BTLstr->ennemi[index].mindtime ; index2++)
			{
				x-=1;
				y-=1;
			}
			if (y < 0){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else if (x < 0) {return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->ennemi[index].position.x -= 1;
				BTLstr->ennemi[index].position.y -= 1;
				return 7;
			}
			break;
		default:
			for(index2 = 0 ; index2 < BTLstr->ennemi[index].mindtime ; index2++)
			{
				y-=1;
			}
			if (y < 0){return MouvemementChauveSouris(BTLstr, rat, systeme, index);}
			else
			{
				BTLstr->ennemi[index].position.y -= 1;
				return 0;
			}
			break;
	}
	return 0;
}
