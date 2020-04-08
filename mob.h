#ifndef MOBH
#define MOBH

#include "struct.h"

struct DONJON;

void initmob(struct MOB *mob);
void SetMob(int i, struct DONJON *donjon);
void SyncMob(struct DONJON *donjon, struct PERSO *perso);

#endif
