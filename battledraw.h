#ifndef BATTLEDRAWH
#define BATTLEDRAWH

void BattleDraw_FloorItems(struct typecombat *BTLstr,struct PACKobjet *objet);
void BattleDraw_Ennemy(struct typecombat *BTLstr, int arcademode);
void BattleDraw_Player(struct typecombat *BTLstr,struct PERSO *perso, struct DIVERSsysteme *systeme);
void BattleDraw_Projectile(struct typecombat *BTLstr);

#endif
