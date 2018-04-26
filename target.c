#include "target.h"

void NewTarget(struct TARGET *target, struct SDL_Rect pos)
{
    target->pos.x = pos.x;
    target->pos.y = pos.y;
}
