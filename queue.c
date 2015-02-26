#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "jeux.h"
#include "main.h"

typedef struct Element Element;
typedef struct File File;
typedef struct PACKmonstre PACKmonstre;

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

void Free_Queue_Element(File *file)
{
	if (file->premier != NULL)
    {
		Element *elementDefile = file->premier;
		
		file->premier = file->premier->suivant;
        free(elementDefile);
    }	
}

int Read_Creature_Queue(File *file)
{
    if (file == NULL)
    {
        return -1;
    }

    int nombreDefile = -1;

    /* On vérifie s'il y a quelque chose à défiler */
    if (file->premier != NULL)
    {

        nombreDefile = file->premier->nombre;
    }
    else
    {
		return -1;
	}

    return nombreDefile;
}

void initqueue(File *file, int ID)
{
	int ret = 0;
	
	while(ret != -1)
	{
		ret = Read_Creature_Queue(file);
		Free_Queue_Element(file);
	}
	
	switch(ID)
	{
		case 0:
			Add_Creature_Queue(file, RAT_BLANC , 15);
			Add_Creature_Queue(file, RAT_VERT , 5);
			Add_Creature_Queue(file, RAT_JAUNE , 1);
			break;
		case 1:
			Add_Creature_Queue(file, RAT_BLANC , 5);
			Add_Creature_Queue(file, RAT_VERT , 15);
			Add_Creature_Queue(file, RAT_JAUNE , 7);
			Add_Creature_Queue(file, RAT_ORANGE , 2);
			break;
		case 2:
			Add_Creature_Queue(file, RAT_VERT , 5);
			Add_Creature_Queue(file, RAT_JAUNE , 17);
			Add_Creature_Queue(file, RAT_ORANGE , 9);
			Add_Creature_Queue(file, RAT_ROUGE , 1);
			break;
	}
	
}
