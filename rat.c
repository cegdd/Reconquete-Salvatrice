#include <SDL2/SDL.h>

#include "systeme.h"

int TestColision_Rat(SDL_Rect *rat, int x, int y)
{
    SDL_Rect pix = {x, y, 1, 1};
    if (checkdistance(&pix, rat, 30) == -1 )
    {
        return 1;
    }
    return 0;
}
