#ifndef BATTLEDRAWH
#define BATTLEDRAWH

void BattleDraw_FloorItems(typecombat *BTLstr, DIVERSsysteme *systeme, PACKobjet *objet);
void BattleDraw_Ennemy(typecombat *BTLstr, DIVERSsysteme *systeme, int arcademode);
void BattleDraw_Player(typecombat *BTLstr, DIVERSsysteme *systeme, PERSO *perso);
void BattleDraw_Projectile(typecombat *BTLstr, DIVERSsysteme *systeme);

#endif
