#include "main.h"
#include "colision.h"
#include "image.h"

extern int screenh, screenw;

void BattleDraw_FloorItems(struct typecombat *BTLstr,struct PACKobjet *objet)
{
    int index;
    for (index = 0; index < BTLstr->NBlootsol ; index++)
    {
        if (BTLstr->lootsol[index] != BTL_OBJ_FLOOR)
        {
            BTLstr->plootsol[index].w = BTLstr->oldplootsol[index].w * BTLstr->animobjet;
            BTLstr->plootsol[index].h = BTLstr->oldplootsol[index].h * BTLstr->animobjet;
        }
        draw(objet->objet[BTLstr->IDlootsol[index]].texture, &BTLstr->plootsol[index]);
    }
}

void BattleDraw_Ennemy(struct typecombat *BTLstr, int arcademode)
{
    int index, calcul;
    for (index = 0; index < LIMITEmobARCADE ; index++)
	{
		/*looted stuff*/
		if (BTLstr->creature[index].ontheway != 0 && BTLstr->creature[index].m_pict.pict.pos.x < screenw)
		{
			BTLstr->creature[index].m_pict.pict.pos.w = BTLstr->creature[index].STATICposition.w * BTLstr->animobjet;
			BTLstr->creature[index].m_pict.pict.pos.h = BTLstr->creature[index].STATICposition.h * BTLstr->animobjet;
			if (arcademode == false)
			{	////SDL_RenderCopy(systeme->renderer, BTLstr->peau, NULL, &BTLstr->creature[index].position);
			}
			else
			{	////SDL_RenderCopy(systeme->renderer, BTLstr->piece, NULL, &BTLstr->creature[index].position);
			}
		}
		/*if they're dead but are not looted*/
		else if (BTLstr->creature[index].isdead == true && BTLstr->creature[index].looted == false)
		{
			if (arcademode == false)
			{
				calcul =90+(45 * BTLstr->creature[index].Direction);
				BTLstr->creature[index].m_pict.pict.texture = BTLstr->creature[index].m_pict.texture[2];
				Turn_And_Draw(&BTLstr->creature[index].m_pict.pict, calcul);

			}
			else
			{
				BTLstr->creature[index].m_pict.pict.pos.w = 50;
				BTLstr->creature[index].m_pict.pict.pos.h = 50;
				//draw(BTLstr->piece, &BTLstr->creature[index].position);
			}
		}
		/*if they're alive*/
		else if(BTLstr->creature[index].isdead == false)
		{
			calcul =90+(45 * BTLstr->creature[index].Direction);

            Sync_Moving_Pict(BTLstr->temps, &BTLstr->creature[index].m_pict);
            Turn_And_Draw(&BTLstr->creature[index].m_pict.pict, calcul);
          }

		if (BTLstr->creature[index].isdead == false && BTLstr->creature[index].life < BTLstr->creature[index].lifemax)
		{
			////SDL_RenderCopy(systeme->renderer, BTLstr->creature[index].BarreDeVie->BGtexture, NULL, &BTLstr->creature[index].BarreDeVie->BGposition);
			////SDL_RenderCopy(systeme->renderer, BTLstr->creature[index].BarreDeVie->texture, NULL, &BTLstr->creature[index].BarreDeVie->position);
		}
	}
}

void BattleDraw_Player(struct typecombat *BTLstr,struct PERSO *perso, struct DIVERSsysteme *systeme)
{
    double degre = FindAngle(&perso->perso.pict.pos, &BTLstr->curseur.pos) - 90; /* finding angle*/

	if (BTLstr->poing_tendu == true)
    {
        //SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->pperso_poing, &BTLstr->Pperso, degre, &perso->centrecorp, SDL_FLIP_NONE);
    }
    else
    {
        if (BTLstr->persobouge)
        {
            Sync_Moving_Pict(BTLstr->temps, &perso->perso);
        }
        Turn_And_Draw(&perso->perso.pict, degre);
    }
    /*life bar*/
    //SDL_RenderCopy(systeme->renderer, perso->BarreDeVie->BGtexture, NULL, &perso->BarreDeVie->BGposition);
    //SDL_RenderCopy(systeme->renderer, perso->BarreDeVie->texture, NULL, &perso->BarreDeVie->position);
}

void BattleDraw_Projectile(struct typecombat *BTLstr)
{
    int index;
    for(index = 0 ; index < NBcailloux ; index++)
	{
		if (BTLstr->DepartBalle[index] == RUNNING)
		{
			draw(BTLstr->balle, &BTLstr->pballe[index]);
		}
	}
}

