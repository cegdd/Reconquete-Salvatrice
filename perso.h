#ifndef PERSOH
#define PERSOH

#include "struct.h"

void initperso(struct PERSO *perso,struct DIVERSsysteme *systeme);

int directionperso(struct DIRECTION *direction);

void hitboxplayer (struct DONJON *donjon, struct PERSO *perso, struct DIVERSsysteme *systeme);
void TakeDamage (int index, struct DONJON *donjon, struct PERSO *perso, struct DIVERSsysteme *systeme);

#endif
