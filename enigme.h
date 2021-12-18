#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED

/*#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>
#include <string.h>*/
//#include "PERSO.h"


#include "header1.h"

typedef struct
{
    char question[100];
    char rep1[100];
    char rep2[100];
    char rep3[100];
    char repjuste[100];
    SDL_Surface *Q,*R1,*R2,*R3;
    SDL_Rect positionQ,positionR1,positionR2,positionR3;
    int reponse_juste;
} enigme;

void afficherEnigme(enigme e, SDL_Surface *screen);

void genererEnigme(enigme *e, char question[]);

int sauvegarde_monojoueur(Personnage p,background b,char nom_fichier[],int niveau_actuel);

//void sauvegarde_monojoueur(Personnage p,char nom_fichier[],int niveau_actuel);

//void sauvegarde_multijoueur(Personnage p1,Personnage p2,char nom_fichier[],int niveau_actuel);

int charger_monojoueur(Personnage *p,background *b,char nom_fichier[],int *niveau_actuel);

//int charger_monojoueur(Personnage *p,char nom_fichier[],int *niveau_actuel,SDL_Rect *position);

int charger_monojoueur(Personnage *p,background *b,char nom_fichier[],int *niveau_actuel);

int charger_multijoueur(Personnage *p1,Personnage *p2,char nom_fichier[],int *niveau_actuel);

int resoudre_enigme(enigme e,SDL_Surface *ecran);

void sauvergade_perso(Personnage p,char nomfichier[]);

void sauvegarde_background(background b,int niveau,char nomfichier[]);

void sauvegarde_temps(temps t,char nomfichier[]);

void load_time(temps *t,char nomfichier[]);

void load_background(background *b,int *niveau,char nomfichier[]);

void load_perso(Personnage *p,char nomfichier[]);


void sauvegarde_transition(Personnage p,background b,temps t,int niveau);

void sauvegardes_quitter(Personnage p,background b,temps t,int niveau);

void load_transition(Personnage *p,background *b,temps *t,int *niveau);

void load_quitter(Personnage *p,background *b,temps *t,int *niveau);

// void sauvegarder (personne p, background b, char *nomfichier);
// int charger(personne *p, background *b, char *nomfichier);

#endif // ENIGME_H_INCLUDED
