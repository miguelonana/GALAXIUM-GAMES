#ifndef JEU_MULTIJOUEUR_H_INCLUDED
#define JEU_MULTIJOUEUR_H_INCLUDED

#include "header1.h"


typedef struct
{
    SDL_Surface* minimp;
    SDL_Surface* symbplayer1;
    SDL_Surface* symbplayer2;
    SDL_Rect position_symb1;
    SDL_Rect position_symb2;
    SDL_Rect position_minimap;
} minimap_multijoueur;


void initminimap2(minimap_multijoueur *m,int niveau,SDL_Surface *ecran);

void afficher_minimap2(minimap_multijoueur m,SDL_Surface *ecran);

void free_minimap2(minimap_multijoueur m);

void initialiser_temps2(temps *t,minimap_multijoueur m);

int majminimap2(SDL_Rect posJ,int redimensionnement,minimap_multijoueur m);

int niveau1_multi_joueur(SDL_Surface *ecran);


#endif // JEU_MULTIJOUEUR_H_INCLUDED