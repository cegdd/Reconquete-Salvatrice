#ifndef BATTLEDRAWH
#define BATTLEDRAWH

void BattleDraw_FloorItems(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct PACKobjet *objet);
void BattleDraw_Ennemy(struct typecombat *BTLstr,struct DIVERSsysteme *systeme, int arcademode);
void BattleDraw_Player(struct typecombat *BTLstr,struct DIVERSsysteme *systeme,struct PERSO *perso);
void BattleDraw_Projectile(struct typecombat *BTLstr,struct DIVERSsysteme *systeme);

#endif
