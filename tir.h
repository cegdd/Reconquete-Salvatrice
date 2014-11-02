

typedef struct typecombat typecombat;

void tirer (float px, float py, int canonx, int canony, int tx[][384], int ty[][384], int tableauutile, double *degre);

int HitboxBalle(typecombat *BTLstr, int index);
void COMBATgestionprojectile (typecombat *BTLstr);
void gestiontir(typecombat *BTLstr);
