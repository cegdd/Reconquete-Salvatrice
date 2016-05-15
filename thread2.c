#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <string.h>
#include <pthread.h>

#include "image.h"
#include "thread2.h"
#include "main.h"
#include <SDL_ttf.h>

void* thread2(void  *data)
{
	struct typeFORthreads *online = data;

    char requeterecu[BUFFER] = {'\0'};
    char arg1[20] = {'\0'};
    char arg2[20] = {'\0'};
    char id[4] = {'\0'};
    char chattemp[10][512];
    int index = 0, indexID = 0, index1 = 0, index2 = 0, intid = 0, len = 0, choix = 0;

    while (1)
    {
		recv(online->sock, requeterecu, BUFFER, 0);

		index2 = 0;
        index1 = 0;
        index = 0;
        indexID = 0;

		while (requeterecu[index] != '#' && index < BUFFER)
        {
            id[indexID] = requeterecu[index];
            index++;
            indexID++;
        }
        id[indexID] = '\0';
        index++;

        while (requeterecu[index] != '#' && index < BUFFER)
        {
            arg1[index1] = requeterecu[index];
            index++;
            index1++;
        }
        arg1[index1] = '\0';
        index++;
        while (requeterecu[index] != '#' && index < BUFFER)
        {
            arg2[index2] = requeterecu[index];
            index++;
            index2++;
        }
        arg2[index2] = '\0';

        if (id[0] == 'p')/*========================================================>    p*/
        {
            online->joueurs[intid].enligne = true;
            id[0] = '0';
            intid = atoi(id);
            online->joueurs[intid].position.x = atoi(arg1);
            online->joueurs[intid].position.y = atoi(arg2);

        }
        else if (id[0] == 'n')/*========================================================>    n*/
        {
            id[0] = '0';
            intid = atoi(id);
            sprintf(online->joueurs[intid].pseudo, "%s", arg1);
           // online->joueurs[index].tpseudo = imprime(online->joueurs[intid].pseudo, online->screenw, BLANC,
			//	online->systeme, NULL, NULL);
            online->joueurs[intid].enligne = true;
        }
        else if (id[0] == 'w')/*========================================================>    w*/
        {
            id[0] = '0';
            intid = atoi(id);
            online->joueurs[intid].enligne = false;
        }
        else if (id[0] == 'c')/*========================================================>    c*/
        {
            id[0] = '0';
            intid = atoi(id);
            len = atoi(arg1);
            choix = choixstringchat(online->chat.poschat);
            memset(online->chat.schat[choix], '\0', 512);
            memset(chattemp[choix], '\0', 512);
            recv(online->sock, chattemp[choix], len, 0);
            sprintf(online->chat.schat[choix], "%s : %s", online->joueurs[intid].pseudo, chattemp[choix]);
        }
        else if (id[0] == 'q')/*========================================================>    q*/
        {
            id[0] = '0';
            intid = atoi(id);
            memset(online->joueurs[intid].pseudo, '\0', 20);
            online->joueurs[intid].enligne = false;
        }


        for (index = 0 ; index < BUFFER ; index++)
        {
            requeterecu[index] = '\0';
        }
        for (index = 0 ; index < 4 ; index++)
        {
            id[index] = '\0';
        }
    }
}

int choixstringchat(int *poschat)
{
    int i;
    for (i = 0; i < 10 ; i++)
    {
        poschat[i] = poschat[i] - 1;
    }
    for (i = 0; i < 10 ; i++)
    {
        if (poschat[i] == -1) {poschat[i] = 9; return i;}
    }
    return 0;
}

