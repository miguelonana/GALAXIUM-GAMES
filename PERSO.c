/*#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "PERSO.h"
#include <math.h>*/

#include "header1.h"

void init(Personnage *p,int num_perso)
{
    p->player_number=num_perso;
}


void init_perso(Personnage *p,SDL_Surface *ecran)//initialisation personnage 1
{
    int vitesse_max=1;

    p->image_actuel=IMG_Load("resources/images/surplace_droite.png");
    p->position_sprite.x=0;
    p->position_sprite.y=0;
    p->position_sprite.w=90;
    p->position_sprite.h=p->image_actuel->h;
    p->action_precedente=-1;
    p->action=surplace_droite;
    p->direction=droite;

    p->nombre_vie=5;
    p->score=0;
    p->position.y=ecran->h-p->image_actuel->h-60;
    p->position.x=150;

    p->vitesse=vitesse_max;
    p->acceleration=0;

    charger_image_animation(p->ANIMATION);//chargement des animations



}

void init_perso2(Personnage *p,SDL_Surface *ecran)//initialisation personnage 2
{
    int vitesse_max=1;


    p->image_actuel=IMG_Load("resources/images/perso2_surplace_droite.png");
    p->position_sprite.x=0;
    p->position_sprite.y=0;
    p->position_sprite.w=90;
    p->position_sprite.h=p->image_actuel->h;

    p->nombre_vie=5;
    p->score=0;
    p->position.y=ecran->h-p->image_actuel->h-60;
    p->position.x=(ecran->w/2) + p->position_sprite.w+150;
    p->direction=droite;
    p->action=surplace_droite;
    p->vitesse=vitesse_max;
    p->acceleration=0;
    p->action_precedente=surplace_droite;

    charger_image_animation2(p->ANIMATION);
}



void afficher_perso(Personnage p,SDL_Surface *ecran,TTF_Font *police)
{
    //TTF_Font *police=NULL;
    SDL_Surface *image_vie=NULL,*image_score=NULL,*image_player_num=NULL;
    char score[100000],player_number[100];
    SDL_Color couleur= {255,255,255};
    SDL_Rect position_vie,position_score,position_num_player;
    int i;

    //police=TTF_OpenFont("resources/polices/police.ttf",20);
    image_vie=IMG_Load("resources/images/vie.png");


    sprintf(player_number,"PLAYER %d",p.player_number);
    image_player_num=TTF_RenderText_Blended(police,player_number,couleur);

    sprintf(score,"SCORE: %0.f",p.score);
    image_score=TTF_RenderText_Blended(police,score,couleur);


    if(p.player_number==1)
    {
        position_num_player.x=10;
        position_num_player.y=10;

        position_vie.x=position_num_player.x;
        position_vie.y=19+position_num_player.y;

        position_score.x=position_num_player.x;
        position_score.y=51+position_vie.y;
    }
    else if(p.player_number==2)
    {
        position_num_player.x=(ecran->w/2)+10;
        position_num_player.y=10;

        position_vie.x=position_num_player.x;
        position_vie.y=19+position_num_player.y;

        position_score.x=position_num_player.x;
        position_score.y=51+position_vie.y;

    }


    // SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(image_player_num,NULL,ecran,&position_num_player);
    for(i=0; i<p.nombre_vie; i++)
    {
        SDL_BlitSurface(image_vie,NULL,ecran,&position_vie);
        position_vie.x=position_vie.x+47+5;
    }
    SDL_BlitSurface(image_score,NULL,ecran,&position_score);
    SDL_BlitSurface(p.image_actuel,&p.position_sprite,ecran,&p.position);


    /*liberation des resources*/
    SDL_FreeSurface(image_vie);
    SDL_FreeSurface(image_score);
    SDL_FreeSurface(image_player_num);
    //SDL_FreeSurface(image_player_num);
    //TTF_CloseFont(police);
}


void deplacer_perso(Personnage *p,int dt)
{
    int dx;

    dx=((p->acceleration/2)*(dt*dt))+(p->vitesse*dt);

    if(p->direction==gauche && p->position.x>20)
        p->position.x=p->position.x-(dx/2);
    else if(p->direction==droite && p->position.x<largeur_fenetre-25)
        p->position.x=p->position.x+(dx/2);
    else if(p->direction==haut)
        p->position.y=p->position.y-(dx/2);
    else if(p->direction==bas)
        p->position.y=p->position.y+(dx/2);

    /*p->direction=-1;
    p->action=-1;*/
}

void charger_image_animation(animation ANIMATION[])
{
    /*marcher vers la droite*/
    ANIMATION[marcher_droite].sprite_sheet=IMG_Load("resources/images/courrir_droite.png");
    ANIMATION[marcher_droite].largeur=90;
    ANIMATION[marcher_droite].x_max=810;
    ANIMATION[marcher_droite].num_sprite=marcher_droite;
    ANIMATION[marcher_droite].nombre_image=9;


    /*marcher vers la gauche*/
    ANIMATION[marcher_gauche].sprite_sheet=IMG_Load("resources/images/courrir_gauche.png");
    ANIMATION[marcher_gauche].largeur=90;
    ANIMATION[marcher_gauche].x_max=810;
    ANIMATION[marcher_gauche].num_sprite=marcher_gauche;
    ANIMATION[marcher_gauche].nombre_image=9;


    /*frapper vers la droite*/
    ANIMATION[frapper_droite].sprite_sheet=IMG_Load("resources/images/attaque_droite.png");//frapper a droite
    ANIMATION[frapper_droite].largeur=150;
    ANIMATION[frapper_droite].x_max=750;
    ANIMATION[frapper_droite].num_sprite=frapper_droite;
    ANIMATION[frapper_droite].nombre_image=5;

    ANIMATION[surplace_droite].sprite_sheet=IMG_Load("resources/images/surplace_droite.png");//surplace ,regarder a droite
    ANIMATION[surplace_droite].largeur=90;
    ANIMATION[surplace_droite].x_max=180;
    ANIMATION[surplace_droite].num_sprite=surplace_droite;
    ANIMATION[surplace_droite].nombre_image=2;


    ANIMATION[surplace_gauche].sprite_sheet=IMG_Load("resources/images/surplace_gauche.png");//surplace ,regarder a gauche
    ANIMATION[surplace_gauche].largeur=90;
    ANIMATION[surplace_gauche].x_max=180;
    ANIMATION[surplace_gauche].num_sprite=surplace_gauche;
    ANIMATION[surplace_gauche].nombre_image=2;


    ANIMATION[frapper_gauche].sprite_sheet=IMG_Load("resources/images/attaque_gauche.png");//frapper a gauche
    ANIMATION[frapper_gauche].largeur=150;
    ANIMATION[frapper_gauche].x_max=750;
    ANIMATION[frapper_gauche].num_sprite=frapper_gauche;
    ANIMATION[frapper_gauche].nombre_image=5;
}


void charger_image_animation2(animation ANIMATION[])
{
    /*marcher vers la droite*/
    ANIMATION[marcher_droite].sprite_sheet=IMG_Load("resources/images/perso2_marcher_droite.png");
    ANIMATION[marcher_droite].largeur=90;
    ANIMATION[marcher_droite].x_max=810;
    ANIMATION[marcher_droite].num_sprite=marcher_droite;
    ANIMATION[marcher_droite].nombre_image=9;


    /*marcher vers la gauche*/
    ANIMATION[marcher_gauche].sprite_sheet=IMG_Load("resources/images/perso2_marcher_gauche.png");
    ANIMATION[marcher_gauche].largeur=90;
    ANIMATION[marcher_gauche].x_max=810;
    ANIMATION[marcher_gauche].num_sprite=marcher_gauche;
    ANIMATION[marcher_gauche].nombre_image=9;


    /*frapper vers la droite*/
    ANIMATION[frapper_droite].sprite_sheet=IMG_Load("resources/images/perso2_frapper_droite.png");//frapper a droite
    ANIMATION[frapper_droite].largeur=150;
    ANIMATION[frapper_droite].x_max=750;
    ANIMATION[frapper_droite].num_sprite=frapper_droite;
    ANIMATION[frapper_droite].nombre_image=5;

    ANIMATION[surplace_droite].sprite_sheet=IMG_Load("resources/images/perso2_surplace_droite.png");//surplace ,regarder a droite
    ANIMATION[surplace_droite].largeur=90;
    ANIMATION[surplace_droite].x_max=180;
    ANIMATION[surplace_droite].num_sprite=surplace_droite;
    ANIMATION[surplace_droite].nombre_image=2;


    ANIMATION[surplace_gauche].sprite_sheet=IMG_Load("resources/images/perso2_surplace_gauche.png");//surplace ,regarder a gauche
    ANIMATION[surplace_gauche].largeur=90;
    ANIMATION[surplace_gauche].x_max=180;
    ANIMATION[surplace_gauche].num_sprite=surplace_gauche;
    ANIMATION[surplace_gauche].nombre_image=2;


    ANIMATION[frapper_gauche].sprite_sheet=IMG_Load("resources/images/perso2_frapper_gauche.png");//frapper a gauche
    ANIMATION[frapper_gauche].largeur=150;
    ANIMATION[frapper_gauche].x_max=750;
    ANIMATION[frapper_gauche].num_sprite=frapper_gauche;
    ANIMATION[frapper_gauche].nombre_image=5;
}


void initialise_entity(Personnage *p/*,animation ANIMATION[]*/)
{
    if(p->action==p->action_precedente)/*si on effectue la meme action qu'avant*/
    {
        p->position_sprite.x=p->position_sprite.x+p->ANIMATION[p->action].largeur;

        if(p->position_sprite.x>=p->ANIMATION[p->action].x_max)
            p->position_sprite.x=0;

        p->position_sprite.h=p->ANIMATION[p->action].sprite_sheet->h;
        p->position_sprite.w=p->ANIMATION[p->action].largeur;
        p->position_sprite.y=0;

        p->action=-1;
    }
    else if(p->action!=p->action_precedente)/*si on a changer d'action*/
    {
        p->image_actuel=p->ANIMATION[p->action].sprite_sheet;

        p->position_sprite.h=p->ANIMATION[p->action].sprite_sheet->h;
        p->position_sprite.w=p->ANIMATION[p->action].largeur;
        p->position_sprite.y=0;
        p->position_sprite.x=0;

        p->action_precedente=p->action;
        p->action=-1;
    }
    //p->direction=-1;
}


void animer_perso(Personnage *p)
{
    //animation ANIMATION[10];//tableau d'animations

    /*if(p->player_number==1)
        charger_image_animation(ANIMATION);//chargement des animations
    else if(p->player_number==2)
        charger_image_animation2(ANIMATION);//chargement des animations pour le joueur 2*/

    initialise_entity(p);

}


void saut(Personnage *p)
{
    if(p->direction==droite)
    {
        p->position.y-=100;
        if(p->position.x<largeur_fenetre-100)
            p->position.x+=100;
        else
            p->position.x+=largeur_fenetre-p->position.x;
    }
    else if(p->direction==gauche)
    {
        p->position.y-=100;
        if(p->position.x>5)
            p->position.x-=100;
        else
            p->position.x-=p->position.x-5;
    }
    else
        p->position.y-=100;


    p->action_precedente=p->action;

    if(p->direction==droite)
        p->action=surplace_droite;
    else if(p->direction==gauche)
        p->action=surplace_gauche;

}
