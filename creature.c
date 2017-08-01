#include <stdlib.h>
#include <stdbool.h>

#include "image.h"
#include "creature.h"

void initcreature(struct CREATURE *creature)
{
    creature->aggressif = false;
    creature->Rvision = 0;
    creature->vitesse = 0;
    creature->dps = 0;
    creature->Ratk = 0;
    creature->vie  = 0;
    creature->name[0]  = '\0';
    creature->imgpath[0]  = '\0';
    creature->pict.texture  = -1;
    setPos4(&creature->pict.pos, 0, 0, 0, 0);
}
