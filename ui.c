#include <stdio.h>
#include <SDL.h>
#include <math.h>

#include "image.h"
#include "main.h"
#include "evenement.h"
#include "ui.h"
#include "deplacement.h"
#include "systeme.h"
#include "colision.h"

extern int screenh, screenw;

void gestionui (struct DIVERSsysteme *systeme,struct DIVERSui *ui,struct DIVERScraft *craft,struct PACKbouton *bouton,
                struct DIVERSchat *chat,struct DIVERSinventaire *inventaire,struct PACKobjet *objet,struct PERSO *perso,
                struct PACKpnj *pnj)
{
    int index = 0;
	/*si un dialogue a été lancer*/
	if (ui->lancedialogue == true)
	{
		char texte[512] = "Toumai :\n motive le développeur de ce jeu pour qu'il se bouge le cul a faire la suite ;)\n \n \n \n \n";
		ui->dialogue_text.texture = fenetredialogue(screenw*0.3, screenh*0.5, &ui->dialogue_back.pos, &ui->dialogue_text.pos, texte, BLANC, systeme);
		ui->dialogueactif = 1;
		ui->lancedialogue = false;
	}
	/*if the mouse moved*/
	if (systeme->pointeur.pos.x != systeme->oldpp.x ||
        systeme->pointeur.pos.y != systeme->oldpp.y)
	{
		inventaire->idsurvoler = -1;

		/*si l'interface de craft est actif*/
		if (ui->craft_open == true)
		{
			if (systeme->pointeur.pos.y >= screenh*0.467 && systeme->pointeur.pos.y <= (screenh*0.467)+(screenh*0.03))
			{
				if (systeme->pointeur.pos.x >= 0 && systeme->pointeur.pos.x <= screenw*0.143)
				{
					craft->bcraftpointer = ARME;
				}
				else if (systeme->pointeur.pos.x >= screenw*0.143 && systeme->pointeur.pos.x <= screenw*0.286)
				{
					craft->bcraftpointer = TORSE;
				}
				else if (systeme->pointeur.pos.x >= screenw*0.286 && systeme->pointeur.pos.x <= screenw*0.428)
				{
					craft->bcraftpointer = COU;
				}
				else if (systeme->pointeur.pos.x >= screenw*0.428 && systeme->pointeur.pos.x <= screenw*0.571)
				{
					craft->bcraftpointer = DOS;
				}
				else if (systeme->pointeur.pos.x >= screenw*0.571 && systeme->pointeur.pos.x <= screenw*0.714)
				{
					craft->bcraftpointer = PIED;
				}
				else if (systeme->pointeur.pos.x >= screenw*0.714 && systeme->pointeur.pos.x <= screenw*0.857)
				{
					craft->bcraftpointer = TAILLE;
				}
				else if (systeme->pointeur.pos.x >= screenw*0.857 && systeme->pointeur.pos.x <= screenw)
				{
					craft->bcraftpointer = TETE;
				}
				else
				{
					craft->bcraftpointer = -1;
				}
			}
			else if (systeme->pointeur.pos.y <= screenh*0.5 && systeme->pointeur.pos.x >= 410)
			{
				craft->bcraftpointer = -1;
				if (systeme->pointeur.pos.x >= screenw*0.623 && systeme->pointeur.pos.x <= screenw*0.732 &&
					systeme->pointeur.pos.y >= screenh*0.39 && systeme->pointeur.pos.y <= screenh*0.456 &&
					bouton->crafter.etat != 2)
				{
					bouton->crafter.etat = 1;
				}
				else if (bouton->crafter.etat != 2)
				{
					bouton->crafter.etat = 0;
				}
			}
			else
			{
			    craft->planpointer = -1;
				craft->bcraftpointer = -1;
				if (bouton->crafter.etat != 2)
				{
					bouton->crafter.etat = 0;
				}

				for(index = 0 ; index < 10 ; index++)
                {
                    if (systeme->pointeur.pos.x >= screenw*0.007 &&
                        systeme->pointeur.pos.x <= screenw*0.3 &&
                        systeme->pointeur.pos.y >= (screenh*0.04)*index &&
                        systeme->pointeur.pos.y <= (screenh*0.04)*(index+1))
                    {
                        craft->planpointer = index;
                    }
                }
			}
		}
		else if (ui->menu_open)
		{
			if (colisionbox(&systeme->pointeur.pos, &ui->BoutonQuitter.pos, true) &&
                ui->BoutonQuitter.etat != B_CLIQUER)
			{
				ui->BoutonQuitter.etat = B_SURVOLER;
			}
			else if (ui->BoutonQuitter.etat != B_CLIQUER)
			{
				ui->BoutonQuitter.etat = B_NORMAL;
			}
		}
		/*si l'inventaire est actif*/
		if (ui->inventaire_open)
		{
			if (systeme->pointeur.pos.y +  systeme->pointeur.pos.h < inventaire->box[0].pos.y + inventaire->box[0].pos.h)
			{
				int idcase = calculclicinventaire(systeme->pointeur.pos, systeme);
				if (idcase >= 0 && idcase < TAILLESAC)
				{
					if (objet->sac1[idcase].IDobjet != -1 &&
                        objet->sac1[idcase].IDobjet >= 0 &&
                        objet->sac1[idcase].IDobjet <= TAILLESAC)
					{
						inventaire->idsurvoler = objet->sac1[idcase].IDobjet;
					}
				}
			}
		}
	}

	if (ui->craft_open == true &&
		checkdistance(&perso->perso.pict.pos, &craft->petabli, 250) == 1) /*assez proche de l'etabli pour l'activer*/
    {
        ui->craft_open = false;
    }
    if (ui->dialogueactif == 1&&
		checkdistance(&perso->perso.pict.pos, &pnj->toumai.pos, 250) == 1 && /*assez distant de toumai pour qu'il se taise*/
        pnj->toumaiParle == true)
    {
        pnj->toumaiParle = false;
        ui->dialogueactif = 0;
    }
    if (checkdistance(&perso->perso.pict.pos, &pnj->toumai.pos, 3500) == 1 &&/*assez loin pour signaler de s'arreter*/
        ui->distanceprevenu == false)
    {
        ui->distanceprevenu = true;
        ui->dialogue_text.texture = fenetredialogue(screenw*0.4, screenh*0.8, &ui->dialogue_back.pos, &ui->dialogue_text.pos, "stop !\n il n'y rien a voir ici pour l'instant.\n\n\n\n\n\n\n", BLANC, systeme);
        ui->dialogueactif = 1;
    }
    else if (checkdistance(&perso->perso.pict.pos, &pnj->toumai.pos, 3500) != 1)/*asser proche pour réinitilaliser le conseil*/
    {
        ui->distanceprevenu = false;
    }

}

GLuint fenetredialogue(int x, int y, SDL_Rect* pdialogue, SDL_Rect* ptextedialogue, char texte[],
							int couleur,struct DIVERSsysteme *systeme)
{/*pdialogue is the background and ptextedialogue is the text inside.*/
/*just set "x" and "y" and everything will be automaticaly set up.*/
    GLuint picture;
	int lenght, high;

	if (texte != NULL)
	{
		picture = imprime(texte, x, couleur, systeme, &lenght, &high);
	}

	pdialogue->x = (screenw-x)/2;
	pdialogue->y = (screenh-y)/2;
	pdialogue->w = x;
	pdialogue->h = y;

	if (ptextedialogue != NULL)
	{
		ptextedialogue->w = lenght - (lenght/100)*5;
		ptextedialogue->h = high - 20;
		ptextedialogue->x = pdialogue->x + 20 + (pdialogue->w/2) - (lenght/2);
		ptextedialogue->y = (pdialogue->y + pdialogue->h) - ptextedialogue->h;
	}

	return picture;
}

SDL_Texture *DrawSDLText(SDL_Rect* ptextedialogue, char texte[], int color, int ALIGN,struct DIVERSsysteme *systeme)
{
	SDL_Texture *texture;
	int lenght, high;
//	texture = imprime(texte, ptextedialogue->x, color, systeme, &lenght, &high);

	switch(ALIGN)
	{
		case ALIGN_LEFT:
			ptextedialogue->x = 0;
			break;
		case ALIGN_RIGHT:
			ptextedialogue->x = (ptextedialogue->x + ptextedialogue->w) - lenght;
			break;
		case ALIGN_CENTER:
			ptextedialogue->x = ptextedialogue->x + (ptextedialogue->w/2) - (lenght/2);
			break;
		default:
			break;
	}

	ptextedialogue->y = ptextedialogue->y + (ptextedialogue->h/2) - (high/2);
	ptextedialogue->w = lenght;
	ptextedialogue->h = high;

	return texture;
}

int calculclicinventaire(SDL_Rect pointeur ,struct DIVERSsysteme *systeme)
{
	int ligne = ((screenh*0.4+screenw*0.0417) - (pointeur.y+pointeur.h))/(screenw*0.0417);
	int colonne = pointeur.x/(screenw*0.0417);
	return (ligne*24)+colonne;
}

void afficherCRAFT(struct DIVERScraft *craft,struct DIVERSui *ui,struct PACKbouton *bouton,struct PACKobjet *objet,
				struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme)
{
	int index;
	/*affichage du fond*/
	//SDL_RenderCopy	(systeme->renderer, craft->BGcraft, NULL, &ui->pUIhaut);

	/*affichage des onglets*/
	for (index = 0 ; index < 7 ; index++)
	{
		if (craft->bcraftactif == index)
		{
			//SDL_RenderCopy	(systeme->renderer, bouton->bcraft[index].cliquer, NULL, &bouton->bcraft[index].position);
		}
		else if (craft->bcraftpointer == index)
		{
			//SDL_RenderCopy	(systeme->renderer, bouton->bcraft[index].survoler, NULL, &bouton->bcraft[index].position);
		}
		else
		{
			//SDL_RenderCopy	(systeme->renderer, bouton->bcraft[index].normal, NULL, &bouton->bcraft[index].position);
		}
	}
	/*affichage des plans*/
	for (index = 0 ; index < 10 ; index++)
	{
		if (craft->bcraftactif != -1)
		{
		    craft->posplan.y = (screenh*0.04)*index;

			if (craft->planactif == index)
			{
                //SDL_RenderCopy	(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][index].resultatID].texturenom[2], NULL, &craft->posplan);
			}
			else if (craft->planpointer == index && craft->planpointer <  craft->planparonglets[craft->bcraftactif] )
			{
                //SDL_RenderCopy	(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][index].resultatID].texturenom[1], NULL, &craft->posplan);
            }
			else if (objet->PLANstuff[craft->bcraftactif][index].resultatID != -1)
			{
                //SDL_RenderCopy	(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][index].resultatID].texturenom[0], NULL, &craft->posplan);
			}
		}
	}

	/*affichage de la composition du plan*/
	if (craft->planactif >= 0 && craft->planactif < 10)
	{
		for (index = 0 ; index < objet->PLANstuff[craft->bcraftactif][craft->planactif].compodifferente ; index++)
			{
				sprintf(objet->PLANstuff[craft->bcraftactif][craft->planactif].textecompo[index], "==> %d %s", objet->PLANstuff[craft->bcraftactif][craft->planactif].compoNB[index], objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].compoID[index]].nom);
				SDL_DestroyTexture(craft->tcomponame[index]);
				if (inventaire->totalID[objet->PLANstuff[craft->bcraftactif][craft->planactif].compoID[index]] >= objet->PLANstuff[craft->bcraftactif][craft->planactif].compoNB[index])
				{
					/*objet dispo*/
//					craft->tcomponame[index] = imprime (objet->PLANstuff[craft->bcraftactif][craft->planactif].textecompo[index],
//						screenw, VERT, systeme, NULL, NULL);
					objet->PLANstuff[craft->bcraftactif][craft->planactif].compodispo[index] = true;
				}
				else
				{
					/*objet pas dispo*/
//					craft->tcomponame[index] = imprime (objet->PLANstuff[craft->bcraftactif][craft->planactif].textecompo[index],
//						screenw, ROUGE, systeme, NULL, NULL);
					objet->PLANstuff[craft->bcraftactif][craft->planactif].compodispo[index] = false;
				}

				//SDL_RenderCopy(systeme->renderer, craft->tcomponame[index], NULL,  &craft->poscompocraft[index]);
			}

		/*image resultat*/
		//SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].texture, NULL, &craft->posimageresultatcraft);

		/*si l'objet possède des stats*/
		if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].type == EQUIPEMENT)
		{
			craft->pstats.y = screenh*0.160;
			/*stat defense*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].def != 0)
			{
				craft->pstats.y += screenh*0.065;
				//SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].texturedef, NULL, &craft->pstats);
			}
			/*stat life*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].life != 0)
			{
				craft->pstats.y += screenh*0.065;
				//SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].texturelife, NULL, &craft->pstats);
			}
			/*stat regenlife*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].regenlife != 0)
			{
				craft->pstats.y += screenh*0.065;
				//SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].textureregenlife, NULL, &craft->pstats);
			}
			/*stat force*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].force != 0)
			{
				craft->pstats.y += screenh*0.065;
				//SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].textureforce, NULL, &craft->pstats);
			}
			/*stat portée*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].portee != 0)
			{
				craft->pstats.y += screenh*0.065;
				//SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].textureportee, NULL, &craft->pstats);
			}
		}

		if (bouton->crafter.etat == 0)
		{
			//SDL_RenderCopy	(systeme->renderer, bouton->crafter.normal, NULL, &bouton->crafter.position);
		}
		else if (bouton->crafter.etat == 1)
		{
			//SDL_RenderCopy	(systeme->renderer, bouton->crafter.survoler, NULL, &bouton->crafter.position);
		}
		else
		{
			//SDL_RenderCopy	(systeme->renderer, bouton->crafter.cliquer, NULL, &bouton->crafter.position);
		}


		for (index = 0 ; index < objet->PLANstuff[craft->bcraftactif][craft->planactif].compodifferente ; index++)
		{
			//SDL_RenderCopy	(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].compoID[index]].texture, NULL,  &craft->posimagecompocraft[index]);
		}
	}
}

void afficherINVENTAIRE(struct DIVERSinventaire *inventaire,struct DIVERSui *ui,struct PACKobjet *objet,struct DIVERSsysteme *systeme)
{
	int index;
	char snbobjet[4];
	/*background*/
	draw_pict(&inventaire->fond);
	/*bags*/
	draw_pict(&inventaire->sac);
	/*rubbish*/
	if (objet->objetenmain.IDobjet != -1)
    {
        draw_pict(&inventaire->rubbish);
    }
	/*for each cases*/
	for (index = 0 ; index < TAILLESAC ; index++)
	{
		/*the case*/
		draw_pict(&inventaire->box[index]);
		/*si la case contient un objet*/
		if(objet->sac1[index].NBobjet > 0 && objet->sac1[index].IDobjet > -1)
		{
			/*image de l'objet*/
			draw(objet->objet[objet->sac1[index].IDobjet].texture, &inventaire->box[index].pos);
			/*si il y a plus d'un objet*/
			if (objet->sac1[index].NBobjet > 1)
			{
				/*si le nombre d'objet est égale au nombre maximum empilable*/
				if (objet->sac1[index].NBobjet == objet->objet[objet->sac1[index].IDobjet].empilage)
				{
				    draw(objet->objet[objet->sac1[index].IDobjet].quantite, &inventaire->pnbobjet[index]);
				}
				else
				{
					sprintf (snbobjet, "%d", objet->sac1[index].NBobjet);
					draw(imprime(snbobjet, screenw, ROUGE, systeme, NULL, NULL), &inventaire->pnbobjet[index]);
				}
			}
		}

	}
	if (inventaire->idsurvoler != -1)
	{
		afficherDETAIL(inventaire, objet, systeme, inventaire->idsurvoler);
	}
}

void afficherUI(bool enligne,struct DIVERSui *ui,struct PACKbouton *bouton,struct DIVERStemps *temps,struct PERSO *perso,
                struct DIVERSinventaire *inventaire, struct DIVERSsysteme *systeme,
                struct PACKrecompense *recompense,struct PACKobjet *objet)
{
	int index, calculposy;
	/*coins*/
	draw_button(&ui->corner_chat);
	draw_button(&ui->corner_menu);
	draw_button(&ui->corner_inventaire);

	if (ui->menu_open)
	{
		/*BackGround*/
		draw_pict(&ui->BGmenu);
		/*infos*/
		draw_pict(&temps->temps);
		draw_pict(&temps->fps);

		draw_pict(&perso->tlife);
		draw_pict(&perso->tdefense);
		draw_pict(&perso->tregenlife);
		draw_pict(&perso->tforce);
		draw_pict(&perso->tportee);

		/*désignation stuff*/
		for (index = 0 ; index < 7 ; index++)
		{
		    draw(inventaire->box[0].texture, &ui->casestuff[index].pos);
			if(ui->casestuff[index].IDobjet != -1)
			{
			    draw(objet->objet[ui->casestuff[index].IDobjet].texture, &ui->casestuff[index].pos);
			}
			else
			{
				//SDL_RenderCopy	(systeme->renderer, ui->tdesignationstuff[index], NULL, &ui->pcasestuff[index]);
			}
		}
		for (index = 0 ; index < 7 ; index++)
		{
		/*si pointeur dans case stuff*/
			if (colisionbox(&systeme->pointeur.pos, &ui->casestuff[index].pos, true) &&
				ui->casestuff[index].IDobjet != -1)
			{
				afficherDETAIL(inventaire, objet, systeme, ui->casestuff[index].IDobjet);
			}
		}
        draw_button(&ui->BoutonQuitter);

		/*lumieres*/
		if(enligne == false)	{//SDL_RenderCopy(systeme->renderer, ui->lumiereoff, NULL, &ui->plumiere);

		}
		else	{//SDL_RenderCopy(systeme->renderer, ui->lumiereon, NULL, &ui->plumiere);

		}
	}


/*dialogue*/
	if (ui->dialogueactif == 1)
	{
	    draw_pict (&ui->dialogue_back);
	    draw_pict (&ui->dialogue_text);
	}
	else if (ui->dialogueactif == 2)
	{
		//SDL_RenderCopy	(systeme->renderer, systeme->BG, NULL, &recompense->pBGrecompense);
		//SDL_RenderCopy	(systeme->renderer, recompense->tvictoire, NULL, &recompense->ptvictoire);
		//SDL_RenderCopy	(systeme->renderer, recompense->ttexterecompensecombat, NULL, &recompense->ptrecompesecombat);
		calculposy = 0;
		for(index = 0 ; index < LOOTMAX ; index++)
		{
			if (recompense->recompenseNB[index] != 0)
			{
				recompense->precompensecombat.y = screenh*0.326 + (calculposy*(screenh*0.0651));
				//SDL_RenderCopy	(systeme->renderer, recompense->ttextelootcombat[index], NULL, &recompense->precompensecombat);
				calculposy++;
			}
		}
	}
}

void afficherMAP(struct DIVERSmap *carte,struct DIVERSsysteme *systeme,struct DIVERScraft *craft)
{
    draw_pict(&carte->cellule.pict);
    //SDL_RenderCopy(systeme->renderer, craft->tetabli, NULL, &craft->petabli);
}

void afficherPNJ(struct PERSO *perso,struct PACKpnj *pnj,struct DIVERSsysteme *systeme)
{
    draw_pict(&pnj->toumai);
	//SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->spriteup[0], &pnj->toumai, -90,NULL, SDL_FLIP_NONE);
	//SDL_RenderCopyEx(systeme->renderer, perso->cheveuxblanc, NULL, &pnj->toumai, -90,NULL, SDL_FLIP_NONE);
}

void afficherMOB(struct PACKmonstre *monstre,struct DIVERSsysteme *systeme, struct DIVERStemps *temps)
{
	int index;
	for (index = 0 ; index < 3 ; index++)
	{
		if (monstre->rat[index].etat == ALIVE)
		{
		    Sync_Moving_Pict(temps->tpact, &monstre->rat[index].m_pict);
		    Turn_And_Draw(&monstre->rat[index].m_pict.pict, monstre->rat[index].direction*45);
        }
	}
}

void afficherJOUEURS(struct PERSO *perso,struct DIVERSdeplacement *deplacement,struct DIVERSsysteme *systeme,
                     struct typeFORthreads *online, struct DIVERStemps *temps)
{
    int index, calcul;
	/*joueur client*/
	if (deplacement->direction.direction == -1)
	{
		calcul = 180-(45 * deplacement->direction.olddirection);
	}
	else
	{
		calcul = 180-(45 * deplacement->direction.direction);
	}

    if (deplacement->persobouge == 1)
    {
        Sync_Moving_Pict(temps->tpact, &perso->perso);
    }
    else
    {
        perso->perso.pict.texture = perso->perso.texture[0];
    }

	Turn_And_Draw(&perso->perso.pict, calcul);

	//SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->spriteup[deplacement->indexanimperso], &perso->pperso, calcul,NULL, SDL_FLIP_NONE);
	//SDL_RenderCopy(systeme->renderer, perso->tpseudo, NULL, &perso->ptpseudo);


	/*joueurs en ligne
	for(index = 0 ; index < MAX_JOUEURS ; index++)
	{
		if (online->joueurs[index].enligne == 1)
		{
			online->joueurs[index].posjoueurscalculer.x = online->joueurs[index].position.x + deplacement->x;
			online->joueurs[index].posjoueurscalculer.y = online->joueurs[index].position.y + deplacement->y;
			online->joueurs[index].posjoueurscalculer.h = 48;
			online->joueurs[index].posjoueurscalculer.w = 68;

			if (online->joueurs[index].oldposjoueurs.x != online->joueurs[index].position.x ||
				online->joueurs[index].oldposjoueurs.y != online->joueurs[index].position.y)
			{
				deplacement->directionjoueurs[index] = calculdirectionjoueurs(online->joueurs[index].position, online->joueurs[index].oldposjoueurs);
				online->joueurs[index].oldposjoueurs.x = online->joueurs[index].position.x;
			   online->joueurs[index].oldposjoueurs.y = online->joueurs[index].position.y;

			}
			calcul = 45 * deplacement->directionjoueurs[index];

			online->joueurs[index].ppseudo.x = online->joueurs[index].posjoueurscalculer.x;
			online->joueurs[index].ppseudo.y = online->joueurs[index].posjoueurscalculer.y - 33;
			online->joueurs[index].ppseudo.w = 100;
			online->joueurs[index].ppseudo.h = 30;
			//SDL_RenderCopyEx			(systeme->renderer, perso->tperso, &perso->spriteup[0], &online->joueurs[index].posjoueurscalculer, calcul,NULL, SDL_FLIP_NONE);
			//SDL_RenderCopyEx			(systeme->renderer, perso->cheveuxbrun, NULL, &online->joueurs[index].posjoueurscalculer, calcul,NULL, SDL_FLIP_NONE);
			//SDL_RenderCopy				(systeme->renderer, online->joueurs[index].tpseudo, NULL, &online->joueurs[index].ppseudo);
		}
	}*/
}

void afficherCHAT(struct DIVERSchat *chat,struct DIVERSui *ui, int lenbuffer,struct DIVERSsysteme *systeme)
{
	int index;
	//SDL_RenderCopy	(systeme->renderer, chat->BGchat, NULL, &ui->pUIbas);
	for(index = 0; index < 10 ; index++)
	{
		SDL_QueryTexture(chat->tstringchat[index], NULL, NULL, &chat->pstringchat[index].w, NULL);
		//SDL_RenderCopy	(systeme->renderer, chat->tstringchat[index], NULL, &chat->pstringchat[index]);
	}
	if (chat->saisiechat == 1)
	{
		//SDL_RenderCopy	(systeme->renderer, chat->BGchatactif, NULL, &chat->pchatactif);
	}
	if (lenbuffer > 0)
	{
		SDL_QueryTexture(chat->tbufferchat, NULL, NULL, &chat->pbufferchat.w, NULL);
		//SDL_RenderCopy	(systeme->renderer, chat->tbufferchat, NULL, &chat->pbufferchat);
	}
}

void afficherPOINTEUR(struct DIVERSsysteme *systeme,struct PACKobjet *objet)
{
	draw_pict(&systeme->pointeur);
	if (objet->objetenmain.IDobjet != -1)
	{
		systeme->ppobj.x = systeme->pointeur.pos.x + 15;
		systeme->ppobj.y = systeme->pointeur.pos.y + 20;
		draw (objet->objet[objet->objetenmain.IDobjet].texture, &systeme->ppobj);
	}

}

void afficherDETAIL(struct DIVERSinventaire *inventaire,struct PACKobjet *objet,struct DIVERSsysteme *systeme, int id)
{
    int largeurmax = 0;

	inventaire->pdetail.x = systeme->pointeur.pos.x + 15;
	inventaire->pdetail.h = 80;
	inventaire->pdetail.y = systeme->pointeur.pos.y - systeme->pointeur.pos.h - 15;

	largeurmax = objet->objet[id].LARGEURnom;

	if(largeurmax < inventaire->aide.lenght)/*clic droit*/
	{
		largeurmax = inventaire->aide.lenght;
	}
	if(objet->objet[id].type == EQUIPEMENT)
	{
		if(objet->objet[id].def > 0)/*def*/
		{
			if(largeurmax < objet->objet[id].tdef.lenght)
			{
				largeurmax = objet->objet[id].tdef.lenght;
			}
			inventaire->pdetail.h += 40;
		}
		if(objet->objet[id].life > 0)/*life*/
		{
			if(largeurmax < objet->objet[id].tlife.lenght)
			{
				largeurmax = objet->objet[id].tlife.lenght;
			}
			inventaire->pdetail.h += 40;
		}
		if(objet->objet[id].regenlife > 0)/*regenlife*/
		{
			if(largeurmax < objet->objet[id].tregenlife.lenght)
			{
				largeurmax = objet->objet[id].tregenlife.lenght;
			}
			inventaire->pdetail.h += 40;
		}
		if(objet->objet[id].force > 0)/*force*/
		{
			if(largeurmax < objet->objet[id].tforce.lenght)
			{
				largeurmax = objet->objet[id].tforce.lenght;
			}
			inventaire->pdetail.h += 40;
		}
		if(objet->objet[id].portee > 0)/*portee*/
		{
			if(largeurmax < objet->objet[id].tportee.lenght)
			{
				largeurmax = objet->objet[id].tportee.lenght;
			}
			inventaire->pdetail.h += 40;
		}
	}
	inventaire->pdetail.w = largeurmax;


/*ajustement bas ecran*/
	if (inventaire->pdetail.y < 0)
	{
		inventaire->pdetail.y = inventaire->pdetail.h;
	}
/*ajustement droite ecran*/
	if (inventaire->pdetail.x + inventaire->pdetail.w > screenw)
	{
		inventaire->pdetail.x = screenw - inventaire->pdetail.w -20;
	}

/*affichage*/
	inventaire->pdetail.w += 20;
	inventaire->pdetail.y = systeme->pointeur.pos.y - inventaire->pdetail.h;
	draw(systeme->BG, &inventaire->pdetail);

	if(objet->objet[id].type == EQUIPEMENT)
	{
	    inventaire->pdetail.x += 10;
        inventaire->pdetail.y += 5;
        inventaire->pdetail.h = 30;
        inventaire->pdetail.w = inventaire->aide.lenght;

        draw(inventaire->aide.img.texture, &inventaire->pdetail);
        inventaire->pdetail.y -= 10;
		inventaire->pdetail.h = 40;

		if (objet->objet[id].def > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.w = objet->objet[id].tdef.lenght;
			draw(objet->objet[id].tdef.img.texture, &inventaire->pdetail);
		}
		if (objet->objet[id].life > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.w = objet->objet[id].tlife.lenght;
			draw(objet->objet[id].tlife.img.texture, &inventaire->pdetail);
		}
		if (objet->objet[id].regenlife > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.w = objet->objet[id].tregenlife.lenght;
			draw(objet->objet[id].tregenlife.img.texture, &inventaire->pdetail);
		}
		if (objet->objet[id].force > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.w = objet->objet[id].tforce.lenght;
			draw(objet->objet[id].tforce.img.texture, &inventaire->pdetail);
		}
		if (objet->objet[id].portee > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.w = objet->objet[id].tportee.lenght;
			draw(objet->objet[id].tportee.img.texture, &inventaire->pdetail);
		}
		inventaire->pdetail.w = objet->objet[id].LARGEURnom;
		inventaire->pdetail.y += 40;
		draw(objet->objet[id].texturenom[2],&inventaire->pdetail);

	}
	else
	{
	    draw(objet->objet[id].texturenom[2],&inventaire->pdetail);
	}
}
