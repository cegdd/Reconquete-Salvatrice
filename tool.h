#ifndef TOOLH
#define TOOLH
typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct typecombat typecombat;
typedef struct BARREVIE BARREVIE;

void DrawTestGrid(typecombat *BTLstr, DIVERSsysteme *systeme);
void UnWriteSquareTestGrid(typecombat *BTLstr, SDL_Rect *area);
void UnWriteCircleTestGrid (typecombat *BTLstr, SDL_Point *middle, int width);
BARREVIE* AddLifeBar(int life, int lenght, DIVERSsysteme *systeme);

#endif /* TOOLH*/
