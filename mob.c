#include "mob.h"
#include "image.h"
#include "tool.h"
#include "donjon.h"

void initmob(struct MOB *mob)
{
    mob->fixe = true;
    mob->vie = 0;
    mob->ID = 0;
    mob->angle = 0;
    mob->scale = 0.0;
    mob->hookpict.translation.x = 0;
    mob->hookpict.translation.y = 0;
    setPos4(&mob->hookpict.pict.pos, 0, 0, 0, 0);
    mob->hookpict.pict.texture = -1;
    PATH_init(&mob->path);
}

void SetMob(int i, struct DONJON *donjon)
{
    donjon->mob[i].hookpict.pict.texture = donjon->creature[donjon->mob[i].ID].pict.texture;
    setPos4(&donjon->mob[i].hookpict.pict.pos, 0, 0,
            donjon->creature[donjon->mob[i].ID].pict.pos.w * donjon->mob[i].scale,
            donjon->creature[donjon->mob[i].ID].pict.pos.h * donjon->mob[i].scale);

    donjon->mob[i].BarreDeVie = AddLifeBar(donjon->creature[donjon->mob[i].ID].vie, 68);
}
