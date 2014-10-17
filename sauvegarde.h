#ifndef SAUVEGARDEH
#define SAUVEGARDEH

typedef struct EMPLACEMENT EMPLACEMENT;
typedef struct PERSO PERSO;
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct DIVERSui DIVERSui;

void chargersauvegarde(DIVERSsysteme *systeme);
void sauvegardetout(char sauvegarde[][50],SDL_Rect pmap, PERSO *perso, int temptotal, int unuse,
					 struct EMPLACEMENT *sac, int tailledusac, DIVERSui *ui);
void initsauvegarde(char sauvegarde[][50], int ligne, int colonne);

void ecris(char string[50], FILE *fichier);
void lis(char string[4096], char *ret);

#endif
