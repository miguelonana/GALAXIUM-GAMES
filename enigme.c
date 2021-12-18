/*#include "enigme.h"
#include "PERSO.h"
#include "background.h"*/
#include "header1.h"

void afficherEnigme(enigme e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.Q,NULL,screen,&e.positionQ);
    SDL_BlitSurface(e.R1,NULL,screen,&e.positionR1);
    SDL_BlitSurface(e.R2,NULL,screen,&e.positionR2);
    SDL_BlitSurface(e.R3,NULL,screen,&e.positionR3);
//SDL_Flip(screen);
}



void genererEnigme(enigme *e, char question[])
{
    FILE *fichier=NULL;
    int numero_question;

    TTF_Font *police=NULL;
    SDL_Color couleur= {0,0,0};
    police= TTF_OpenFont("resources/polices/Enchanted Land.otf",27);
    int i;


    srand(time(NULL));
    numero_question=rand()%7;

    fichier=fopen(question,"r");
    if(fichier==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {

        for(i=-1; i<4; i++)
        {
            fscanf(fichier,"%s %s %s %s %s %d \n",e->question,e->rep1,e->rep2,e->rep3,e->repjuste,&e->reponse_juste);
            if(i==numero_question)
                break;
        }

        fclose(fichier);

        e->Q=TTF_RenderText_Blended(police,e->question,couleur);
        e->R1=TTF_RenderText_Blended(police,e->rep1,couleur);
        e->R2=TTF_RenderText_Blended(police,e->rep2,couleur);
        e->R3=TTF_RenderText_Blended(police,e->rep3,couleur);
        // e->reponse_Juste=TTF_RenderText_Blended(police,&e->repjuste,couleur);

        (*e).positionQ.x=50;
        (*e).positionQ.y=50;

        (*e).positionR1.x=50;
        (*e).positionR1.y=150;

        (*e).positionR2.x=50;
        (*e).positionR2.y=200;

        (*e).positionR3.x=50;
        (*e).positionR3.y=250;

        TTF_CloseFont(police);

    }
}





/*void sauvegarde_monojoueur(Personnage p,char nom_fichier[],int niveau_actuel)
{
    FILE *f=NULL;
    //int niveau;

    f=fopen(nom_fichier,"w+");
    if(f==NULL)
        printf("erreur douverture du fichier de sauvegarde\n");
    else
    {
        fprintf(f,"niveau: %d nombre_vie: %d score: %f ",niveau_actuel,p.nombre_vie,p.score);
        fclose(f);
    }
}*/




int sauvegarde_monojoueur(Personnage p,background b,char nom_fichier[],int niveau_actuel)
{
    FILE *f=NULL;

    f=fopen(nom_fichier,"w+b");

    if(f!=NULL)
    {

        fwrite(&p,sizeof(Personnage),1,f);
        fwrite(&b,sizeof(background),1,f);
        fwrite(&niveau_actuel,sizeof(int),1,f);
        printf("partie sauvergarder avec succes \n");

        fclose(f);
        return 1;
    }
    else
    {
        printf("echec d'ouverture du fichier binaire \n");
        return 0;
    }
}

void sauvergade_perso(Personnage p,char nomfichier[])
{
    FILE *f=NULL;

    f=fopen(/*"resources/sauvegardes/sauvergarde_perso.txt"*/nomfichier,"w+");
    if(f==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {
        fprintf(f,"%d %f %d %d %d \n",p.nombre_vie,p.score,p.player_number,p.position.x,p.position.y);
        fclose(f);
    }
}



void sauvegarde_background(background b,int niveau,char nomfichier[])
{
    FILE *f=NULL;

    f=fopen(/*"resources/sauvegardes/sauvergarde_background.txt"*/nomfichier,"w+");
    if(f==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {
        fprintf(f,"%d %d %d %d %d %d %d %d %d \n",b.camera_pos1.x,b.camera_pos1.y,b.camera_pos1.w,b.camera_pos1.h,b.camera_pos2.x,b.camera_pos2.y,b.camera_pos2.w,b.camera_pos2.h,niveau);
        fclose(f);
    }
}


void sauvegarde_temps(temps t,char nomfichier[])
{
    FILE *f=NULL;

    f=fopen(/*"resources/sauvegardes/sauvergarde_temps.txt"*/nomfichier,"w+");
    if(f==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {
        fprintf(f,"%d %d %d %s %d %d %d \n",t.secondesEcoulees,t.t1,t.t2,t.entree,t.couleur.r,t.couleur.b,t.couleur.g);
        fclose(f);
    }
}

void load_time(temps *t,char nomfichier[])
{
    FILE *f=NULL;

    f=fopen(/*"resources/sauvegardes/sauvergarde_temps.txt"*/nomfichier,"r");
    if(f==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {
        fscanf(f,"%d %d %d %s %d %d %d \n",&t->secondesEcoulees,&t->t1,&t->t2,t->entree,&t->couleur.r,&t->couleur.b,&t->couleur.g);
        fclose(f);
    }
}


void load_background(background *b,int *niveau,char nomfichier[])
{
    FILE *f=NULL;

    f=fopen(/*"resources/sauvegardes/sauvergarde_background.txt"*/nomfichier,"r");
    if(f==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {
        fscanf(f,"%d %d %d %d %d %d %d %d %d \n",&b->camera_pos1.x,&b->camera_pos1.y,&b->camera_pos1.w,&b->camera_pos1.h,&b->camera_pos2.x,&b->camera_pos2.y,&b->camera_pos2.w,&b->camera_pos2.h,niveau);
        fclose(f);
    }
}


void load_perso(Personnage *p,char nomfichier[])
{
    FILE *f=NULL;

    f=fopen(/*"resources/sauvegardes/sauvergarde_perso.txt"*/nomfichier,"r");
    if(f==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {
        fscanf(f,"%d %f %d %d %d \n",&p->nombre_vie,&p->score,&p->player_number,&p->position.x,&p->position.y);
        fclose(f);
    }
}


void sauvegarde_transition(Personnage p,background b,temps t,int niveau)
{
    sauvergade_perso(p,"resources/sauvegardes/sauvergarde_perso.txt");

    sauvegarde_background(b,niveau,"resources/sauvegardes/sauvergarde_background.txt");

    sauvegarde_temps(t,"resources/sauvegardes/sauvergarde_temps.txt");
}


void sauvegardes_quitter(Personnage p,background b,temps t,int niveau)
{
    sauvergade_perso(p,"resources/sauvegardes/sauvergarde_perso.txt");

    sauvegarde_background(b,niveau,"resources/sauvegardes/sauvergarde_background.txt");

    sauvegarde_temps(t,"resources/sauvegardes/sauvergarde_temps.txt");
}


void load_transition(Personnage *p,background *b,temps *t,int *niveau)
{
    load_time(t,"resources/sauvegardes/sauvergarde_temps.txt");

    load_background(b,niveau,"resources/sauvegardes/sauvergarde_background.txt");

    load_perso(p,"resources/sauvegardes/sauvergarde_perso.txt");
}


void load_quitter(Personnage *p,background *b,temps *t,int *niveau)
{
    load_time(t,"resources/sauvegardes/sauvergarde_temps.txt");

    load_background(b,niveau,"sauvergarde_background.txt");

    load_perso(p,"resources/sauvegardes/sauvergarde_perso.txt");
}



void sauvegarde_multijoueur(Personnage p1,Personnage p2,char nom_fichier[],int niveau_actuel)
{
    FILE *f=NULL;
    //int niveau;

    f=fopen(nom_fichier,"w+");
    if(f==NULL)
        printf("erreur douverture du fichier de sauvegarde\n");
    else
    {
        fprintf(f,"\n niveau: %d nombre_vie: %d score: %f \n",niveau_actuel,p1.nombre_vie,p1.score);
        fprintf(f,"\n niveau: %d nombre_vie: %d score: %f \n",niveau_actuel,p2.nombre_vie,p2.score);

        fclose(f);
    }
}



/*int charger_monojoueur(Personnage *p,char nom_fichier[],int *niveau_actuel,SDL_Rect *position)
{
    FILE *f=NULL;

    f=fopen(nom_fichier,"r");
    if(f==NULL)
    {
        printf("echec d'ouverture du fichier \n");
        return 0;
    }
    else
    {
        fscanf(f,"niveau: %d nombre_vie: %d score: %f positionx: positiony: ",&(*niveau_actuel),&p->nombre_vie,&p->score);

        fclose(f);
        return 1;
    }

}*/



int charger_monojoueur(Personnage *p,background *b,char nom_fichier[],int *niveau_actuel)
{
    FILE *f=NULL;

    f=fopen(nom_fichier,"rb");
    if(f==NULL)
    {
        printf("echec d'ouverture du fichier \n");
        return 0;
    }
    else
    {
        fread(p,sizeof(Personnage),1,f);
        fread(b,sizeof(background),1,f);
        fread(niveau_actuel,sizeof(int),1,f);

        fclose(f);
        return 1;
    }

}




/*int charger_multijoueur(Personnage *p1,Personnage *p2,char nom_fichier[],int *niveau_actuel)
{
    FILE *f=NULL;

    f=fopen(nom_fichier,"r");
    if(f==NULL)
    {
        printf("echec d'ouverture du fichier \n");
        return 0;
    }
    else
    {
        fscanf(f,"\n niveau: %d nombre_vie: %d score: %f \n\n niveau: %d nombre_vie: %d score: %f \n",&(*niveau_actuel),&p1->nombre_vie,&p1->score,NULL,&p2->nombre_vie,&p2->score);

        fclose(f);
        return 1;
    }
}*/



int resoudre_enigme(enigme e,SDL_Surface *ecran)
{
    int continuer=1;
    SDL_Surface *background_enigme=IMG_Load("resources/images/fond_ecran_menu.png");
    SDL_Rect position;
    position.x=0;
    position.y=0;
    SDL_Event evenement;

    SDL_Surface *image_vrai=IMG_Load("resources/images/couchevrai.png");
    SDL_Surface *image_faux=IMG_Load("resources/images/couchefaux.png");

    SDL_BlitSurface(background_enigme,NULL,ecran,&position);
    afficherEnigme(e,ecran);
    SDL_Flip(ecran);
    SDL_Delay(300);

    while(continuer)
    {
        SDL_PollEvent(&evenement);

        switch(evenement.type)
        {
        case SDL_QUIT:
            return 0;//voulez vous vraiment quitter
            break;
        case SDL_KEYDOWN:

            switch(evenement.key.keysym.sym)
            {
            case SDLK_KP1:
                if(e.reponse_juste==1)
                {
                    SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR1);
                    SDL_Flip(ecran);
                    SDL_Delay(1000);
                    return 1;
                    break;
                }
                else
                {
                    SDL_BlitSurface(image_faux,NULL,ecran,&e.positionR1);
                    SDL_Flip(ecran);
                    SDL_Delay(1500);
                    switch(e.reponse_juste)
                    {
                    case 2:
                        SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR2);
                        SDL_Flip(ecran);
                        SDL_Delay(1500);
                        return -1;
                        break;
                    case 3:
                        SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR3);
                        SDL_Flip(ecran);
                        SDL_Delay(1500);
                        return -1;
                        break;
                    }
                    break;
                }
                continuer=0;
                break;
            case SDLK_KP2:
                if(e.reponse_juste==2)
                {
                    SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR2);
                    SDL_Flip(ecran);
                    SDL_Delay(1000);
                    return 1;
                    break;
                }
                else
                {
                    SDL_BlitSurface(image_faux,NULL,ecran,&e.positionR2);
                    SDL_Flip(ecran);
                    SDL_Delay(1500);
                    switch(e.reponse_juste)
                    {
                    case 1:
                        SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR1);
                        SDL_Flip(ecran);
                        SDL_Delay(1500);
                        return -1;
                        break;
                    case 3:
                        SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR3);
                        SDL_Flip(ecran);
                        SDL_Delay(1500);
                        return -1;
                        break;
                    }
                    break;
                }
                continuer=0;
                break;
            case SDLK_KP3:
                if(e.reponse_juste==3)
                {
                    SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR3);
                    SDL_Flip(ecran);
                    SDL_Delay(1000);
                    return 1;
                    break;
                }
                else
                {
                    SDL_BlitSurface(image_faux,NULL,ecran,&e.positionR3);
                    SDL_Flip(ecran);
                    SDL_Delay(1500);
                    switch(e.reponse_juste)
                    {
                    case 1:
                        SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR1);
                        SDL_Flip(ecran);
                        SDL_Delay(1500);
                        return -1;
                        break;
                    case 2:
                        SDL_BlitSurface(image_vrai,NULL,ecran,&e.positionR2);
                        SDL_Flip(ecran);
                        SDL_Delay(1500);
                        return -1;
                        break;
                    }
                    break;

                }
            }
            break;
        }

    }

    SDL_FreeSurface(background_enigme);
    SDL_FreeSurface(image_vrai);
    SDL_FreeSurface(image_faux);
    SDL_FreeSurface(e.Q);
    SDL_FreeSurface(e.R1);
    SDL_FreeSurface(e.R2);
    SDL_FreeSurface(e.R3);

}

