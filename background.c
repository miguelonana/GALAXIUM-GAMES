

#include "header1.h"

void init_background(background *bckg,SDL_Surface *ecran,int niveau)
{
    //SDL_Rect pos;

    switch(niveau)
    {
    case 1:
        bckg->image=IMG_Load("resources/images/level_1.png");//background level 1
        break;
    case 2:
        bckg->image=IMG_Load("resources/images/level_2.png");//background level 2
        break;
    case 3:
        bckg->image=IMG_Load("resources/images/level_3.png");//background level 3
        break;
    }

    /*pos.x=0;
    pos.y=(bckg->image->h)-hauteur_fenetre;*/


    bckg->camera_pos1.x=0;
    bckg->camera_pos1.y=ecran->h-hauteur_fenetre;

    bckg->camera_pos1.w=ecran->w;
    bckg->camera_pos1.h=ecran->h;
    bckg->pos_background1.x=0;
    bckg->pos_background1.y=0;

    // bckg->pos_background1=pos;

    /*bckg->camera_pos2.x=350;
    bckg->camera_pos2.y=0;

    bckg->camera_pos2.w=350;
    bckg->camera_pos2.h=700;

    bckg->pos_background2.x=350;
    bckg->pos_background2.y=0;*/
}


void init_background_multijoueur(background *bckg,SDL_Surface *ecran,int niveau)
{
    switch(niveau)
    {
    case 1:
        bckg->image=IMG_Load("resources/images/level_1.png");//background level 1
        break;
    case 2:
        bckg->image=IMG_Load("resources/images/background.jpg");//background level 2
        break;
    case 3:
        bckg->image=IMG_Load("resources/images/background.jpg");//background level 3
        break;
    }

//joueur 1
    bckg->camera_pos1.x=0;
    bckg->camera_pos1.y=0;

    bckg->camera_pos1.w=ecran->w/2;
    bckg->camera_pos1.h=ecran->h;

    bckg->pos_background1.x=0;
    bckg->pos_background1.y=0;



    //joueur 2
    bckg->camera_pos2.x=0;
    bckg->camera_pos2.y=0;

    bckg->camera_pos2.w=ecran->w/2;
    bckg->camera_pos2.h=ecran->h;

    bckg->pos_background2.x=(ecran->w/2)+10;
    bckg->pos_background2.y=0;
}

void afficher_background(background bckg,SDL_Surface *screen)
{
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(bckg.image,&bckg.camera_pos1, screen, &bckg.pos_background1);//blittage_ecran_joueur1
    //SDL_BlitSurface(bckg.image,&bckg.camera_pos2, screen, &bckg.pos_background2);//blittage_ecran_joueur2
}


void afficher_background_multijoueur(background bckg,SDL_Surface *screen)
{
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(bckg.image,&bckg.camera_pos1, screen, &bckg.pos_background1);//blittage_ecran_joueur1
    SDL_BlitSurface(bckg.image,&bckg.camera_pos2, screen, &bckg.pos_background2);//blittage_ecran_joueur2
}


void scrolling(background *bckg,int direction,int pasAvancement)
{
    if(direction==gauche)
        bckg->camera_pos1.x-=pasAvancement;
    else if (direction==droite)
        bckg->camera_pos1.x+=pasAvancement;
    else if (direction==haut)
        bckg->camera_pos1.y-=pasAvancement;
    else if(direction==bas)
        bckg->camera_pos1.y+=pasAvancement;

    if(bckg->camera_pos1.x>=bckg->image->w-bckg->camera_pos1.w)
        bckg->camera_pos1.x=bckg->image->w-bckg->camera_pos1.w;


    if(bckg->camera_pos1.x<=0)
        bckg->camera_pos1.x=0;

}


void scrolling_2(background *bckg,int direction,int pasAvancement)
{
    if(direction==gauche)
        bckg->camera_pos2.x-=pasAvancement;
    else if (direction==droite)
        bckg->camera_pos2.x+=pasAvancement;
    else if (direction==haut)
        bckg->camera_pos2.y-=pasAvancement;
    else if(direction==bas)
        bckg->camera_pos2.y+=pasAvancement;

    if(bckg->camera_pos2.x>=bckg->image->w-bckg->camera_pos2.w)
        bckg->camera_pos2.x=bckg->image->w-bckg->camera_pos2.w;


    if(bckg->camera_pos2.x<=0)
        bckg->camera_pos2.x=0;

}
