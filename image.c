#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "main.h"

typedef struct DIVERSsysteme DIVERSsysteme;
typedef struct TEXTE TEXTE;


SDL_Texture* LoadingImage(char* emplacement, int transparence, DIVERSsysteme *systeme)
{
	SDL_Texture *texture = NULL;
	texture = IMG_LoadTexture(systeme->renderer, emplacement);
	if (texture == NULL)
	{
		printf("%s\n", SDL_GetError());
		printf("probleme chargement de l'image %s\n", emplacement);
	}

	if (transparence > 0)
	{
		SDL_SetTextureAlphaMod(texture,transparence);
	}

	return texture;
}

Uint32 obtenirPixel(SDL_Surface *surface[], int pixx, int pixy)
{
	int indexcalque = 0, x = pixx, y = pixy;
	if(pixx >= 7500) {indexcalque = indexcalque + 3;	x = x -7500;}
	else if(pixx >= 5000) {indexcalque = indexcalque + 2;	x = x -5000;}
	else if(pixx >= 2500) {indexcalque = indexcalque + 1;	x = x -2500;}

	if(pixy >= 7500) {indexcalque = indexcalque + 12;	y = y -7500;}
	else if(pixy >= 5000) {indexcalque = indexcalque + 8;	y = y -5000;}
	else if(pixy >= 2500) {indexcalque = indexcalque + 4;	y = y -2500;}

    int nbOctetsParPixel = surface[indexcalque]->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface[indexcalque]->pixels + y * surface[indexcalque]->pitch + x * nbOctetsParPixel;
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

Uint32 obtenirPixel2(SDL_Surface *surface, int pixx, int pixy)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + pixy * surface->pitch + pixx * nbOctetsParPixel;
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

void chargement (DIVERSsysteme *systeme)
{
	SDL_Rect pecran, prs;

	pecran.x = 0;
	pecran.y = 0;
	pecran.w = systeme->screenw;
	pecran.h = systeme->screenh;

	prs.w = systeme->screenw*0.7;
	prs.h = systeme->screenh*0.8;
	prs.x = (systeme->screenw - prs.w) / 2;
	prs.y = systeme->screenh*-0.2;


	SDL_Texture *chargement = LoadingImage("rs/images/chargement.png", 0, systeme);
	SDL_Texture *rs = LoadingImage("rs/fonds/rs.png", 0, systeme);
    SDL_RenderClear(systeme->renderer);
    SDL_RenderCopy(systeme->renderer, chargement, NULL, &pecran);
    pecran.y = 200;
    SDL_RenderCopy(systeme->renderer, chargement, NULL, &pecran);
    SDL_RenderCopy(systeme->renderer, rs, NULL, &prs);
    SDL_RenderPresent(systeme->renderer);
}

SDL_Texture* imprime (char s[], int len, int couleur, DIVERSsysteme *systeme, int *LenghtReturn, int *HighReturn)
{

    SDL_Surface *SurfTemp = NULL;
	static SDL_Color Noir = {0, 0, 0, 0};
	static SDL_Color Gris = {127, 127,127, 0};
	static SDL_Color Blanc = {255, 255, 255, 0};
	static SDL_Color Rouge = {255, 0, 0, 0};
	static SDL_Color Vert = {0, 255, 0, 0};
	static SDL_Color Bleu = {0, 0, 255, 0};

	if (couleur == BLANC)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police, (const char *)s, Blanc, len);
    }
    else if (couleur == ROUGE)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police, (const char *)s, Rouge, len);
    }
    else if (couleur == GRIS)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police, (const char *)s, Gris, len);
    }
	else if (couleur == NOIR)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police, (const char *)s, Noir, len);
    }
    else if (couleur == VERT)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police, (const char *)s, Vert, len);
    }
    else if (couleur == BLEU)
    {
        SurfTemp = TTF_RenderText_Blended_Wrapped(systeme->police, (const char *)s, Bleu, len);
    }
    SDL_Texture *TextureTemp = SDL_CreateTextureFromSurface(systeme->renderer, SurfTemp);

    if (LenghtReturn != NULL && HighReturn)
    {
        SDL_QueryTexture(TextureTemp, NULL, NULL, LenghtReturn, HighReturn);
    }
    SDL_FreeSurface(SurfTemp);
	return TextureTemp;
}

void ANIMmort (DIVERSsysteme *systeme)
{
	SDL_Rect pecran;

	pecran.x = 0;
	pecran.y = 0;
	pecran.w = systeme->screenw;
	pecran.h = systeme->screenh;

	SDL_RenderCopy(systeme->renderer, systeme->BGmort, NULL, &pecran);
    SDL_RenderPresent(systeme->renderer);
    #if FASTLOG == 0 //pour moi, pour ne pas attendre
    SDL_Delay(1500);
    #endif
}
