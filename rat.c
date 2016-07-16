#include <SDL.h>

#include "systeme.h"
#include "main.h"
#include "tool.h"
#include "image.h"

extern int screenh, screenw;

int TestColision_Rat(SDL_Rect *rat, int x, int y, int direction)
{
    SDL_Rect pix = {0, 0, 1, 1};
    pix.x = x;
    pix.y = y;

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
    else if (direction == LEFT)
    {
        pix.x += 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.x += 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == RIGHT)
    {
        pix.x -= 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.x -= 15;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == UPRIGHT)
    {
        pix.y += 10;
        pix.x -= 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y += 10;
        pix.x -= 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == LEFTUP)
    {
        pix.y += 10;
        pix.x += 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y += 10;
        pix.x += 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == RIGHTDOWN)
    {
        pix.y -= 10;
        pix.x -= 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y -= 10;
        pix.x -= 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    else if (direction == DOWNLEFT)
    {
        pix.y -= 10;
        pix.x += 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
        pix.y -= 10;
        pix.x += 10;
        if (checkdistance(&pix, rat, 10) == -1 )
        {
            return 1;
        }
    }
    return 0;
}
