#ifndef MOBH
#define MOBH

#include "image.h"
#include "path.h"

struct MOB
{
    bool fixe;

    int vie;
    int ID;
    int angle;

    double scale;

    struct BARREVIE *BarreDeVie;
    struct hookpict hookpict;
    struct PATH path;
};

void initmob(struct MOB *mob);

#endif
