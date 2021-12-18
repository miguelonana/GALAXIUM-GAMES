/*#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>*/
#include "header1.h"


int main(int argc, char** argv)
{
    SDL_Surface *ecran=NULL;//l'ecran

    int evolution=1;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    int niveau,nombre_joueur;

//initialisation de la sdl
    initialiser_sdl();

    SDL_WM_SetIcon(IMG_Load(/*"Logo.png"*/"resources/images/Logo.png"),NULL);//icon fenetre du jeu

    ecran=SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/);//lecran

    SDL_WM_SetCaption("CoroKnight",NULL);//nom jeu

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));//ouverture de lecran
    SDL_Flip(ecran);
    SDL_Delay(1000);

//affichage du nom de l'equipe au debut
    Mix_Chunk  *son_debut=NULL;
    son_debut=Mix_LoadWAV(/*"son_debut.wav"*/"resources/sons/son_debut.wav");
    Mix_PlayChannel(-1,son_debut,0);
    affiche_nom_equipe(ecran,/*"Enchanted Land.otf"*/"resources/polices/Enchanted Land.otf");//affiche un texte a l'ecran avant le jeu.(nom du groupe)
    SDL_Flip(ecran);
    SDL_Delay(7000);
//fin affichage nom equipe

    do
    {
        switch(MENU_jeu(ecran))
        {
        case 0:
            evolution=0;
            break;
        case 1:
            switch(interface_choix_mode_jeu(ecran))
            {
            case charger_partie:
                //sauvegarde_monojoueur(p,b,"sauvegarde_monojoueur.bin",1);
                quel_sauvegarde_lire(/*"resources\sauvegardes2\quel.txt"*/"resources/sauvegardes2/quel.txt",&nombre_joueur,&niveau);
                if(nombre_joueur==1)
                {
                    switch(niveau)
                    {
                    case 1:
                        if(niveau1_mono_joueur_from_save(ecran))
                        {
                            SDL_BlitSurface(IMG_Load(/*"annonce_niv2.png"*/"resources/images/annonce_niv2.png"),NULL,ecran,&position);
                            SDL_Flip(ecran);
                            SDL_Delay(1000);
                            if(niveau2_mono_joueur(ecran)==1)
                            {
                                /**niveau 3**/
                                SDL_BlitSurface(IMG_Load(/*"annonce_niv3.png"*/"resources/images/annonce_niv3.png"),NULL,ecran,&position);
                                SDL_Flip(ecran);
                                SDL_Delay(1000);
                                if(niveau3_mono_joueur(ecran)==1)
                                {
                                    /*fin du jeu*/
                                    SDL_BlitSurface(IMG_Load(/*"jeu_complete.png"*/"jeu_complete.png"),NULL,ecran,&position);
                                    SDL_Flip(ecran);
                                    SDL_Delay(3000);
                                }
                                break;
                            }
                        }
                        break;
                    case 2:
                        if(niveau2_mono_joueur_from_save(ecran))
                        {
                            SDL_BlitSurface(IMG_Load(/*"annonce_niv3.png"*/"resources/images/annonce_niv3.png"),NULL,ecran,&position);
                            SDL_Flip(ecran);
                            SDL_Delay(1000);
                            if(niveau3_mono_joueur(ecran)==1)
                            {
                                /*fin du jeu*/
                                SDL_BlitSurface(IMG_Load(/*"jeu_complete.png"*/"resources/images/jeu_complete.png"),NULL,ecran,&position);
                                SDL_Flip(ecran);
                                SDL_Delay(3000);
                            }
                            break;
                        }
                        break;
                    case 3:
                        if(niveau3_mono_joueur_from_save(ecran)==1)
                        {
                            /*fin du jeu*/
                            SDL_BlitSurface(IMG_Load(/*"jeu_complete.png"*/"resources/images/jeu_complete.png"),NULL,ecran,&position);
                            SDL_Flip(ecran);
                            SDL_Delay(3000);
                        }
                        break;

                    }
                }
                break;
            case mono_joueur:
                if(interface_choix_input(ecran,mono_joueur)==keyboard || interface_choix_input(ecran,mono_joueur)==keyboard_et_souris)
                {
                    intro(ecran,mono_joueur);
                    SDL_BlitSurface(IMG_Load(/*"annonce_niv1.png"*/"resources/images/annonce_niv1.png"),NULL,ecran,&position);
                    SDL_Flip(ecran);
                    SDL_Delay(1000);
                    if(niveau1_mono_joueur(ecran)==1)
                    {
                        /**niveau 2**/
                        SDL_BlitSurface(IMG_Load(/*"annonce_niv2.png"*/"resources/images/annonce_niv2.png"),NULL,ecran,&position);
                        SDL_Flip(ecran);
                        SDL_Delay(1000);
                        if(niveau2_mono_joueur(ecran)==1)
                        {
                            /**niveau 3**/
                            SDL_BlitSurface(IMG_Load(/*"annonce_niv3.png"*/"resources/images/annonce_niv3.png"),NULL,ecran,&position);
                            SDL_Flip(ecran);
                            SDL_Delay(1000);
                            if(niveau3_mono_joueur(ecran)==1)
                            {
                                /*fin du jeu*/
                                SDL_BlitSurface(IMG_Load(/*"jeu_complete.png"*/"resources/images/jeu_complete.png"),NULL,ecran,&position);
                                SDL_Flip(ecran);
                                SDL_Delay(3000);
                            }
                        }
                    }
                }
                else if(interface_choix_input(ecran,mono_joueur)==mannette)
                {
                    //jouer avec la mannette de jeu
                    break;
                }
                break;
            case multi_joueur:
                if(interface_choix_input(ecran,multi_joueur)==keyboard)
                {
                    intro(ecran,multi_joueur);
                    niveau1_multi_joueur(ecran);
                }
                break;
            }
            break;
        }
    }
    while(evolution!=0);

    fermer_sdl();//fermeture de la sdl
    SDL_FreeSurface(ecran);//liberation de l'ecran
    Mix_FreeChunk(son_debut);//liberation
    SDL_Quit();
    exit(EXIT_SUCCESS);
    return 0;
}
