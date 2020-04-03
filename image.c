#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "image.h"
#include "struct.h"

#include <LIBcegdd_ui.h>


extern int screenh, screenw;

void chargement (struct DIVERSsysteme *systeme)
{
    struct pict logo, fond;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(0,screenw,0,screenh);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	CEGDD_UI_setPos4(&logo.pos, 0, 200, screenw, screenh);
	CEGDD_UI_setPos4(&fond.pos, 0, screenh*-0.2, screenw*0.7, screenh*0.8);
    fond.pos.x = (screenw - fond.pos.w) / 2;

	fond.texture = loadTexture("rs/images/chargement.png");
	logo.texture = loadTexture("rs/fonds/rs.png");

	draw_pict(&fond);
	draw_pict(&logo);

    glFlush();
    SDL_GL_SwapWindow(systeme->screen);

    SDL_Delay(1000);
}

GLuint imprime (char s[], int len, int couleur,struct DIVERSsysteme *systeme, int *LenghtReturn, int *HighReturn)
{
    SDL_Surface *SurfTemp = NULL;
    SDL_Color Noir = {0, 0, 0, 0};
	SDL_Color Gris = {127, 127,127, 0};
	SDL_Color Blanc = {255, 255, 255, 0};
	SDL_Color Rouge = {255, 0, 0, 0};
	SDL_Color Vert = {0, 255, 0, 0};
	SDL_Color Bleu = {0, 0, 255, 0};


    if(systeme->police == NULL)
    {
        printf ("police not load\n");
    }

	if (couleur == BLANC)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police1, (const char *)s, Blanc, len);
    }
    else if (couleur == ROUGE)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police1, (const char *)s, Rouge, len);
    }
    else if (couleur == GRIS)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police1, (const char *)s, Gris, len);
    }
	else if (couleur == NOIR)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police1, (const char *)s, Noir, len);
    }
    else if (couleur == VERT)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police1, (const char *)s, Vert, len);
    }
    else
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police1, (const char *)s, Bleu, len);
    }


    if (LenghtReturn != NULL)
    {
        *LenghtReturn = SurfTemp->w;
    }
    if (HighReturn != NULL)
    {
        *HighReturn = SurfTemp->h;
    }

    return convertTexture(SurfTemp);
}

void ANIMmort (struct DIVERSsysteme *systeme)
{
	//SDL_RenderCopy(systeme->renderer, systeme->BGmort, NULL, &pecran);
    glFlush();
    SDL_GL_SwapWindow(systeme->screen);
    #if FASTLOG == 0 /*pour moi, pour ne pas attendre*/
    SDL_Delay(1500);
    #endif
}

GLuint loadTexture(const char * filename)
{
    GLuint glID;
    SDL_Surface * picture_surface = NULL;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface * gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;
    SDL_PixelFormat format;

    picture_surface = IMG_Load(filename);

    if (picture_surface == NULL)
        {return 0;}

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;

    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);

    gl_fliped_surface = flipSurface(gl_surface);

    glGenTextures(1, &glID);

    glBindTexture(GL_TEXTURE_2D, glID);


    glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w,
                 gl_fliped_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                 gl_fliped_surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    SDL_FreeSurface(gl_fliped_surface);
    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);

    return glID;
}

GLuint convertTexture(SDL_Surface *surface)
{
    GLuint glID;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface * gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;
    SDL_PixelFormat format;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    format = *(surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;

    gl_surface = SDL_ConvertSurface(surface,&format,SDL_SWSURFACE);

    gl_fliped_surface = flipSurface(gl_surface);

    glGenTextures(1, &glID);

    glBindTexture(GL_TEXTURE_2D, glID);


    glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w,
                 gl_fliped_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                 gl_fliped_surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return glID;
}

SDL_Surface *flipSurface(SDL_Surface * surface)
{
    int current_line,pitch;
    SDL_Surface * fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   surface->w,surface->h,
                                   surface->format->BitsPerPixel,
                                   surface->format->Rmask,
                                   surface->format->Gmask,
                                   surface->format->Bmask,
                                   surface->format->Amask);



    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);

    pitch = surface->pitch;
    for (current_line = 0; current_line < surface->h; current_line ++)
    {
        memcpy(&((unsigned char* )fliped_surface->pixels)[current_line*pitch],
               &((unsigned char* )surface->pixels)[(surface->h - 1  -
                                                    current_line)*pitch],
               pitch);
    }

    SDL_UnlockSurface(fliped_surface);
    SDL_UnlockSurface(surface);
    return fliped_surface;
}

void draw_pict(struct pict *image)
{
    glBindTexture(GL_TEXTURE_2D, image->texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(image->pos.x,image->pos.y);
        glTexCoord2d(0,1);          glVertex2d(image->pos.x,image->pos.y+image->pos.h);
        glTexCoord2d(1,1);          glVertex2d(image->pos.x+image->pos.w,image->pos.y+image->pos.h);
        glTexCoord2d(1,0);          glVertex2d(image->pos.x+image->pos.w,image->pos.y);
    glEnd();
}
void draw_hookpict(struct hookpict *image, SDL_Rect *support)
{
    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    glBindTexture(GL_TEXTURE_2D, image->pict.texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(image->pict.pos.x,image->pict.pos.y);
        glTexCoord2d(0,1);          glVertex2d(image->pict.pos.x,image->pict.pos.y+image->pict.pos.h);
        glTexCoord2d(1,1);          glVertex2d(image->pict.pos.x+image->pict.pos.w,image->pict.pos.y+image->pict.pos.h);
        glTexCoord2d(1,0);          glVertex2d(image->pict.pos.x+image->pict.pos.w,image->pict.pos.y);
    glEnd();
}

void draw_hook(GLuint texture, SDL_Rect *pos, SDL_Rect *support)
{
    pos->x += support->x;
    pos->y += support->y;

    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(pos->x,pos->y);
        glTexCoord2d(0,1);          glVertex2d(pos->x,pos->y+pos->h);
        glTexCoord2d(1,1);          glVertex2d(pos->x+pos->w,pos->y+pos->h);
        glTexCoord2d(1,0);          glVertex2d(pos->x+pos->w,pos->y);
    glEnd();
}

void draw(GLuint texture, SDL_Rect *pos)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(pos->x,pos->y);
        glTexCoord2d(0,1);          glVertex2d(pos->x,pos->y+pos->h);
        glTexCoord2d(1,1);          glVertex2d(pos->x+pos->w,pos->y+pos->h);
        glTexCoord2d(1,0);          glVertex2d(pos->x+pos->w,pos->y);
    glEnd();
}

void draw_color_black(SDL_Rect *pos)
{
    glColor3ub(0, 0, 0);
        glBegin(GL_QUADS);
            glVertex2d(pos->x,pos->y);
            glVertex2d(pos->x,pos->y+pos->h);
            glVertex2d(pos->x+pos->w,pos->y+pos->h);
            glVertex2d(pos->x+pos->w,pos->y);
        glEnd();
    glColor3ub(255, 255, 255);
}

void draw_button(struct BOUTON *bouton)
{
    glBindTexture(GL_TEXTURE_2D, bouton->texture);
    switch(bouton->etat)
    {
        case B_IMPOSSIBLE:
            glColor3ub(255, 0, 0);
            break;
        case B_SURVOLER:
            glColor3ub(150, 150, 255);
            break;
        case B_CLIQUER:
            glColor3ub(0, 0, 255);
            break;
        default:
            glColor3ub(255, 255, 255);
            break;
    }
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(bouton->pos.x,bouton->pos.y);
        glTexCoord2d(0,1);          glVertex2d(bouton->pos.x,bouton->pos.y+bouton->pos.h);
        glTexCoord2d(1,1);          glVertex2d(bouton->pos.x+bouton->pos.w,bouton->pos.y+bouton->pos.h);
        glTexCoord2d(1,0);          glVertex2d(bouton->pos.x+bouton->pos.w,bouton->pos.y);
    glEnd();

    glColor3ub(255, 255, 255);
}

void setPos2rect(SDL_Rect *point, int x, int y)
{
    point->x = x;
    point->y = y;
}

void Turn_And_Draw (struct pict *img, float angle)
{
    SDL_Point temp;
    temp.x = img->pos.x;
    temp.y = img->pos.y;

    img->pos.x = 0 - (img->pos.w/2);
    img->pos.y = 0 - (img->pos.h/2);

	glTranslatef(temp.x+(img->pos.w/2), temp.y+(img->pos.h/2), 0);
	glRotatef(angle, 0, 0 ,1);

	draw_pict(img);

	img->pos.x = temp.x;
	img->pos.y = temp.y;

    glLoadIdentity();
}

void turn_draw_hookpict(int angle, struct hookpict *image, SDL_Rect *support)
{
    glPushMatrix();

    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    Turn_And_Draw(&image->pict, angle);

    glPopMatrix();
}


void Sync_Moving_Pict(int time, struct moving_pict *m_pict)
{
    if (time - m_pict->time >= m_pict->delay)
    {
        m_pict->time = time;
        m_pict->current++;
        if(m_pict->current >= m_pict->frame)
        {
            m_pict->current = 0;
        }
        m_pict->pict.texture = m_pict->texture[m_pict->current];
    }
}

SDL_Point PointOf(SDL_Rect rect)
{
    SDL_Point var;
    var.x = rect.x;
    var.y = rect.y;
    return var;
}


GLuint loadTextureandsize(const char * filename, struct SDL_Rect *pos)
{
    GLuint glID;
    SDL_Surface * picture_surface = NULL;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface * gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;
    SDL_PixelFormat format;

    picture_surface = IMG_Load(filename);
    if (picture_surface == NULL)
        {   printf ("surface %s not correctly loaded \n", filename);
            return 0;}//0 is an error for opengl

    pos->w = picture_surface->w;
    pos->h = picture_surface->h;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;

    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);

    gl_fliped_surface = flipSurface(gl_surface);

    glGenTextures(1, &glID);

    glBindTexture(GL_TEXTURE_2D, glID);


    glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w,
                 gl_fliped_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                 gl_fliped_surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    SDL_FreeSurface(gl_fliped_surface);
    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);

    return glID;
}
