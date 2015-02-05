#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include  <pthread.h>

#include "main.h"
#include "thread1.h"
#include "map.h"
#include "login.h"
#include "sauvegarde.h"
#include "jeux.h"
#include "tableau.h"
#include "queue.h"

int main (int argc, char *argv[])
{	
	if (argc == *argv[0]){}//juste pour les warnings
	srand(2);

    SDL_Init (SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    TTF_Init();
    atexit(TTF_Quit);
    IMG_Init(IMG_INIT_PNG);
    atexit(IMG_Quit);
	Mix_Init(MIX_INIT_MP3);
    atexit(Mix_Quit);

    struct DIVERSsysteme systeme;
    struct typeFORthreads online;
    initonline(&online, &systeme);
    pthread_t lethread1;
    int ret = 0;

    SDL_ShowCursor(SDL_DISABLE);
    systeme.screen = SDL_CreateWindow("Reconquete salvatrice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    systeme.renderer = SDL_CreateRenderer(systeme.screen, -1, SDL_RENDERER_ACCELERATED);
    SDL_MaximizeWindow(systeme.screen);
	SDL_GetWindowSize(systeme.screen , &systeme.screenw , &systeme.screenh);

	initsystem(&systeme);
	initsauvegarde(systeme.sauvegarde, NBargSAVE, C);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 1024);
	Mix_AllocateChannels(0);
	Mix_VolumeMusic(64);


	#if FASTLOG == 1//juste pour moi, pour éviter le log
	sprintf(systeme.sauvegarde[0], "cegdd");
	sprintf(systeme.sauvegarde[1], "mdpbidon");
	pthread_create(&lethread1, NULL, *thread1, &online);
	chargersauvegarde(&systeme);
	if (chargementcarte(&systeme, &online) != 1) {return EXIT_FAILURE;}
	return EXIT_SUCCESS;
	#endif // FASTLOG

	Mix_Music *sound = Mix_LoadMUS("game.mp3");
	if (sound == NULL){ printf("musique non trouvée"); return EXIT_FAILURE;}
	else if (Mix_PlayMusic(sound, -1) < 0){ printf("musique non jouable"); return EXIT_FAILURE;}
	
	//si le login est accepté
	ret = login(&systeme);
	while (ret != 0)
	{
		if (ret == 2)
		{
			//creation thread pour socket
			pthread_create(&lethread1, NULL, *thread1, &online);
			chargersauvegarde(&systeme);

			Mix_PauseMusic ();
			//lancement du jeu
			if (chargementcarte(&systeme, &online) != 1) {return EXIT_FAILURE;}
		}
		else if (ret == 5)
		{
			Mix_PauseMusic ();
			chargementarcade(&systeme);
			if (Mix_PlayMusic(sound, -1) < 0){ printf("musique non jouable"); return EXIT_FAILURE;}
		}
		else
		{
			printf("login return : %d", ret);
		}
		ret = login(&systeme);
	}

	Mix_FreeMusic(sound);
	TTF_CloseFont(systeme.police1);
	TTF_CloseFont(systeme.police);
    return EXIT_SUCCESS;
}

int chargementcarte(struct DIVERSsysteme *systeme, struct typeFORthreads *online)
{
	PACKbouton bouton;
    PACKobjet objet;
    PACKmonstre monstre;
    PERSO perso;
    DIVERSinventaire inventaire;
    DIVERSdeplacement deplacement;
    DIVERStemps temps;
    DIVERSui ui;
    DIVERSchat chat;
    DIVERSmap carte;
    PACKpnj pnj;
    PACKrecompense recompense;
    typeFORevent FORevent;
    DIVERScraft craft;

    if (temps.temptotal != 0)
	{
		srand(temps.temptotal);
	}
	
	initcraft(&craft, systeme);
    initobjet(&objet, systeme, &craft);
    initcraft(&craft, systeme);
    initbouton(&bouton, systeme);
    initmonstre(&monstre, systeme);
    initinventaire(&inventaire, systeme);
    initdeplacement(&deplacement, systeme);
    initperso(&perso, systeme);
    initmap(&carte, systeme, &perso);
    inittemps(&temps, systeme);
    initui(&ui, systeme);
    initchat(&chat, systeme);
    initpnj(&pnj);
    initrecompense(&recompense, systeme);
    initFORevent(&FORevent, &objet, &bouton, &inventaire, systeme, &deplacement, &chat, &ui, &craft, &monstre, &perso, &pnj);
    SDL_RenderCopy(systeme->renderer, craft.tetabli, NULL, &craft.petabli);
    
    map(systeme, online, &bouton, &objet, &monstre, &perso, &inventaire, &deplacement, &temps, &ui, &chat, &craft, &carte, &pnj, &recompense, &FORevent);
	return 1;
}

int chargementarcade (struct DIVERSsysteme *systeme)
{
	PACKmonstre monstre;
	DIVERSinventaire inventaire;
	DIVERSchat chat;
	DIVERSui ui;
	DIVERSdeplacement deplacement;
	DIVERScraft craft;
	PACKobjet objet;
	PERSO perso;
	PACKrecompense recompense;
	
	initmonstre(&monstre, systeme);
	initinventaire(&inventaire, systeme);
	initchat(&chat, systeme);
	initui(&ui, systeme);
	initdeplacement(&deplacement, systeme);
	initcraft(&craft, systeme);
	initobjet(&objet, systeme, &craft);
	initperso(&perso, systeme);
	initrecompense(&recompense, systeme);
	
	lancementcombat(&monstre, &inventaire, &chat, &ui, &deplacement, &objet, &perso, systeme, &recompense, true);
	return 0;
}
