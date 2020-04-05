#ifndef IMAGEH
#define IMAGEH

#include "SDL2/SDL_ttf.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "struct.h"

void chargement (struct DIVERSsysteme *systeme);
void ANIMmort (struct DIVERSsysteme *systeme);

GLuint loadTextureandsize(const char * filename, struct SDL_Rect *pos);

void draw_hookpict(struct hookpict *image, SDL_Rect *support);
void draw_hook(GLuint texture, SDL_Rect *pos, SDL_Rect *support);
void draw(GLuint texture, SDL_Rect *pos);
void draw_button(struct BOUTON *bouton);
void draw_color_black(SDL_Rect *pos);
void Turn_And_Draw (struct pict *img, float angle);
void turn_draw_hookpict(int angle, struct hookpict *image, SDL_Rect *support);
void Sync_Moving_Pict(int time, struct moving_pict *m_pict);
SDL_Point PointOf(SDL_Rect rect);


#endif
