#ifndef IMAGEH
#define IMAGEH

#include <SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "struct.h"

SDL_Texture* LoadingImage(char* emplacement, int transparence,struct DIVERSsysteme *systeme);
Uint8 obtenirPixel(SDL_Surface *surface, SDL_Point *pix);
Uint8 obtenirPixel_hook(SDL_Surface *surface, SDL_Point *pix);
void chargement (struct DIVERSsysteme *systeme);
GLuint imprime (char s[], int len, int couleur,struct DIVERSsysteme *systeme, int *LenghtReturn, int *HighReturn);
void ANIMmort (struct DIVERSsysteme *systeme);

SDL_Surface * flipSurface(SDL_Surface * surface);
GLuint convertTexture(SDL_Surface *surface);
GLuint loadTexture(const char * filename);
GLuint loadTextureandsize(const char * filename, struct SDL_Rect *pos);

void draw_pict(struct pict *image);
void draw_hookpict(struct hookpict *image, SDL_Rect *support);
void draw_hook(GLuint texture, SDL_Rect *pos, SDL_Rect *support);
void draw(GLuint texture, SDL_Rect *pos);
void draw_button(struct BOUTON *bouton);
void draw_color_black(SDL_Rect *pos);
void setPos4(SDL_Rect *pos, int x, int y, int w, int h);
void setPos2rect(SDL_Rect *pos, int x, int y);
void setPos2(SDL_Point *point, int x, int y);
void Turn_And_Draw (struct pict *img, float angle);
void turn_draw_hookpict(int angle, struct hookpict *image, SDL_Rect *support);
void Sync_Moving_Pict(int time, struct moving_pict *m_pict);
SDL_Point PointOf(SDL_Rect rect);


#endif
