#ifndef SAUVEGARDEH
#define SAUVEGARDEH

#include "main.h"

void chargersauvegarde(struct DIVERSsysteme *systeme);
void sauvegardetout(char sauvegarde[][50],SDL_Rect pmap,struct PERSO *perso, int temptotal, int unuse,
					 struct EMPLACEMENT *sac, int tailledusac,struct DIVERSui *ui);
void initsauvegarde(char sauvegarde[][50], int ligne, int colonne);

void ecris(char string[50], FILE *fichier);
void lis(char string[4096], char *ret);

#endif
