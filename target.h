#ifndef TARGETH
#define TARGETH

#include <SDL.h>

struct TARGET
{
    SDL_Point pos;
};

void NewTarget(struct TARGET *target, struct SDL_Rect pos);

#endif
