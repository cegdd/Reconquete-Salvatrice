#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "donjon.h"
#include "mob.h"
#include "sauvegarde.h"
#include "image.h"

#include <LIBcegdd_ui.h>

extern int screenh, screenw;

void initdonjon(struct DONJON *donjon,struct DIVERSsysteme *systeme)
{
    int i = 0;

    sprintf(donjon->path, "rs/maps/dj0.RSCryptedMap");

    donjon->nombremonstre = 0;
    donjon->nbcreature = 0;

	for (i = 0 ; i < 128 ; i++)
    {
        initcreature(&donjon->creature[i]);
    }
    for (i = 0 ; i < 512 ; i++)
    {
        initmob(&donjon->mob[i]);
    }
}

void LoadDonjon(struct DONJON *donjon, char *name)
{
    char temp[128];
    char buffer[4096] = {'\0'};
    FILE *fichier = NULL;
    int i, i2;
    int x = 0, y = 0;

    sprintf(temp, "rs/maps/%s.RSCryptedMap", name);
    fichier = fopen(temp, "r");

    if (fichier != NULL)
    {

        //nom de la map
        lis(fichier, buffer);

        sprintf(temp, "rs/maps/%s.png", buffer);
        donjon->map.pict.texture = loadTextureandsize(temp, &donjon->map.pict.pos);
        CEGDD_UI_setPos2(&donjon->origin, screenw/2, screenh/2);

        sprintf(temp, "rs/maps/%snb.png", buffer);
        donjon->map.calque = IMG_Load(temp);

        if (!glIsTexture(donjon->map.pict.texture) ||
            donjon->map.calque == NULL)
        {
            printf("donjon map : %s not founded\n", temp);
        }
        //nombre de creature
        lis(fichier, buffer);

        donjon->nbcreature = atoi(buffer);
        for(i = 0 ; i < donjon->nbcreature ; i++)
        {
            //ID same as i
            lis(fichier, buffer);
            //name
            lis(fichier, buffer);
            strcpy(donjon->creature[i].name, buffer);
            //image
            lis(fichier, buffer);
            strcpy(donjon->creature[i].imgpath, buffer);
            //vie
            lis(fichier, buffer);
            donjon->creature[i].vie = atoi(buffer);
            //agressif
            lis(fichier, buffer);
            donjon->creature[i].aggressif = saybool(buffer[0]);
            if (donjon->creature[i].aggressif == true)
            {
                lis(fichier, buffer);
                donjon->creature[i].Rvision = atoi(buffer);
            }
            //vitesse
            lis(fichier, buffer);
            donjon->creature[i].vitesse = atoi(buffer);
            //dps
            lis(fichier, buffer);
            donjon->creature[i].dps = atoi(buffer);
            //Ratk
            lis(fichier, buffer);
            donjon->creature[i].Ratk = atoi(buffer);
            //hitlaps
            lis(fichier, buffer);
            donjon->creature[i].hitlaps = atoi(buffer);

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
            CEGDD_UI_setPos2(&donjon->map.translation, -x, -y);
        }

        //nombre de mobs
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
            //echelle
            lis(fichier, buffer);
            donjon->mob[i].scale = atoi(buffer);
            //angle
            lis(fichier, buffer);
            donjon->mob[i].angle = atoi(buffer);
            //fixe
            lis(fichier, buffer);
            donjon->mob[i].fixe = saybool(buffer[0]);
            if (donjon->mob[i].fixe == false)
            {
                lis(fichier, buffer);
                donjon->mob[i].path.counter = atoi(buffer);
                for (i2 = 0 ; i2 < donjon->mob[i].path.counter ; i2++)
                {
                    lis(fichier, buffer);
                    donjon->mob[i].path.x[i2] = atoi(buffer);
                    lis(fichier, buffer);
                    donjon->mob[i].path.y[i2] = atoi(buffer);
                    donjon->mob[i].path.used[i2] = true;
                }
                if (donjon->mob[i].path.counter > 0)
                {
                    lis(fichier, buffer);
                    donjon->mob[i].path.loop = saybool(buffer[0]);
                }
            }
            SetMob(i, donjon);
        }
        fclose(fichier);
    }
    else
    {
        printf("no project founded\n");
    }
}


