#ifndef EVENEMENTH
#define EVENEMENTH

#include <stdbool.h>
#include "main.h"
#include "login.h"

void boucleevent (bool *lancermessage,struct typeFORevent *FORevent);
int boucleeventcombat (struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct DIRECTION *direction,struct DIVERSui *ui);
int boucleeventlogin (struct typelogin *loginstore,struct DIVERSsysteme *systeme);
int LoopEventBattleDeath (struct typecombat *BTLstr, SDL_Event *event);

void eventmapclavierdown(struct typeFORevent *FORevent);
void eventmapclavierup(bool *lancermessage,struct typeFORevent *FORevent);
void eventmapsourisgaucheup(struct typeFORevent *FORevent);
void eventmapsourisdroiteup(struct typeFORevent *FORevent);
void eventmapsourisgauchedown(struct typeFORevent *FORevent);
void eventmapsourisdroitedown(struct typeFORevent *FORevent);

void sourisactionzone(struct typeFORevent *FORevent);

#endif
