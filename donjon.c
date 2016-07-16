#include <stdio.h>
#include <stdlib.h>
#include "struct.h"


void LoadDonjon(struct DONJON *donjon)
{
    FILE *fichier;

    fichier = fopen(donjon->path, "r");

    fclose(fichier);
}
