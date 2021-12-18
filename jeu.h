#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "header1.h"


typedef struct
{
	int vies;
	SDL_Surface *attack_left;
	SDL_Surface *attack_right;
	SDL_Surface *stay_left;
	SDL_Surface *stay_right;
	SDL_Rect position;
	int action;
	int action_precedente;
}boss;

void intro(SDL_Surface *ecran,int mode_de_jeu);

int collision_pieces(SDL_Rect pos_pieces,Personnage p);

int niveau1_mono_joueur(SDL_Surface *ecran);

int niveau2_mono_joueur(SDL_Surface *ecran);

int niveau3_mono_joueur(SDL_Surface *ecran);


#endif // JEU_H_INCLUDED
