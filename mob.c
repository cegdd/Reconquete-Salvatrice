#include "mob.h"
#include "path.h"

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
