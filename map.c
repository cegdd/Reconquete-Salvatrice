#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <math.h>

#include "evenement.h"
#include "image.h"
#include "jeux.h"
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

extern int screenh, screenw;

int map (struct DIVERSsysteme *systeme,struct typeFORthreads *online,struct PACKbouton *bouton ,struct PACKobjet *objet,
        struct PACKmonstre *monstre,struct PERSO *perso,struct DIVERSinventaire *inventaire,struct DIVERSdeplacement *deplacement,
		struct DIVERStemps *temps,struct DIVERSui *ui,struct DIVERSchat *chat,struct DIVERScraft *craft,struct DIVERSmap *carte,
		struct PACKpnj *pnj,struct PACKrecompense *recompense,struct typeFORevent *FORevent)
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

			/*sichronisation des données*/
			sinchronisation(pnj, carte, monstre, craft, systeme, online, perso);
            /*animation monstre*/
            ANIMmonstre(monstre, temps);
            /*calcul direction joueur client*/
            deplacement->direction.direction = directionperso(&deplacement->direction);
            /*deplacement*/
            deplacementperso_map(carte, perso, &deplacement->direction, &carte->origin);
            /*recupération coordonées souris*/
            SDL_GetMouseState(&systeme->pointeur.pos.x, &systeme->pointeur.pos.y);
            systeme->pointeur.pos.y = (systeme->pointeur.pos.y - screenh + systeme->pointeur.pos.h) * -1;
            /*gestion de l'ui*/
            gestionui(systeme, ui, craft, bouton, chat, inventaire, objet, perso, pnj);
            /*detection des combats*/
            detectioncombat(monstre, inventaire, ui, deplacement, objet, perso, systeme, recompense, false);
            /*gestion des evenement*/
            boucleevent(&online->chat.lancermessage, FORevent);
            /*gestion du chat*/
            gestionchat(chat, systeme, online);

/*##################################################################################################################################################################################
											##################### AFFICHAGE #####################																	#
##################################################################################################################################################################################*/

            /*effacage de l'écran*/
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

            /*affichage de la carte*/
            afficherMAP(carte, systeme, craft);
            //SDL_RenderCopy(systeme->renderer, craft->tetabli, NULL, &craft->petabli);
            /*affichage des pnj*/
            afficherPNJ(perso, pnj, systeme);
            /*affichage des mobs*/
            afficherMOB(monstre, systeme, temps);
            /*affichage des joueurs*/
            afficherJOUEURS(perso, deplacement, systeme, online, temps);
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

            /*rendu éran*/
            glFlush();
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

            for (index = 0 ; index < 3 ; index++)/* popping time*/
			{
				if (monstre->rat[index].etat != ALIVE)/* != 0*/
				{
					monstre->rat[index].etat++;
				}
			}

			/*if it's the first second of this player*/
            if (temps->temptotal == 5)
            {
                char texte[2548] = "\nprisonnier :  \n   salut ... \n ça tombe bien,\n j'avais besoin d'un coup de main !\n tiens ! prend ce lance pierre et vas nous chercher\nquelques rat !\n\n\n\n\n\n\n\n\n\n\n\n\n\n   APPUIE SUR ENTRÉE POUR CONTINUER";
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
                sauvegardetout(systeme->sauvegarde, carte->cellule.pict.pos, perso, temps->temptotal, 0, objet->sac1, TAILLESAC, ui);
                temps->tpspoursave = temps->temptotal;
            }

            printf("%d frame/sec\n", temps->i);
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

    sauvegardetout(systeme->sauvegarde, carte->cellule.pict.pos, perso, temps->temptotal, 0, objet->sac1, TAILLESAC, ui);

    return 1;
}



void detectioncombat(struct PACKmonstre *monstre,struct DIVERSinventaire *inventaire,struct DIVERSui *ui,
                     struct DIVERSdeplacement *deplacement,struct PACKobjet *objet,struct PERSO *perso,struct DIVERSsysteme *systeme,
                     struct PACKrecompense *recompense, bool arcademode)
{
	int index;

	for(index = 0 ; index < 3 ; index++)
    {
        if(colisionbox(&perso->perso.pict.pos, &monstre->rat[index].m_pict.pict.pos, false) == true &&
           monstre->rat[index].etat == ALIVE)
        {
			monstre->rat[index].Engaged = true;
			monstre->rat[index].etat = lancementcombat(monstre, inventaire, ui, deplacement, objet, perso, systeme, recompense, arcademode);
			initqueue(&monstre->rat[index].queue, monstre->rat[index].ID);
			monstre->rat[index].Engaged = false;
		}
	}
}

int lancementcombat(struct PACKmonstre *monstre,struct DIVERSinventaire *inventaire,struct DIVERSui *ui,
                    struct DIVERSdeplacement *deplacement,struct PACKobjet *objet,struct PERSO *perso,struct DIVERSsysteme *systeme,
                    struct PACKrecompense *recompense, bool arcademode)
{
    int indexloot = 0, index2, RETcombat;
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


		/*initialisation des tableaux de récompense*/
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

	/*############lancement du combat############*/
	RETcombat = combat(perso->life, monstre, systeme, perso, recompense, objet, ui, arcademode);

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
			ui->dialogue_text.texture = fenetredialogue(screenw*0.4, screenh*0.8, &ui->dialogue_back.pos, &ui->dialogue_text.pos, "Vous avez fui,\ntous les objets obtenu pendant le combat on été abandonné sur place.\n\n\n\n(entrée/échap pour continuer)\n",
									  BLANC, systeme);
			ui->dialogueactif = 1;
			return DEAD; /*the creature*/
		}
		/*si joueur vivant*/
		else if (RETcombat == BTL_WON)
		{
			/*dialogue de récompense*/
			ui->dialogueactif = 2;

			/*si des récompenses on été obtenue*/
			while (recompense->recompenseNB[indexloot] > 0)
			{
				/*ecriture de la récompense*/
				sprintf(slootcombat, "-> %d %s", recompense->recompenseNB[indexloot], objet->objet[recompense->recompenseID[indexloot]].nom);
				SDL_DestroyTexture(recompense->ttextelootcombat[indexloot]);
			//	recompense->ttextelootcombat[indexloot] = imprime(slootcombat, screenw, BLANC, systeme, NULL, NULL);

				for (index2 = 0 ; index2 < recompense->recompenseNB[indexloot] ; index2++)
				{
					/*insertion des récompenses 1 par 1*/
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

void ANIMmonstre(struct PACKmonstre *monstre,struct DIVERStemps *temps)
{
	int index;

	for(index = 0 ; index < 3 ; index++)
	{
		if (temps->tpact - monstre->rat[index].tempsanim >= 128)
		{
			monstre->rat[index].tempsanim = temps->tpact;
			monstre->rat[index].indexanim++;

			if(monstre->rat[index].indexanim >= 2)
			{
				monstre->rat[index].indexanim = 0;
			}
		}
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

void sinchronisation(struct PACKpnj *pnj,struct DIVERSmap *carte,struct PACKmonstre *monstre,struct DIVERScraft *craft,
                     struct DIVERSsysteme *systeme,struct typeFORthreads *online,struct PERSO *perso)
{
	int index;

	carte->cellule.pict.pos.x = carte->origin.x + carte->cellule.translation.x;
	carte->cellule.pict.pos.y = carte->origin.y + carte->cellule.translation.y;

	pnj->toumai.pos.x =                 carte->cellule.pict.pos.x + 580;
	pnj->toumai.pos.y =                 carte->cellule.pict.pos.y + 1020;
	monstre->rat[0].m_pict.pict.pos.x =    carte->cellule.pict.pos.x + 1700;
	monstre->rat[0].m_pict.pict.pos.y =    carte->cellule.pict.pos.y + 500;
	monstre->rat[1].m_pict.pict.pos.x =    carte->cellule.pict.pos.x + 2000;
	monstre->rat[1].m_pict.pict.pos.y =    carte->cellule.pict.pos.y + 600;
	monstre->rat[2].m_pict.pict.pos.x =    carte->cellule.pict.pos.x + 2000;
	monstre->rat[2].m_pict.pict.pos.y =    carte->cellule.pict.pos.y + 200;
	craft->petabli.x =              carte->cellule.pict.pos.x + 830;
	craft->petabli.y =              carte->cellule.pict.pos.y + 830;

	systeme->oldpp.x = systeme->pointeur.pos.x;
	systeme->oldpp.y = systeme->pointeur.pos.y;

	for (index = 0 ; index < 3 ; index++)
	{
		if (monstre->rat[index].etat >= TEMPSREPOPBATMOUTHS)
		{
			monstre->rat[index].etat = ALIVE;
		}
	}
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
