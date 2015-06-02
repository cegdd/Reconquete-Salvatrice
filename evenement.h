#ifndef EVENEMENTH
#define EVENEMENTH

#include <stdbool.h>
#include "main.h"

typedef struct typeFORevent typeFORevent;
typedef struct typelogin typelogin;
typedef struct typecombat typecombat;
typedef struct DIRECTION DIRECTION;

void boucleevent (bool *lancermessage, typeFORevent *FORevent);
int boucleeventcombat (typecombat *BTLstr,struct DIVERSsysteme *systeme, DIRECTION *direction,struct DIVERSui *ui);
int boucleeventlogin (typelogin *loginstore,struct DIVERSsysteme *systeme);
int LoopEventBattleDeath (typecombat *BTLstr, SDL_Event *event);

void eventmapclavierdown(typeFORevent *FORevent);
void eventmapclavierup(bool *lancermessage, typeFORevent *FORevent);
void eventmapsourisgaucheup(typeFORevent *FORevent);
void eventmapsourisdroiteup(typeFORevent *FORevent);
void eventmapsourisgauchedown(typeFORevent *FORevent);
void eventmapsourisdroitedown(typeFORevent *FORevent);

void sourisactionzone(typeFORevent *FORevent);

#endif
