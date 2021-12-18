#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

/*#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>*/

#include "header1.h"

typedef struct
{
    char question[100];
    char reponse1[100];
    char reponse2[100];
    char reponse3[100];
    int numrep;
} enigmesf;

enigmesf generer();
int afficherenigme(enigmesf e, SDL_Surface*ecran);


#endif // FONCTION_H_INCLUDED

