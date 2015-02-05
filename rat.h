#ifndef TIRH
#define TIRH
typedef struct typecombat typecombat;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct RAT RAT;

int TestColision_Rat(SDL_Rect *rat, int x, int y, int direction);
void ADD_Rat(int type, int MemoryArea, typecombat *BTLstr, DIVERSsysteme *systeme, RAT *rat);

#endif
