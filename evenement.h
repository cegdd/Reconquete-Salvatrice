#ifndef EVENEMENTH
#define EVENEMENTH

#include <stdbool.h>
#include <SDL.h>
#include "main.h"
#include "login.h"

void boucleevent (bool *lancermessage,struct typeFORevent *FORevent);
int boucleeventlogin (struct typelogin *loginstore,struct DIVERSsysteme *systeme);
void eventmapclavierdown(struct typeFORevent *FORevent);
void eventmapclavierup(bool *lancermessage,struct typeFORevent *FORevent);
void eventmapsourisgaucheup(struct typeFORevent *FORevent);
void eventmapsourisdroiteup(struct typeFORevent *FORevent);
void eventmapsourisgauchedown(struct typeFORevent *FORevent);
void eventmapsourisdroitedown(struct typeFORevent *FORevent);

void sourisactionzone(struct typeFORevent *FORevent);

#endif
