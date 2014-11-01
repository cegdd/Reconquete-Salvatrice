#include <SDL2/SDL.h>

#include "systeme.h"
#include "colision.h"
#include "main.h"
#include "jeux.h"


typedef struct typecombat typecombat;

int HitboxPoing(typecombat *BTLstr, SDL_Rect *pennemi)
{
    int k = 0, l = 0;
    SDL_Rect pix = {k, l, 1, 1};


    if (checkdistance(pennemi, &BTLstr->Pperso, 120) == -1 )//degrossissage pour calcul précis
    {
        for(k = BTLstr->Pperso.x ; k <= BTLstr->Pperso.x + BTLstr->Pperso.w ; k++)
        {
            for(l = BTLstr->Pperso.y ; l <= BTLstr->Pperso.y + BTLstr->Pperso.h; l++)
            {
                pix.x = k;
                pix.y = l;
                if (checkdistance(&BTLstr->Pperso, pennemi, 30) == 1)
                {
                    if (colisionfromage(&pix, pennemi, &BTLstr->pcurseur, 20) == true)
                    {
                        BTLstr->calque[k][l] = 1;
                        //return 0;
                    }
                }
            }
        }
    }
    return -1;
}


