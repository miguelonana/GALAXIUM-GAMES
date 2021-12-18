#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED

#include "header1.h"


typedef struct
{
    SDL_Surface* minimp;
    SDL_Surface* symbplayer;
    //SDL_Surface* symbenemi ;
    /*SDL_Event ev;
    float possymplayerX;
    float possymplayerY;*/
    // float possymenemiX;
    //float possymenemiY;
    SDL_Rect position_symb;
    SDL_Rect position_minimap;
} minimap;


/*typedef struct
{
    Uint32 start;
    //TTF_Font *font;
    SDL_Surface *seconds;
    SDL_Color textColor;
    char timeshown[100];

} temps;*/


typedef struct
{
	SDL_Surface *texte;
	SDL_Rect position;

	TTF_Font *police;

	char entree[100];
	int secondesEcoulees;
	SDL_Color couleur;
	time_t t1, t2;
	int min, sec;
}temps;

void initminimap(minimap *m,int niveau,SDL_Surface *ecran);

int majminimap(SDL_Rect posJ,int redimensionnement,minimap m);

void afficher_minimap(minimap m,SDL_Surface *ecran);

void free_minimap(minimap m);

void initialiser_temps(temps *t,minimap m);

void afficher_temps(temps *t, SDL_Surface *screen,TTF_Font *police);

SDL_Color GetPixel(SDL_Surface *Background, int x, int y);

int collisionPP(Personnage p, SDL_Surface *Masque);


//void Initemps(temps *t);

/*minimap afficherminimap(minimap m,SDL_Surface * screen);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void Initemps(temps *t);
temps affichertemps(temps t,SDL_Surface* screen);
int collisionBB(MC m, Entity e)*/


#endif // MINIMAP_H_INCLUDED
