#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

/*#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>*/
//#include "PERSO.h"

#include "header1.h"

//enum{gauche,droite,haut,bas};

typedef struct
{
    SDL_Surface *image;

    SDL_Rect camera_pos1;
    SDL_Rect camera_pos2;

    SDL_Rect pos_background1;
    SDL_Rect pos_background2;
} background;


void init_background(background *bckg,SDL_Surface *ecran,int niveau);

void afficher_background(background bckg,SDL_Surface *screen);

void scrolling(background *bckg,int direction,int pasAvancement);

void scrolling_2(background *bckg,int direction,int pasAvancement);//scrolling pour le deuxieme background

void init_background_multijoueur(background *bckg,SDL_Surface *ecran,int niveau);

void afficher_background_multijoueur(background bckg,SDL_Surface *screen);

#endif // BACKGROUND_H_INCLUDED
