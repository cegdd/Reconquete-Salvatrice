#include <SDL2/SDL.h>

#include "systeme.h"
#include "main.h"

int TestColision_Rat(SDL_Rect *rat, int x, int y, int direction)
{
    SDL_Rect pix = {x, y, 1, 1};
    if (checkdistance(&pix, rat, 10) == -1 )
    {
        return 1;
    }


    if (direction == UP)
    {
        pix.y += 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y += 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == DOWN)
    {
        pix.y -= 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y -= 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    return 0;
}
