#ifndef HEADER1_H_INCLUDED
#define HEADER1_H_INCLUDED


/*bibliotheque standard*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/*bibliotheque SDL*/
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/*bibliotheque personnel*/
#include "menu.h"
#include "background.h"
#include "PERSO.h"
#include "enigmesf.h"
#include "es.h"
#include "minimap.h"
#include "enigme.h"
#include "interface_debut_jeu.h"
#include "jeu.h"
#include "jeu_multijoueur.h"
#include "saved_games.h"
#include "autres.h"

#define hauteur_fenetre 550/*600*///dimensions de la fenetre
#define largeur_fenetre 800/*800*/

#define hauteur_fenetre_fullscreen 550//dimensions de la fenetre en mode fullscreen
#define largeur_fenetre_fullscreen 800

#define avancement_scrolling 10
#define avancement_scrolling_rapide 20

#endif // HEADER1_H_INCLUDED
