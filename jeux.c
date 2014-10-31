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

float combat (float vie, struct RAT *rat, struct DIVERSsysteme *systeme, PERSO *perso, DIVERSinventaire *inventaire,
              PACKrecompense *recompense, PACKobjet *objet, DIVERSui *ui)
{
	//structure contenant toutes les variables pour les combats
	typecombat BTLstr;
	DIRECTION direction;

	int index, fps = 0;

	//initialisation des variables
	initcombatstore(&BTLstr, systeme, vie, &direction);

	while (BTLstr.continuer == -1)
	{
		BTLstr.temps = SDL_GetTicks();

		//calcul ~120/sec
		if (BTLstr.temps - BTLstr.tempscalcul >= 8)
		{
			BTLstr.tempscalcul = BTLstr.temps;

			//si joueur mort
			//if (vie <= 0) {return BTL_LOST;}

			//gestion des événements
			BTLstr.continuer = boucleeventcombat (&BTLstr, systeme, &direction, ui);
			//calcul direction joueur
			direction.direction = directionperso(&direction);
			//deplacement
			deplacementperso(NULL, perso, &direction, systeme, &BTLstr.Pperso.x, &BTLstr.Pperso.y, 0);
			//recupération coordonées souris
			SDL_GetMouseState(&BTLstr.px, &BTLstr.py);

			//actualisation des coordonées
			BTLstr.pcurseur.x = BTLstr.px;
			BTLstr.pcurseur.y = BTLstr.py;
			BTLstr.canonx = BTLstr.Pperso.x + (BTLstr.Pperso.w/2);
			BTLstr.canony = BTLstr.Pperso.y + (BTLstr.Pperso.h/2);
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
			COMBATgestionOBJETsol(&BTLstr, systeme, recompense);
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
			afficherCOMBAT(&BTLstr, systeme, perso, rat, inventaire, objet);
		}
		else if (BTLstr.temps - BTLstr.tempsseconde >= 1000)//1000
		{
			//temporaire
			sprintf(BTLstr.StringVie, "fps : %d",fps);
			BTLstr.tVie = imprime (BTLstr.StringVie, systeme->screenw*0.3, NOIR, systeme, NULL);
			fps = 0;
			BTLstr.tempsseconde = BTLstr.temps;

			BTLstr.alive = 0;
			for(index = 0 ; index < BTLstr.NBennemi ; index++)
			{
				if (BTLstr.ennemi[index].vie > 0)
				{
					BTLstr.alive += 1;
				}
			}
		}
		else {SDL_Delay(1);}
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
	return BTL_LOST;
}

void afficherCOMBAT(typecombat *BTLstr, DIVERSsysteme *systeme, PERSO *perso, RAT *rat, DIVERSinventaire *inventaire, PACKobjet *objet)
{
	int calcul, index;

	SDL_RenderClear(systeme->renderer);

	SDL_RenderCopy(systeme->renderer, BTLstr->fond, NULL, &BTLstr->pecran);

	//loot au sol
	for (index = 0; index < BTLstr->NBlootsol ; index++)
	{
		if (BTLstr->lootsol[index] != BTL_OBJ_FLOOR)
		{
			BTLstr->plootsol[index].w = BTLstr->oldplootsol[index].w * BTLstr->animobjet;
			BTLstr->plootsol[index].h = BTLstr->oldplootsol[index].h * BTLstr->animobjet;
		}
		SDL_RenderCopy(systeme->renderer, objet->objet[BTLstr->IDlootsol[index]].texture, NULL, &BTLstr->plootsol[index]);
	}

	//ennemi
	for (index = 0; index < BTLstr->NBennemi ; index++)
	{
		//looted stuff
		if (BTLstr->ennemi[index].ontheway != 0 && BTLstr->ennemi[index].position.x < systeme->screenw)
		{
			BTLstr->ennemi[index].position.w = BTLstr->ennemi[index].STATICposition.w * BTLstr->animobjet;
			BTLstr->ennemi[index].position.h = BTLstr->ennemi[index].STATICposition.h * BTLstr->animobjet;
			SDL_RenderCopy(systeme->renderer, BTLstr->peau, NULL, &BTLstr->ennemi[index].position);
		}
		//si elles sont mortes et pas ramasser
		else if (BTLstr->ennemi[index].vie <= 0 && BTLstr->ennemi[index].looted == 0)
		{
			calcul =90+(45 * BTLstr->ennemi[index].Direction);
			SDL_RenderCopyEx(systeme->renderer,rat->texture[2], NULL, &BTLstr->ennemi[index].position, calcul,NULL, SDL_FLIP_NONE);
		}
		else if (BTLstr->ennemi[index].vie > 0)//si elles sont vivantes
		{
			calcul =90+(45 * BTLstr->ennemi[index].Direction);
			SDL_RenderCopyEx(systeme->renderer, rat->texture[BTLstr->ennemi[index].indexanim], NULL, &BTLstr->ennemi[index].position, calcul,NULL, SDL_FLIP_NONE);
		}
	}

	SDL_RenderCopy											(systeme->renderer, BTLstr->tVie, NULL, &BTLstr->ptVie);

	//joueur

	double degre = FindAngle(&BTLstr->Pperso, &BTLstr->pcurseur) + 90; //obtention de l'angle

	if (BTLstr->poing_tendu == true)
    {
        perso->pperso_poing.x = BTLstr->Pperso.x;
        perso->pperso_poing.y = BTLstr->Pperso.y;
        SDL_RenderCopyEx(systeme->renderer, perso->texture_poing[0], NULL, &perso->pperso_poing, degre, &perso->centrecorp, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyEx(systeme->renderer, perso->textureperso[BTLstr->indexanimperso], NULL, &BTLstr->Pperso, degre,NULL, SDL_FLIP_NONE);
    }
	SDL_RenderCopyEx(systeme->renderer, perso->cheveuxbrun, NULL, &BTLstr->Pperso, degre,NULL, SDL_FLIP_NONE);

	for(BTLstr->irect = 0 ; BTLstr->irect < NBcailloux ; BTLstr->irect++)
	{
		if (BTLstr->DepartBalle[BTLstr->irect] == RUNNING)
		{
			SDL_RenderCopy(systeme->renderer, BTLstr->balle, NULL, &BTLstr->pballe[BTLstr->irect]);
		}

	}
	#if TESTGRID == 1
	DrawTestGrid(BTLstr, systeme);
    #endif // TESTGRID

	SDL_RenderCopy	(systeme->renderer, inventaire->Uiinventaire, NULL, &inventaire->puiinventaire);

	SDL_RenderCopy(systeme->renderer, BTLstr->curseur, NULL, &BTLstr->pcurseur);

	SDL_RenderPresent(systeme->renderer);
}

int Hitboxjoueur (SDL_Rect pmob, SDL_Rect pperso, float *ptrvie, PERSO *perso)
{
	static int premiercoup;
	if (pperso.x + pperso.w < pmob.x)
	{
		premiercoup = 0;
		return 1;
	}
	else if ( pperso.x > pmob.x + pmob.w)
	{
		premiercoup = 0;
		return 2;
	}

	if(pmob.y < pperso.y + pperso.h && pmob.y + pmob.h > pperso.y &&
			pmob.x < pperso.x+pperso.w && pmob.x+pmob.w > pperso.x)
	{
		if (premiercoup == 0)
		{
			if (DEGATsubitCHOC >= perso->defense/2)
			{
				*ptrvie = *ptrvie -((DEGATsubitCHOC)-(perso->defense/2));
			}
			premiercoup = 1;
		}
		else
		{
			if (DEGATsubitDUREE >= perso->defense)
			{
				float degat = DEGATsubitDUREE-perso->defense;
				*ptrvie = *ptrvie - degat;
			}
		}
		return 0;
	}
	return -1;
}

int HitboxBalle(typecombat *BTLstr, SDL_Rect pballe[], SDL_Rect *pennemi, int direction)
{//fonction appeler pour chaque monstres
	int i, k = 0, l = 0;
	SDL_Rect pix = {k, l, 1, 1};

	#if TESTGRID == 1
	SDL_Point point;
	#endif // TESTGRID

	for (i = 0 ; i < NBcailloux ; i++)
	{   //tri et degrossissage pour calcul précis
	    if (checkdistance(pennemi, &pballe[i], 120) == -1 && BTLstr->DepartBalle[i] == RUNNING )
        {
            #if TESTGRID == 1
            point.x = pballe[i].x;
            point.y = pballe[i].y;
            UnWriteCircleTestGrid(BTLstr, &point, 10);
            #endif // TESTGRID

            for(k = pballe[i].x ; k <= pballe[i].x + pballe[i].w ; k++)
            {
                for(l = pballe[i].y ; l <= pballe[i].y + pballe[i].h; l++)
                {
                    pix.x = k;
                    pix.y = l;

                    if (checkdistance(&pix, &pballe[i], 10) == -1 )
                    {
                        if (TestColision_Rat(pennemi, pix.x, pix.y, direction) == 1)
                        {
                            #if TESTGRID == 1
                            point.x = pballe[i].x;
                            point.y = pballe[i].y;
                            UnWriteCircleTestGrid(BTLstr, &point, 10);
                            #endif // TESTGRID
                            return i;
                        }
                    }
                }
            }
        }
	}
	return -1;
}

int HitboxPoing(typecombat *BTLstr, SDL_Rect *pennemi)
{
    int k = 0, l = 0;
    SDL_Rect pix = {k, l, 1, 1};


    if (checkdistance(pennemi, &BTLstr->Pperso, 120) == -1 )//degrossissage pour calcul précis
    {
        for(k = BTLstr->Pperso.x ; k <= BTLstr->Pperso.x + BTLstr->Pperso.w ; k++)
        {
            for(l = BTLstr->Pperso.y ; l <= BTLstr->Pperso.y + BTLstr->Pperso.h; l++)
            {
                pix.x = k;
                pix.y = l;
                if (checkdistance(&BTLstr->Pperso, pennemi, 30) == 1)
                {
                    if (colisionfromage(&pix, pennemi, &BTLstr->pcurseur, 20) == true)
                    {
                        BTLstr->calque[k][l] = 1;
                        //return 0;
                    }
                }
            }
        }
    }
return -1;
}

void COMBATgestionCLICetCOLISION (typecombat *BTLstr, DIVERSui *ui)
{
    if (BTLstr->letirdemander == true)
    {
        if (ui->casestuff[ARME].IDobjet == 3)
        {
            gestiontir(BTLstr);
            COMBATgestionprojectile(BTLstr);
        }
    }
    COMBATgestionDEGAT(BTLstr, ui);
}

void COMBATgestionprojectile (typecombat *BTLstr)
{
	int index;
	for (index = 0 ; index < NBcailloux ; index++)
	{
		if (BTLstr->DepartBalle[index] != UNUSED && BTLstr->i[index] < PRECISIONcailloux - 1 && BTLstr->DepartBalle[index] != STOP)
		{
			BTLstr->i[index] = BTLstr->i[index]+1;
			BTLstr->pballe[index].x = BTLstr->tx[index][BTLstr->i[index]];
			BTLstr->pballe[index].y = BTLstr->ty[index][BTLstr->i[index]];
		}
		else if (BTLstr->i[index] >= PRECISIONcailloux-1)
		{
			BTLstr->pballe[index].x = BTLstr->tx[index][PRECISIONcailloux-1];
			BTLstr->pballe[index].y = BTLstr->ty[index][PRECISIONcailloux-1];
			BTLstr->DepartBalle[index] = STOP;
		}
		else
		{
			BTLstr->DepartBalle[index] = RUNNING;
		}
	}
}

void COMBATgestionDEGAT (typecombat *BTLstr, DIVERSui *ui)
{
	int index, index2;

	for (index = 0; index < BTLstr->NBennemi ; index++)
	{
		if(BTLstr->ennemi[index].vie > 0)
		{
		    BTLstr->ResultatHitbox = -1;//initialisation

		    //décision dégat lancepierre
		    if (ui->casestuff[ARME].IDobjet == 3)
            {
                    BTLstr->ResultatHitbox = HitboxBalle(BTLstr, BTLstr->pballe,
                                                         &BTLstr->ennemi[index].position, BTLstr->ennemi[index].Direction);
            }
            //décision dégat mains nue
            else if (ui->casestuff[ARME].IDobjet == -1)
            {
                BTLstr->ResultatHitbox = HitboxPoing(BTLstr, &BTLstr->ennemi[index].position);
            }

			//si dégat infligé
			if (BTLstr->ResultatHitbox != -1)
			{
				for (index2 = BTLstr->i[BTLstr->ResultatHitbox] ; index2 < 768 ; index2++ )
				{
					BTLstr->tx[BTLstr->ResultatHitbox][index2] = -100;
				}
				BTLstr->DepartBalle[BTLstr->ResultatHitbox] = UNUSED; // pour projectile
				BTLstr->ennemi[index].vie = 0;
			}
		}
	}
}

void COMBATanimationPERSO(typecombat *BTLstr)
{
	if (BTLstr->temps - BTLstr->tempsanimationjoueur >= 128)
	{
		if (BTLstr->persobouge == 1)
		{
			BTLstr->tempsanimationjoueur = BTLstr->temps;
			BTLstr->indexanimperso++;
			if(BTLstr->indexanimperso >= 2)
			{
				BTLstr->indexanimperso = 0;
			}
		}
		else
		{
			BTLstr->indexanimperso = 2;
		}
	}
}

void COMBATanimationMOB(typecombat *BTLstr)
{
	int index;

	for (index = 0 ; index < BTLstr->NBennemi ; index++)
	{
		if (BTLstr->temps - BTLstr->ennemi[index].tempsanimation >= 128 && BTLstr->ennemi[index].vie > 0)
		{
			BTLstr->ennemi[index].tempsanimation = BTLstr->temps;
			BTLstr->ennemi[index].indexanim++;
			if(BTLstr->ennemi[index].indexanim >= 2)
			{
				BTLstr->ennemi[index].indexanim = 0;
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
		if (BTLstr->ennemi[index].vie > 0)
		{
			BTLstr->ennemi[index].Direction = MouvemementChauveSouris(BTLstr, rat, systeme, index);
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

void COMBATgestionOBJETsol(typecombat *BTLstr, DIVERSsysteme *systeme, PACKrecompense *recompense)
{
	int index;

	for (index = 0 ; index < BTLstr->NBennemi ; index++)
	{
		if (BTLstr->ennemi[index].vie > 0){}
		else if (BTLstr->ennemi[index].ontheway == 1 && BTLstr->ennemi[index].position.x < systeme->screenw)
		{
			BTLstr->ennemi[index].wayx += BTLstr->ennemi[index].dx;
			BTLstr->ennemi[index].wayy += BTLstr->ennemi[index].dy;

			BTLstr->ennemi[index].position.x = BTLstr->ennemi[index].oldposx + (int)BTLstr->ennemi[index].wayx;
			BTLstr->ennemi[index].position.y = BTLstr->ennemi[index].oldposy + (int)BTLstr->ennemi[index].wayy;
		}
		else if (BTLstr->ennemi[index].looted == 0)
		{
			//si on marche dessus
			if (colisionbox(&BTLstr->ennemi[index].position, &BTLstr->Pperso, 0))
			{
				//ajout aux récompenses
				ADDloot(recompense, 0, 1);

				//objet en cour de deplacement
				BTLstr->ennemi[index].ontheway = 1;

				//calcul des différences
				float difx = systeme->screenw - BTLstr->ennemi[index].position.x;
				float dify = systeme->screenh - BTLstr->ennemi[index].position.y;

				//enregistrement des positions initiales
				BTLstr->ennemi[index].oldposx = BTLstr->ennemi[index].position.x;
				BTLstr->ennemi[index].oldposy = BTLstr->ennemi[index].position.y;

				if (dify > difx)
				{
					BTLstr->ennemi[index].dx = (difx/dify)*3;
					BTLstr->ennemi[index].dy = 3;
				}
				else if (difx > dify)
				{
					BTLstr->ennemi[index].dx = 3;
					BTLstr->ennemi[index].dy = (dify/difx)*3;
				}
				else
				{
					BTLstr->ennemi[index].dx = 3;
					BTLstr->ennemi[index].dy = 3;
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

void gestiontir(typecombat *BTLstr)
{
    tirer (BTLstr->px, BTLstr->py, BTLstr->canonx, BTLstr->canony, BTLstr->tx, BTLstr->ty, BTLstr->tableauutile, &BTLstr->degre);

    BTLstr->letirdemander = false;
    BTLstr->DepartBalle[BTLstr->tableauutile] = RUNNING;
    BTLstr->i[BTLstr->tableauutile] = 0;
    BTLstr->tableauutile++;
    if (BTLstr->tableauutile == 20)
	{
		BTLstr->tableauutile = 0;
	}
}
