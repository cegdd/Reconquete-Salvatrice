#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <math.h>

#include "evenement.h"
#include "image.h"
#include "ui.h"
#include "sauvegarde.h"
#include "map.h"
#include "main.h"
#include "colision.h"
#include "deplacement.h"
#include "tableau.h"
#include "systeme.h"
#include "listechaine.h"
#include "queue.h"
#include "donjon.h"
#include "tir.h"
#include "tool.h"

extern int screenh, screenw;

int map (struct DIVERSsysteme *systeme,struct typeFORthreads *online,struct PACKbouton *bouton ,struct PACKobjet *objet,
        struct PERSO *perso,struct DIVERSinventaire *inventaire,struct DIVERSdeplacement *deplacement,
		struct DIVERStemps *temps,struct DIVERSui *ui,struct DIVERSchat *chat,struct DIVERScraft *craft,
		struct PACKrecompense *recompense,struct typeFORevent *FORevent,struct TIR *TIR)
{
    int index;
    chargement(systeme);
    #if CHEAT == 1

    for (index = 0 ; index < TAILLESAC ; index++)
    {
        videemplacement(&FORevent->objet->sac1[index]);
    }
    for (index = 0 ; index < 10 ; index++)
    {
		insertionsac(objet, 0);
		insertionsac(objet, 2);
		insertionsac(objet, 7);
	}
	insertionsac(objet, 3);
	insertionsac(objet, 1);
	insertionsac(objet, 4);
	insertionsac(objet, 5);
	insertionsac(objet, 6);
	insertionsac(objet, 8);
	insertionsac(objet, 9);

    #endif

    struct DONJON dj0;
    initdonjon(&dj0, systeme);
    LoadDonjon(&dj0, "dj0");
                systeme->djisloaded = true;

    online->jeuxACTIF = 1;

    for(index = 0 ; index < MAX_JOUEURS ; index++)
    {
        online->joueurs[index].ppseudo.x = 20000;
        online->joueurs[index].ppseudo.y = 20000;
        online->joueurs[index].position.w = 0;
        online->joueurs[index].position.h = 0;
    }
    checkandrefreshstuff(perso, objet, systeme, ui);
    checkinventaire(objet, inventaire);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(0,screenw,0,screenh);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

/*#############################################################################################################################################################
											##################### Boucle De Jeu #####################																					#
######################################################################################################################################################################*/
systeme->continuer = 1;
    while (systeme->continuer == 1)
    {
        temps->tpact = SDL_GetTicks();

        if (temps->tpact - temps->tpapr >= 15) /*15   ms*/
        {
            temps->tpapr = temps->tpact;
            temps->i++;

			/*sichronisation des donn�es*/
			sinchronisation(craft, systeme, online, perso, &dj0);
            /*calcul direction joueur client*/
            deplacement->direction.direction = directionperso(&deplacement->direction);
            /*deplacement*/
            checkPixel(&dj0.map, perso);
            move_map(perso, &deplacement->direction, &dj0.origin);
            /*recup�ration coordon�es souris*/
            SDL_GetMouseState(&systeme->pointeur.pos.x, &systeme->pointeur.pos.y);
            systeme->pointeur.pos.y = (systeme->pointeur.pos.y - screenh + systeme->pointeur.pos.h) * -1;
            /*gestion de l'ui*/
            gestionui(systeme, ui, craft, bouton, chat, inventaire, objet, perso);
            /*detection des combats*/
           // detectioncombat(monstre, inventaire, ui, deplacement, objet, perso, systeme, recompense, false);
            /*gestion des evenement*/
            boucleevent(&online->chat.lancermessage, FORevent, TIR);
            /*gestion du chat*/
            gestionchat(chat, systeme, online);

            if (TIR->letirdemander == true)
            {
                gestiontir(TIR, systeme, perso, &dj0);
            }
            COMBATgestionprojectile (TIR, &dj0);


/*##################################################################################################################################################################################
											##################### AFFICHAGE #####################																	#
##################################################################################################################################################################################*/

            /*effacage de l'�cran*/
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

            /*affichage de la carte*/
            draw_pict(&dj0.map.pict);
            for (index=0 ; index<dj0.nombremonstre ; index++)
            {
                if(dj0.mob[index].BarreDeVie->life > 0)
                {
                    draw_hookpict(&dj0.mob[index].hookpict, &dj0.map.pict.pos);

                    CalculerBarreDeVie(dj0.mob[index].BarreDeVie->baselife , dj0.mob[index].BarreDeVie->life, 68);
                    setPos2rect(&dj0.mob[index].BarreDeVie->pBG, dj0.mob[index].hookpict.pict.pos.x-1 + ((dj0.mob[index].hookpict.pict.pos.w-68)/2),
                                dj0.mob[index].hookpict.pict.pos.y + dj0.mob[index].hookpict.pict.pos.h+4);
                    setPos4(&dj0.mob[index].BarreDeVie->pbarre, dj0.mob[index].hookpict.pict.pos.x + ((dj0.mob[index].hookpict.pict.pos.w-68)/2),
                                dj0.mob[index].hookpict.pict.pos.y + dj0.mob[index].hookpict.pict.pos.h+5,
                                CalculerBarreDeVie(dj0.mob[index].BarreDeVie->baselife , dj0.mob[index].BarreDeVie->life, 68), 5);

                    draw(systeme->BGnoir, &dj0.mob[index].BarreDeVie->pBG);
                    draw(systeme->BGblanc, &dj0.mob[index].BarreDeVie->pbarre);
                }
            }
            /*affichage des joueurs*/
            afficherJOUEURS(perso, deplacement, systeme, online, temps);

            BattleDraw_Projectile(TIR, &dj0);
            /*affichage du chat*/
            if (ui->chat_open == true)
            {
                afficherCHAT(chat, ui, online->chat.lenbuffer, systeme);
            }
            /*affichage de l'inventaire*/
            else if (ui->inventaire_open == true)
            {
                afficherINVENTAIRE(inventaire, ui, objet, systeme);
            }
            /*affichage de l'interface utilisateur*/
            afficherUI(online->isonline, ui, bouton, temps, perso, inventaire, systeme, recompense, objet);
            /*affichage de l'interface de crafting*/
            if (ui->craft_open == true)
            {
                afficherCRAFT(craft, ui, bouton, objet, inventaire, systeme);
            }
            /*affichage du pointeur*/
            afficherPOINTEUR(systeme, objet);

            /*rendu �ran*/
            glFlush();
            glFinish();
            SDL_GL_SwapWindow(systeme->screen);
        }
        else
        {
			SDL_Delay(5);
		}

/*###########################################################################################################################
								##################### Frame Par Secondes #####################								#
###########################################################################################################################*/

        if (temps->tpact - temps->tpap >= 1000)
        {
            temps->temptotal++;

			/*if it's the first second of this player*/
            if (temps->temptotal == 5)
            {
                char texte[2548] = "\nprisonnier :  \n   salut ... \n �a tombe bien,\n j'avais besoin d'un coup de main !\n tiens ! prend ce lance pierre et vas nous chercher\nquelques rat !\n\n\n\n\n\n\n\n\n\n\n\n\n\n   APPUIE SUR ENTR�E POUR CONTINUER";
                ui->dialogue_text.texture = fenetredialogue(screenw*0.4, screenh*0.8, &ui->dialogue_back.pos, &ui->dialogue_text.pos, texte, BLANC, systeme);
                ui->dialogueactif = 1;
                insertionsac(objet, 3);
            }

            if (temps->temptotal - temps->oldipourregen >= 3)
            {
                if (perso->life < perso->lifemax)
                {
                    perso->life += REGEN;
                    perso->life += perso->regenlife;
                    if (perso->life > perso->lifemax)
					{
						perso->life = perso->lifemax;
					}
                    temps->oldipourregen = temps->temptotal;
                }

            }
            else
			{
				if (perso->life < perso->lifemax)
                {
                    perso->life += perso->regenlife;
                    if (perso->life > perso->lifemax)
					{
						perso->life = perso->lifemax;
					}
                }
			}
            if (temps->temptotal - temps->tpspoursave >= 30)
            {
                sauvegardetout(systeme->sauvegarde, dj0.map.pict.pos, perso, temps->temptotal, 0, objet->sac1, TAILLESAC, ui);
                temps->tpspoursave = temps->temptotal;
            }

            sprintf(temps->StringI, "IPS => %d", temps->i);
            sprintf(perso->slife, "vie : %0.0f/%d", perso->life, perso->lifemax);
            sprintf(temps->stringtempstotal, "age du personnage : %dj %dh %dmin %dsec", calcultempsjours(temps->temptotal), calcultempsheures(temps->temptotal), calcultempsminutes(temps->temptotal), calcultempssecondes(temps->temptotal));

            temps->fps.texture = imprime (temps->StringI, screenw, BLANC, systeme, NULL, NULL);
            perso->tlife.texture = imprime (perso->slife, screenw, BLANC, systeme, NULL, NULL);
            temps->temps.texture = imprime (temps->stringtempstotal, screenw, BLANC, systeme, NULL, NULL);

            for(index = 0; index < 10 ; index++)
            {
                if(online->chat.schat[index][0] != '\0')
                {
                    chat->pstringchat[index].y = (screenh*0.5)+(online->chat.poschat[index]*(screenh*0.047));
                    SDL_DestroyTexture(chat->tstringchat[index]);
                  //  chat->tstringchat[index] = imprime(online->chat.schat[index], screenw, BLANC, systeme, NULL, NULL);
                }
            }

            temps->i = 0;
            temps->tpap = temps->tpact;
        }
    }

/*###########################################################################################################################
																															#
								##################### Fin de Fonction #####################									#
																														#
###########################################################################################################################*/

    sauvegardetout(systeme->sauvegarde, dj0.map.pict.pos, perso, temps->temptotal, 0, objet->sac1, TAILLESAC, ui);

    return 1;
}


int lancementcombat(struct DIVERSinventaire *inventaire,struct DIVERSui *ui,
                    struct DIVERSdeplacement *deplacement,struct PACKobjet *objet,struct PERSO *perso,struct DIVERSsysteme *systeme,
                    struct PACKrecompense *recompense, bool arcademode)
{
    int indexloot = 0, index2 = 0, RETcombat = 0;
    char slootcombat[120];

	/*ecran de chargement*/
	chargement(systeme);

	if (arcademode == false)
	{
		/*cloture des UIs et arret du personnage*/
		ui->inventaire_open = false;
		ui->chat_open = false;
		systeme->inbattle = true;
		ui->dialogueactif = 0;
		deplacement->persobouge = 0;


		/*initialisation des tableaux de r�compense*/
		for (index2 = 0 ; index2 < LOOTMAX ; index2++)
		{
			recompense->recompenseNB[index2] = 0;
		}
		for (index2 = 0 ; index2 < NOMBREOBJETS ; index2++)
		{
			recompense->recompenseID[index2] = -1;
		}
	}
	else if (arcademode == true)
	{
		ui->casestuff[ARME].IDobjet = 3;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	if (arcademode == false)
	{
		deplacement->direction.bas = 0;
		deplacement->direction.haut = 0;
		deplacement->direction.gauche = 0;
		deplacement->direction.droite = 0;
		checkinventaire(objet, inventaire);


		/*if player dead*/
		if (RETcombat == BTL_LOST)
		{
			/*ecran de mort*/
			ANIMmort(systeme);
			perso->life = perso->lifemax;

			return ALIVE; /*the creature*/
		}
		/*si le joueur a fui*/
		else if (RETcombat == BTL_LEAVED)
		{
			ui->dialogue_text.texture = fenetredialogue(screenw*0.4, screenh*0.8, &ui->dialogue_back.pos, &ui->dialogue_text.pos, "Vous avez fui,\ntous les objets obtenu pendant le combat on �t� abandonn� sur place.\n\n\n\n(entr�e/�chap pour continuer)\n",
									  BLANC, systeme);
			ui->dialogueactif = 1;
			return DEAD; /*the creature*/
		}
		/*si joueur vivant*/
		else if (RETcombat == BTL_WON)
		{
			/*dialogue de r�compense*/
			ui->dialogueactif = 2;

			/*si des r�compenses on �t� obtenue*/
			while (recompense->recompenseNB[indexloot] > 0)
			{
				/*ecriture de la r�compense*/
				sprintf(slootcombat, "-> %d %s", recompense->recompenseNB[indexloot], objet->objet[recompense->recompenseID[indexloot]].nom);
				SDL_DestroyTexture(recompense->ttextelootcombat[indexloot]);
			//	recompense->ttextelootcombat[indexloot] = imprime(slootcombat, screenw, BLANC, systeme, NULL, NULL);

				for (index2 = 0 ; index2 < recompense->recompenseNB[indexloot] ; index2++)
				{
					/*insertion des r�compenses 1 par 1*/
					insertionsac(objet, recompense->recompenseID[indexloot]);
				}
				indexloot++;
			}
		}
		perso->perso.pict.pos.x = screenw/2-perso->perso.pict.pos.w;
        perso->perso.pict.pos.y = screenh/2-perso->perso.pict.pos.h;
	}
	if (RETcombat == BTL_RESTART)
	{
		return 2;
	}
	else
	{
		return DEAD; /*the creature*/
	}
}

void gestionchat(struct DIVERSchat *chat,struct DIVERSsysteme *systeme,struct typeFORthreads *online)
{
    if (chat->lettre != '\0' && online->chat.lenbuffer <128)
    {
        if (chat->lettre == '*'&& online->chat.lenbuffer > 0)
        {
            online->chat.lenbuffer--;
            online->chat.bufferchat[online->chat.lenbuffer] = '\0';
        }
        else if (chat->lettre != '*')
        {
            online->chat.bufferchat[online->chat.lenbuffer] = chat->lettre;
            online->chat.lenbuffer++;

        }
        chat->lettre = '\0';
        SDL_DestroyTexture(chat->tbufferchat);
    //    chat->tbufferchat = imprime(online->chat.bufferchat, screenw, BLANC, systeme, NULL, NULL);
    }
}

void sinchronisation(struct DIVERScraft *craft,struct DIVERSsysteme *systeme,struct typeFORthreads *online,
                     struct PERSO *perso,struct DONJON *donjon)
{

    donjon->map.pict.pos.x = donjon->origin.x + donjon->map.translation.x;
    donjon->map.pict.pos.y = donjon->origin.y + donjon->map.translation.y;

	systeme->oldpp.x = systeme->pointeur.pos.x;
	systeme->oldpp.y = systeme->pointeur.pos.y;
}


int calcultempssecondes(int temptotal)
{
    return ((temptotal % 86400) % 3600) % 60;
}

int calcultempsminutes(int temptotal)
{
    return ((temptotal % 86400) % 3600) / 60;
}

int calcultempsheures(int temptotal)
{
    return (temptotal % 86400) / 3600;
}

int calcultempsjours(int temptotal)
{
    return temptotal/86400;
}
