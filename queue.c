#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct Element Element;
typedef struct File File;

void Add_Creature_Queue(File *file, int nvNombre, int quantity)
{
	int index;
	
	for(index = 0 ; index < quantity ; index++)
	{
		Element *nouveau = malloc(sizeof(*nouveau));
		if (file == NULL || nouveau == NULL)
		{
			exit(EXIT_FAILURE);
		}

		nouveau->nombre = nvNombre;
		nouveau->suivant = NULL;

		if (file->premier != NULL) /* La file n'est pas vide */
		{
			/* On se positionne à la fin de la file */
			Element *elementActuel = file->premier;
			while (elementActuel->suivant != NULL)
			{
				elementActuel = elementActuel->suivant;
			}
			elementActuel->suivant = nouveau;
		}
		else /* La file est vide, notre élément est le premier */
		{
			file->premier = nouveau;
		}
	}
}


int Read_Creature_Queue(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDefile = -1;

    /* On vérifie s'il y a quelque chose à défiler */
    if (file->premier != NULL)
    {
        Element *elementDefile = file->premier;

        nombreDefile = elementDefile->nombre;
        file->premier = elementDefile->suivant;
        free(elementDefile);
    }

    return nombreDefile;
}
