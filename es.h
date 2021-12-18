/**
*@file es.h
*@author Nayrouz Tebib
*@version 1.0
*@date
*/

#ifndef ES_H_INCLUDED
#define ES_H_INCLUDED


#include "header1.h"

//structs
typedef enum state state;
enum state {waiting,following,attacking};

/**
* @struct enemy
* @brief struct for 2nd entity
*/
typedef struct
{
	SDL_Surface *img_attacking_gauche;
	SDL_Surface *img_attacking_droite;

	//SDL_Surface *img_waiting;

	SDL_Surface *img_following_gauche;
	SDL_Surface *img_following_droite;

	//SDL_Surface *img;/*!< pictures*/

	SDL_Rect pos; /*!< pos dans sprite sheet*/
	SDL_Rect poss; /*!< pos on the screen*/

	int dir; /*!< direction*/
	state s; /*!< status*/

	int battu;
}enemy;



//declaration des fonctions
void initEnnemi(enemy *e);//done
void afficherEnnemi(enemy e, SDL_Surface * screen);//done
void animerEnnemi( enemy * e);//done
void deplacer( enemy * e);//done
void deplacerp( enemy * e);//testi beha el dep taa lperso
int collisionBB( Personnage p, enemy e); // int collisionBB( SDL_Rect posp,  SDL_Rect pose) ; done zeda
void updateEnnemi (enemy *e, Personnage p);

#endif // ES_H_INCLUDED
