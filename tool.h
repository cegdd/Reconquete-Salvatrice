#ifndef TOOLH
#define TOOLH

void DrawTestGrid(struct typecombat *BTLstr,struct DIVERSsysteme *systeme);
void UnWriteSquareTestGrid(struct typecombat *BTLstr, SDL_Rect *area);
void UnWriteCircleTestGrid (struct typecombat *BTLstr, SDL_Point *middle, int width);
struct BARREVIE* AddLifeBar(int life, int lenght,struct DIVERSsysteme *systeme);

#endif /* TOOLH*/
