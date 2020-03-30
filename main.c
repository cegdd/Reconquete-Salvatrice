#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <pthread.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "struct.h"
#include "perso.h"
#include "tableau.h"
#include "sauvegarde.h"
#include "main.h"
#include "login.h"
#include "map.h"

int screenh, screenw;

int main( int argc , char ** argv )
{
    int ret = 0;

    struct DIVERSsysteme systeme;
    struct typeFORthreads online;
    Mix_Music *sound = NULL;
    SDL_GLContext contexteOpenGL;

    initonline(&online, &systeme);
    /*pthread_t lethread1;*/

	if (argc == *argv[0]){}/*juste pour les warnings*/
	srand(2); /*define a random*/

    SDL_Init (SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    TTF_Init();
    atexit(TTF_Quit);

    IMG_Init(IMG_INIT_PNG);
    atexit(IMG_Quit);
	Mix_Init(MIX_INIT_MP3);
    atexit(Mix_Quit);

    systeme.screen = SDL_CreateWindow("Reconquete salvatrice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    contexteOpenGL = SDL_GL_CreateContext(systeme.screen);
	SDL_GetWindowSize(systeme.screen , &screenw , &screenh);
	SDL_ShowCursor(SDL_DISABLE);

	SDL_SetRelativeMouseMode(true);

	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	gluOrtho2D(0,screenw,0,screenh);
    glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER,0.5f);
    glEnable(GL_ALPHA_TEST);
	initsystem(&systeme);
	initsauvegarde(systeme.sauvegarde, NBargSAVE, C);


	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 1024);
	Mix_AllocateChannels(0);
	Mix_VolumeMusic(64);


	#if FASTLOG == 1/*juste pour moi, pour �viter le log*/
	sprintf(systeme.sauvegarde[0], "cegdd");
	sprintf(systeme.sauvegarde[1], "mdpbidon");
	/*pthread_create(&lethread1, NULL, *thread1, &online);*/
	chargersauvegarde(&systeme);
	if (chargementcarte(&systeme, &online) != 1) {return EXIT_FAILURE;}
	return EXIT_SUCCESS;
	#endif /* FASTLOG*/

	sound = Mix_LoadMUS("game.mp3");
	if (sound == NULL){ printf("musique non trouv�e"); return EXIT_FAILURE;}
	else if (Mix_PlayMusic(sound, -1) < 0){ printf("musique non jouable"); return EXIT_FAILURE;}

	/*si le login est accept�*/
	ret = login(&systeme);
	while (ret != 0)
	{
		if (ret == 2)
		{
			/*creation thread pour socket*/
			/*pthread_create(&lethread1, NULL, *thread1, &online);*/
			chargersauvegarde(&systeme);


			Mix_PauseMusic ();
			/*lancement du jeu*/
			if (chargementcarte(&systeme, &online) != 1) {return EXIT_FAILURE;}
			return EXIT_SUCCESS;
		}
		else if (ret == 5)
		{
			Mix_PauseMusic ();
			//chargementarcade(&systeme);
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
	SDL_GL_DeleteContext(contexteOpenGL);
    return 0;
}

int chargementcarte(struct DIVERSsysteme *systeme, struct typeFORthreads *online)
{
	struct PACKbouton bouton;
    struct PACKobjet objet;
    struct PERSO perso;
    struct DIVERSinventaire inventaire;
    struct DIVERSdeplacement deplacement;
    struct DIVERStemps temps;
    struct DIVERSui ui;
    struct DIVERSchat chat;
    struct PACKrecompense recompense;
    struct typeFORevent FORevent;
    struct DIVERScraft craft;
    struct TIR TIR;

    inittemps(&temps, systeme);
    if (temps.temptotal != 0)
	{
		srand(temps.temptotal);
	}

    initobjet(&objet, systeme, &craft);
    initcraft(&craft, systeme);
    initbouton(&bouton, systeme);
    initinventaire(&inventaire, systeme);
    initdeplacement(&deplacement, systeme);
    initperso(&perso, systeme);
    initui(&ui, systeme);
    initchat(&chat, systeme);
    initrecompense(&recompense, systeme);
    initFORevent(&FORevent, &objet, &bouton, &inventaire, systeme, &deplacement, &chat, &ui, &craft, &perso);
    initTIR(&TIR);


    map(systeme, online, &bouton, &objet, &perso, &inventaire, &deplacement, &temps, &ui, &chat, &craft, &recompense, &FORevent, &TIR);
	return 1;
}
