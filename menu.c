/*#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "menu.h"*/
#include "header1.h"

void initialiser_sdl()
{
    //SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
    TTF_Init();
}


void fermer_sdl()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}


void affiche_nom_equipe(SDL_Surface *ecran,char nom_police[])//affiche le nom de lequipe sur l'ecran
{
    TTF_Font *police=NULL;
    SDL_Surface *texte=NULL;
    SDL_Color couleur_texte= {0,255,0};//couleur nom debut
    SDL_Rect position;


    position.x=60;
    position.y=ecran->h/2;

    police=TTF_OpenFont(nom_police,80);
    texte=TTF_RenderText_Blended(police,"   GALAXIUM   GAMES",couleur_texte);

    SDL_BlitSurface(texte,NULL,ecran,&position);

    TTF_CloseFont(police);

}

void charger_backgrounds(Background backgrounds[])
{
    backgrounds[background_menu].image=IMG_Load(/*"fond_ecran_menu.png"*/"resources/images/test.jpg");//chemin image background menu
    backgrounds[background_jouer].image=IMG_Load("resources/images/fond_ecran_jeu.png");//chemin image background jeu
    backgrounds[background_option].image=IMG_Load("resources/images/fond_ecran_option.png");//chemin image background option
    backgrounds[background_highest_scores].image=IMG_Load("resources/images/fond_ecran_option.png");

    backgrounds[background_menu].position.x=0;
    backgrounds[background_menu].position.y=0;

    backgrounds[background_jouer].position.x=0;
    backgrounds[background_jouer].position.y=0;

    backgrounds[background_option].position.x=0;
    backgrounds[background_option].position.y=0;

    backgrounds[background_menu].etat=background_menu;
    backgrounds[background_jouer].etat=background_jouer;
    backgrounds[background_option].etat=background_option;
    backgrounds[background_highest_scores].etat=background_highest_scores;
}


void charger_boutons(Boutton Button[],SDL_Surface *ecran)//charger les image des boutons
{
    Button[boutton_jouer].boutton_active=IMG_Load("resources/images/play_2.png");
    Button[boutton_jouer].boutton_desactive=IMG_Load("resources/images/play_1.png");

    Button[boutton_option].boutton_active=IMG_Load("resources/images/options_2.png");
    Button[boutton_option].boutton_desactive=IMG_Load("resources/images/options_1.png");

    Button[boutton_quitter].boutton_active=IMG_Load("resources/images/quitter_2.png");
    Button[boutton_quitter].boutton_desactive=IMG_Load("resources/images/quitter_1.png");

    Button[boutton_jouer].etat=0;
    Button[boutton_option].etat=0;
    Button[boutton_quitter].etat=0;


    Button[boutton_jouer].position.x=((ecran->w)/3)-20;
    Button[boutton_jouer].position.y=(ecran->h)/3 ;

    Button[boutton_option].position.x=((ecran->w)/3)-20 ;
    Button[boutton_option].position.y=8*(ecran->h)/15 ;

    Button[boutton_quitter].position.x=((ecran->w)/3)-20 ;
    Button[boutton_quitter].position.y= 11*(ecran->h)/15;
}


//collage des surfaces du menu(texte,bouttons,fond d'eran)
void coller_surface_menu(SDL_Surface *texte_nom_jeu,SDL_Rect position_texte,Background background_actuel, Boutton jouer,Boutton option,Boutton quitter,SDL_Surface *ecran)
{

    SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
    SDL_BlitSurface(texte_nom_jeu,NULL,ecran,&position_texte);

    if(jouer.etat==1)
        SDL_BlitSurface(jouer.boutton_active,NULL,ecran,&jouer.position);
    else
        SDL_BlitSurface(jouer.boutton_desactive,NULL,ecran,&jouer.position);

    if(option.etat==1)
        SDL_BlitSurface(option.boutton_active,NULL,ecran,&option.position);
    else
        SDL_BlitSurface(option.boutton_desactive,NULL,ecran,&option.position);

    if(quitter.etat==1)
        SDL_BlitSurface(quitter.boutton_active,NULL,ecran,&quitter.position);
    else
        SDL_BlitSurface(quitter.boutton_desactive,NULL,ecran,&quitter.position);

}

//cet fonction affiche le background du menu
void jouer(SDL_Surface *ecran,Background B)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(B.image,NULL,ecran,&B.position);
    SDL_Flip(ecran);

    SDL_Delay(2000);
}

//met a jour l'etat des boutons apres un clic
int etat_boutton_apres_clique(Boutton B,SDL_Event evenement)
{
    if(evenement.button.x>=B.position.x && evenement.button.x<=B.position.x+B.boutton_active->w  &&  evenement.button.y>=B.position.y && evenement.button.y<=B.position.y+B.boutton_active->h)
        return 1;
    else
        return 0;
}

//met a jour l'etat des boutons apres un mouvement de la souris
int etat_bouton_apres_mouvement_souris(Boutton B,SDL_Event evenement)
{
    if(evenement.motion.x>=B.position.x && evenement.motion.x<=B.position.x+B.boutton_desactive->w  &&  evenement.motion.y>=B.position.y && evenement.motion.y<=B.position.y+B.boutton_desactive->h)
        return 1;
    else
        return 0;
}
//charge les images qui constituent la parti options
void charger_image_option(Boutton option[3],SDL_Surface *ecran)
{
    int curseur_sur_barre_volume=1;

    option[high_scores].boutton_active=IMG_Load("resources/images/highest_score_2.png");//chargement des images du boutton "heighscores"
    option[high_scores].boutton_desactive=IMG_Load("resources/images/highest_score_1.png");

    option[curseur_sur_barre_volume].boutton_active=IMG_Load("resources/images/curseur_volume.png");//chargement de l'image du curseur sur la barre de volume

    option[high_scores].position.x=ecran->w/2;//initialisation de la position du bouttons highscores
    option[high_scores].position.y=3*(ecran->h)/4;
    option[high_scores].etat=0;

    option[control_ecran].boutton_active=IMG_Load("resources/images/bouton_normal_screen_1.png");
    option[control_ecran].boutton_desactive=IMG_Load("resources/images/bouton_fullscreen_1.png");

    option[control_ecran].position.x=(option[high_scores].position.x)-300;//initialisation de la position du bouttons highscores
    option[control_ecran].position.y=3*(ecran->h)/4;
    option[control_ecran].etat=0;

}
//blittage des surfaces de la sections options
void coller_surface_option(Boutton option[3],SDL_Surface *barre_volume,SDL_Surface *ecran,SDL_Rect position1,SDL_Rect position2,int dimension)
{
    //int high_scores=0;
    int curseur_sur_barre_volume=1;

    SDL_BlitSurface(barre_volume,NULL,ecran,&position1);

    SDL_BlitSurface(option[curseur_sur_barre_volume].boutton_active,NULL,ecran,&position2);

    if(option[high_scores].etat==0)
        SDL_BlitSurface(option[high_scores].boutton_desactive,NULL,ecran,&option[high_scores].position);
    else
        SDL_BlitSurface(option[high_scores].boutton_active,NULL,ecran,&option[high_scores].position);

    if(option[control_ecran].etat==0 && dimension==mode_fenetre)
        SDL_BlitSurface(option[control_ecran].boutton_desactive,NULL,ecran,&option[control_ecran].position);
    else if(option[control_ecran].etat==1 && dimension==mode_fenetre)
        SDL_BlitSurface(IMG_Load("resources/images/bouton_fullscreen_2.png"),NULL,ecran,&option[control_ecran].position);
    else if(option[control_ecran].etat==0 && dimension==mode_fullscreen)
        SDL_BlitSurface(option[control_ecran].boutton_active,NULL,ecran,&option[control_ecran].position);
    else if(option[control_ecran].etat==1 && dimension==mode_fullscreen)
        SDL_BlitSurface(IMG_Load("resources/images/bouton_normal_screen_2.png"),NULL,ecran,&option[control_ecran].position);
}

void initialisation_position(SDL_Rect *position_texte,SDL_Rect *position_barre,SDL_Rect *position_curseur,SDL_Rect *position_texte_option,SDL_Rect *position_texte_volume,SDL_Surface *ecran)
{

    position_barre->x=ecran->w/4;//position de la barre de volume dans la parti option
    position_barre->y=(ecran->h/2)-60;

    position_curseur->x= position_barre->x+250;
    position_curseur->y= position_barre->y+45;//position du curseur

    position_texte_volume->x=position_barre->x;//position texte volume
    position_texte_volume->y=position_barre->y+30;


    position_texte->x=((ecran->w)/5)+45;//position texte "NOM DU JEU"
    position_texte->y=(ecran->h)/20;

    position_barre->x=ecran->w/4;//position de la barre de volume
    position_barre->y=(ecran->h/2)-60;
    position_curseur->x= position_barre->x+250;
    position_curseur->y= position_barre->y+45;//position du curseur
    position_texte_volume->x=position_barre->x;//position texte "volume"
    position_texte_volume->y=position_barre->y+30;

    position_texte_option->x=(ecran->w)/3;//position texte "OPTION"
    position_texte_option->y=((ecran->h)/5);
}


void coller_surface_highestscore(Background B,SDL_Surface * score,SDL_Surface *ecran,SDL_Surface *H)
{
    SDL_Rect position;
    position.x=0;
    position.y=0;

    SDL_Rect position1;
    position1.x=0;
    position1.y=(ecran->h/4);

    SDL_Rect position2;
    position2.x=0;
    position2.y=(ecran->h/2);


    SDL_BlitSurface(B.image,NULL,ecran,&position);
    SDL_BlitSurface(H,NULL,ecran,&position1);
    SDL_BlitSurface(score,NULL,ecran,&position2);

}

/*void charger_animations(animation anim[],SDL_Surface *ecran)//charge les images des aniations
{
    anim[0].image=IMG_Load("animations_1.png");
    anim[0].position.x=0;
    anim[0].position.y=ecran->h-anim[0].image->h;

    anim[1].image=IMG_Load("animations_2.png");
    anim[1].position.x=ecran->w - anim[1].image->w;
    anim[1].position.y=0;

    anim[2].image=IMG_Load("animations_2.png");
    anim[2].position.x=0;
    anim[2].position.y=ecran->h - anim[2].image->h;

    anim[3].image=IMG_Load("animations_3.png");
    anim[3].position.x=ecran->w - anim[3].image->w;
    anim[3].position.y=ecran->h - anim[3].image->h;

}*/

/*void blit_animations(animation anim[],SDL_Surface *ecran)
{
    int i;
    for(i=0; i<4; i++)
    {
        SDL_BlitSurface(anim[i].image,NULL,ecran,&anim[i].position);
    }
}*/

/*void deplacer_animations(animation anim[])
{
    //anim[0].position.x=anim[0].position.x+7;
    anim[1].position.x=anim[1].position.x-7;
    anim[2].position.x=anim[2].position.x+7;
    //anim[3].position.x=anim[3].position.x-7;
}*/

//fonction qui gere le menu
int  MENU_jeu(SDL_Surface *ecran)
{
    int retour;//0 pour sortir du menu , 1 pour aller dans le jeu

    /**les backgrounds**/
    Background backgrounds[4];//les backgrounds
    Background background_actuel;//le background utiliser actuellement

    /**les bouttons**/
    Boutton Button[3];//bouttons du menu
    Boutton option[3];//bouttons des options

    SDL_Surface *barre_volume=NULL;
    SDL_Rect position_barre,position_curseur,position_texte_option,position_texte_volume;

    Mix_Music *son_menu=NULL;//les sons
    Mix_Chunk *son_boutton=NULL;

    SDL_Event evenement;//variable d'evenements

    int continuer=1,volume_music=128,dimension=mode_fenetre;//volume du sons continu,initailiser a la valeur max

    TTF_Font *police_nom_jeu=NULL,*police_volume=NULL;//les polices et colueurs
    SDL_Color couleur_nom_jeu= /*{73,109,130}*/ {39,86,106},couleur_texte_option= {39,60,71};

    //donnees concernant l'animation
    int temps_precedent=0,temps_actuel=0,i=0;
    //animation Animations[4];
    SDL_Rect pos_animations1,pos_animations2;

    SDL_Surface *texte_nom_jeu=NULL,*texte_option=NULL,*texte_volume=NULL;
    SDL_Rect position_texte;

    police_nom_jeu=TTF_OpenFont("resources/polices/Lordish.ttf",110);//chargement de la police
    police_volume=TTF_OpenFont("resources/polices/Enchanted Land.otf",40);
    TTF_Font *police_highest_scores=TTF_OpenFont("resources/polices/Lordish.ttf",90);

    charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
    charger_boutons(Button,ecran);
    son_menu=Mix_LoadMUS("resources/sons/son_jeu.wav");
    son_boutton=Mix_LoadWAV("resources/sons/click.wav");
    barre_volume=IMG_Load("resources/images/barre_volume.png");
    charger_image_option(option,ecran);
    //charger_animations(Animations,ecran);

    initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);//initialisation des positions

    texte_nom_jeu=TTF_RenderText_Blended(police_nom_jeu,"CoroKnight",couleur_nom_jeu);
    texte_volume=TTF_RenderText_Blended(police_volume,"VOLUME ",couleur_texte_option);
    texte_option=TTF_RenderText_Blended(police_nom_jeu,"Options",couleur_texte_option);


    float current_highest_score=-1;
    char highscore_character[1000];
    lire_highest_score("resources/sauvegardes/highestscores.txt",&current_highest_score);
    if(current_highest_score==-1)
        printf("echec de lecture du highestscore actuel\n");
    else
        sprintf(highscore_character,"%0.f",current_highest_score);

    SDL_Surface *texte_highestscores=NULL,*image_highestscore=NULL;
    texte_highestscores=TTF_RenderText_Blended(police_highest_scores,"Current_Highest_Score",couleur_nom_jeu);
    image_highestscore=TTF_RenderText_Blended(police_highest_scores,highscore_character,couleur_nom_jeu);

    background_actuel=backgrounds[background_menu];
    //background_actuel.etat=background_menu;
    /**background_actuel.dimension=mode_fenetre;**/

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
    SDL_Flip(ecran);

    Mix_VolumeMusic(volume_music);//initialisation music
    Mix_PlayMusic(son_menu,-1);


    while(continuer)
    {


        SDL_PollEvent(&evenement);

        /*if(background_actuel.etat==background_menu)
        {
            temps_actuel=SDL_GetTicks();
            if(temps_actuel-temps_precedent>1000)
            {
                deplacer_animations(Animations);
                coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                blit_animations(Animations,ecran);
                SDL_Flip(ecran);
                temps_precedent=temps_actuel;
            }

            if(temps_precedent>=3000)
            {
                temps_actuel=0;
                temps_precedent=0;
                charger_animations(Animations,ecran);
            }
        }*/
        /*if(background_actuel.etat==background_menu)
        {
            temps_actuel=SDL_GetTicks();
            if(temps_actuel-temps_precedent>2000)
            {
                coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                SDL_Flip(ecran);
                temps_precedent=temps_actuel;
                i++;
            }
            if(i==4)
                i=0;
        }*/



        switch(evenement.type)
        {
        case SDL_QUIT:
            continuer=0;
            //return 0;
            retour=0;
            break;
        case SDL_KEYDOWN:
            switch(evenement.key.keysym.sym)
            {
            case SDLK_j:
                if(background_actuel.etat==background_menu)
                {
                    Mix_PlayChannel(-1,son_boutton,0);//son clavier
                    Button[boutton_jouer].etat=1;
                    Button[boutton_option].etat=0;
                    Button[boutton_quitter].etat=0;

                    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                    //blit_animations(Animations,ecran);
                    //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                    SDL_Flip(ecran);
                    SDL_Delay(300);

                    //jouer
                    /*background_actuel=backgrounds[background_jouer];
                    jouer(ecran,background_actuel);*/
                    return 1;
                    /*retour=1;
                    continuer=0;*/
                    break;
                }
                else
                    break;

                break;

            case SDLK_o:
                if(background_actuel.etat==background_menu)
                {
                    Mix_PlayChannel(-1,son_boutton,0);
                    Button[boutton_jouer].etat=0;
                    Button[boutton_option].etat=1;
                    Button[boutton_quitter].etat=0;

                    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                    //blit_animations(Animations,ecran);
                    //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                    SDL_Flip(ecran);
                    SDL_Delay(300);

                    //option

                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    background_actuel=backgrounds[background_option];
                    SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);


                    SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                    SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                    coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                    SDL_Flip(ecran);

                    break;
                }
                else
                    break;

                break;
            case SDLK_q:
                if(background_actuel.etat==background_menu)
                {
                    Mix_PlayChannel(-1,son_boutton,0);
                    Button[boutton_jouer].etat=0;
                    Button[boutton_option].etat=0;
                    Button[boutton_quitter].etat=1;
                    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                    //blit_animations(Animations,ecran);
                    SDL_Flip(ecran);
                    SDL_Delay(300);
                    continuer=0;
                    retour=0;
                    break;
                }
                else
                    break;

                break;
            case SDLK_ESCAPE:
                if(background_actuel.etat==background_option)
                {
                    Mix_PlayChannel(-1,son_boutton,0);
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    Button[boutton_jouer].etat=0;
                    Button[boutton_option].etat=0;
                    Button[boutton_quitter].etat=0;
                    background_actuel=backgrounds[background_menu];
                    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                    //blit_animations(Animations,ecran);
                    //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                    SDL_Flip(ecran);

                    SDL_Delay(300);
                    break;
                }
                else if(background_actuel.etat==background_highest_scores)
                {
                    //option

                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    background_actuel=backgrounds[background_option];
                    SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);


                    SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                    SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                    coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                    SDL_Flip(ecran);
                    SDL_Delay(100);
                }

                /*else if(background_actuel.etat==background_jouer)
                {
                    Mix_PlayChannel(-1,son_boutton,0);
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    Button[boutton_jouer].etat=0;
                    Button[boutton_option].etat=0;
                    Button[boutton_quitter].etat=0;
                    background_actuel=backgrounds[background_menu];
                    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                    blit_animations(Animations,ecran);
                    SDL_Flip(ecran);

                    SDL_Delay(300);
                    break;
                }*/
                else
                    break;

                break;
            case SDLK_KP_MINUS:
                if(background_actuel.etat==background_option && volume_music>0)
                {
                    position_curseur.x=position_curseur.x-3;
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    background_actuel=backgrounds[background_option];
                    SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);

                    SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                    SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                    coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                    SDL_Flip(ecran);
                    volume_music=volume_music-1;
                    Mix_VolumeMusic(volume_music);
                    break;
                }
                else
                    break;

                break;
            case SDLK_KP_PLUS:
                if(background_actuel.etat==background_option && volume_music<128)
                {
                    position_curseur.x=position_curseur.x+3;
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    background_actuel=backgrounds[background_option];
                    SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);

                    SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                    SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                    coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                    SDL_Flip(ecran);
                    volume_music=volume_music+1;
                    Mix_VolumeMusic(volume_music);
                    break;
                }
                else
                    break;

                break;
            case SDLK_DOWN:
                if(background_actuel.etat!=background_menu)
                    break;
                else
                {
                    if(Button[boutton_jouer].etat==0 && Button[boutton_option].etat==0 && Button[boutton_quitter].etat==0)
                    {
                        Button[boutton_jouer].etat=1;
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                        //blit_animations(Animations,ecran);
                        //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                        SDL_Flip(ecran);
                        Mix_PlayChannel(-1,son_boutton,0);
                        SDL_Delay(300);
                        break;
                    }
                    if(Button[boutton_jouer].etat==1 && Button[boutton_option].etat==0 && Button[boutton_quitter].etat==0)
                    {
                        Button[boutton_jouer].etat=0;
                        Button[boutton_option].etat=1;
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                        //blit_animations(Animations,ecran);
                        //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                        SDL_Flip(ecran);
                        Mix_PlayChannel(-1,son_boutton,0);
                        SDL_Delay(300);
                        break;
                    }
                    if(Button[boutton_jouer].etat==0 && Button[boutton_option].etat==1 && Button[boutton_quitter].etat==0)
                    {
                        Button[boutton_jouer].etat=0;
                        Button[boutton_option].etat=0;
                        Button[boutton_quitter].etat=1;
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                        //blit_animations(Animations,ecran);
                        //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                        SDL_Flip(ecran);
                        Mix_PlayChannel(-1,son_boutton,0);
                        SDL_Delay(300);
                        break;
                    }
                }
                break;
            case SDLK_UP:
                if(background_actuel.etat!=background_menu)
                    break;
                else
                {

                    if(Button[boutton_jouer].etat==0 && Button[boutton_option].etat==0 && Button[boutton_quitter].etat==0)
                    {
                        Button[boutton_quitter].etat=1;
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                        //blit_animations(Animations,ecran);
                        //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                        SDL_Flip(ecran);
                        Mix_PlayChannel(-1,son_boutton,0);
                        SDL_Delay(300);
                        break;
                    }
                    if(Button[boutton_jouer].etat==0 && Button[boutton_option].etat==1 && Button[boutton_quitter].etat==0)
                    {
                        Button[boutton_jouer].etat=1;
                        Button[boutton_option].etat=0;
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                        //blit_animations(Animations,ecran);
                        //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                        SDL_Flip(ecran);
                        Mix_PlayChannel(-1,son_boutton,0);
                        SDL_Delay(300);
                        break;
                    }
                    if(Button[boutton_jouer].etat==0 && Button[boutton_option].etat==0 && Button[boutton_quitter].etat==1)
                    {
                        Button[boutton_jouer].etat=0;
                        Button[boutton_option].etat=1;
                        Button[boutton_quitter].etat=0;
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                        //blit_animations(Animations,ecran);
                        //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                        SDL_Flip(ecran);
                        Mix_PlayChannel(-1,son_boutton,0);
                        SDL_Delay(300);
                        break;
                    }

                }
                break;
            case SDLK_LEFT:
                if(background_actuel.etat!=background_option)
                    break;
                else
                {
                    if(option[control_ecran].etat==0 && option[high_scores].etat==0)
                    {
                        option[control_ecran].etat=0;
                        option[high_scores].etat=1;

                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }

                    else if(option[control_ecran].etat==1 && option[high_scores].etat==0)
                    {
                        option[control_ecran].etat=0;
                        option[high_scores].etat=1;

                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }

                    else if(option[control_ecran].etat==0 && option[high_scores].etat==1)
                    {
                        option[control_ecran].etat=1;
                        option[high_scores].etat=0;

                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }
                }
                SDL_Delay(100);
                break;
            case SDLK_RIGHT:
                if(background_actuel.etat!=background_option)
                    break;
                else
                {
                    if(option[control_ecran].etat==0 && option[high_scores].etat==0)
                    {
                        option[control_ecran].etat=1;
                        option[high_scores].etat=0;

                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }
                    else if(option[control_ecran].etat==1 && option[high_scores].etat==0)
                    {
                        option[control_ecran].etat=0;
                        option[high_scores].etat=1;

                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }
                    else if(option[control_ecran].etat==0 && option[high_scores].etat==1)
                    {
                        option[control_ecran].etat=1;
                        option[high_scores].etat=0;

                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }
                }
                SDL_Delay(100);
                break;
            case SDLK_RETURN:
                /*if(background_actuel.etat!=background_menu)
                    break;*/
                if(background_actuel.etat==background_menu)
                {
                    if(Button[boutton_jouer].etat==1)
                    {
                        Mix_PlayChannel(-1,son_boutton,0);
                        //jouer
                        //background_actuel.etat=background_jouer;
                        //jouer(ecran,backgrounds[background_jouer]);
                        //retour=1;
                        return 1;
                        //continuer=0;
                        break;
                    }
                    if(Button[boutton_option].etat==1)
                    {
                        Mix_PlayChannel(-1,son_boutton,0);
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                        background_actuel.etat=background_option;


                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        break;
                    }
                    if(Button[boutton_quitter].etat==1)
                    {
                        Mix_PlayChannel(-1,son_boutton,0);
                        Button[boutton_jouer].etat=0;
                        Button[boutton_option].etat=0;
                        Button[boutton_quitter].etat=1;
                        coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                        //blit_animations(Animations,ecran);
                        SDL_Flip(ecran);
                        SDL_Delay(300);
                        continuer=0;
                        retour=0;
                        break;
                    }

                }
                else if(background_actuel.etat==background_option)
                {
                    if(option[high_scores].etat==1)
                    {
                        background_actuel=backgrounds[background_highest_scores];
                        coller_surface_highestscore(background_actuel,image_highestscore,ecran,texte_highestscores);
                        SDL_Flip(ecran);
                    }
                    else if(option[control_ecran].etat==1)
                    {
                        if(dimension==mode_fullscreen)
                        {
                            option[control_ecran].etat=1;
                            option[high_scores].etat=0;
                            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                            coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                            SDL_Flip(ecran);
                            SDL_Delay(50);

                            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                            ecran=SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/);
                            charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
                            charger_boutons(Button,ecran);
                            initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);
                            position_curseur.x=position_curseur.x-3*(128-volume_music);
                            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                            background_actuel=backgrounds[background_option];
                            SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                            background_actuel.etat=background_option;

                            SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                            SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                            coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                            SDL_Flip(ecran);
                            dimension=mode_fenetre;
                        }
                        else if(dimension==mode_fenetre)
                        {
                            option[control_ecran].etat=1;
                            option[high_scores].etat=0;
                            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                            coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                            SDL_Flip(ecran);
                            SDL_Delay(300);

                            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                            ecran=SDL_SetVideoMode(largeur_fenetre_fullscreen,hauteur_fenetre_fullscreen,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/|SDL_FULLSCREEN);
                            charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
                            charger_boutons(Button,ecran);
                            initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);
                            position_curseur.x=position_curseur.x-3*(128-volume_music);
                            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                            background_actuel=backgrounds[background_option];
                            SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);

                            SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                            SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                            coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                            SDL_Flip(ecran);
                            dimension=mode_fullscreen;
                        }
                    }
                }
                break;
            case SDLK_n:
                if(background_actuel.etat==background_option && dimension==mode_fullscreen)
                {
                    option[control_ecran].etat=1;
                    option[high_scores].etat=0;
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                    SDL_Flip(ecran);
                    SDL_Delay(50);

                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    ecran=SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/);
                    charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
                    charger_boutons(Button,ecran);
                    initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);
                    position_curseur.x=position_curseur.x-3*(128-volume_music);
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    background_actuel=backgrounds[background_option];
                    SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                    background_actuel.etat=background_option;

                    SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                    SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                    coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                    SDL_Flip(ecran);
                    dimension=mode_fenetre;
                    break;
                }

                if(background_actuel.etat==background_menu && dimension==mode_fullscreen)
                {
                    SDL_Delay(300);
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    ecran=SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/);
                    charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
                    charger_boutons(Button,ecran);
                    initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);
                    position_curseur.x=position_curseur.x-3*(128-volume_music);
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    background_actuel=backgrounds[background_menu];
                    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                    //blit_animations(Animations,ecran);
                    //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                    SDL_Flip(ecran);
                    dimension=mode_fenetre;
                    break;

                }

                break;
            case SDLK_f:
                if(background_actuel.etat==background_option && dimension==mode_fenetre)
                {
                    option[control_ecran].etat=1;
                    option[high_scores].etat=0;
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                    SDL_Flip(ecran);
                    SDL_Delay(300);

                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    ecran=SDL_SetVideoMode(largeur_fenetre_fullscreen,hauteur_fenetre_fullscreen,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/|SDL_FULLSCREEN);
                    charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
                    charger_boutons(Button,ecran);
                    initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);
                    position_curseur.x=position_curseur.x-3*(128-volume_music);
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    background_actuel=backgrounds[background_option];
                    SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);

                    SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                    SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                    coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                    SDL_Flip(ecran);
                    dimension=mode_fullscreen;
                    break;
                }
                if(background_actuel.etat==background_menu && dimension==mode_fenetre)
                {
                    SDL_Delay(300);
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    ecran=SDL_SetVideoMode(largeur_fenetre_fullscreen,hauteur_fenetre_fullscreen,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/|SDL_FULLSCREEN);
                    charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
                    charger_boutons(Button,ecran);
                    initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);
                    position_curseur.x=position_curseur.x-3*(128-volume_music);
                    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                    background_actuel=backgrounds[background_menu];
                    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                    //blit_animations(Animations,ecran);
                    SDL_Flip(ecran);
                    dimension=mode_fullscreen;
                    break;

                }

                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch(evenement.button.button)
            {
            case SDL_BUTTON_LEFT:
                if(background_actuel.etat==background_menu)
                {
                    Button[boutton_jouer].etat=etat_boutton_apres_clique(Button[boutton_jouer],evenement);
                    Button[boutton_option].etat=etat_boutton_apres_clique(Button[boutton_option],evenement);
                    Button[boutton_quitter].etat=etat_boutton_apres_clique(Button[boutton_quitter],evenement);

                    if(Button[boutton_jouer].etat==1 || Button[boutton_option].etat==1 || Button[boutton_quitter].etat==1)
                        Mix_PlayChannel(-1,son_boutton,0);

                    coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                    //blit_animations(Animations,ecran);
                    //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                    SDL_Flip(ecran);
                    SDL_Delay(300);

                    if(Button[boutton_jouer].etat==1 )
                    {
                        /*background_actuel.etat=background_jouer;
                        jouer(ecran,backgrounds[background_jouer]);*/
                        return 1;
                        //retour=1;
                        //continuer=0;
                    }

                    else if(Button[boutton_option].etat==1)
                    {

                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);

                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);


                    }
                    else if(Button[boutton_quitter].etat==1)
                    {
                        continuer=0;
                        SDL_Delay(1000);
                        //return 0;
                        retour=0;
                        //sortir du menu et du jeu;
                        break;
                    }
                }

                else if(background_actuel.etat==background_option)
                {
                    option[control_ecran].etat=etat_boutton_apres_clique(option[control_ecran],evenement);
                    option[high_scores].etat=etat_boutton_apres_clique(option[high_scores],evenement);

                    if(option[control_ecran].etat==1 || option[high_scores].etat==1)
                        Mix_PlayChannel(-1,son_boutton,0);

                    if(option[control_ecran].etat==1 && dimension==mode_fenetre)
                    {
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        SDL_Delay(300);

                        ecran=SDL_SetVideoMode(largeur_fenetre_fullscreen,hauteur_fenetre_fullscreen,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/|SDL_FULLSCREEN);
                        charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
                        charger_boutons(Button,ecran);
                        initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);
                        position_curseur.x=position_curseur.x-3*(128-volume_music);
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);

                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        dimension=mode_fullscreen;
                        break;
                    }

                    if(option[control_ecran].etat==1 && dimension==mode_fullscreen)
                    {
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        SDL_Delay(50);

                        ecran=SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_RESIZABLE*/);
                        charger_backgrounds(backgrounds);//chargement des resources(images,sons) et initialisation des positions
                        charger_boutons(Button,ecran);
                        initialisation_position(&position_texte,&position_barre,&position_curseur,&position_texte_option,&position_texte_volume,ecran);
                        position_curseur.x=position_curseur.x-3*(128-volume_music);
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        background_actuel=backgrounds[background_option];
                        SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                        background_actuel.etat=background_option;

                        SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                        SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                        coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                        SDL_Flip(ecran);
                        dimension=mode_fenetre;
                        break;
                    }
                    break;

                }
                break;

            }
            break;
        case SDL_MOUSEMOTION:
            if(background_actuel.etat==background_menu && Button[boutton_jouer].etat==0 && Button[boutton_option].etat==0 && Button[boutton_quitter].etat==0)
            {
                Button[boutton_jouer].etat=etat_bouton_apres_mouvement_souris(Button[boutton_jouer],evenement);
                Button[boutton_option].etat=etat_bouton_apres_mouvement_souris(Button[boutton_option],evenement);
                Button[boutton_quitter].etat=etat_bouton_apres_mouvement_souris(Button[boutton_quitter],evenement);

                coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                //blit_animations(Animations,ecran);
                //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                SDL_Flip(ecran);
                SDL_Delay(50);

                if(Button[boutton_jouer].etat==1 || Button[boutton_option].etat==1 || Button[boutton_quitter].etat==1)
                {
                    Mix_PlayChannel(-1,son_boutton,0);
                    break;
                }
                //break;
            }
            if(background_actuel.etat==background_menu &&( Button[boutton_jouer].etat==1 || Button[boutton_option].etat==1 || Button[boutton_quitter].etat==1))
            {
                Button[boutton_jouer].etat=etat_bouton_apres_mouvement_souris(Button[boutton_jouer],evenement);
                Button[boutton_option].etat=etat_bouton_apres_mouvement_souris(Button[boutton_option],evenement);
                Button[boutton_quitter].etat=etat_bouton_apres_mouvement_souris(Button[boutton_quitter],evenement);

                coller_surface_menu(texte_nom_jeu,position_texte,background_actuel,Button[boutton_jouer],Button[boutton_option],Button[boutton_quitter],ecran);
                //blit_animations(Animations,ecran);
                //SDL_BlitSurface(Animations[i].image,NULL,ecran,&Animations[0].position);
                SDL_Flip(ecran);
                SDL_Delay(50);
                break;
            }
            if(background_actuel.etat==background_option && option[high_scores].etat==0 && option[control_ecran].etat==0)
            {
                option[high_scores].etat=etat_bouton_apres_mouvement_souris(option[high_scores],evenement);
                option[control_ecran].etat=etat_bouton_apres_mouvement_souris(option[control_ecran],evenement);
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                //background_actuel=backgrounds[background_option];
                SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                //background_actuel.etat=background_option;

                SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                SDL_Flip(ecran);

                if(option[high_scores].etat==1 || option[control_ecran].etat==1)
                {
                    Mix_PlayChannel(-1,son_boutton,0);
                    break;
                }
                break;
            }
            if(background_actuel.etat==background_option && (option[high_scores].etat==1 || option[control_ecran].etat==1))
            {
                option[high_scores].etat=etat_bouton_apres_mouvement_souris(option[high_scores],evenement);
                option[control_ecran].etat=etat_bouton_apres_mouvement_souris(option[control_ecran],evenement);
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(background_actuel.image,NULL,ecran,&background_actuel.position);
                SDL_BlitSurface(texte_volume,NULL,ecran,&position_texte_volume);
                SDL_BlitSurface(texte_option,NULL,ecran,&position_texte_option);
                coller_surface_option(option,barre_volume,ecran,position_barre,position_curseur,dimension);
                SDL_Flip(ecran);
                break;
            }
            break;

        }
    }

    //liberation des resources
    SDL_FreeSurface(backgrounds[background_jouer].image);
    SDL_FreeSurface(backgrounds[background_option].image);
    SDL_FreeSurface(backgrounds[background_jouer].image);

    SDL_FreeSurface(Button[boutton_jouer].boutton_active);
    SDL_FreeSurface(Button[boutton_jouer].boutton_desactive);
    SDL_FreeSurface(Button[boutton_option].boutton_active);
    SDL_FreeSurface(Button[boutton_option].boutton_desactive);
    SDL_FreeSurface(Button[boutton_quitter].boutton_active);
    SDL_FreeSurface(Button[boutton_quitter].boutton_desactive);


    return retour;
}


