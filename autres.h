#ifndef AUTRES_H_INCLUDED
#define AUTRES_H_INCLUDED

#include "header1.h"

#define quitter_sans_sauvegarde 0
#define quitter_et_sauvegader 1
#define annuler 2

#define resume_game 1
#define back_to_menu 2



void charger_boutton_quitter(Boutton button[],SDL_Surface *ecran);

void coller_surface_quitter(Boutton button[],SDL_Surface *ecran);

int quitter(Personnage p,background b,SDL_Surface *ecran,int niveau_actuel,temps t);

void charger_boutton_pause(Boutton Pause[],SDL_Surface *ecran);

void coller_surface_pause(SDL_Surface *ecran,Boutton button[]);

int enigme_avec_ou_sans_fichier();

void quel_sauvegarde_ecrire(char nom_fichier[],int nombre_joueur,int niveau);

void quel_sauvegarde_lire(char nom_fichier[],int *nombre_joueur,int *niveau);

int mise_a_jour_highscores(char nom_fichier[],float score);

void lire_highest_score(char nom_fichier[],float *score);


#endif // AUTRES_H_INCLUDED
