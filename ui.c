#include <stdio.h>
#include <SDL.h>
#include <math.h>

#include "image.h"
#include "main.h"
#include "evenement.h"
#include "ui.h"
#include "deplacement.h"
#include "systeme.h"


void gestionui (struct DIVERSsysteme *systeme,struct DIVERSui *ui,struct DIVERScraft *craft,struct PACKbouton *bouton,
                struct DIVERSchat *chat,struct DIVERSinventaire *inventaire,struct PACKobjet *objet,struct PERSO *perso,
                struct PACKpnj *pnj)
{
    int index = 0;
	/*si un dialogue a été lancer*/
	if (ui->lancedialogue == 2)
	{
		char texte[512] = "Toumai :\n motive le développeur de ce jeu pour qu'il se bouge le cul a faire la suite ;)\n \n \n \n \n";
		ui->ttextedialogue = fenetredialogue(systeme->screenw*0.3, systeme->screenh*0.5, &ui->pdialogue, &ui->ptextedialogue, texte, BLANC, systeme);
		ui->dialogueactif = 1;
		ui->lancedialogue = 0;
	}
	/*if the mouse moved*/
	if (systeme->pp.x != systeme->oldpp.x ||
        systeme->pp.y != systeme->oldpp.y)
	{
		inventaire->idsurvoler = -1;

		/*test des coins*/
		TestCursorOnCorner(ui, systeme);
		testcoin(ui, chat, inventaire);

		/*si l'interface de craft est actif*/
		if (craft->actif == true)
		{
			if (systeme->pp.y >= systeme->screenh*0.467 && systeme->pp.y <= (systeme->screenh*0.467)+(systeme->screenh*0.03))
			{
				if (systeme->pp.x >= 0 && systeme->pp.x <= systeme->screenw*0.143)
				{
					craft->bcraftpointer = ARME;
				}
				else if (systeme->pp.x >= systeme->screenw*0.143 && systeme->pp.x <= systeme->screenw*0.286)
				{
					craft->bcraftpointer = TORSE;
				}
				else if (systeme->pp.x >= systeme->screenw*0.286 && systeme->pp.x <= systeme->screenw*0.428)
				{
					craft->bcraftpointer = COU;
				}
				else if (systeme->pp.x >= systeme->screenw*0.428 && systeme->pp.x <= systeme->screenw*0.571)
				{
					craft->bcraftpointer = DOS;
				}
				else if (systeme->pp.x >= systeme->screenw*0.571 && systeme->pp.x <= systeme->screenw*0.714)
				{
					craft->bcraftpointer = PIED;
				}
				else if (systeme->pp.x >= systeme->screenw*0.714 && systeme->pp.x <= systeme->screenw*0.857)
				{
					craft->bcraftpointer = TAILLE;
				}
				else if (systeme->pp.x >= systeme->screenw*0.857 && systeme->pp.x <= systeme->screenw)
				{
					craft->bcraftpointer = TETE;
				}
				else
				{
					craft->bcraftpointer = -1;
				}
			}
			else if (systeme->pp.y <= systeme->screenh*0.5 && systeme->pp.x >= 410)
			{
				craft->bcraftpointer = -1;
				if (systeme->pp.x >= systeme->screenw*0.623 && systeme->pp.x <= systeme->screenw*0.732 &&
					systeme->pp.y >= systeme->screenh*0.39 && systeme->pp.y <= systeme->screenh*0.456 &&
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
                    if (systeme->pp.x >= systeme->screenw*0.007 &&
                        systeme->pp.x <= systeme->screenw*0.3 &&
                        systeme->pp.y >= (systeme->screenh*0.04)*index &&
                        systeme->pp.y <= (systeme->screenh*0.04)*(index+1))
                    {
                        craft->planpointer = index;
                    }
                }
			}
		}
		else if (ui->coinhaut == 1)
		{
			if (systeme->pp.x >= systeme->screenw*0.7 && systeme->pp.x <= (systeme->screenw*0.7)+(systeme->screenw*0.04) &&
			systeme->pp.y >= systeme->screenh*0.3 && systeme->pp.y <= (systeme->screenh*0.3)+(systeme->screenw*0.04) &&
			bouton->BoutonQuitter.etat != 2)
			{
				bouton->BoutonQuitter.etat = 1;
			}
			else if (bouton->BoutonQuitter.etat != 2)
			{
				bouton->BoutonQuitter.etat = 0;
			}
		}
		/*si l'inventaire est actif*/
		if (ui->coinbas == 2)
		{
			if (systeme->pp.y > systeme->screenh*0.526)
			{
				int idcase = calculclicinventaire(&systeme->pp.y, &systeme->pp.x, systeme);
				if (idcase >= 0 && idcase < TAILLESAC)
				{
					if (objet->sac1[idcase].IDobjet != -1)
					{
						inventaire->idsurvoler = objet->sac1[idcase].IDobjet;
					}
				}
			}
		}
	}
	/* if cursor didn't move but is in a corner */
	else if (ui->PointedCorner != 0)
    {
        /*corners tests*/
		TestCursorOnCorner(ui, systeme);
		testcoin(ui, chat, inventaire);
    }

	if (craft->actif == true &&
		checkdistance(&perso->pperso, &craft->petabli, 250) == 1) /*assez proche de l'etabli pour l'activer*/
    {
        craft->actif = false;
    }
    if (ui->dialogueactif == 1&&
		checkdistance(&perso->pperso, &pnj->toumai, 250) == 1 && /*assez distant de toumai pour qu'il se taise*/
        pnj->toumaiParle == true)
    {
        pnj->toumaiParle = false;
        ui->dialogueactif = 0;
    }
    if (checkdistance(&perso->pperso, &pnj->toumai, 3500) == 1 &&/*assez loin pour signaler de s'arreter*/
        ui->distanceprevenu == false)
    {
        ui->distanceprevenu = true;
        ui->ttextedialogue = fenetredialogue(systeme->screenw*0.4, systeme->screenh*0.8, &ui->pdialogue, &ui->ptextedialogue, "stop !\n il n'y rien a voir ici pour l'instant.\n\n\n\n\n\n\n", BLANC, systeme);
        ui->dialogueactif = 1;
    }
    else if (checkdistance(&perso->pperso, &pnj->toumai, 3500) != 1)/*asser proche pour réinitilaliser le conseil*/
    {
        ui->distanceprevenu = false;
    }

}

SDL_Texture *fenetredialogue(int x, int y, SDL_Rect* pdialogue, SDL_Rect* ptextedialogue, char texte[],
							int couleur,struct DIVERSsysteme *systeme)
{/*pdialogue is the background and ptextedialogue is the text inside.*/
/*just set "x" and "y" and everything will be automaticaly set up.*/

	SDL_Texture *texture = NULL;
	int lenght, high;

	if (texte != NULL)
	{
		texture = imprime(texte, x, couleur, systeme, &lenght, &high);
	}

	pdialogue->x = (systeme->screenw-x)/2;
	pdialogue->y = (systeme->screenh-y)/2;
	pdialogue->w = x;
	pdialogue->h = y;

	if (ptextedialogue != NULL)
	{
		ptextedialogue->w = lenght - (lenght/100)*5;
		ptextedialogue->h = high - 20;
		ptextedialogue->x = pdialogue->x + 20 + (pdialogue->w/2) - (lenght/2);
		ptextedialogue->y = pdialogue->y + 20;
	}

	return texture;
}

SDL_Texture *DrawSDLText(SDL_Rect* ptextedialogue, char texte[], int color, int ALIGN,struct DIVERSsysteme *systeme)
{
	SDL_Texture *texture;
	int lenght, high;
	texture = imprime(texte, ptextedialogue->x, color, systeme, &lenght, &high);

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

void testcoin(struct DIVERSui *ui,struct DIVERSchat *chat,struct DIVERSinventaire *inventaire)
{
	int statcoinhaut = 0, statcoinbas = 0, time = 0;
	time = TimeOnCorner(ui);

	if (ui->OnLeftDown && time > 1000)/*							coin bas gauche*/
	{
	    ui->PointedCorner = 0;
		if (statcoinbas != 1)
		{
			statcoinbas = 1;
			if (ui->coinbas == 1)/*bas inactif*/
			{
				ui->coinbas = 0;
				if (chat->saisiechat== 1)
				{
					chat->saisiechat = 2;
				}
				inventaire->actif = false;
				chat->chatactif = false;
			}
			else/*chat actif*/
			{
				ui->coinbas = 1;
				if (chat->saisiechat == 2)
					{
						chat->saisiechat = 1;
					}
				inventaire->actif = false;
				chat->chatactif = true;
			}
		}
	}
	else if (ui->OnRightDown && time > 1000)/*		coin bas droit*/
	{
	    ui->PointedCorner = 0;
		if (statcoinbas != 2)
		{
			statcoinbas = 2;
			if (ui->coinbas == 2)/*bas inactif*/
			{
				ui->coinbas = 0;
				if (chat->saisiechat== 1)
				{
					chat->saisiechat = 2;
				}
				inventaire->actif = false;
				chat->chatactif = false;
			}
			else/*inventaire actif*/
			{
				ui->coinbas = 2;
				if (chat->saisiechat== 1)
				{
					chat->saisiechat = 2;
				}
				inventaire->actif = true;
				chat->chatactif = false;
			}
		}

	}
	else if (ui->OnLeftUp && time > 1000)/*						coin haut gauche*/
	{
	    ui->PointedCorner = 0;
		if (statcoinhaut != 1)
		{
			statcoinhaut = 1;
			if (ui->coinhaut == 1)
			{
				ui->coinhaut = 0;
				ui->menuactif = false;
			}
			else
			{
				ui->coinhaut = 1;
				ui->menuactif = true;
			}
		}
	}
	if (!ui->OnLeftDown && !ui->OnLeftUp && !ui->OnRightDown && !ui->OnRightUp)/*								aucun coin*/
	{
		statcoinbas = 0;
		statcoinhaut = 0;
		ui->PointedCorner = 0;
	}
}

int calculclicinventaire(int *ptrpy, int *ptrpx,struct DIVERSsysteme *systeme)
{
	int ligne = (*ptrpy - (systeme->screenh*0.526))/(systeme->screenw*0.0417);
	int colonne = *ptrpx/(systeme->screenw*0.0417);
	return (ligne*24)+colonne;
}

void afficherCRAFT(struct DIVERScraft *craft,struct DIVERSui *ui,struct PACKbouton *bouton,struct PACKobjet *objet,
				struct DIVERSinventaire *inventaire,struct DIVERSsysteme *systeme)
{
	int index;
	/*affichage du fond*/
	SDL_RenderCopy	(systeme->renderer, craft->BGcraft, NULL, &ui->pUIhaut);

	/*affichage des onglets*/
	for (index = 0 ; index < 7 ; index++)
	{
		if (craft->bcraftactif == index)
		{
			SDL_RenderCopy	(systeme->renderer, bouton->bcraft[index].cliquer, NULL, &bouton->bcraft[index].position);
		}
		else if (craft->bcraftpointer == index)
		{
			SDL_RenderCopy	(systeme->renderer, bouton->bcraft[index].survoler, NULL, &bouton->bcraft[index].position);
		}
		else
		{
			SDL_RenderCopy	(systeme->renderer, bouton->bcraft[index].normal, NULL, &bouton->bcraft[index].position);
		}
	}
	/*affichage des plans*/
	for (index = 0 ; index < 10 ; index++)
	{
		if (craft->bcraftactif != -1)
		{
		    craft->posplan.y = (systeme->screenh*0.04)*index;

			if (craft->planactif == index)
			{
                SDL_RenderCopy	(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][index].resultatID].texturenom[2], NULL, &craft->posplan);
			}
			else if (craft->planpointer == index && craft->planpointer <  craft->planparonglets[craft->bcraftactif] )
			{
                SDL_RenderCopy	(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][index].resultatID].texturenom[1], NULL, &craft->posplan);
            }
			else if (objet->PLANstuff[craft->bcraftactif][index].resultatID != -1)
			{
                SDL_RenderCopy	(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][index].resultatID].texturenom[0], NULL, &craft->posplan);
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
					craft->tcomponame[index] = imprime (objet->PLANstuff[craft->bcraftactif][craft->planactif].textecompo[index],
						systeme->screenw, VERT, systeme, NULL, NULL);
					objet->PLANstuff[craft->bcraftactif][craft->planactif].compodispo[index] = true;
				}
				else
				{
					/*objet pas dispo*/
					craft->tcomponame[index] = imprime (objet->PLANstuff[craft->bcraftactif][craft->planactif].textecompo[index],
						systeme->screenw, ROUGE, systeme, NULL, NULL);
					objet->PLANstuff[craft->bcraftactif][craft->planactif].compodispo[index] = false;
				}

				SDL_RenderCopy(systeme->renderer, craft->tcomponame[index], NULL,  &craft->poscompocraft[index]);
			}

		/*image resultat*/
		SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].texture, NULL, &craft->posimageresultatcraft);

		/*si l'objet possède des stats*/
		if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].type == 1)
		{
			craft->pstats.y = systeme->screenh*0.160;
			/*stat defense*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].def != 0)
			{
				craft->pstats.y += systeme->screenh*0.065;
				SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].texturedef, NULL, &craft->pstats);
			}
			/*stat life*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].life != 0)
			{
				craft->pstats.y += systeme->screenh*0.065;
				SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].texturelife, NULL, &craft->pstats);
			}
			/*stat regenlife*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].regenlife != 0)
			{
				craft->pstats.y += systeme->screenh*0.065;
				SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].textureregenlife, NULL, &craft->pstats);
			}
			/*stat force*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].force != 0)
			{
				craft->pstats.y += systeme->screenh*0.065;
				SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].textureforce, NULL, &craft->pstats);
			}
			/*stat portée*/
			if(objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].portee != 0)
			{
				craft->pstats.y += systeme->screenh*0.065;
				SDL_RenderCopy(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].resultatID].textureportee, NULL, &craft->pstats);
			}
		}

		if (bouton->crafter.etat == 0)
		{
			SDL_RenderCopy	(systeme->renderer, bouton->crafter.normal, NULL, &bouton->crafter.position);
		}
		else if (bouton->crafter.etat == 1)
		{
			SDL_RenderCopy	(systeme->renderer, bouton->crafter.survoler, NULL, &bouton->crafter.position);
		}
		else
		{
			SDL_RenderCopy	(systeme->renderer, bouton->crafter.cliquer, NULL, &bouton->crafter.position);
		}


		for (index = 0 ; index < objet->PLANstuff[craft->bcraftactif][craft->planactif].compodifferente ; index++)
		{
			SDL_RenderCopy	(systeme->renderer, objet->objet[objet->PLANstuff[craft->bcraftactif][craft->planactif].compoID[index]].texture, NULL,  &craft->posimagecompocraft[index]);
		}
	}
}

void afficherINVENTAIRE(struct DIVERSinventaire *inventaire,struct DIVERSui *ui,struct PACKobjet *objet,struct DIVERSsysteme *systeme)
{
	int index;
	char snbobjet[4];
	/*background*/
	SDL_RenderCopy	(systeme->renderer, inventaire->BGinventaire, NULL, &ui->pUIbas);
	/*sacs*/
	SDL_RenderCopy	(systeme->renderer, inventaire->tsacinventaire, NULL, &inventaire->psac);
	/*pour chaques cases*/
	for (index = 0 ; index < TAILLESAC ; index++)
	{
		/*la case*/
		SDL_RenderCopy	(systeme->renderer, inventaire->tcasesac, NULL, &inventaire->pcaseinventaire[index]);
		/*si la case contient un objet*/
		if(objet->sac1[index].NBobjet > 0 && objet->sac1[index].IDobjet > -1)
		{
			/*image de l'objet*/
			SDL_RenderCopy	(systeme->renderer, objet->objet[objet->sac1[index].IDobjet].texture, NULL, &inventaire->pcaseinventaire[index]);
			/*si il y a plus d'un objet*/
			if (objet->sac1[index].NBobjet > 1)
			{
				/*si le nombre d'objet est égale au nombre maximum empilable*/
				if (objet->sac1[index].NBobjet == objet->objet[objet->sac1[index].IDobjet].empilage)
				{
					SDL_RenderCopy	(systeme->renderer, objet->objet[objet->sac1[index].IDobjet].texturenombre, NULL, &inventaire->pnbobjet[index]);
				}
				else
				{
					sprintf (snbobjet, "%d", objet->sac1[index].NBobjet);
					SDL_DestroyTexture(inventaire->tnbobjet);
					inventaire->tnbobjet = imprime(snbobjet, systeme->screenw, ROUGE, systeme, NULL, NULL);
					SDL_RenderCopy	(systeme->renderer, inventaire->tnbobjet, NULL, &inventaire->pnbobjet[index]);
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
	SDL_RenderCopy	(systeme->renderer, ui->Uichat, NULL, &ui->puichat);
	SDL_RenderCopy	(systeme->renderer, ui->Uiinventaire, NULL, &ui->puiinventaire);
	SDL_RenderCopy	(systeme->renderer, ui->uimenu, NULL, &ui->puimenu);

	if (ui->menuactif == true)
	{
		/*BackGround*/
		SDL_RenderCopy	(systeme->renderer, ui->BGmenu, NULL, &ui->pUIhaut);
		/*infos*/
		SDL_RenderCopy	(systeme->renderer, temps->ttemps, NULL, &temps->pttemps);/*temps*/
		SDL_RenderCopy	(systeme->renderer, temps->tfps, NULL, &temps->ptFps);/*fps*/

		perso->pstats.y = systeme->screenh*0.1;
		SDL_RenderCopy	(systeme->renderer, perso->tlife, NULL, &perso->pstats);/*vie*/
		perso->pstats.y += perso->pstats.h;
		SDL_RenderCopy	(systeme->renderer, perso->tdefense, NULL, &perso->pstats);/*defense*/
		perso->pstats.y += perso->pstats.h;
		SDL_RenderCopy	(systeme->renderer, perso->tregenlife, NULL, &perso->pstats);/*regen life*/
		perso->pstats.y += perso->pstats.h;
		SDL_RenderCopy	(systeme->renderer, perso->tforce, NULL, &perso->pstats);/*force*/
		perso->pstats.y += perso->pstats.h;
		SDL_RenderCopy	(systeme->renderer, perso->tportee, NULL, &perso->pstats);/*portee*/
		/*désignation stuff*/
		for (index = 0 ; index < 7 ; index++)
		{
			SDL_RenderCopy	(systeme->renderer, inventaire->tcasesac2, NULL, &ui->pcasestuff[index]);
			if(ui->casestuff[index].IDobjet != -1)
			{
				SDL_RenderCopy	(systeme->renderer, objet->objet[ui->casestuff[index].IDobjet].texture, NULL, &ui->pcasestuff[index]);
			}
			else
			{
				SDL_RenderCopy	(systeme->renderer, ui->tdesignationstuff[index], NULL, &ui->pcasestuff[index]);
			}
		}
		for (index = 0 ; index < 7 ; index++)
		{
		/*si pointeur dans case stuff*/
			if (systeme->pp.x >= ui->pcasestuff[index].x
				&& systeme->pp.x <= ui->pcasestuff[index].x + ui->pcasestuff[index].w
				&& systeme->pp.y >= ui->pcasestuff[index].y
				&& systeme->pp.y <= ui->pcasestuff[index].y + ui->pcasestuff[index].h
				&& ui->casestuff[index].IDobjet != -1)
			{
				afficherDETAIL(inventaire, objet, systeme, ui->casestuff[index].IDobjet);
			}
		}
		/*bouton quitter*/
		switch(bouton->BoutonQuitter.etat)
		{
		case 1:
			SDL_RenderCopy	(systeme->renderer, bouton->BoutonQuitter.survoler, NULL, &bouton->BoutonQuitter.position);
			break;
		case 2:
			SDL_RenderCopy	(systeme->renderer, bouton->BoutonQuitter.cliquer, NULL, &bouton->BoutonQuitter.position);
			break;
		default:
			SDL_RenderCopy	(systeme->renderer, bouton->BoutonQuitter.normal, NULL, &bouton->BoutonQuitter.position);
			break;
		}
		/*lumieres*/
		if(enligne == false)	{SDL_RenderCopy(systeme->renderer, ui->lumiereoff, NULL, &ui->plumiere);}
		else	{SDL_RenderCopy(systeme->renderer, ui->lumiereon, NULL, &ui->plumiere);}
	}


/*dialogue*/
	if (ui->dialogueactif == 1)
	{
		SDL_RenderCopy	(systeme->renderer, ui->tdialogue, NULL, &ui->pdialogue);
		SDL_RenderCopy	(systeme->renderer, ui->ttextedialogue, NULL, &ui->ptextedialogue);
	}
	else if (ui->dialogueactif == 2)
	{
		SDL_RenderCopy	(systeme->renderer, systeme->BG, NULL, &recompense->pBGrecompense);
		SDL_RenderCopy	(systeme->renderer, recompense->tvictoire, NULL, &recompense->ptvictoire);
		SDL_RenderCopy	(systeme->renderer, recompense->ttexterecompensecombat, NULL, &recompense->ptrecompesecombat);
		calculposy = 0;
		for(index = 0 ; index < LOOTMAX ; index++)
		{
			if (recompense->recompenseNB[index] != 0)
			{
				recompense->precompensecombat.y = systeme->screenh*0.326 + (calculposy*(systeme->screenh*0.0651));
				SDL_RenderCopy	(systeme->renderer, recompense->ttextelootcombat[index], NULL, &recompense->precompensecombat);
				calculposy++;
			}
		}
	}
}

void afficherMAP(struct DIVERSmap *carte,struct DIVERSsysteme *systeme,struct DIVERScraft *craft)
{
	int index;

	for (index = 0 ; index < TILESMAP ; index++)
	{
		SDL_RenderCopy(systeme->renderer, carte->tilemap[index], NULL, &carte->pmap[index]);
	}

	SDL_RenderCopy(systeme->renderer, craft->tetabli, NULL, &craft->petabli);


	/*affichage de la grille de colision*/
    /*
	int i, j;
	SDL_Rect pos;
	pos.w = 50;
	pos.h = 50;
	for (i = 0; i < 400 ; i++)
	{
		for (j = 0 ; j < 400 ; j++)
		{
			pos.x = (j*25)-carte->pmx;
			pos.y = (i*25)-carte->pmy;
			if (carte->grille[i][j].value == 1)
			{
				SDL_RenderCopy(systeme->renderer, systeme->noir, NULL, &pos);
			}
		}
	}*/

}

void afficherPNJ(struct PERSO *perso,struct PACKpnj *pnj,struct DIVERSsysteme *systeme)
{
	SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->spriteup[0], &pnj->toumai, -90,NULL, SDL_FLIP_NONE);
	/*SDL_RenderCopyEx(systeme->renderer, perso->cheveuxblanc, NULL, &pnj->toumai, -90,NULL, SDL_FLIP_NONE);*/
}

void afficherMOB(struct PACKmonstre *monstre,struct DIVERSsysteme *systeme)
{
	int index;
	for (index = 0 ; index < 3 ; index++)
	{
		if (monstre->rat[index].etat == ALIVE)
		{
			SDL_RenderCopyEx(systeme->renderer, monstre->rat[index].texture[RAT_BLANC][monstre->rat[index].indexanim], NULL, &monstre->rat[index].position, monstre->rat[index].direction*45, NULL, SDL_FLIP_NONE);
		}
	}
}

void afficherJOUEURS(struct PERSO *perso,struct DIVERSdeplacement *deplacement,struct DIVERSsysteme *systeme,
                     struct typeFORthreads *online)
{
    int index, calcul;
	/*joueur client*/
	if (deplacement->direction.direction == -1)
	{
		calcul = 180+(45 * deplacement->direction.olddirection);
	}
	else
	{
		calcul = 180+(45 * deplacement->direction.direction);
	}

	SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->spriteup[deplacement->indexanimperso], &perso->pperso, calcul,NULL, SDL_FLIP_NONE);
	perso->ptpseudo.x = perso->pperso.x;
	perso->ptpseudo.y = perso->pperso.y - 33;
	SDL_RenderCopy(systeme->renderer, perso->tpseudo, NULL, &perso->ptpseudo);


	/*joueurs en ligne*/
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
			SDL_RenderCopyEx			(systeme->renderer, perso->tperso, &perso->spriteup[0], &online->joueurs[index].posjoueurscalculer, calcul,NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx			(systeme->renderer, perso->cheveuxbrun, NULL, &online->joueurs[index].posjoueurscalculer, calcul,NULL, SDL_FLIP_NONE);
			SDL_RenderCopy				(systeme->renderer, online->joueurs[index].tpseudo, NULL, &online->joueurs[index].ppseudo);
		}
	}
}

void afficherCHAT(struct DIVERSchat *chat,struct DIVERSui *ui, int lenbuffer,struct DIVERSsysteme *systeme)
{
	int index;
	SDL_RenderCopy	(systeme->renderer, chat->BGchat, NULL, &ui->pUIbas);
	for(index = 0; index < 10 ; index++)
	{
		SDL_QueryTexture(chat->tstringchat[index], NULL, NULL, &chat->pstringchat[index].w, NULL);
		SDL_RenderCopy	(systeme->renderer, chat->tstringchat[index], NULL, &chat->pstringchat[index]);
	}
	if (chat->saisiechat == 1)
	{
		SDL_RenderCopy	(systeme->renderer, chat->BGchatactif, NULL, &chat->pchatactif);
	}
	if (lenbuffer > 0)
	{
		SDL_QueryTexture(chat->tbufferchat, NULL, NULL, &chat->pbufferchat.w, NULL);
		SDL_RenderCopy	(systeme->renderer, chat->tbufferchat, NULL, &chat->pbufferchat);
	}
}

void afficherPOINTEUR(struct DIVERSsysteme *systeme,struct PACKobjet *objet)
{
	SDL_RenderCopy	(systeme->renderer, systeme->pointeur, NULL, &systeme->pp);
	if (objet->objetenmain.IDobjet != -1)
	{
		systeme->ppobj.x = systeme->pp.x + 15;
		systeme->ppobj.y = systeme->pp.y + 20;
		SDL_RenderCopy	(systeme->renderer, objet->objet[objet->objetenmain.IDobjet].texture, NULL, &systeme->ppobj);
	}

}

void afficherDETAIL(struct DIVERSinventaire *inventaire,struct PACKobjet *objet,struct DIVERSsysteme *systeme, int id)
{
    int largeurmax = 0;

	inventaire->pdetail.x = systeme->pp.x + 15;
	inventaire->pdetail.y = systeme->pp.y + 10;
	inventaire->pdetail.h = 60;

	largeurmax = objet->objet[id].LARGEURnom;

	if(largeurmax < inventaire->LARGEURaideclicdroit)/*clic droit*/
	{
		largeurmax = inventaire->LARGEURaideclicdroit;
	}
	if(objet->objet[id].type == 1)
	{
		inventaire->pdetail.h += 10;
		if(objet->objet[id].def > 0)/*def*/
		{
			if(largeurmax < objet->objet[id].LARGEURdef)
			{
				largeurmax = objet->objet[id].LARGEURdef;
			}
			inventaire->pdetail.h += 40;
		}
		if(objet->objet[id].life > 0)/*life*/
		{
			if(largeurmax < objet->objet[id].LARGEURlife)
			{
				largeurmax = objet->objet[id].LARGEURlife;
			}
			inventaire->pdetail.h += 40;
		}
		if(objet->objet[id].regenlife > 0)/*regenlife*/
		{
			if(largeurmax < objet->objet[id].LARGEURregenlife)
			{
				largeurmax = objet->objet[id].LARGEURregenlife;
			}
			inventaire->pdetail.h += 40;
		}
		if(objet->objet[id].force > 0)/*force*/
		{
			if(largeurmax < objet->objet[id].LARGEURforce)
			{
				largeurmax = objet->objet[id].LARGEURforce;
			}
			inventaire->pdetail.h += 40;
		}
		if(objet->objet[id].portee > 0)/*portee*/
		{
			if(largeurmax < objet->objet[id].LARGEURportee)
			{
				largeurmax = objet->objet[id].LARGEURportee;
			}
			inventaire->pdetail.h += 40;
		}
	}
	inventaire->pdetail.w = largeurmax;


/*ajustement bas ecran*/
	if (inventaire->pdetail.y + inventaire->pdetail.h > systeme->screenh)
	{
		inventaire->pdetail.y = systeme->screenh - inventaire->pdetail.h;
	}
/*ajustement droite ecran*/
	if (inventaire->pdetail.x + inventaire->pdetail.w > systeme->screenw)
	{
		inventaire->pdetail.x = systeme->screenw - inventaire->pdetail.w -20;
	}

/*affichage*/
	inventaire->pdetail.w += 20;
	SDL_RenderCopy	(systeme->renderer, systeme->BG, NULL, &inventaire->pdetail);/*BackGround*/

	inventaire->pdetail.x += 10;
	inventaire->pdetail.y += 5;
	inventaire->pdetail.h = 50;
	inventaire->pdetail.w = objet->objet[id].LARGEURnom;

	if(objet->objet[id].type == 1)
	{
		SDL_RenderCopy	(systeme->renderer, objet->objet[id].texturenom[2], NULL, &inventaire->pdetail);/*nom*/
		if (objet->objet[id].def > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.h = 40;
			inventaire->pdetail.w = objet->objet[id].LARGEURdef;
			SDL_RenderCopy	(systeme->renderer, objet->objet[id].texturedef, NULL, &inventaire->pdetail);/*defense*/
		}
		if (objet->objet[id].life > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.h = 40;
			inventaire->pdetail.w = objet->objet[id].LARGEURlife;
			SDL_RenderCopy	(systeme->renderer, objet->objet[id].texturelife, NULL, &inventaire->pdetail);/*life*/
		}
		if (objet->objet[id].regenlife > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.h = 40;
			inventaire->pdetail.w = objet->objet[id].LARGEURregenlife;
			SDL_RenderCopy	(systeme->renderer, objet->objet[id].textureregenlife, NULL, &inventaire->pdetail);/*regenlife*/
		}
		if (objet->objet[id].force > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.h = 40;
			inventaire->pdetail.w = objet->objet[id].LARGEURforce;
			SDL_RenderCopy	(systeme->renderer, objet->objet[id].textureforce, NULL, &inventaire->pdetail);/*force*/
		}
		if (objet->objet[id].portee > 0)
		{
			inventaire->pdetail.y += 40;
			inventaire->pdetail.h = 40;
			inventaire->pdetail.w = objet->objet[id].LARGEURportee;
			SDL_RenderCopy	(systeme->renderer, objet->objet[id].textureportee, NULL, &inventaire->pdetail);/*portee*/
		}
		inventaire->pdetail.y += 35;
		inventaire->pdetail.h = 30;
		inventaire->pdetail.w = inventaire->LARGEURaideclicdroit;
		SDL_RenderCopy	(systeme->renderer, inventaire->taideclicdroit, NULL, &inventaire->pdetail);/*aide clic droit*/
	}
	else
	{
		SDL_RenderCopy	(systeme->renderer, objet->objet[id].texturenom[0], NULL, &inventaire->pdetail);/*nom*/
	}
}

void TestCursorOnCorner(struct DIVERSui *ui, struct DIVERSsysteme *systeme)
{
    if (systeme->pp.x <= 5 && systeme->pp.y >= systeme->screenh-5)/*							down left corner*/
    {
        ui->OnLeftDown = true;
        ui->OnRightDown = false;
        ui->OnRightUp = false;
        ui->OnLeftUp = false;

        SDL_SetTextureAlphaMod(ui->Uichat,255);
        SDL_SetTextureAlphaMod(ui->uimenu,100);
        SDL_SetTextureAlphaMod(ui->Uiinventaire,100);
    }
    else if (systeme->pp.x >= systeme->screenw-5 && systeme->pp.y >= systeme->screenh-5)/*		down right corner*/
	{
	    ui->OnRightDown = true;
	    ui->OnLeftDown = false;
	    ui->OnRightUp = false;
	    ui->OnLeftUp = false;

	    SDL_SetTextureAlphaMod(ui->Uiinventaire,255);
	    SDL_SetTextureAlphaMod(ui->Uichat,100);
	    SDL_SetTextureAlphaMod(ui->uimenu,100);
	}
	else if (systeme->pp.x >= systeme->screenw-5 && systeme->pp.y <= 5)/*		             up right corner*/
	{
	    ui->OnRightUp = true;
	    ui->OnLeftDown = false;
	    ui->OnRightDown = false;
	    ui->OnLeftUp = false;
	}
	else if (systeme->pp.x <= 5 && systeme->pp.y <= 5)/*						                up left corner*/
	{
	    ui->OnLeftUp = true;
	    ui->OnRightUp = false;
	    ui->OnLeftDown = false;
	    ui->OnRightDown = false;

	    SDL_SetTextureAlphaMod(ui->uimenu,255);
	    SDL_SetTextureAlphaMod(ui->Uichat,100);
	    SDL_SetTextureAlphaMod(ui->Uiinventaire,100);
	}
	if (systeme->pp.x > 5 && systeme->pp.x < systeme->screenw-5 &&
        systeme->pp.y < systeme->screenh-5 && systeme->pp.y > 5)/*								no corner*/
	{
	    ui->OnRightUp = false;
	    ui->OnLeftDown = false;
	    ui->OnRightDown = false;
	    ui->OnLeftUp = false;

	    SDL_SetTextureAlphaMod(ui->uimenu,100);
	    SDL_SetTextureAlphaMod(ui->Uichat,100);
	    SDL_SetTextureAlphaMod(ui->Uiinventaire,100);
	}
}

int TimeOnCorner(struct DIVERSui *ui)
{
    int result = 0;
    ui->CornerTime = SDL_GetTicks();

    if(ui->OnLeftDown)
    {
        if (ui->PointedCorner == 3)
        {
            result = ui->CornerTime - ui->OldCornerTime;
            return result;
        }
        else
        {
            ui->PointedCorner = 3;
            ui->OldCornerTime = ui->CornerTime;
        }
    }
    else if (ui->OnLeftUp)
    {
        if (ui->PointedCorner == 1)
        {
            result = ui->CornerTime - ui->OldCornerTime;
            return result;
        }
        else
        {
            ui->PointedCorner = 1;
            ui->OldCornerTime = ui->CornerTime;
        }
    }
    else if (ui->OnRightDown)
    {
        if (ui->PointedCorner == 4)
        {
            result = ui->CornerTime - ui->OldCornerTime;
            return result;
        }
        else
        {
            ui->PointedCorner = 4;
            ui->OldCornerTime = ui->CornerTime;
        }
    }
    else if (ui->OnRightUp)
    {

    }

    return 0;
}
