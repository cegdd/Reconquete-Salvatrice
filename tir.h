

typedef struct typecombat typecombat;

void tirer (float px, float py, int canonx, int canony, int tx[][384], int ty[][384], int tableauutile, double *degre);

int HitboxBalle(typecombat *BTLstr, SDL_Rect pballe[], SDL_Rect *pennemi, int Iennemi);
void COMBATgestionprojectile (typecombat *BTLstr);
void gestiontir(typecombat *BTLstr);
