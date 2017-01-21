#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "sauvegarde.h"
#include "struct.h"
#include "image.h"
#include "tool.h"

extern int screenh, screenw;

void LoadDonjon(struct DONJON *donjon, char *name)
{
    char temp[128];
    char buffer[4096] = {'\0'};
    FILE *fichier = NULL;
    int i;
    int x = 0, y = 0;

    sprintf(temp, "rs/maps/%s.RSCryptedMap", name);
    fichier = fopen(temp, "r");

    if (fichier != NULL)
    {

        //nom de la map
        lis(fichier, buffer);

        sprintf(temp, "rs/maps/%s.png", buffer);
        donjon->map.pict.texture = loadTextureandsize(temp, &donjon->map.pict.pos);
        setPos2(&donjon->origin, screenw/2, screenh/2);

        sprintf(temp, "rs/maps/%snb.png", buffer);
        donjon->map.calque = IMG_Load(temp);

        if (!glIsTexture(donjon->map.pict.texture))
        {
            printf("donjon map : %s not founded\n", temp);
        }

        lis(fichier, buffer);

        donjon->nbcreature = atoi(buffer);
        for(i = 0 ; i < donjon->nbcreature ; i++)
        {
            lis(fichier, buffer);
            lis(fichier, buffer);
            sprintf(donjon->creature[i].name, buffer);
            lis(fichier, buffer);
            sprintf(donjon->creature[i].imgpath, buffer);
            lis(fichier, buffer);
            donjon->creature[i].vie = atoi(buffer);

            sprintf(buffer, "rs/images/%s", donjon->creature[i].imgpath);
            donjon->creature[i].pict.texture = loadTextureandsize(buffer, &donjon->creature[i].pict.pos);
        }

        //si le joueur est poser
        lis(fichier, buffer);
        if (buffer[0] == '1')
        {
            //translation joueur en x
            lis(fichier, buffer);
            x = atoi(buffer);
            //translation joueur en y
            lis(fichier, buffer);
            y = atoi(buffer);
            setPos2(&donjon->map.translation, -x, -y);
        }

        //nombre de mobs
      //  listmob(systeme);

        lis(fichier, buffer);
        donjon->nombremonstre = atoi(buffer);

        for(i=0 ; i < donjon->nombremonstre ; i++)
        {
            //ID des mobs
            lis(fichier, buffer);
            donjon->mob[i].ID = atoi(buffer);
            //translation mob en x
            lis(fichier, buffer);
            donjon->mob[i].hookpict.translation.x = atoi(buffer);
            //translation mob en y
            lis(fichier, buffer);
            donjon->mob[i].hookpict.translation.y = atoi(buffer);

            donjon->mob[i].hookpict.pict.texture = donjon->creature[donjon->mob[i].ID].pict.texture;
            setPos4(&donjon->mob[i].hookpict.pict.pos, 0, 0, donjon->creature[donjon->mob[i].ID].pict.pos.w, donjon->creature[donjon->mob[i].ID].pict.pos.h);

            donjon->mob[i].BarreDeVie = AddLifeBar(donjon->creature[donjon->mob[i].ID].vie, 68);
        }
        fclose(fichier);
    }
    else
    {
        printf("no project founded\n");
    }
}


