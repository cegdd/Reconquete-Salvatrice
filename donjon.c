#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "sauvegarde.h"
#include "struct.h"
#include "image.h"

extern int screenh, screenw;

void LoadDonjon(struct DONJON *donjon)
{
    FILE *fichier;
    char buffer[4096] = {'\0'};
    char ret[256] = {'\0'};
    char temp[128] = {'0'};
    int x=0, y=0, w=0, h=0;

    fichier = fopen(donjon->path, "r");
    if (fichier == NULL)
    {
        printf("donjon file : %s not founded\n", donjon->path);
    }

    lis(fichier, buffer);// lecture du nom de la map
    uncrypt(buffer, ret);

    sprintf(temp, "rs/maps/%s.png", ret);
    donjon->map.pict.texture = loadTexture(temp);

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
    setPos4(&donjon->map.pict.pos, 0, 0 ,w, h);
    setPos2(&donjon->origin, screenw/2, screenh/2);

    sprintf(temp, "rs/maps/%snb.png", ret);
    donjon->map.calque = IMG_Load(temp);

    if (!glIsTexture(donjon->map.pict.texture))
    {
        printf("donjon map : %s not founded\n", temp);
    }

    lis(fichier, buffer);// lecture du booleen pour l'existence du joueur
    uncrypt(buffer, ret);
    if (atoi(ret) == 1)
    {
        lis(fichier, buffer);//lecture du joueur en x
        uncrypt(buffer, ret);
        x = atoi(ret);
        lis(fichier, buffer);//lecture du joueur en y
        uncrypt(buffer, ret);
        y = atoi(ret);
        printf("%d %d\n", x, y);
        setPos2(&donjon->map.translation, -x*2, -y*2);
    }

    fclose(fichier);
}
