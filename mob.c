#include "mob.h"

#include "systeme.h"
#include "perso.h"
#include "path.h"
#include "deplacement.h"
#include "tool.h"

void initmob(struct MOB *mob)
{
    mob->fixe = true;
    mob->vie = 0;
    mob->ID = 0;
    mob->angle = 0;
    mob->scale = 0.0;
    mob->TimeSinceAtk = 0;
    mob->hookpict.translation.x = 0;
    mob->hookpict.translation.y = 0;
    CEGDD_UI_setPos4(&mob->hookpict.pict.pos, 0, 0, 0, 0);
    CEGDD_UI_setPos4(&mob->hookpict.Originpos, 0, 0, 0, 0);
    mob->hookpict.pict.texture = -1;
    PATH_init(&mob->path);
    mob->straightpath = NULL;
}

void SetMob(int i, struct DONJON *donjon)
{
    donjon->mob[i].hookpict.pict.texture = donjon->creature[donjon->mob[i].ID].pict.texture;
    CEGDD_UI_setPos4(&donjon->mob[i].hookpict.pict.pos, 0, 0,
            donjon->creature[donjon->mob[i].ID].pict.pos.w * donjon->mob[i].scale,
            donjon->creature[donjon->mob[i].ID].pict.pos.h * donjon->mob[i].scale);
    CEGDD_UI_setPos4(&donjon->mob[i].hookpict.pict.pos,
            0,
            0,
            donjon->creature[donjon->mob[i].ID].pict.pos.w * donjon->mob[i].scale,
            donjon->creature[donjon->mob[i].ID].pict.pos.h * donjon->mob[i].scale);

    donjon->mob[i].BarreDeVie = AddLifeBar(donjon->creature[donjon->mob[i].ID].vie, 68);
    donjon->mob[i].atkDone = false;
    donjon->mob[i].TimeSinceAtk = 0;
}

void SyncMob(struct DONJON *donjon, struct PERSO *perso)
{
    int i = 0;
    int time  = SDL_GetTicks();
    for (i = 0 ; i < donjon->nombremonstre ; i++)
    {
        if (donjon->creature[donjon->mob[i].ID].vie > 0)
        {
            if(donjon->mob[i].atkDone == true &&
               time - donjon->mob[i].TimeSinceAtk <= donjon->creature[donjon->mob[i].ID].hitlaps)
            {
                    donjon->mob[i].atkDone = false;
            }

                if (checkdistance(&donjon->mob[i].hookpict.pict.pos,
                                  &perso->perso.pict.pos,
                                  donjon->creature[donjon->mob[i].ID].Ratk) == false)
                {
                        NewStraightPath(donjon, perso->perso.pict.pos);
                        printf ("mob en %d %d attaque perso en %d %d vecteur = %f %f\n"   ,donjon->mob[0].hookpict.translation.x - donjon->map.pict.pos.x
                                                                    ,donjon->mob[0].hookpict.translation.y - donjon->map.pict.pos.y
                                                                    ,donjon->mob[0].straightpath->target.pos.x - donjon->map.pict.pos.x
                                                                    ,donjon->mob[0].straightpath->target.pos.y - donjon->map.pict.pos.y
                                                                    ,donjon->mob[0].straightpath->vecteur_X
                                                                    ,donjon->mob[0].straightpath->vecteur_Y);
                }
        }
    }
}
