
void tirer (float px, float py, int canonx, int canony, int tx[][PRECISIONcailloux], int ty[][PRECISIONcailloux],
            int tableauutile, double *degre, struct DONJON *donjon);

//int HitboxBalle(struct typecombat *BTLstr, int index);
void gestiontir(struct TIR *TIR, struct DIVERSsysteme *systeme, struct PERSO *perso, struct DONJON *donjon);
void COMBATgestionprojectile (struct TIR *TIR, struct DONJON *donjon);
void BattleDraw_Projectile(struct TIR *TIR, struct DONJON *donjon);
