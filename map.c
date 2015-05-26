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

int map (DIVERSsysteme *systeme, typeFORthreads *online, PACKbouton *bouton , PACKobjet *objet, PACKmonstre *monstre, PERSO *perso, DIVERSinventaire *inventaire, DIVERSdeplacement *deplacement,
		DIVERStemps *temps, DIVERSui *ui, DIVERSchat *chat, DIVERScraft *craft, DIVERSmap *carte, PACKpnj *pnj, PACKrecompense *recompense, typeFORevent *FORevent)
{
    chargement(systeme);
    #if CHEAT == 1
    int indextmp;
    for (indextmp = 0 ; indextmp < 10 ; indextmp++)
    {
		insertionsac(objet, 0);
		insertionsac(objet, 2);
		insertionsac(objet, 7);
	}

    #endif

    online->jeuxACTIF = 1;

    int index;
    for(index = 0 ; index < MAX_JOUEURS ; index++)
    {
        online->joueurs[index].ppseudo.x = 20000;
        online->joueurs[index].ppseudo.y = 20000;
        online->joueurs[index].position.w = 0;
        online->joueurs[index].position.h = 0;
    }
    checkandrefreshstuff(perso, objet, systeme, ui);
    checkinventaire(objet, inventaire);

/*#############################################################################################################################################################
											##################### Boucle De Jeu #####################																					#
######################################################################################################################################################################*/

    while (systeme->continuer == 1)
    {
        temps->tpact = SDL_GetTicks();

        if (temps->tpact - temps->tpapr >= 15) /*15   ms*/
        {
            temps->tpapr = temps->tpact;
            temps->i++;

			/*sichronisation des données*/
			sinchronisation(pnj, carte, monstre, craft, systeme, online, perso);

            /*animation personnage qui marche*/
            ANIMpersomarche(deplacement, temps);
            ANIMmonstre(monstre, temps);
            /*deplacement de la carte*/
            deplacementmap(&carte->pmap[0], TILESMAP, deplacement->x, deplacement->y);
            /*calcul direction joueur client*/
            deplacement->direction.direction = directionperso(&deplacement->direction);
            /*deplacement*/
            deplacementperso(&carte->calque[0], perso, &deplacement->direction, systeme, &deplacement->x, &deplacement->y, 1);
            /*recupération coordonées souris*/
            SDL_GetMouseState(&systeme->pp.x, &systeme->pp.y);
            /*gestion de l'ui*/
            gestionui(systeme, ui, craft, bouton, chat, inventaire, objet, perso, pnj);
            /*detection des combats*/
            detectioncombat(monstre, inventaire, chat, ui, deplacement, objet, perso, systeme, recompense, false);
            /*gestion des evenement*/
            boucleevent(&online->chat.lancermessage, FORevent);
            /*gestion du chat*/
            gestionchat(chat, systeme, online);

/*##################################################################################################################################################################################
											##################### AFFICHAGE #####################																	#
##################################################################################################################################################################################*/

            /*effacage de l'écran*/
            SDL_RenderClear(systeme->renderer);

            /*affichage de la carte*/
            afficherMAP(carte, systeme, craft);
            SDL_RenderCopy(systeme->renderer, craft->tetabli, NULL, &craft->petabli);
            /*affichage des pnj*/
            afficherPNJ(perso, pnj, systeme);
            /*affichage des mobs*/
            afficherMOB(monstre, systeme);
            /*affichage des joueurs*/
            afficherJOUEURS(perso, deplacement, systeme, online);
            /*affichage du chat*/
            if (chat->chatactif == true)
            {
                afficherCHAT(chat, ui, online->chat.lenbuffer, systeme);
            }
            /*affichage de l'inventaire*/
            else if (inventaire->actif == true)
            {
                afficherINVENTAIRE(inventaire, ui, objet, systeme);
            }
            /*affichage de l'interface utilisateur*/
            afficherUI(online->isonline, ui, bouton, temps, perso, chat, inventaire, systeme, recompense, objet);
            /*affichage de l'interface de crafting*/
            if (craft->actif == true)
            {
                afficherCRAFT(craft, ui, bouton, objet, inventaire, systeme);
            }
            /*affichage du pointeur*/
            afficherPOINTEUR(systeme, objet);

            /*rendu éran*/
            SDL_RenderPresent(systeme->renderer);
        }

/*###########################################################################################################################
								##################### Frame Par Secondes #####################								#
###########################################################################################################################*/

        else if (temps->tpact - temps->tpap >= 1000)
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
            if (temps->temptotal == 1)
            {
                char texte[2548] = "           Toumai :\n\nBonjour à toi jeune ...\njeune quoi exactement?\nJe suis vieux, mes yeux sont fatigués\nmais mon esprit reste vif!\nEt à ta démarche je devine que tu n'es\npas du coin.\nJ'ignore ce que tu viens faire ici mais je dois te prévenir :\n\nles lieux ne sont pas sûrs!\nEt en tant que sage de la tribue, je dois m'assurer que tu puisses survivre au moins quelques jours.\n Tiens ! Prend ceci, c'est le lance pierre de mon fils.\nAvec une bonne pierre entre les 2 yeux je ne donne pas cher de leurs vies! \n\n   APPUIE SUR ENTRÉE POUR CONTINUER";
                ui->ttextedialogue = fenetredialogue(systeme->screenw*0.4, systeme->screenh*0.8, &ui->pdialogue, &ui->ptextedialogue, texte, BLANC, systeme);
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
                sauvegardetout(systeme->sauvegarde, carte->pmap[0], perso, temps->temptotal, 0, objet->sac1, TAILLESAC, ui);
                temps->tpspoursave = temps->temptotal;
            }


            sprintf(temps->StringI, "IPS => %d", temps->i);
            sprintf(perso->slife, "vie : %0.1f/%d", perso->life, perso->lifemax);
            sprintf(temps->stringtempstotal, "age du personnage : %dj %dh %dmin %dsec", calcultempsjours(temps->temptotal), calcultempsheures(temps->temptotal), calcultempsminutes(temps->temptotal), calcultempssecondes(temps->temptotal));

            SDL_DestroyTexture(temps->tfps);
            SDL_DestroyTexture(perso->tlife);
            SDL_DestroyTexture(temps->ttemps);

            temps->tfps = imprime (temps->StringI, systeme->screenw, BLANC, systeme, NULL, NULL);
            perso->tlife = imprime (perso->slife, systeme->screenw, BLANC, systeme, NULL, NULL);
            temps->ttemps = imprime (temps->stringtempstotal, systeme->screenw, BLANC, systeme, NULL, NULL);

            for(index = 0; index < 10 ; index++)
            {
                if(online->chat.schat[index][0] != '\0')
                {
                    chat->pstringchat[index].y = (systeme->screenh*0.5)+(online->chat.poschat[index]*(systeme->screenh*0.047));
                    SDL_DestroyTexture(chat->tstringchat[index]);
                    chat->tstringchat[index] = imprime(online->chat.schat[index], systeme->screenw, BLANC, systeme, NULL, NULL);
                }
            }

            temps->i = 0;
            temps->tpap = temps->tpact;
        }
        else
        {
			SDL_Delay(5);
		}
    }

/*###########################################################################################################################
																															#
								##################### Fin de Fonction #####################									#
																														#
###########################################################################################################################*/

    sauvegardetout(systeme->sauvegarde, carte->pmap[0], perso, temps->temptotal, 0, objet->sac1, TAILLESAC, ui);

    for (index = 0 ; index < TILESMAP ; index++)
    {
        SDL_UnlockSurface(carte->calque[index]);
    }

    /*si la condition de boucle est toujours vrai, la fonction a été terminée par erreur.*/
    /*                 (devrais être impossible mais j'ai eu le cas)*/
    if (systeme->continuer == 1)
    {
        return -1;
    }
    return 1;
}



void detectioncombat(PACKmonstre *monstre, DIVERSinventaire *inventaire, DIVERSchat *chat, DIVERSui *ui,
                     DIVERSdeplacement *deplacement, PACKobjet *objet, PERSO *perso,DIVERSsysteme *systeme,
                     PACKrecompense *recompense, bool arcademode)
{
	int index;

	for(index = 0 ; index < 3 ; index++)
    {
        if (perso->pperso.x+perso->pperso.w >= monstre->rat[index].position.x &&
                perso->pperso.y+perso->pperso.h >= monstre->rat[index].position.y &&
                perso->pperso.y <= monstre->rat[index].position.y+monstre->rat[index].position.h &&
                perso->pperso.x <= monstre->rat[index].position.x+monstre->rat[index].position.w &&
                monstre->rat[index].etat == ALIVE)
        {
			monstre->rat[index].Engaged = true;
			monstre->rat[index].etat = lancementcombat(monstre, inventaire, chat, ui, deplacement, objet, perso, systeme, recompense, arcademode);
			initqueue(&monstre->rat[index].queue, monstre->rat[index].ID);
			monstre->rat[index].Engaged = false;
		}
	}
}







int lancementcombat(PACKmonstre *monstre, DIVERSinventaire *inventaire, DIVERSchat *chat, DIVERSui *ui,
                     DIVERSdeplacement *deplacement, PACKobjet *objet, PERSO *perso,DIVERSsysteme *systeme,
                     PACKrecompense *recompense, bool arcademode)
{
    int indexloot = 0, index2, RETcombat;
    char slootcombat[120];

	/*ecran de chargement*/
	chargement(systeme);

	if (arcademode == false)
	{
		/*cloture des UIs et arret du personnage*/
		inventaire->actif = false;
		chat->chatactif = false;
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

	SDL_RenderClear(systeme->renderer);

	/*############lancement du combat############*/
	RETcombat = combat(perso->life, monstre, systeme, perso, inventaire, recompense, objet, ui, arcademode);

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
			/*replacement du joueur au départ avec toute sa vie*/
			deplacement->x = 0;
			deplacement->y = -200;
			perso->pperso.x = systeme->screenw/2;
			perso->pperso.y = systeme->screenh/2;
			perso->life = perso->lifemax;

			return ALIVE; /*the creature*/
		}
		/*si le joueur a fui*/
		else if (RETcombat == BTL_LEAVED)
		{
			ui->ttextedialogue = fenetredialogue(systeme->screenw*0.4, systeme->screenh*0.8, &ui->pdialogue, &ui->ptextedialogue, "Vous avez fui,\ntous les objets obtenu pendant le combat on été abandonné sur place.\n\n\n\n(entrée/échap pour continuer)\n",
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
				recompense->ttextelootcombat[indexloot] = imprime(slootcombat, systeme->screenw, BLANC, systeme, NULL, NULL);

				for (index2 = 0 ; index2 < recompense->recompenseNB[indexloot] ; index2++)
				{
					/*insertion des récompenses 1 par 1*/
					insertionsac(objet, recompense->recompenseID[indexloot]);
				}
				indexloot++;
			}
		}
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

void ANIMpersomarche(DIVERSdeplacement *deplacement, DIVERStemps *temps)
{
    if (temps->tpact - temps->tempsanimationjoueur >= 128)
    {
        if (deplacement->persobouge == 1)
		{
			temps->tempsanimationjoueur = temps->tpact;
			deplacement->indexanimperso++;
            if(deplacement->indexanimperso >= 8)
            {
                deplacement->indexanimperso = 0;
            }
		}
		else
		{
			deplacement->indexanimperso = 0;
		}
    }
}

void ANIMmonstre(PACKmonstre *monstre, DIVERStemps *temps)
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

void gestionchat(DIVERSchat *chat, DIVERSsysteme *systeme, typeFORthreads *online)
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
        chat->tbufferchat = imprime(online->chat.bufferchat, systeme->screenw, BLANC, systeme, NULL, NULL);
    }
}

void sinchronisation(PACKpnj *pnj, DIVERSmap *carte, PACKmonstre *monstre, DIVERScraft *craft, DIVERSsysteme *systeme
							, typeFORthreads *online, PERSO *perso)
{
	int index;

	pnj->toumai.x = carte->pmap[0].x + 160;
	pnj->toumai.y = carte->pmap[0].y + 575;
	carte->pmx = carte->pmap[0].x * -1;
	carte->pmy = carte->pmap[0].y * -1;
	monstre->rat[1].position.x = carte->pmap[0].x + 1150;
	monstre->rat[1].position.y = carte->pmap[0].y + 1500;
	monstre->rat[0].position.x = carte->pmap[0].x + 540;
	monstre->rat[0].position.y = carte->pmap[0].y + 1232;
	monstre->rat[2].position.x = carte->pmap[0].x + 347;
	monstre->rat[2].position.y = carte->pmap[0].y + 1432;
	craft->petabli.x = carte->pmap[0].x + 830;
	craft->petabli.y = carte->pmap[0].y + 830;

	systeme->oldpp.x = systeme->pp.x;
	systeme->oldpp.y = systeme->pp.y;

	online->posjoueurx = carte->pmx + perso->pperso.x;
	online->posjoueury = carte->pmy + perso->pperso.y;

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
