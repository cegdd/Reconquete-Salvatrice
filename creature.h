#ifndef CREATUREH
#define CREATUREH

#include "struct.h"

struct CREATURE
{
    bool aggressif;

    int vie;
    int Rvision;
    int vitesse;
    int dps;
    int Ratk;

    char name[64];
    char imgpath[128];

    struct pict pict;
};

void initcreature(struct CREATURE *creature);

#endif
