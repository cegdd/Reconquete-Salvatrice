#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "sauvegarde.h"
#include "struct.h"
#include "image.h"

extern int screenh, screenw;

void LoadDonjon(struct DONJON *donjon, char *name)
{
    char temp[128];
    char buffer[4096] = {'\0'};
    FILE *fichier = NULL;
    int i, j;
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

        j = atoi(buffer);
        for(i = 0 ; i < j ; i++)
        {
            lis(fichier, buffer);
            lis(fichier, buffer);
           // sprintf(systeme->creature[i].name, buffer);
            lis(fichier, buffer);
           // sprintf(systeme->creature[i].imgpath, buffer);
            lis(fichier, buffer);
           // systeme->creature[i].vie = atoi(buffer);
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
      //      data->mob[i].ID = atoi(buffer);
            //translation mob en x
            lis(fichier, buffer);
            donjon->monstre[i].translation.x = atoi(buffer);
            //translation mob en y
            lis(fichier, buffer);
            donjon->monstre[i].translation.y = atoi(buffer);
       //     data->mob[i].actif = true;
       //     data->mob[i].monstre.pict.texture = systeme->creature[data->mob[i].ID].pict.texture;
       //     setPos4(&data->mob[i].monstre.pict.pos, 0, 0, systeme->creature[data->mob[i].ID].pict.pos.w, systeme->creature[data->mob[i].ID].pict.pos.h);
        }
        fclose(fichier);
    }
    else
    {
        printf("no project founded\n");
    }
}


