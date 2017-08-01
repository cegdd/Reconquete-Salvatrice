#ifndef DONJONH
#define DONJONH

#include "struct.h"
#include "creature.h"
#include "mob.h"

struct DONJON
{
    char path[64];
    struct floor map;
    SDL_Point origin;
    struct MOB mob [512];

    int nombremonstre;

    struct CREATURE creature[128];
    int nbcreature;
};

void initdonjon(struct DONJON *donjon,struct DIVERSsysteme *systeme);
void LoadDonjon(struct DONJON *donjon, char *name);

#endif
