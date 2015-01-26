#ifndef TIRH
#define TIRH
typedef struct typecombat typecombat;
typedef struct DIVERSsysteme DIVERSsysteme;

int TestColision_Rat(SDL_Rect *rat, int x, int y, int direction);
void ADD_Rat(int MemoryArea, typecombat *BTLstr, DIVERSsysteme *systeme);

#endif
