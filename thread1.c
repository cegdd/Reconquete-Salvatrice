#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <string.h>
#include <pthread.h>
#include <SDL_ttf.h>

#include "thread2.h"
#include "main.h"


void* thread1(void  *data)
{
    struct typeFORthreads *online = data;

    int oldpx = 0, oldpy = 0;
    int resultatconnect = -1;
    char position[15] = {'\0'};

    SOCKADDR_IN info;
    pthread_t lethread2;

    #if WINDOWS == 1
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);
    #endif

    info.sin_addr.s_addr = inet_addr(IPSERVEUR);
    info.sin_family = AF_INET;
    info.sin_port = htons(32);

	online->sock = socket(AF_INET, SOCK_STREAM, 0);
	while (resultatconnect < 0)
	{
		resultatconnect = connect(online->sock, (SOCKADDR*)&info, sizeof(info));
		if (resultatconnect == -1)
        {
            perror("erreur-->connect");
        }
		SDL_Delay(5000);
	}
	while (online->jeuxACTIF != 1)
	{
		SDL_Delay(100);
	}
	online->isonline = true;

    pthread_create(&lethread2, NULL, *thread2, online);
    send(online->sock, online->systeme->sauvegarde[0], 20, 0);

    while (1)
    {
		if (resultatconnect >= 0)
		{
			online->isonline = true;
			while (oldpx == online->posjoueurx && oldpy == online->posjoueury)
			{
			    if (online->systeme->inbattle == true)
                {
                    position[0] = 'w';
                    send(online->sock, position, 15, 0);
                    memset(position, '\0', 15);
                    online->systeme->inbattle = false;
                }
				if (online->chat.lancermessage == 1 && online->chat.lenbuffer > 0)
                {
                    #if WINDOWS == 1
                    sprintf(position, "c%d", strlen(online->chat.bufferchat));
                    #else
                    sprintf(position, "c%zu", strlen(online->chat.bufferchat));
                    #endif
                    send(online->sock, position, 15, 0);
                    send(online->sock, online->chat.bufferchat, strlen(online->chat.bufferchat), 0);
                    online->chat.lancermessage = 0;
                    memset(online->chat.bufferchat, '\0', 512);
                    memset(position, '\0', 15);
                    online->chat.lenbuffer = 0;
                }
                else if (online->chat.lancermessage == true) {online->chat.lancermessage = false;}

			}
			sprintf(position, "p00#%d#%d#", online->posjoueurx, online->posjoueury);
			oldpx = online->posjoueurx;
			oldpy = online->posjoueury;
			if (send(online->sock, position, 15, 0) <= 0)
			{
				resultatconnect = -1;
			}
		}
		else
		{
			online->isonline = true;
			online->sock = socket(AF_INET, SOCK_STREAM, 0);
			resultatconnect = connect(online->sock, (SOCKADDR*)&info, sizeof(info));
			SDL_Delay(100);
		}
    }
    return 0;
}


