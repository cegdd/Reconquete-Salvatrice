
void tirer (float px, float py, int canonx, int canony, int tx[][PRECISIONcailloux], int ty[][PRECISIONcailloux],
            int tableauutile, double *degre, struct DIVERSmap *carte);

//int HitboxBalle(struct typecombat *BTLstr, int index);
void gestiontir(struct TIR *TIR, struct DIVERSsysteme *systeme, struct PERSO *perso, struct DIVERSmap *carte);
void COMBATgestionprojectile (struct TIR *TIR);
void BattleDraw_Projectile(struct TIR *TIR, struct DIVERSmap *carte);
