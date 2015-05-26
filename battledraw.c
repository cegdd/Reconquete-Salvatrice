
typedef struct typecombat typecombat;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct PACKobjet PACKobjet;

#include "main.h"
#include "colision.h"

void BattleDraw_FloorItems(typecombat *BTLstr, DIVERSsysteme *systeme, PACKobjet *objet)
{
    int index;
    for (index = 0; index < BTLstr->NBlootsol ; index++)
    {
        if (BTLstr->lootsol[index] != BTL_OBJ_FLOOR)
        {
            BTLstr->plootsol[index].w = BTLstr->oldplootsol[index].w * BTLstr->animobjet;
            BTLstr->plootsol[index].h = BTLstr->oldplootsol[index].h * BTLstr->animobjet;
        }
        SDL_RenderCopy(systeme->renderer, objet->objet[BTLstr->IDlootsol[index]].texture, NULL, &BTLstr->plootsol[index]);
    }
}

void BattleDraw_Ennemy(typecombat *BTLstr, DIVERSsysteme *systeme, int arcademode)
{
    int index, calcul;
    for (index = 0; index < LIMITEmobARCADE ; index++)
	{
		/*looted stuff*/
		if (BTLstr->creature[index].ontheway != 0 && BTLstr->creature[index].position.x < systeme->screenw)
		{
			BTLstr->creature[index].position.w = BTLstr->creature[index].STATICposition.w * BTLstr->animobjet;
			BTLstr->creature[index].position.h = BTLstr->creature[index].STATICposition.h * BTLstr->animobjet;
			if (arcademode == false)
			{	SDL_RenderCopy(systeme->renderer, BTLstr->peau, NULL, &BTLstr->creature[index].position);}
			else
			{	SDL_RenderCopy(systeme->renderer, BTLstr->piece, NULL, &BTLstr->creature[index].position);}
		}
		/*si elles sont mortes et pas ramasser*/
		else if (BTLstr->creature[index].isdead == true && BTLstr->creature[index].looted == 0)
		{
			if (arcademode == false)
			{
				calcul =90+(45 * BTLstr->creature[index].Direction);
				SDL_RenderCopyEx(systeme->renderer,BTLstr->creature[index].texture[2], NULL, &BTLstr->creature[index].position, calcul,NULL, SDL_FLIP_NONE);

			}
			else
			{
				BTLstr->creature[index].position.w = 50;
				BTLstr->creature[index].position.h = 50;
				SDL_RenderCopy(systeme->renderer,BTLstr->piece, NULL, &BTLstr->creature[index].position);
			}
		}
		else if(BTLstr->creature[index].isdead == false)/*if they're alive*/
		{
			calcul =90+(45 * BTLstr->creature[index].Direction);
			SDL_RenderCopyEx(systeme->renderer, BTLstr->creature[index].texture[BTLstr->creature[index].indexanim], NULL, &BTLstr->creature[index].position, calcul,NULL, SDL_FLIP_NONE);
		}

		if (BTLstr->creature[index].isdead == false && BTLstr->creature[index].life < BTLstr->creature[index].lifemax)
		{
			SDL_RenderCopy(systeme->renderer, BTLstr->creature[index].BarreDeVie->BGtexture, NULL, &BTLstr->creature[index].BarreDeVie->BGposition);
			SDL_RenderCopy(systeme->renderer, BTLstr->creature[index].BarreDeVie->texture, NULL, &BTLstr->creature[index].BarreDeVie->position);
		}
	}
}

void BattleDraw_Player(typecombat *BTLstr, DIVERSsysteme *systeme, PERSO *perso)
{
    double degre = FindAngle(&BTLstr->Pperso, &BTLstr->pcurseur) + 90; /* finding angle*/

	if (BTLstr->poing_tendu == true)
    {
        SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->pperso_poing, &BTLstr->Pperso, degre, &perso->centrecorp, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->spriteup[BTLstr->indexanimperso], &BTLstr->Pperso, degre,NULL, SDL_FLIP_NONE);
    }
    /*life bar*/
    SDL_RenderCopy(systeme->renderer, perso->BarreDeVie->BGtexture, NULL, &perso->BarreDeVie->BGposition);
    SDL_RenderCopy(systeme->renderer, perso->BarreDeVie->texture, NULL, &perso->BarreDeVie->position);
}

void BattleDraw_Projectile(typecombat *BTLstr, DIVERSsysteme *systeme)
{
    int index;
    for(index = 0 ; index < NBcailloux ; index++)
	{
		if (BTLstr->DepartBalle[index] == RUNNING)
		{
			SDL_RenderCopy(systeme->renderer, BTLstr->balle, NULL, &BTLstr->pballe[index]);
		}
	}
}

