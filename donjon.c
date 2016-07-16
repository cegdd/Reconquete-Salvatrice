#include <stdio.h>
#include <stdlib.h>

#include "sauvegarde.h"
#include "struct.h"


void LoadDonjon(struct DONJON *donjon)
{
    FILE *fichier;
    char buffer[4096] = {'\0'};
    char ret[256] = {'\0'};

    fichier = fopen(donjon->path, "r");
    if (fichier == NULL)
    {
        printf("donjon file : %s not founded\n", donjon->path);
    }

    lis(fichier, buffer);

    uncrypt(buffer, ret);
    printf("%s\n", ret);

    fclose(fichier);
}
