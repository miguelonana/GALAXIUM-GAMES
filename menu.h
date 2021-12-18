#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


/*#define hauteur_fenetre 650//dimensions de la fenetre
#define largeur_fenetre 780*/

#include "header1.h"

#define background_menu 0//constantes pour les backgrounds
#define background_jouer 1
#define background_option 2
#define background_highest_scores 3

#define boutton_jouer 0//constantes pour les bouttons du menu
#define boutton_option 1
#define boutton_quitter 2

#define high_scores 0//constantes pour les bouttons des options
#define control_ecran 2

/*#define hauteur_fenetre_fullscreen 700
#define largeur_fenetre_fullscreen 950*/

enum {mode_fenetre,mode_fullscreen};


//structure boutton
typedef struct
{
    int etat;
    SDL_Surface *boutton_active;
    SDL_Surface *boutton_desactive;
    SDL_Rect position;
} Boutton;

//structure background(fond d'ecran)
typedef struct
{
    int etat;
    SDL_Surface *image;
    SDL_Rect position;
    //int dimension;
} Background;

//structure animations pour le menu
/*typedef struct
{
    SDL_Surface *image;
    SDL_Rect position;
} animation;*/

void initialiser_sdl();

void fermer_sdl();//ferme toutes les parties de la SDL

void affiche_nom_equipe(SDL_Surface *ecran,char nom_police[]);//affiche le nom de l'equipe

void charger_backgrounds(Background backgrounds[]);//charge les images des backgrounds

void charger_boutons(Boutton Button[],SDL_Surface *ecran);//charge les image des boutons

void coller_surface_menu(SDL_Surface *texte_nom_jeu,SDL_Rect position_texte,Background background_actuel, Boutton jouer,Boutton option,Boutton quitter,SDL_Surface *ecran);//blittage des surfaces de la sections menu

//void jouer(SDL_Surface *ecran,Background B);//affiche le background du jeu

int etat_boutton_apres_clique(Boutton B,SDL_Event evenement);//met a jour l'etat des boutton apres un clique

int etat_bouton_apres_mouvement_souris(Boutton B,SDL_Event evenement);//met a jour l'etat des boutton apres un mouvement du curseur

void charger_image_option(Boutton option[3],SDL_Surface *ecran);//charge les images de la sections options

void coller_surface_option(Boutton option[3],SDL_Surface *barre_volume,SDL_Surface *ecran,SDL_Rect position1,SDL_Rect position2,int dimension);//blittage des surfaces de la sections options

void initialisation_position(SDL_Rect *position_texte,SDL_Rect *position_barre,SDL_Rect *position_curseur,SDL_Rect *position_texte_option,SDL_Rect *position_texte_volume,SDL_Surface *ecran);//initialise la position des textes et de la barre de volume en fonctions de l'ecran

//void charger_animations(animation anim[],SDL_Surface *ecran);//charge les images des aniations

//void blit_animations(animation anim[],SDL_Surface *ecran);

//void deplacer_animations(animation anim[]);

void coller_surface_highestscore(Background B,SDL_Surface * score,SDL_Surface *ecran,SDL_Surface *H);

int MENU_jeu(SDL_Surface *ecran);//fonction qui gere le menu



#endif // MENU_H_INCLUDED

