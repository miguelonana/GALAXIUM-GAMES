#ifndef INTERFACE_DEBUT_JEU_H_INCLUDED
#define INTERFACE_DEBUT_JEU_H_INCLUDED


#include "header1.h"


enum{partie,mode_jeu,charger_partie,nouvelle_partie,skip,multi_joueur,mono_joueur,keyboard_et_souris};


#define boutton_nouvelle_partie 0
#define boutton_charger_partie 1
#define boutton_mono_joueur 2
#define boutton_multi_joueur 3


#define keyboard 0
#define souris 1
#define mannette 2

void charger_resources_interface(Boutton Button[],SDL_Surface *ecran);

void charger_resources_interface_choix_inputs_2(Boutton inputs[],SDL_Surface *ecran);

void coller_surface(int stade,Boutton button[],SDL_Surface *ecran);

int interface_choix_mode_jeu(SDL_Surface *ecran);

void charger_resources_interface_choix_inputs(Boutton inputs[],SDL_Surface *ecran);

void charger_resources_interface_choix_inputs_2(Boutton inputs[],SDL_Surface *ecran);

void coller_surface_interface_inputs(Boutton inputs[],SDL_Surface *ecran,int mode_de_jeu,SDL_Surface *fond_ecran,SDL_Surface *textes[],SDL_Rect position_texte1,SDL_Rect position_texte2,Boutton inputs2[]);

int interface_choix_input(SDL_Surface *ecran,int mode_de_jeu);

#endif // INTERFACE_DEBUT_JEU_H_INCLUDED
