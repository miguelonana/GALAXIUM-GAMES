


#include "header1.h"


void charger_boutton_quitter(Boutton button[],SDL_Surface *ecran)
{
    button[quitter_sans_sauvegarde].boutton_active=IMG_Load("resources/images/boutton_quit_without_saving_2.png");
    button[quitter_sans_sauvegarde].boutton_desactive=IMG_Load("resources/images/boutton_quitter_sans_sauvergarder_1.png");

    button[quitter_et_sauvegader].boutton_active=IMG_Load("resources/images/boutton_save_and_quit_2.png");
    button[quitter_et_sauvegader].boutton_desactive=IMG_Load("resources/images/boutton_enregistrer_et_quitter_1.png");

    button[annuler].boutton_active=IMG_Load("resources/images/boutton_cancel_2.png");
    button[annuler].boutton_desactive=IMG_Load("resources/images/boutton_annuler_1.png");

    button[quitter_sans_sauvegarde].etat=0;
    button[quitter_et_sauvegader].etat=0;
    button[annuler].etat=0;

    button[quitter_sans_sauvegarde].position.x=((ecran->w)/3)-20;
    button[quitter_sans_sauvegarde].position.y=(ecran->h)/3;

    button[quitter_et_sauvegader].position.x=((ecran->w)/3)-20;
    button[quitter_et_sauvegader].position.y=8*(ecran->h)/15 ;

    button[annuler].position.x=((ecran->w)/3)-20;
    button[annuler].position.y=11*(ecran->h)/15;
}


void coller_surface_quitter(Boutton button[],SDL_Surface *ecran)
{
    if(button[quitter_sans_sauvegarde].etat==1)
        SDL_BlitSurface(button[quitter_sans_sauvegarde].boutton_active,NULL,ecran,&button[quitter_sans_sauvegarde].position);
    else
        SDL_BlitSurface(button[quitter_sans_sauvegarde].boutton_desactive,NULL,ecran,&button[quitter_sans_sauvegarde].position);

    if(button[quitter_et_sauvegader].etat==1)
        SDL_BlitSurface(button[quitter_et_sauvegader].boutton_active,NULL,ecran,&button[quitter_et_sauvegader].position);
    else
        SDL_BlitSurface(button[quitter_et_sauvegader].boutton_desactive,NULL,ecran,&button[quitter_et_sauvegader].position);

    if(button[annuler].etat==1)
        SDL_BlitSurface(button[annuler].boutton_active,NULL,ecran,&button[annuler].position);
    else
        SDL_BlitSurface(button[annuler].boutton_desactive,NULL,ecran,&button[annuler].position);

}


int quitter(Personnage p,background b,SDL_Surface *ecran,int niveau_actuel,temps t)
{
    Boutton button[3];
    SDL_Surface *fond_ecran=IMG_Load("resources/images/fond_ecran_menu.png");
    SDL_Event evenement;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    int continuer=1;

    charger_boutton_quitter(button,ecran);
    SDL_BlitSurface(fond_ecran,NULL,ecran,&position);
    coller_surface_quitter(button,ecran);
    SDL_Flip(ecran);

    while(continuer)
    {
        SDL_PollEvent(&evenement);
        switch(evenement.type)
        {
        case SDL_KEYDOWN:
            switch(evenement.key.keysym.sym)
            {
            case SDLK_UP:
                if(button[quitter_sans_sauvegarde].etat==0 && button[quitter_et_sauvegader].etat==0 && button[annuler].etat==0)
                {

                    button[quitter_sans_sauvegarde].etat=0;
                    button[quitter_et_sauvegader].etat=0;
                    button[annuler].etat=1;
                }
                else if(button[quitter_sans_sauvegarde].etat==1 && button[quitter_et_sauvegader].etat==0 && button[annuler].etat==0)
                {

                    button[quitter_sans_sauvegarde].etat=0;
                    button[quitter_et_sauvegader].etat=0;
                    button[annuler].etat=1;
                }
                else if(button[quitter_sans_sauvegarde].etat==0 && button[quitter_et_sauvegader].etat==1 && button[annuler].etat==0)
                {

                    button[quitter_sans_sauvegarde
                          ].etat=1;
                    button[quitter_et_sauvegader].etat=0;
                    button[annuler].etat=0;
                }
                else if(button[quitter_sans_sauvegarde].etat==0 && button[quitter_et_sauvegader].etat==0 && button[annuler].etat==1)
                {

                    button[quitter_sans_sauvegarde].etat=0;
                    button[quitter_et_sauvegader].etat=1;
                    button[annuler].etat=0;
                }
                SDL_BlitSurface(fond_ecran,NULL,ecran,&position);
                coller_surface_quitter(button,ecran);
                SDL_Flip(ecran);
                SDL_Delay(150);
                break;
            case SDLK_DOWN:
                if(button[quitter_sans_sauvegarde].etat==0 && button[quitter_et_sauvegader].etat==0 && button[annuler].etat==0)
                {

                    button[quitter_sans_sauvegarde].etat=1;
                    button[quitter_et_sauvegader].etat=0;
                    button[annuler].etat=0;
                }
                else if(button[quitter_sans_sauvegarde].etat==1 && button[quitter_et_sauvegader].etat==0 && button[annuler].etat==0)
                {

                    button[quitter_sans_sauvegarde].etat=0;
                    button[quitter_et_sauvegader].etat=1;
                    button[annuler].etat=0;
                }
                else if(button[quitter_sans_sauvegarde].etat==0 && button[quitter_et_sauvegader].etat==1 && button[annuler].etat==0)
                {

                    button[quitter_sans_sauvegarde].etat=0;
                    button[quitter_et_sauvegader].etat=0;
                    button[annuler].etat=1;
                }
                else if(button[quitter_sans_sauvegarde].etat==0 && button[quitter_et_sauvegader].etat==0 && button[annuler].etat==1)
                {

                    button[quitter_sans_sauvegarde].etat=1;
                    button[quitter_et_sauvegader].etat=0;
                    button[annuler].etat=0;
                }
                SDL_BlitSurface(fond_ecran,NULL,ecran,&position);
                coller_surface_quitter(button,ecran);
                SDL_Flip(ecran);
                SDL_Delay(150);
                break;
            case SDLK_RETURN:
                if(button[quitter_et_sauvegader].etat==1 && button[quitter_sans_sauvegarde].etat==0 && button[annuler].etat==0)
                {
                    sauvegardes_quitter(p,b,t,niveau_actuel);
                    quel_sauvegarde_ecrire("resources/sauvegardes2/quel.txt",1,niveau_actuel);
                    continuer=0;
                    return quitter_et_sauvegader;
                }
                else if(button[quitter_et_sauvegader].etat==0 && button[quitter_sans_sauvegarde].etat==1 && button[annuler].etat==0)
                    return quitter_sans_sauvegarde;
                else if(button[quitter_et_sauvegader].etat==0 && button[quitter_sans_sauvegarde].etat==0 && button[annuler].etat==1)
                    return annuler;
            }
        }
        SDL_BlitSurface(fond_ecran,NULL,ecran,&position);
        coller_surface_quitter(button,ecran);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(fond_ecran);
    SDL_FreeSurface(button[annuler].boutton_active);
    SDL_FreeSurface(button[annuler].boutton_desactive);
    SDL_FreeSurface(button[quitter_et_sauvegader].boutton_active);
    SDL_FreeSurface(button[quitter_et_sauvegader].boutton_desactive);
    SDL_FreeSurface(button[quitter_sans_sauvegarde].boutton_active);
    SDL_FreeSurface(button[quitter_sans_sauvegarde].boutton_desactive);
}



void charger_boutton_pause(Boutton Pause[],SDL_Surface *ecran)
{
    Pause[resume_game].boutton_active=IMG_Load("resources/images/boutton_resume_game_2.png");
    Pause[resume_game].boutton_desactive=IMG_Load("resources/images/boutton_resume_game_1.png");

    Pause[back_to_menu].boutton_active=IMG_Load("resources/images/boutton_back_to_menu_2png.png");
    Pause[back_to_menu].boutton_desactive=IMG_Load("resources/images/boutton_back_to_menu_1.png");


    Pause[resume_game].etat=0;
    Pause[back_to_menu].etat=0;


    Pause[resume_game].position.x=((ecran->w)/3)-20;
    Pause[resume_game].position.y=(ecran->h)/3;

    Pause[back_to_menu].position.x=((ecran->w)/3)-20;
    Pause[back_to_menu].position.y=8*(ecran->h)/15 ;
}

void coller_surface_pause(SDL_Surface *ecran,Boutton button[])
{
    SDL_Surface *fond_ecran=IMG_Load("resources/images/fond_ecran_menu.png");
    SDL_Rect position;
    position.x=0;
    position.y=0;

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(fond_ecran,NULL,ecran,&position);
    if(button[resume_game].etat==1)
        SDL_BlitSurface(button[resume_game].boutton_active,NULL,ecran,&button[resume_game].position);
    else
        SDL_BlitSurface(button[resume_game].boutton_desactive,NULL,ecran,&button[resume_game].position);

    if(button[back_to_menu].etat==1)
        SDL_BlitSurface(button[back_to_menu].boutton_active,NULL,ecran,&button[back_to_menu].position);
    else
        SDL_BlitSurface(button[back_to_menu].boutton_desactive,NULL,ecran,&button[back_to_menu].position);
}




int enigme_avec_ou_sans_fichier()
{
    int e;

    srand(time(NULL));
    e=rand()%2;

    return e;
}


void quel_sauvegarde_ecrire(char nom_fichier[],int nombre_joueur,int niveau)
{
    FILE *f=NULL;
    f=fopen(nom_fichier,"w+");
    if(f==NULL)
        printf("echec douverture du fichier\n");
    else
    {
        fprintf(f,"%d %d \n",nombre_joueur,niveau);
        fclose(f);
    }
}

void quel_sauvegarde_lire(char nom_fichier[],int *nombre_joueur,int *niveau)
{
    FILE *f=NULL;
    f=fopen(nom_fichier,"r");
    if(f==NULL)
        printf("echec douverture du fichier\n");
    else
    {
        fscanf(f,"%d %d \n",nombre_joueur,niveau);
        fclose(f);
    }
}



int mise_a_jour_highscores(char nom_fichier[],float score)
{
    FILE *f=NULL;
    float highest_score_actuel=-1;
    f=fopen(nom_fichier,"r");
    if(f==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {
        fscanf(f,"%f \n",&highest_score_actuel);
        fclose(f);
    }

    if(highest_score_actuel==-1)
        printf("echec de lecture du fichier\n");
    else
    {
        if(score>=highest_score_actuel)
        {
            printf("highest score atteint\n");
            f=fopen(nom_fichier,"w+");
            if(f==NULL)
                printf("echec d'ouverture du fichier\n");
            else
            {
                fprintf(f,"%f \n",score);
                fclose(f);
                return 1;
            }
        }
        else
            return 0;
    }
}



void lire_highest_score(char nom_fichier[],float *score)
{

    FILE *f=NULL;
    (*score)=-1;
    f=fopen(nom_fichier,"r");
    if(f==NULL)
        printf("echec d'ouverture du fichier\n");
    else
    {
        fscanf(f,"%f \n",score);
        fclose(f);
    }
    if((*score)==-1)
        printf("echec de lecture\n");
    else
        printf("lecture reussie\n");
}
