#ifndef MOBH
#define MOBH

#include "path.h"
#include "struct.h"

struct DONJON;

struct MOB
{
    bool fixe;
    bool atkDone;

    int vie;
    int ID;
    int angle;
    int TimeSinceAtk;

    double scale;

    struct BARREVIE *BarreDeVie;
    struct hookpict hookpict;
    struct PATH path;
};

void initmob(struct MOB *mob);
void SetMob(int i, struct DONJON *donjon);
void SyncMob(struct DONJON *donjon);

#endif
