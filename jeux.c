#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <math.h>

#include "rat.h"
#include "tir.h"
#include "jeux.h"
#include "evenement.h"
#include "main.h"
#include "image.h"
#include "tableau.h"
#include "ia.h"
#include "deplacement.h"
#include "colision.h"
#include "systeme.h"
#include "tool.h"
#include "CaC.h"
#include "ui.h"
#include "battledraw.h"
#include "queue.h"

extern int screenh, screenw;

float combat (float vie,struct PACKmonstre *monstre,struct DIVERSsysteme *systeme,struct PERSO *perso,
              struct PACKrecompense *recompense,struct PACKobjet *objet,
              struct DIVERSui *ui, bool arcademode)
{
	#if BATTLE_LOG == 1
	printf("battle is starting ...\n");
	#endif

	/*structure contenant toutes les variables pour les combats*/
	struct typecombat BTLstr;
	struct DIRECTION direction;

	int index, fps = 0;
	int ret, ret2;
	#if BATTLE_LOG == 1
	printf("memory is allocated\n");
	#endif

	/*initialisation des variables*/
	initcombatstore(&BTLstr, systeme, &direction , monstre);
	/*finding who we are fighting*/

	BTLstr.IndexCreature = FindCreatureEngaged(monstre);
	if (BTLstr.IndexCreature == -1 && arcademode == false)	{	return -1; printf("no creature founded\n");	} /*if creature not found*/
	else if ( arcademode == true) { BTLstr.IndexCreature = 1;	}	/*if arcademode*/
	#if BATTLE_LOG == 1
	printf("figthing creature : %d\n", BTLstr.IndexCreature);
	#endif
	if (arcademode == true)
	{
		BTLstr.ptVie.h = screenh*0.2;
		BTLstr.ptVie.w = screenw*0.6;
		perso->life = 100;/* should be 100*/
	}
	else
	{
		perso->life = vie;
	}
	#if BATTLE_LOG == 1
	printf("loop is beginning : player's life : %f\n", perso->life);
	#endif
	while (BTLstr.continuer == -1)
	{
	    #if BATTLE_LOG == 1
        printf("loop\n");
        #endif
		BTLstr.temps = SDL_GetTicks();

		/*calcul ~120/sec*/
		if (BTLstr.temps - BTLstr.tempscalcul >= 8)
		{
		    #if BATTLE_LOG == 1
            printf("calcul...\n");
            #endif
			BTLstr.tempscalcul = BTLstr.temps;

			/*gestion des événements*/
			BTLstr.continuer = boucleeventcombat (&BTLstr, systeme, &direction, ui);
			/*calcul direction joueur*/
			direction.direction = directionperso(&direction);
			/*deplacement*/
			deplacementperso_combat(perso, &direction);
			/*recording mouse position*/
			SDL_GetMouseState(&BTLstr.curseur.pos.x, &BTLstr.curseur.pos.y);
            BTLstr.curseur.pos.y = (BTLstr.curseur.pos.y - screenh + BTLstr.curseur.pos.h) * -1;

			/*actualisation des coordonées*/
			SyncData(&BTLstr, perso);

			/*gestion des attaques*/
			COMBATgestionCLICetCOLISION (&BTLstr, ui);

			/*gestion des projectiles*/
			if (ui->casestuff[ARME].IDobjet == 3)
            {
                COMBATgestionprojectile(&BTLstr);
            }

			/*gestion des ennemis*/
			#if ARRET_MOB == 0
			COMBATgestionENNEMI(&BTLstr, monstre->mob, systeme);
			#endif /* ARRET_MOB*/

			/*gestion des objets au sol*/
			COMBATgestionOBJETsol(&BTLstr, systeme, recompense, perso);
			/*animations*/
			COMBATanimationOBJET(&BTLstr);
		}

		/*affichage ~60/sec*/
		if (BTLstr.temps - BTLstr.tempsaffichage >= 0)/*16*/
		{
		    #if BATTLE_LOG == 1
            printf("displaying...\n");
            #endif
			fps++;
			BTLstr.tempsaffichage = BTLstr.temps;
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
			afficherCOMBAT(&BTLstr, systeme, perso, ui, objet, arcademode);
            #if BATTLE_LOG_DISPLAY == 1
            printf("rendering...");
             printf("SDL_Init failed: %s\n", SDL_GetError());
            #endif
			glFlush();
            SDL_GL_SwapWindow(systeme->screen);
			#if BATTLE_LOG == 1
            printf("rendu d'affichage\n");
            #endif
		}

		else if (BTLstr.temps - BTLstr.tempsseconde >= 1000)/*1000*/
		{
		    #if BATTLE_LOG == 1
            printf("fps...\n");
            #endif
			if (arcademode == true)
			{
				sprintf(BTLstr.StringVie, "fps : %d       ennemi en vie : %d         ennemi vaincu : %d         score : %d", fps, BTLstr.alive, BTLstr.ennemivaincue, BTLstr.arcadescore);/*fps*/
			}
			else
			{
				sprintf(BTLstr.StringVie, "fps : %d", fps);
			}
			BTLstr.tVie = DrawSDLText(&BTLstr.ptVie, BTLstr.StringVie, NOIR, ALIGN_LEFT, systeme);
			fps = 0;
			BTLstr.tempsseconde = BTLstr.temps;

			/*counting creature*/
			BTLstr.alive = 0;
			for(index = 0 ; index < LIMITEmobARCADE ; index++)
			{
				if (BTLstr.creature[index].isdead == false)
				{
					BTLstr.alive += 1;
				}
			}
			/*if player dead*/
			if (perso->life  <= 0 && arcademode == true)
			{
				#if BATTLE_LOG == 1
				printf("player is dead\n");
				#endif
				JoueurMort(&BTLstr, systeme, ui, perso, objet, arcademode);
			}
			else if (perso->life <= 0)
			{
				#if BATTLE_LOG == 1
				printf("player is dead\n");
				#endif
				BTLstr.continuer = BTL_LOST;
			}
		}

		/*adding creature ~1.25/sec*/
		if (BTLstr.temps - BTLstr.TimeAddEnnemy >= 1250)
		{
		    #if BATTLE_LOG == 1
			printf("adding creature\n");
			#endif
			BTLstr.TimeAddEnnemy = BTLstr.temps;

			ret2 = Read_Creature_Queue(&monstre->mob[BTLstr.IndexCreature].queue);
			switch (ret2)
			{
				case RAT_BLANC:
					ret = FindCreatureMemoryArea(&BTLstr);
					if (ret != -1)
					{
						ADD_Rat(RAT_BLANC, ret, &BTLstr, systeme, monstre->mob);
						Free_Queue_Element(&monstre->rat[BTLstr.IndexCreature].queue);
					}
					break;
				case RAT_VERT:
					ret = FindCreatureMemoryArea(&BTLstr);
					if (ret != -1)
					{
						ADD_Rat(RAT_VERT, ret, &BTLstr, systeme, monstre->rat);
						Free_Queue_Element(&monstre->rat[BTLstr.IndexCreature].queue);
					}
					break;
				case RAT_JAUNE:
					ret = FindCreatureMemoryArea(&BTLstr);
					if (ret != -1)
					{
						ADD_Rat(RAT_JAUNE, ret, &BTLstr, systeme, monstre->rat);
						Free_Queue_Element(&monstre->rat[BTLstr.IndexCreature].queue);
					}
					break;
				case RAT_ORANGE:
					ret = FindCreatureMemoryArea(&BTLstr);
					if (ret != -1)
					{
						ADD_Rat(RAT_ORANGE, ret, &BTLstr, systeme, monstre->rat);
						Free_Queue_Element(&monstre->rat[BTLstr.IndexCreature].queue);
					}
					break;
				case RAT_ROUGE:
					ret = FindCreatureMemoryArea(&BTLstr);
					if (ret != -1)
					{
						ADD_Rat(RAT_ROUGE, ret, &BTLstr, systeme, monstre->rat);
						Free_Queue_Element(&monstre->rat[BTLstr.IndexCreature].queue);
					}
					break;
				case -1:  /*out of queue*/
					if (arcademode == true && BTLstr.IndexCreature < 3)
					{
						BTLstr.IndexCreature++;
					}
					break;
				default:
					break;
			}
		}
	}
	return BTLstr.continuer;
}

int FindCreatureMemoryArea(struct typecombat *BTLstr)
{
    #if BATTLE_LOG == 1
    printf("searching free space for creature\n");
    #endif
	int index;

	for(index = 0 ; index < LIMITEmobARCADE ; index++)
	{
		if (BTLstr->creature[index].iserasable == true)
		{
			#if BATTLE_LOG == 1
			printf("adding creature number :%d\n", index);
			#endif
			return index;
		}
	}

	return -1;
}

void afficherCOMBAT(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct PERSO *perso,
					struct DIVERSui *ui,struct PACKobjet *objet, bool arcademode)
{
    #if BATTLE_LOG_DISPLAY == 1
    printf("affichage du fond\n");
    #endif

	draw_pict(&BTLstr->fond);

    #if BATTLE_LOG_DISPLAY == 1
    printf("affichage des loot au sol\n");
    #endif

	if (arcademode == false)
	{
	    BattleDraw_FloorItems(BTLstr, objet);
	}

	#if BATTLE_LOG_DISPLAY == 1
    printf("affichage des ennemis\n");
    #endif

    BattleDraw_Ennemy(BTLstr, arcademode);

    #if BATTLE_LOG_DISPLAY == 1
    printf("affichage du texte\n");
    #endif

	//SDL_RenderCopy(systeme->renderer, BTLstr->tVie, NULL, &BTLstr->ptVie);

    #if BATTLE_LOG_DISPLAY == 1
    printf("affichage du joueur\n");
    #endif

    BattleDraw_Player(BTLstr, perso, systeme);

	#if BATTLE_LOG_DISPLAY == 1
    printf("affichage des projectiles\n");
    #endif

    BattleDraw_Projectile(BTLstr);

	#if TESTGRID == 1
	DrawTestGrid(BTLstr, systeme);/*not working ! (because of the big array)*/
    #endif /* TESTGRID*/

    #if BATTLE_LOG_DISPLAY == 1
    printf("affichage de l'UI\n");
    #endif

    draw_pict(&BTLstr->curseur);
}

void Hitboxjoueur (struct typecombat *BTLstr,struct PERSO *perso, int id)
{
	if (BTLstr->premiercoup[id] == 0)
	{
		if (DEGATsubitCHOC >= perso->defense/2)
		{
			perso->life -= ((DEGATsubitCHOC)-(perso->defense/2));
		}
	}
	else
	{
		if (DEGATsubitDUREE >= perso->defense/100)
		{
			perso->life -= (DEGATsubitDUREE-(perso->defense/100));
		}
	}
	BTLstr->premiercoup[id] = 1;
}

void COMBATgestionCLICetCOLISION (struct typecombat *BTLstr,struct DIVERSui *ui)
{
    if (BTLstr->letirdemander == true && ui->casestuff[ARME].IDobjet == 3)
    {
        gestiontir(BTLstr);
        COMBATgestionprojectile(BTLstr);
    }
    COMBATgestionDEGAT(BTLstr, ui);
}

void COMBATgestionDEGAT (struct typecombat *BTLstr,struct DIVERSui *ui)
{
	int index, index2;

	for (index = 0; index < LIMITEmobARCADE ; index++)
	{
		if(BTLstr->creature[index].life > 0)
		{
		    BTLstr->ResultatHitbox = -1;/*initialisation*/

		    /*décision dégat lancepierre*/
		    if (ui->casestuff[ARME].IDobjet == 3 ||
                ui->casestuff[ARME].IDobjet == 13)
            {
                    BTLstr->ResultatHitbox = HitboxBalle(BTLstr, index);
            }
            /*décision dégat mains nue*/
            else if (ui->casestuff[ARME].IDobjet == -1)
            {
                    BTLstr->ResultatHitbox = HitboxPoing(BTLstr, index);
            }

			/*si dégat infligé*/
			if (BTLstr->ResultatHitbox != -1)
			{
				for (index2 = BTLstr->i[BTLstr->ResultatHitbox] ; index2 < 768 ; index2++ )
				{
					BTLstr->tx[BTLstr->ResultatHitbox][index2] = -100;
				}
				BTLstr->DepartBalle[BTLstr->ResultatHitbox] = UNUSED; /* pour projectile*/

				Hit_Creature(index, BTLstr);
			}
		}
	}
	BTLstr->letirdemander = false;
}

void COMBATanimationOBJET(struct typecombat *BTLstr)
{
	if (BTLstr->temps - BTLstr->tempsanimationobjet >= 20)
	{
		BTLstr->tempsanimationobjet = BTLstr->temps;

		if(BTLstr->animobjetway == 0)
		{
			BTLstr->animobjet -= 0.05;
		}
		else
		{
			BTLstr->animobjet += 0.05;
		}

		if(BTLstr->animobjet > 1.4)
		{
			BTLstr->animobjetway = 0;
		}
		else if(BTLstr->animobjet < 0.6)
		{
			BTLstr->animobjetway = 1;
		}
	}
}

void COMBATgestionENNEMI(struct typecombat *BTLstr, struct RAT *rat,struct DIVERSsysteme *systeme)
{
	int index;


	for (index = 0 ; index < LIMITEmobARCADE ; index++)
	{
		if (BTLstr->creature[index].isdead == false)
		{
			BTLstr->creature[index].Direction = MouvemementChauveSouris(BTLstr, rat, systeme, index);
		}
	}
}

void ADDloot(struct PACKrecompense *recompense, int id, int nombre)
{
	int index = 0;
	/*recherche d'un objet equivalent ou d'une case vide*/
	while(index < NOMBREOBJETS)
	{
		if (recompense->recompenseID[index] == -1)	{break;}
		else if (recompense->recompenseID[index] == id)	{break;}
		else
		{
			index++;
			if (index > NOMBREOBJETS)	{return;}
		}
	}

	/*adding to loot*/
	recompense->recompenseID[index] = id;
	recompense->recompenseNB[index] += nombre;
}

void COMBATgestionOBJETsol(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct PACKrecompense *recompense,struct PERSO *perso)
{
	int index;
	float difx = 0, dify = 0;

	for (index = 0 ; index < LIMITEmobARCADE ; index++)
	{
		/*s'il est vivant*/
		if (BTLstr->creature[index].isdead == false)
		{
			if (checkdistance(&BTLstr->Pperso, &BTLstr->creature[index].m_pict.pict.pos, 50) == -1)
			{
				Hitboxjoueur (BTLstr, perso, index);
			}
			else
			{
				BTLstr->premiercoup[index] = 0;
			}
		}
		else if (BTLstr->creature[index].ontheway == 0)
		{
			/*si on marche dessus*/
			if (colisionbox(&BTLstr->creature[index].m_pict.pict.pos, &BTLstr->Pperso, false))
			{
				#if BATTLE_LOG == 1
				printf("looting creature number : %d\n", index);
				#endif

				BTLstr->arcadescore += 10;

				/*ajout aux récompenses*/
				ADDloot(recompense, 0, 1);

				/*objet en cour de deplacement*/
				BTLstr->creature[index].ontheway = 1;

				/*calcul des différences*/
				difx = screenw - BTLstr->creature[index].m_pict.pict.pos.x;
				dify = screenh - BTLstr->creature[index].m_pict.pict.pos.y;

				/*enregistrement des positions initiales*/
				BTLstr->creature[index].oldposx = BTLstr->creature[index].m_pict.pict.pos.x;
				BTLstr->creature[index].oldposy = BTLstr->creature[index].m_pict.pict.pos.y;

				if (dify > difx)
				{
					BTLstr->creature[index].dx = (difx/dify)*3;
					BTLstr->creature[index].dy = 3;
				}
				else if (difx > dify)
				{
					BTLstr->creature[index].dx = 3;
					BTLstr->creature[index].dy = (dify/difx)*3;
				}
				else
				{
					BTLstr->creature[index].dx = 3;
					BTLstr->creature[index].dy = 3;
				}
			}
		}
		else if (BTLstr->creature[index].ontheway == 1 && BTLstr->creature[index].m_pict.pict.pos.x < screenw)
		{
			BTLstr->creature[index].wayx += BTLstr->creature[index].dx;
			BTLstr->creature[index].wayy += BTLstr->creature[index].dy;

			BTLstr->creature[index].m_pict.pict.pos.x = BTLstr->creature[index].oldposx + (int)BTLstr->creature[index].wayx;
			BTLstr->creature[index].m_pict.pict.pos.y = BTLstr->creature[index].oldposy + (int)BTLstr->creature[index].wayy;
		}
		else if (BTLstr->creature[index].ontheway == 1 && BTLstr->creature[index].m_pict.pict.pos.x > screenw)
		{
			BTLstr->creature[index].ontheway = 0;
			BTLstr->creature[index].looted = true;
			BTLstr->creature[index].iserasable = true;
		}
	}

	/*parcour des objets*/
	for (index = 0 ; index < BTLstr->NBlootsol ; index++)
	{
		/*si l'objet est déjà en mouvement*/
		if (BTLstr->lootsol[index] == BTL_OBJ_MOVE && BTLstr->plootsol[index].x < screenw)
		{
			BTLstr->lootsolWAYX[index] += BTLstr->lootsolDX[index];
			BTLstr->lootsolWAYY[index] += BTLstr->lootsolDY[index];

			BTLstr->plootsol[index].x = BTLstr->oldplootsol[index].x + (int)BTLstr->lootsolWAYX[index];
			BTLstr->plootsol[index].y = BTLstr->oldplootsol[index].y + (int)BTLstr->lootsolWAYY[index];
		}

		/*si il est a terre et que le joueur marche dessus*/
		else if (BTLstr->lootsol[index] == BTL_OBJ_FLOOR &&
				colisionbox(&BTLstr->plootsol[index], &BTLstr->Pperso, false))
		{
			/*ajout aux récompenses*/
			ADDloot(recompense, BTLstr->IDlootsol[index], 1);

			/*objet en cour de deplacement*/
			BTLstr->lootsol[index] = BTL_OBJ_MOVE;

			/*calcul des différences*/
			difx = screenw - BTLstr->plootsol[index].x;
			dify = screenh - BTLstr->plootsol[index].y;

			/*enregistrement des positions initiales*/
			BTLstr->oldplootsol[index].x = BTLstr->plootsol[index].x;
			BTLstr->oldplootsol[index].y = BTLstr->plootsol[index].y;

			if (dify > difx)
			{
				BTLstr->lootsolDX[index] = (difx/dify)*3;
				BTLstr->lootsolDY[index] = 3;
			}
			else if (difx > dify)
			{
				BTLstr->lootsolDX[index] = 3;
				BTLstr->lootsolDY[index] = (dify/difx)*3;
			}
			else
			{
				BTLstr->lootsolDX[index] = 3;
				BTLstr->lootsolDY[index] = 3;
			}
		}
	}
}

void SyncData(struct typecombat *BTLstr,struct PERSO *perso)
{
	int index;
	BTLstr->Pperso.x = perso->perso.pict.pos.x;
	BTLstr->Pperso.y = perso->perso.pict.pos.y;
	BTLstr->canonx = BTLstr->Pperso.x + (BTLstr->Pperso.w/2);
	BTLstr->canony = BTLstr->Pperso.y + (BTLstr->Pperso.h/2);

	perso->BarreDeVie->position.x = BTLstr->Pperso.x;
	perso->BarreDeVie->position.y = BTLstr->Pperso.y -20;
	perso->BarreDeVie->position.w = CalculerBarreDeVie(perso->lifemax, perso->life, BTLstr->Pperso.w);
	perso->BarreDeVie->BGposition.x = perso->BarreDeVie->position.x - 1;
	perso->BarreDeVie->BGposition.y = perso->BarreDeVie->position.y - 1;

	for(index = 0 ; index < LIMITEmobARCADE ; index++)
	{
		if (BTLstr->creature[index].isdead == false)
		{
		BTLstr->creature[index].BarreDeVie->position.x = BTLstr->creature[index].m_pict.pict.pos.x;
		BTLstr->creature[index].BarreDeVie->position.y = BTLstr->creature[index].m_pict.pict.pos.y -20;
		BTLstr->creature[index].BarreDeVie->position.w = CalculerBarreDeVie(BTLstr->creature[index].lifemax,
						BTLstr->creature[index].life, BTLstr->creature[index].m_pict.pict.pos.w);
		BTLstr->creature[index].BarreDeVie->BGposition.x = BTLstr->creature[index].BarreDeVie->position.x - 1;
		BTLstr->creature[index].BarreDeVie->BGposition.y = BTLstr->creature[index].BarreDeVie->position.y - 1;
		}
	}
}

int CalculerBarreDeVie(int VieDeBase, int VieActuelle, int width)
{
	return ((float)width / (float)VieDeBase) * (float)VieActuelle;
}

void JoueurMort(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct DIVERSui *ui,struct PERSO *perso,
				struct PACKobjet *objet, bool arcademode)
{
	SDL_Event event;
	char score[64][20];
	SDL_Texture *texture[64];
	SDL_Rect position[64];
	int continuer = 0;
	int ret = -1;

	/*setting background*/
	//texture[0] = fenetredialogue(systeme->pecran.w/3, systeme->pecran.h*0.911, &position[0], NULL, NULL, BLANC, systeme);
	ui->dialogueactif = 1;

	/*setting up all texts*/
	ret = PositionOfDeathDisplay(texture, position, score, systeme);
	while (continuer == 0)
	{
		continuer = LoopEventBattleDeath (BTLstr, &event);
		/*recording mouse position*/
		SDL_GetMouseState(&BTLstr->curseur.pos.x, &BTLstr->curseur.pos.y);

		afficherCOMBAT(BTLstr, systeme, perso, ui, objet, arcademode);
		DrawDeathDisplay(BTLstr, systeme, texture, position, ret);
		//SDL_RenderCopy(systeme->renderer, BTLstr->curseur, NULL, &BTLstr->pcurseur);
		glFlush();
        SDL_GL_SwapWindow(systeme->screen);

		SDL_Delay(16);
	}
}

void DrawDeathDisplay(struct typecombat *BTLstr,struct DIVERSsysteme *systeme, SDL_Texture *texture[], SDL_Rect position[], int ret)
{
	int index;

	/*rendering Background and texts*/
	//SDL_RenderCopy(systeme->renderer, systeme->BG, NULL, &position[0]);
	for(index = 1 ; index <= ret ; index++)
	{
		//SDL_RenderCopy(systeme->renderer, texture[index], NULL, &position[index]);
	}

	/*rendering button "play again"*/
	if (BTLstr->rejouer.etat == B_SURVOLER)
	{	//SDL_RenderCopy(systeme->renderer, BTLstr->rejouer.survoler, NULL, &BTLstr->rejouer.position);
	}
	else if (BTLstr->rejouer.etat == B_CLIQUER)
	{	//SDL_RenderCopy(systeme->renderer, BTLstr->rejouer.cliquer, NULL, &BTLstr->rejouer.position);
	}
	else
	{	//SDL_RenderCopy(systeme->renderer, BTLstr->rejouer.normal, NULL, &BTLstr->rejouer.position);
	}
	/*rendering button "quit"*/
	if (BTLstr->quitter.etat == B_SURVOLER)
	{	//SDL_RenderCopy(systeme->renderer, BTLstr->quitter.survoler, NULL, &BTLstr->quitter.position);
	}
	else if (BTLstr->quitter.etat == B_CLIQUER)
	{	//SDL_RenderCopy(systeme->renderer, BTLstr->quitter.cliquer, NULL, &BTLstr->quitter.position);
	}
	else
	{	//SDL_RenderCopy(systeme->renderer, BTLstr->quitter.normal, NULL, &BTLstr->quitter.position);
	}
}

int PositionOfDeathDisplay(SDL_Texture *texture[], SDL_Rect position[], char score[][20],
                            struct DIVERSsysteme *systeme)
{
	int PosUsed = 0;

	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; /*50*PosUsed*/
	sprintf(score[PosUsed],"1: 3000");
	texture[PosUsed] = DrawSDLText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);

	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; /*50*PosUsed*/
	sprintf(score[PosUsed],"2: 1200");
	texture[PosUsed] = DrawSDLText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);

	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; /*50*PosUsed*/
	sprintf(score[PosUsed],"3: 990");
	texture[PosUsed] = DrawSDLText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);

	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; /*50*PosUsed*/
	sprintf(score[PosUsed],"4: 460");
	texture[PosUsed] = DrawSDLText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);

	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; /*50*PosUsed*/
	sprintf(score[PosUsed],"5: 75");
	texture[PosUsed] = DrawSDLText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);

	return PosUsed;
}

void Hit_Creature(int index,struct typecombat *BTLstr)
{
	BTLstr->creature[index].life -= 10;
	if (BTLstr->creature[index].life <= 0)
	{
		BTLstr->creature[index].isdead = true;
		BTLstr->creature[index].m_pict.current = 2;
		BTLstr->arcadescore += 5;
		#if BATTLE_LOG == 1
		printf("creature number %d is dead\n", index);
		#endif
	}
}

int FindCreatureEngaged(struct PACKmonstre *monstre)
{
	int index;

	for (index = 0 ; index < 3 ; index ++)
	{
		if (monstre->rat[index].Engaged == true)
		{
			return index;
		}
	}
	return -1;
}

int FindCreatureID(struct PACKmonstre *monstre, int ID)
{
	int index;

	for (index = 0 ; index < 3 ; index ++)
	{
		if (monstre->rat[index].ID == ID)
		{
			return index;
		}
	}
	return -1;
}
