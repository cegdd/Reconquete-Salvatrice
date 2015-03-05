#ifndef EVENEMENTH
#define EVENEMENTH

#include <stdbool.h>

typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct typeFORevent typeFORevent;
typedef struct typelogin typelogin;
typedef struct typecombat typecombat;
typedef struct DIRECTION DIRECTION;
typedef struct DIVERSui DIVERSui;

void boucleevent (bool *lancermessage, typeFORevent *FORevent);
int boucleeventcombat (typecombat *BTLstr, DIVERSsysteme *systeme, DIRECTION *direction, DIVERSui *ui);
int boucleeventlogin (typelogin *loginstore, DIVERSsysteme *systeme);
int LoopEventBattleDeath (typecombat *BTLstr, DIVERSsysteme *systeme, SDL_Event *event);

void eventmapclavierdown(typeFORevent *FORevent);
void eventmapclavierup(bool *lancermessage, typeFORevent *FORevent);
void eventmapsourisgaucheup(typeFORevent *FORevent);
void eventmapsourisdroiteup(typeFORevent *FORevent);
void eventmapsourisgauchedown(typeFORevent *FORevent);
void eventmapsourisdroitedown(typeFORevent *FORevent);

void sourisactionzone(typeFORevent *FORevent);

#endif
