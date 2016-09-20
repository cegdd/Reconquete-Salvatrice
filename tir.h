
void tirer (float px, float py, int canonx, int canony, int tx[][384], int ty[][384], int tableauutile, double *degre);

//int HitboxBalle(struct typecombat *BTLstr, int index);
void gestiontir(struct TIR *TIR, struct DIVERSsysteme *systeme, struct PERSO *perso);
void COMBATgestionprojectile (struct TIR *TIR);
void BattleDraw_Projectile(struct TIR *TIR);
