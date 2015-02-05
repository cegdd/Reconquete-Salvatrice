#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <math.h>

#include "rat.h"
#include "evenement.h"
#include "tir.h"
#include "jeux.h"
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

float combat (float vie, struct RAT *rat, struct DIVERSsysteme *systeme, PERSO *perso, DIVERSinventaire *inventaire,
              PACKrecompense *recompense, PACKobjet *objet, DIVERSui *ui, bool arcademode)
{
	//structure contenant toutes les variables pour les combats
	typecombat BTLstr;
	DIRECTION direction;
	
	int index, fps = 0;
	
	//initialisation des variables
	initcombatstore(&BTLstr, systeme, &direction, arcademode);
	
	if (arcademode == true)
	{
		BTLstr.ptVie.h = systeme->screenh*0.2;
		BTLstr.ptVie.w = systeme->screenw*0.6;
		perso->life = 100;// should be 100
	}
	else
	{
		perso->life = vie;
	}

	while (BTLstr.continuer == -1)
	{
		BTLstr.temps = SDL_GetTicks();

		//calcul ~120/sec
		if (BTLstr.temps - BTLstr.tempscalcul >= 8)
		{
			BTLstr.tempscalcul = BTLstr.temps;

			//gestion des événements
			BTLstr.continuer = boucleeventcombat (&BTLstr, systeme, &direction, ui);
			//calcul direction joueur
			direction.direction = directionperso(&direction);
			//deplacement
			deplacementperso(NULL, perso, &direction, systeme, &BTLstr.Pperso.x, &BTLstr.Pperso.y, 0);
			//recupération coordonées souris
			SDL_GetMouseState(&BTLstr.px, &BTLstr.py);

			//actualisation des coordonées
			SyncData(&BTLstr, perso);
			
			//gestion des attaques
			COMBATgestionCLICetCOLISION (&BTLstr, ui);

			//gestion des projectiles
			if (ui->casestuff[ARME].IDobjet == 3)
            {
                COMBATgestionprojectile(&BTLstr);
            }

			//gestion des ennemis
			#if ARRET_MOB == 0
			COMBATgestionENNEMI(&BTLstr, rat, systeme);
			#endif // ARRET_MOB

			//gestion des objets au sol
			COMBATgestionOBJETsol(&BTLstr, systeme, recompense, arcademode, ui, perso);
			//animations
			COMBATanimationPERSO(&BTLstr);
			COMBATanimationMOB	(&BTLstr);
			COMBATanimationOBJET(&BTLstr);
		}


		//affichage ~60/sec
		if (BTLstr.temps - BTLstr.tempsaffichage >= 16)//16
		{
			fps++;
			BTLstr.tempsaffichage = BTLstr.temps;
			afficherCOMBAT(&BTLstr, systeme, perso, rat, inventaire, objet, arcademode);
		}
		
		else if (BTLstr.temps - BTLstr.tempsseconde >= 1000)//1000
		{
			if (arcademode == true)
			{
				sprintf(BTLstr.StringVie, "fps : %d       ennemi en vie : %d         ennemi vaincu : %d         score : %d", fps, BTLstr.alive, BTLstr.ennemivaincue, BTLstr.arcadescore);//fps
			}
			else
			{
				sprintf(BTLstr.StringVie, "fps : %d", fps);
			}
			BTLstr.tVie = DrawText(&BTLstr.ptVie, BTLstr.StringVie, NOIR, ALIGN_LEFT, systeme);
			fps = 0;
			BTLstr.tempsseconde = BTLstr.temps;

			//counting creature
			BTLstr.alive = 0;
			for(index = 0 ; index < BTLstr.NBennemi ; index++)
			{
				if (BTLstr.creature[index].isdead == false)
				{
					BTLstr.alive += 1;
				}
			}
			//if player dead
			if (perso->life  <= 0 && arcademode == true) { JoueurMort(&BTLstr, systeme, ui);}
			else if (perso->life <= 0) {BTLstr.continuer = BTL_LOST;}
		}
		//adding creature ~60/sec
		if (BTLstr.temps - BTLstr.TimeAddEnnemy >= 64)//64
		{
			
			
			BTLstr.TimeAddEnnemy = BTLstr.temps;
			if ( arcademode == true)
			{
				int ret = FindCreatureMemoryArea(&BTLstr);
				if (ret != -1)
				{
					int ret2 = Read_Creature_Queue(&BTLstr.CreatureQueue);
					printf("%d\n",ret2);
					switch (ret2)
					{
						case RAT_BLANC:
							BTLstr.NBennemi++;
							ADD_Rat(RAT_BLANC, ret, &BTLstr, systeme, rat);
							break;
						case RAT_VERT:
							BTLstr.NBennemi++;
							ADD_Rat(RAT_VERT, ret, &BTLstr, systeme, rat);
							break;
						case RAT_JAUNE:
							BTLstr.NBennemi++;
							ADD_Rat(RAT_JAUNE, ret, &BTLstr, systeme, rat);
							break;
						case RAT_ORANGE:
							BTLstr.NBennemi++;
							ADD_Rat(RAT_ORANGE, ret, &BTLstr, systeme, rat);
							break;
						case RAT_ROUGE:
							BTLstr.NBennemi++;
							ADD_Rat(RAT_ROUGE, ret, &BTLstr, systeme, rat);
							break;
						default:
							break;
					}
				}
			}
		}
	}

	//si il fui
	if (BTLstr.continuer == BTL_LEAVED)
	{
		return BTL_LEAVED;
	}
	else if (BTLstr.continuer == BTL_WON)
	{
		return BTL_WON;
	}
	else
    {
        return BTL_LOST;
    }
}

int FindCreatureMemoryArea(typecombat *BTLstr)
{
	int index;

	for(index = 0 ; index < LIMITEmobARCADE ; index++)
	{
		if (BTLstr->creature[index].isdead == true)
		{
			return index;
		}
	}
	
	return -1;
}

void afficherCOMBAT(typecombat *BTLstr, DIVERSsysteme *systeme, PERSO *perso, 
					RAT *rat, DIVERSinventaire *inventaire, PACKobjet *objet, 
					bool arcademode)
{
	int calcul, index;

	SDL_RenderClear(systeme->renderer);

	SDL_RenderCopy(systeme->renderer, BTLstr->fond, NULL, &BTLstr->pecran);

	//loot au sol
	if (arcademode == false)
	{
		for (index = 0; index < BTLstr->NBlootsol ; index++)
		{
			if (BTLstr->lootsol[index] != BTL_OBJ_FLOOR)
			{
				BTLstr->plootsol[index].w = BTLstr->oldplootsol[index].w * BTLstr->animobjet;
				BTLstr->plootsol[index].h = BTLstr->oldplootsol[index].h * BTLstr->animobjet;
			}
			SDL_RenderCopy(systeme->renderer, objet->objet[BTLstr->IDlootsol[index]].texture, NULL, &BTLstr->plootsol[index]);
		}
	}
	//ennemi
	for (index = 0; index < BTLstr->NBennemi ; index++)
	{
		//looted stuff
		if (BTLstr->creature[index].ontheway != 0 && BTLstr->creature[index].position.x < systeme->screenw)
		{
			BTLstr->creature[index].position.w = BTLstr->creature[index].STATICposition.w * BTLstr->animobjet;
			BTLstr->creature[index].position.h = BTLstr->creature[index].STATICposition.h * BTLstr->animobjet;
			if (arcademode == false)
			{	SDL_RenderCopy(systeme->renderer, BTLstr->peau, NULL, &BTLstr->creature[index].position);}
			else
			{	SDL_RenderCopy(systeme->renderer, BTLstr->piece, NULL, &BTLstr->creature[index].position);}
		}
		//si elles sont mortes et pas ramasser
		else if (BTLstr->creature[index].isdead == true && BTLstr->creature[index].looted == 0)
		{
			if (arcademode == false)
			{
				calcul =90+(45 * BTLstr->creature[index].Direction);
				SDL_RenderCopyEx(systeme->renderer,rat->texture[RAT_BLANC][2], NULL, &BTLstr->creature[index].position, calcul,NULL, SDL_FLIP_NONE);
			}
			else
			{	
				BTLstr->creature[index].position.w = 50;
				BTLstr->creature[index].position.h = 50;
				SDL_RenderCopy(systeme->renderer,BTLstr->piece, NULL, &BTLstr->creature[index].position);
			}
		}
		else if(BTLstr->creature[index].isdead == false)//if they're alive
		{
			calcul =90+(45 * BTLstr->creature[index].Direction);
			SDL_RenderCopyEx(systeme->renderer, BTLstr->creature[index].texture[BTLstr->creature[index].indexanim], NULL, &BTLstr->creature[index].position, calcul,NULL, SDL_FLIP_NONE);
		}
	}
	//text on top of the screen
	SDL_RenderCopy(systeme->renderer, BTLstr->tVie, NULL, &BTLstr->ptVie);

	//player

	double degre = FindAngle(&BTLstr->Pperso, &BTLstr->pcurseur) + 90; // finding angle

	if (BTLstr->poing_tendu == true)
    {
        SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->pperso_poing, &BTLstr->Pperso, degre, &perso->centrecorp, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyEx(systeme->renderer, perso->tperso, &perso->spriteup[BTLstr->indexanimperso], &BTLstr->Pperso, degre,NULL, SDL_FLIP_NONE);
    }
    //barre de vie
    SDL_RenderCopy(systeme->renderer, perso->BarreDeVie->BGtexture, NULL, &perso->BarreDeVie->BGposition);
    SDL_RenderCopy(systeme->renderer, perso->BarreDeVie->texture, NULL, &perso->BarreDeVie->position);
    for (index = 0 ; index < BTLstr->NBennemi ; index++)
    {
		if (BTLstr->creature[index].isdead == false && BTLstr->creature[index].life < BTLstr->creature[index].lifemax)
		{
			SDL_RenderCopy(systeme->renderer, BTLstr->creature[index].BarreDeVie->BGtexture, NULL, &BTLstr->creature[index].BarreDeVie->BGposition);
			SDL_RenderCopy(systeme->renderer, BTLstr->creature[index].BarreDeVie->texture, NULL, &BTLstr->creature[index].BarreDeVie->position);
		}
	}
	
	//projectiles
	for(index = 0 ; index < NBcailloux ; index++)
	{
		if (BTLstr->DepartBalle[index] == RUNNING)
		{
			SDL_RenderCopy(systeme->renderer, BTLstr->balle, NULL, &BTLstr->pballe[index]);
		}

	}
	#if TESTGRID == 1
	DrawTestGrid(BTLstr, systeme);
    #endif // TESTGRID

	SDL_RenderCopy	(systeme->renderer, inventaire->Uiinventaire, NULL, &inventaire->puiinventaire);

	SDL_RenderCopy(systeme->renderer, BTLstr->curseur, NULL, &BTLstr->pcurseur);

	SDL_RenderPresent(systeme->renderer);
}

void Hitboxjoueur (typecombat *BTLstr, PERSO *perso, int id)
{
	if (BTLstr->premiercoup[id] == 0)
	{
		if (DEGATsubitCHOC >= perso->defense/2)
		{
			perso->life = perso->life - ((DEGATsubitCHOC)-(perso->defense/2));
		}
	}
	else
	{
		if (DEGATsubitDUREE >= perso->defense)
		{
			float degat = DEGATsubitDUREE-(perso->defense/100);
			perso->life = perso->life - degat;
		}
	}
	BTLstr->premiercoup[id] = 1;
}

void COMBATgestionCLICetCOLISION (typecombat *BTLstr, DIVERSui *ui)
{
    if (BTLstr->letirdemander == true && ui->casestuff[ARME].IDobjet == 3)
    {
        gestiontir(BTLstr);
        COMBATgestionprojectile(BTLstr);
    }
    COMBATgestionDEGAT(BTLstr, ui);
}

void COMBATgestionDEGAT (typecombat *BTLstr, DIVERSui *ui)
{
	int index, index2;

	for (index = 0; index < BTLstr->NBennemi ; index++)
	{
		if(BTLstr->creature[index].life > 0)
		{
		    BTLstr->ResultatHitbox = -1;//initialisation

		    //décision dégat lancepierre
		    if (ui->casestuff[ARME].IDobjet == 3)
            {
                    BTLstr->ResultatHitbox = HitboxBalle(BTLstr, index);
            }
            //décision dégat mains nue
            else if (ui->casestuff[ARME].IDobjet == -1)
            {
                    BTLstr->ResultatHitbox = HitboxPoing(BTLstr, index);
            }

			//si dégat infligé
			if (BTLstr->ResultatHitbox != -1)
			{
				for (index2 = BTLstr->i[BTLstr->ResultatHitbox] ; index2 < 768 ; index2++ )
				{
					BTLstr->tx[BTLstr->ResultatHitbox][index2] = -100;
				}
				BTLstr->DepartBalle[BTLstr->ResultatHitbox] = UNUSED; // pour projectile
				
				Hit_Creature(index, BTLstr);
			}
		}
	}
	BTLstr->letirdemander = false;
}

void COMBATanimationPERSO(typecombat *BTLstr)
{
	if (BTLstr->temps - BTLstr->tempsanimationjoueur >= 128)
	{
		if (BTLstr->persobouge == 1)
		{
			BTLstr->tempsanimationjoueur = BTLstr->temps;
			BTLstr->indexanimperso++;
			if(BTLstr->indexanimperso >= 8)
			{
				BTLstr->indexanimperso = 0;
			}
		}
		else
		{
			BTLstr->indexanimperso = 0;
		}
	} 
}

void COMBATanimationMOB(typecombat *BTLstr)
{
	int index;

	for (index = 0 ; index < BTLstr->NBennemi ; index++)
	{
		if (BTLstr->temps - BTLstr->creature[index].tempsanimation >= 128 && BTLstr->creature[index].life > 0)
		{
			BTLstr->creature[index].tempsanimation = BTLstr->temps;
			BTLstr->creature[index].indexanim++;
			if(BTLstr->creature[index].indexanim >= 2)
			{
				BTLstr->creature[index].indexanim = 0;
			}
		}
	}
}

void COMBATanimationOBJET(typecombat *BTLstr)
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

void COMBATgestionENNEMI(typecombat *BTLstr, struct RAT *rat, DIVERSsysteme *systeme)
{
	int index;
	

	for (index = 0 ; index < BTLstr->NBennemi ; index++)
	{
		if (BTLstr->creature[index].life > 0)
		{
			BTLstr->creature[index].Direction = MouvemementChauveSouris(BTLstr, rat, systeme, index);
		}
	}
}

void ADDloot(PACKrecompense *recompense, int id, int nombre)
{
	int index = 0;
	//recherche d'un objet equivalent ou d'une case vide
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

	//ajout ddu loot
	recompense->recompenseID[index] = id;
	recompense->recompenseNB[index] += nombre;
}

void COMBATgestionOBJETsol(typecombat *BTLstr, DIVERSsysteme *systeme, PACKrecompense *recompense, bool arcademode,
							DIVERSui *ui, PERSO *perso)
{
	int index;

	for (index = 0 ; index < BTLstr->NBennemi ; index++)
	{
		//s'il est vivant
		if (BTLstr->creature[index].life > 0)
		{
			if (checkdistance(&BTLstr->Pperso, &BTLstr->creature[index].position, 50) == -1)
			{
				Hitboxjoueur (BTLstr, perso, index);
			}
			else
			{
				BTLstr->premiercoup[index] = 0;
			}
		}
		else if (BTLstr->creature[index].ontheway == 1 && BTLstr->creature[index].position.x < systeme->screenw)
		{
			BTLstr->creature[index].wayx += BTLstr->creature[index].dx;
			BTLstr->creature[index].wayy += BTLstr->creature[index].dy;

			BTLstr->creature[index].position.x = BTLstr->creature[index].oldposx + (int)BTLstr->creature[index].wayx;
			BTLstr->creature[index].position.y = BTLstr->creature[index].oldposy + (int)BTLstr->creature[index].wayy;
		}
		else if (BTLstr->creature[index].looted == 0)
		{
			//si on marche dessus
			if (colisionbox(&BTLstr->creature[index].position, &BTLstr->Pperso, 0))
			{
				BTLstr->arcadescore += 10;
				
				//ajout aux récompenses
				ADDloot(recompense, 0, 1);

				//objet en cour de deplacement
				BTLstr->creature[index].ontheway = 1;

				//calcul des différences
				float difx = systeme->screenw - BTLstr->creature[index].position.x;
				float dify = systeme->screenh - BTLstr->creature[index].position.y;

				//enregistrement des positions initiales
				BTLstr->creature[index].oldposx = BTLstr->creature[index].position.x;
				BTLstr->creature[index].oldposy = BTLstr->creature[index].position.y;

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
	}

	//parcour des objets
	for (index = 0 ; index < BTLstr->NBlootsol ; index++)
	{
		//si l'objet est déjà en mouvement
		if (BTLstr->lootsol[index] == BTL_OBJ_MOVE && BTLstr->plootsol[index].x < systeme->screenw)
		{
			BTLstr->lootsolWAYX[index] += BTLstr->lootsolDX[index];
			BTLstr->lootsolWAYY[index] += BTLstr->lootsolDY[index];

			BTLstr->plootsol[index].x = BTLstr->oldplootsol[index].x + (int)BTLstr->lootsolWAYX[index];
			BTLstr->plootsol[index].y = BTLstr->oldplootsol[index].y + (int)BTLstr->lootsolWAYY[index];
		}

		//si il est a terre et que le joueur marche dessus
		else if (BTLstr->lootsol[index] == BTL_OBJ_FLOOR &&
				colisionbox(&BTLstr->plootsol[index], &BTLstr->Pperso, 0))
		{
			//ajout aux récompenses
			ADDloot(recompense, BTLstr->IDlootsol[index], 1);

			//objet en cour de deplacement
			BTLstr->lootsol[index] = BTL_OBJ_MOVE;

			//calcul des différences
			float difx = systeme->screenw - BTLstr->plootsol[index].x;
			float dify = systeme->screenh - BTLstr->plootsol[index].y;

			//enregistrement des positions initiales
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

void SyncData(typecombat *BTLstr, PERSO *perso)
{
	int index;
	BTLstr->pcurseur.x = BTLstr->px;
	BTLstr->pcurseur.y = BTLstr->py;
	BTLstr->canonx = BTLstr->Pperso.x + (BTLstr->Pperso.w/2);
	BTLstr->canony = BTLstr->Pperso.y + (BTLstr->Pperso.h/2);
	
	perso->BarreDeVie->position.x = BTLstr->Pperso.x;
	perso->BarreDeVie->position.y = BTLstr->Pperso.y -20;
	perso->BarreDeVie->position.w = CalculerBarreDeVie(perso->lifemax, perso->life, BTLstr->Pperso.w);
	perso->BarreDeVie->BGposition.x = perso->BarreDeVie->position.x - 1;
	perso->BarreDeVie->BGposition.y = perso->BarreDeVie->position.y - 1;
	
	for(index = 0 ; index < BTLstr->NBennemi ; index++)
	{
		BTLstr->creature[index].BarreDeVie->position.x = BTLstr->creature[index].position.x;
		BTLstr->creature[index].BarreDeVie->position.y = BTLstr->creature[index].position.y -20;
		BTLstr->creature[index].BarreDeVie->position.w = CalculerBarreDeVie(BTLstr->creature[index].lifemax,
						BTLstr->creature[index].life, BTLstr->creature[index].position.w);
		BTLstr->creature[index].BarreDeVie->BGposition.x = BTLstr->creature[index].BarreDeVie->position.x - 1;
		BTLstr->creature[index].BarreDeVie->BGposition.y = BTLstr->creature[index].BarreDeVie->position.y - 1;
	}
}

int CalculerBarreDeVie(int VieDeBase, int VieActuelle, int width)
{
	return ((float)width / (float)VieDeBase) * (float)VieActuelle;
}

int JoueurMort(typecombat *BTLstr, DIVERSsysteme *systeme, DIVERSui *ui)
{
	char score[64][20];
	SDL_Texture *texture[64];
	SDL_Rect position[64];
	int index;
	
	//setting background
	texture[0] = fenetredialogue(systeme->pecran.w/3, systeme->pecran.h*0.911, &position[0], NULL, NULL, BLANC, systeme);
	ui->dialogueactif = 1;
	//setting up all texts
	int ret = PositionOfDeathDisplay(texture, position, score, BTLstr, systeme);
	
	//rendering Background and texts
	SDL_RenderCopy(systeme->renderer, systeme->BG, NULL, &position[0]);
	for(index = 1 ; index <= ret ; index++)
	{
		SDL_RenderCopy(systeme->renderer, texture[index], NULL, &position[index]);
	}
	SDL_RenderPresent(systeme->renderer);
	SDL_Delay(5000);
	
	BTLstr->continuer = BTL_LOST;
	return 0;
}

int PositionOfDeathDisplay(SDL_Texture *texture[], SDL_Rect position[], char score[][20],
							typecombat *BTLstr, DIVERSsysteme *systeme)
{
	int PosUsed = 0;
	
	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; //50*PosUsed
	sprintf(score[PosUsed],"1: 3000");
	texture[PosUsed] = DrawText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);
	
	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; //50*PosUsed
	sprintf(score[PosUsed],"2: 1200");
	texture[PosUsed] = DrawText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);
	
	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; //50*PosUsed
	sprintf(score[PosUsed],"3: 990");
	texture[PosUsed] = DrawText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);
	
	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; //50*PosUsed
	sprintf(score[PosUsed],"4: 460");
	texture[PosUsed] = DrawText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);
	
	PosUsed++;
	position[PosUsed].x = position[0].x;
	position[PosUsed].y = position[0].y;
	position[PosUsed].w = position[0].w;
	position[PosUsed].h = (systeme->pecran.h * 0.1) * PosUsed; //50*PosUsed
	sprintf(score[PosUsed],"5: 75");
	texture[PosUsed] = DrawText(&position[PosUsed], score[PosUsed], BLANC, ALIGN_CENTER, systeme);
	
	return PosUsed;
}

void Hit_Creature(int index, typecombat *BTLstr)
{
	BTLstr->creature[index].life -= 10;
	if (BTLstr->creature[index].life <= 0)
	{
		BTLstr->creature[index].isdead = true;	
		BTLstr->arcadescore += 5;
	}
}
