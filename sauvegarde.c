#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <string.h>

#include "fichier.h"
#include "sauvegarde.h"

void chargersauvegarde(struct DIVERSsysteme *systeme)
{
	FILE *fichiersauvegarde = NULL, *crypted = NULL;
	char nomfichier[50] = {'\0'};
	char schiffre[5] = {'\0'};
	char caractere = '\0';

	char buffer[4096] = {'\0'};
	char ret[50] = {'\0'};

	int iligne = 0, i, index;

	sprintf(nomfichier, "rs/sauvegarde/%s.RSCryptedSave", systeme->sauvegarde[0]);
	crypted = fopen ((const char *) nomfichier, "r");

	for (i = 0 ; i < NBargSAVE ; i++)
	{
		caractere = fgetc(crypted);
		while (caractere != '#')
		{
			buffer[iligne] = caractere;
			iligne++;
			caractere = fgetc(crypted);
		}
		lis(buffer, ret);

		strcpy(systeme->sauvegarde[i], ret);
		for(index = 0 ; index < 4096 ; index++)
		{
			buffer[index] = '\0';
		}
		iligne = 0;
	}
	fclose(crypted);

	sprintf(nomfichier, "rs/sauvegarde/%s.RSsave2", systeme->sauvegarde[0]);
	fichiersauvegarde = fopen ((const char *) nomfichier, "r");

	for (i = 0 ; i < TAILLESAC ; i++)
	{
		iligne = 0;
		caractere = fgetc(fichiersauvegarde);
		while (caractere != '#')
		{
			schiffre[iligne] = caractere;
			iligne++;
			caractere = fgetc(fichiersauvegarde);
		}
		schiffre[iligne] = '\0';
		iligne = 0;
		systeme->saveinventaire[0][i] = atoi(schiffre);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		caractere = fgetc(fichiersauvegarde);
		while (caractere != '#')
		{
			schiffre[iligne] = caractere;
			iligne++;
			caractere = fgetc(fichiersauvegarde);
		}
		schiffre[iligne] = '\0';
		systeme->saveinventaire[1][i] = atoi(schiffre);
	}
	fclose(fichiersauvegarde);
}

void sauvegardetout(char sauvegarde[][50],SDL_Rect pmap,struct PERSO *perso, int temptotal, int unuse,
					 struct EMPLACEMENT *sac, int tailledusac,struct DIVERSui *ui)
{
	FILE *fichier2 = NULL;
	char nomfichier[50] = {'\0'};
	int index;
	int pseudolen = strlen(sauvegarde[0]);

	sauvegarde[0][pseudolen] = '\0';
	sprintf(nomfichier, "rs/sauvegarde/%s.RSCryptedSave", sauvegarde[0]);

	sprintf(sauvegarde[0], "%s", sauvegarde[0]);		/*pseudo*/
	sprintf(sauvegarde[1], "%s", sauvegarde[1]);		/*mdp*/
	sprintf(sauvegarde[2], "%d", pmap.x);				/*map en x*/
	sprintf(sauvegarde[3], "%d", pmap.y);				/*map en y*/
	sprintf(sauvegarde[4], "%d", perso->perso.pict.pos.x);			/*perso en x*/
	sprintf(sauvegarde[5], "%d", perso->perso.pict.pos.y);			/*perso en y*/
	sprintf(sauvegarde[6], "%d", temptotal);			/*temp total de jeu en seconde*/
	sprintf(sauvegarde[7], "%d", (int)perso->life);				/*quantité de vie*/
	sprintf(sauvegarde[8], "%d", unuse);		/*nombre de batmoule tuer.*/
	sprintf(sauvegarde[9], "%d", tailledusac);		/*taille des sacs*/
	for (index = 0 ; index < 7 ; index++)
	{
		sprintf(sauvegarde[index+10], "%d", ui->casestuff[index].IDobjet);
	}

	fichier2 = fopen ((const char *) nomfichier, "w+");
	for (index = 0 ; index < NBargSAVE ; index++)
	{
		ecris(sauvegarde[index], fichier2);
		fputc('#', fichier2);
	}
	fclose(fichier2);




	sprintf(nomfichier, "rs/sauvegarde/%s.RSsave2", sauvegarde[0]);
	fichier2 = fopen((const char *)nomfichier, "w+");
	for (index = 0 ; index < tailledusac ; index++)
	{
		fprintf(fichier2, "%d#%d#", sac[index].IDobjet, sac[index].NBobjet);
	}
	fclose(fichier2);
}

void initsauvegarde(char sauvegarde[][50], int ligne, int colonne)
{
	register int i, j;

	for (i = 0 ; i < ligne ; i++)
	{
		for (j = 0 ; j < colonne ; j++)
		{
			sauvegarde[i][j] = '\0';
		}
	}

}

void ecris(char string[50], FILE *fichier)
{
	int i = 0, index;
	int valeur = 0;

	while(string[i] != '\0')
	{
		valeur = (int)string[i];
		for(index = 0 ; index < valeur ; index++)
		{
			fputc('O', fichier);
		}
		fputc('0', fichier);
		i++;
	}

}


void lis(char string[4096], char *ret)
{
	int i = 0, index = 0;
	int compteur = 0;

	while(string[i] != '\0')
	{
		while(string[i] == 'O')
		{
			compteur++;
			i++;
		}
		i++;
		ret[index] = compteur;
		compteur = 0;
		index++;
	}
	ret[index] = '\0';
}
