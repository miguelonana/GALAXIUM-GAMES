/**
*@file es.c
*@author Nayrouz Tebib
*@version 1.0
*@date
*/
/*#include "SDL/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "es.h"*/

#include "header1.h"

/**
* @brief To initialize the enemy e .
* @param e the enemy
* @return Nothing
*/

void initEnnemi(enemy *e)
{
    e->dir=gauche;

    e->pos.x=0;
    e->pos.y=0;
    e->pos.w=60;
    e->pos.h=120;

    e->poss.x=0;
    e->poss.y=0;
    //e->img=IMG_Load("ennemi_spr.png");
    e->img_attacking_gauche=IMG_Load("resources/images/ennemi_gauche.png");
    e->img_attacking_droite=IMG_Load("resources/images/ennemi_droite.png");

    e->img_following_gauche=IMG_Load("resources/images/ennemi_gauche.png");
    e->img_following_droite=IMG_Load("resources/images/ennemi_droite.png");

    //e->img_waiting=IMG_Load("");

    e->s=waiting;
    //e->s=following;

}

/**
* @brief To display the enemy e .
* @param e the enemy
* @param screen the screen
* @return Nothing
*/

void afficherEnnemi(enemy e, SDL_Surface * screen)
{
    if(e.s==attacking && e.dir==gauche)
        SDL_BlitSurface(e.img_attacking_gauche,&e.pos,screen,&e.poss);
    else if(e.s==attacking && e.dir==droite)
        SDL_BlitSurface(e.img_attacking_droite,&e.pos,screen,&e.poss);
    else if(e.s!=attacking && e.dir==droite)
        SDL_BlitSurface(e.img_following_droite,&e.pos,screen,&e.poss);
    else if(e.s!=attacking && e.dir==gauche)
        SDL_BlitSurface(e.img_following_gauche,&e.pos,screen,&e.poss);
}

/**
* @brief To animate the enemy e .
* @param e the enemy
* @return Nothing
*/

void animerEnnemi( enemy * e)
{
    //dir=0 maanetha ki bsh ymshi aalimin
    /*if(e->dir==0)
    {

        if(e->pos.x==300)//ken wslt l ekhr frame
            e->pos.x=0;
        else
            e->pos.x=e->pos.x+e->pos.w;;
    }
    if(e->dir==1)
    {

        if(e->pos.x==0)
            e->pos.x=300;
        else
            e->pos.x=e->pos.x-e->pos.w;
    }*/
    if(e->dir==gauche && e->s==attacking)
    {
        e->pos.x+=e->pos.w;
        if(e->pos.x==e->img_attacking_gauche->w)
            e->pos.x=0;
    }
    else if(e->dir==droite && e->s==attacking)
    {
        e->pos.x+=e->pos.w;
        if(e->pos.x==e->img_attacking_droite->w)
            e->pos.x=0;
    }
    else if(e->dir==gauche && e->s!=attacking)
    {
        e->pos.x+=e->pos.w;
        if(e->pos.x==e->img_following_gauche->w)
            e->pos.x=0;
    }
    else if(e->dir==droite && e->s!=attacking)
    {
        e->pos.x+=e->pos.w;
        if(e->pos.x==e->img_following_droite->w)
            e->pos.x=0;
    }
}

/**
* @brief To move the enemy e .
* @param e the enemy
* @return Nothing
*/

void deplacer( enemy * e)
{
    /*if(e->poss.x>50)
    {
        e->dir=gauche;
    }
    if(e->poss.x<0)
    {
        e->dir=droite;
    }*/
    if(e->dir==droite && e->poss.x<hauteur_fenetre)
        e->poss.x+=15;
    else if(e->dir==gauche && e->poss.x>10)
        e->poss.x-=15;
}


/**
* @brief To move the character e .
* @param e the enemy
* @return Nothing
*/

//this function will be deleted
/*void deplacerp( enemy * e)
{
    if(e->pos.x==300)
    {
        e->dir=1;
        e->pos.y=100;
    }
    //if(e->pos.x==0)
    //{e->dir=0;
    //e->pos.y=0;}
    if(e->dir==0)
        e->poss.x++;
    else
        e->poss.x--;
}*/
/**
* @brief bounding box collision .
* @param e the enemy
* @param p the character
* @return integer (collision done or not)
*/

int collisionBB( Personnage p, enemy e)
{
    if ((p.position.x + p.position_sprite.w< e.poss.x)||(p.position.x> e.poss.x + e. pos.w) || (p.position.y + p.position_sprite.h< e.poss.y)||(p.position.y> e.poss.y + e. pos.h))
        return 0;
    else
        return 1;
}
/**
* @brief updating enemy status .
* @param e the enemy
* @param p the character
* @return nothing
*/

void updateEnnemi (enemy *e, Personnage p )
{
    int d;
    d=e->poss.x-(p.position.x);
    //int s1=600,s2=80;

    if(d<0)//modification
    {
        e->dir=droite;
        d=d*(-1);
    }
    else
        e->dir=gauche;
    /*if(p.position.x<e->pos.x)
        e->dir=gauche;*/
    /*else
        e->dir=droite;*/
    //

    /*switch(e->s)
    {
    case waiting:
        if(d>15)
            e->s=waiting;
        else if((d<15)&&(d>10))
            e->s=following;
        break;
    case following:
        if((d<15)&&(d>10))
            e->s=following;
        else if(d<10)
            e->s=attacking;
        break;
    case attacking:
        if(d<10)
            e->s=attacking;
        else if(d<0)
            e->s=waiting;
        break;
    }*/



//modification
    switch(e->s)
    {
    /*case waiting:
        if(d>=s2 && d<=s1)
            e->s=following;
        break;
    case following:
        if(0<d && d<=s2)
            e->s=attacking;
        break;*/
    case waiting:
        if(d>200)
            e->s=waiting;
        else if(d<200)
            e->s=following;
        break;
    case following:
        if(d<150)
            e->s=attacking;
        else if(d>150)
            e->s=following;
        break;
    case attacking:
        e->s=attacking;
        break;

        /*case attacking:
            if(d<=10)
                e->s=waiting;
            break;*/
        /*case attacking:
            /*if(d<=10)
            {
                e->s=waiting;
            }
            break;*/
    }
//

    switch(e->s)
    {
    case waiting:
        //animerEnnemi(&(*e));
        animerEnnemi(e);
        break;
    case following://follow du perso
        //e->dir=0;
        /*animerEnnemi(&(*e)); // walking pics
        deplacer(&(*e));*/

        animerEnnemi(e);
        deplacer(e);
        break;// enemy ymshi lel perso
    case attacking:
        /*animerEnnemi(&(*e));//attacking pics
        deplacer(&(*e));*/

        animerEnnemi(e);//attacking pics
        deplacer(e);
        break; // enemy ymshi lel perso
    }
    /*switch(e->s)
    {
    case waiting:
        if(d>15)
            e->s=waiting;
        else if((d<15)&&(d>10))
            e->s=following;
        break;
    case following:
        if((d<15)&&(d>10))
            e->s=following;
        else if(d<10)
            e->s=attacking;
        break;
    case attacking:
        if(d<10)
            e->s=attacking;
        else if(d<0)
            e->s=waiting;
        break;
    }*/
}
