#include <SDL2/SDL.h>

#include "systeme.h"
#include "colision.h"
#include "main.h"
#include "jeux.h"
#include "rat.h"

typedef struct typecombat typecombat;

int HitboxPoing(typecombat *BTLstr, int index)
{
    int k = 0, l = 0;
    SDL_Rect pix = {k, l, 1, 1};


    if (checkdistance(&BTLstr->creature[index].position, &BTLstr->Pperso, 120) == -1 )//degrossissage pour calcul pr�cis
    {
        for(k = BTLstr->Pperso.x -20; k <= BTLstr->Pperso.x + BTLstr->Pperso.w +20; k++)
        {//parcour des pixels autour du joueur (environ 11000)
            for(l = BTLstr->Pperso.y -30; l <= BTLstr->Pperso.y + BTLstr->Pperso.h+30; l++)
            {
                pix.x = k;
                pix.y = l;

                //d�finition du poing
                if (checkdistance(&pix, &BTLstr->Pperso, 30) == -1 && checkdistance(&pix, &BTLstr->Pperso, 20) == 1)
                {
                    if (colisionfromage(&BTLstr->Pperso, &BTLstr->pcurseur, &pix, 40) == true)
                   {
                        #if TESTGRID == 1
                        BTLstr->calque[k][l] = 1;
                        #endif // TESTGRID
                        if (TestColision_Rat(&BTLstr->creature[index].position, pix.x, pix.y, BTLstr->creature[index].Direction) == 1)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return -1;
}


