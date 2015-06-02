#include "main.h"

void tirer (float px, float py, int canonx, int canony, int tx[][384], int ty[][384], int tableauutile, double *degre);

int HitboxBalle(struct typecombat *BTLstr, int index);
void COMBATgestionprojectile (struct typecombat *BTLstr);
void gestiontir(struct typecombat *BTLstr);
