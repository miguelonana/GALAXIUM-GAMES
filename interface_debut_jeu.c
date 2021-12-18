

#include "header1.h"



void charger_resources_interface(Boutton Button[],SDL_Surface *ecran)
{
    Button[boutton_nouvelle_partie].boutton_active=IMG_Load("resources/images/boutton_new_game_2.png");
    Button[boutton_nouvelle_partie].boutton_desactive=IMG_Load("resources/images/boutton_new_game_1.png");

    Button[boutton_charger_partie].boutton_active=IMG_Load("resources/images/boutton_load_game_2.png");
    Button[boutton_charger_partie].boutton_desactive=IMG_Load("resources/images/boutton_load_game_1.png");

    Button[boutton_mono_joueur].boutton_active=IMG_Load("resources/images/boutton_single_palyer_2.png");
    Button[boutton_mono_joueur].boutton_desactive=IMG_Load("resources/images/boutton_single_palyer_1.png");

    Button[boutton_multi_joueur].boutton_active=IMG_Load("resources/images/boutton_2players_2.png");
    Button[boutton_multi_joueur].boutton_desactive=IMG_Load("resources/images/boutton_2players_1.png");


    Button[boutton_nouvelle_partie].etat=0;
    Button[boutton_charger_partie].etat=0;
    Button[boutton_mono_joueur].etat=0;
    Button[boutton_multi_joueur].etat=0;



    Button[boutton_charger_partie].position.x=((ecran->w)/3)-20;
    Button[boutton_charger_partie].position.y=(ecran->h)/3 ;

    Button[boutton_nouvelle_partie].position.x=((ecran->w)/3)-20 ;
    Button[boutton_nouvelle_partie].position.y=8*(ecran->h)/15 ;

    Button[boutton_mono_joueur].position.x=((ecran->w)/3)-20;
    Button[boutton_mono_joueur].position.y=(ecran->h)/3 ;

    Button[boutton_multi_joueur].position.x=((ecran->w)/3)-20 ;
    Button[boutton_multi_joueur].position.y=8*(ecran->h)/15 ;

}


void coller_surface(int stade,Boutton button[],SDL_Surface *ecran)
{
    switch(stade)
    {
    case partie:
        if(button[boutton_charger_partie].etat==1)
            SDL_BlitSurface(button[boutton_charger_partie].boutton_active,NULL,ecran,&button[boutton_charger_partie].position);
        else
            SDL_BlitSurface(button[boutton_charger_partie].boutton_desactive,NULL,ecran,&button[boutton_charger_partie].position);

        if(button[boutton_nouvelle_partie].etat==1)
            SDL_BlitSurface(button[boutton_nouvelle_partie].boutton_active,NULL,ecran,&button[boutton_nouvelle_partie].position);
        else
            SDL_BlitSurface(button[boutton_nouvelle_partie].boutton_desactive,NULL,ecran,&button[boutton_nouvelle_partie].position);
        break;
    case mode_jeu:
        if(button[boutton_mono_joueur].etat==1)
            SDL_BlitSurface(button[boutton_mono_joueur].boutton_active,NULL,ecran,&button[boutton_mono_joueur].position);
        else
            SDL_BlitSurface(button[boutton_mono_joueur].boutton_desactive,NULL,ecran,&button[boutton_mono_joueur].position);

        if(button[boutton_multi_joueur].etat==1)
            SDL_BlitSurface(button[boutton_multi_joueur].boutton_active,NULL,ecran,&button[boutton_multi_joueur].position);
        else
            SDL_BlitSurface(button[boutton_multi_joueur].boutton_desactive,NULL,ecran,&button[boutton_multi_joueur].position);
        break;

    }

}



int interface_choix_mode_jeu(SDL_Surface *ecran)
{
    Boutton button[4];
    SDL_Surface *fond_ecran=NULL;
    SDL_Event evenement;
    int continuer=1;
    int ou;
    SDL_Rect position_background;

    position_background.x=0;
    position_background.y=0;

    charger_resources_interface(button,ecran);
    fond_ecran=IMG_Load("resources/images/fond_ecran_option.png");//l'image de fond

//les sons
    Mix_Chunk *son_boutton=NULL;
    son_boutton=Mix_LoadWAV("resources/sons/click.wav");


    SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
    coller_surface(partie,button,ecran);
    SDL_Flip(ecran);
    ou=partie;


    while(continuer)
    {
        SDL_PollEvent(&evenement);

        switch(evenement.type)
        {
        case SDL_QUIT:
            return 0;
            break;
        case SDL_KEYDOWN:
            switch(evenement.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                if(ou==partie)
                    return -1;
                else if(ou==mode_jeu)
                {
                    SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                    coller_surface(partie,button,ecran);
                    ou=partie;
                    SDL_Flip(ecran);
                    SDL_Delay(300);

                }
                break;
            case SDLK_UP:
                if(ou==partie)
                {
                    if(button[boutton_nouvelle_partie].etat==0 && button[boutton_charger_partie].etat==0)
                    {
                        button[boutton_nouvelle_partie].etat=1;
                        button[boutton_charger_partie].etat=0;
                    }
                    else if(button[boutton_nouvelle_partie].etat==1 && button[boutton_charger_partie].etat==0)
                    {
                        button[boutton_charger_partie].etat=1;
                        button[boutton_nouvelle_partie].etat=0;
                    }
                    else if(button[boutton_nouvelle_partie].etat==0 && button[boutton_charger_partie].etat==1)
                    {
                        button[boutton_nouvelle_partie].etat=1;
                        button[boutton_charger_partie].etat=0;
                    }

                    if(button[boutton_nouvelle_partie].etat==1 || button[boutton_charger_partie].etat==1)
                        Mix_PlayChannel(-1,son_boutton,0);

                    SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                    coller_surface(partie,button,ecran);
                    SDL_Flip(ecran);
                    SDL_Delay(300);
                    break;
                }


                else if(ou==mode_jeu)
                {
                    if(button[boutton_multi_joueur].etat==0 && button[boutton_mono_joueur].etat==0)
                    {
                        button[boutton_multi_joueur].etat=1;
                        button[boutton_mono_joueur].etat=0;
                    }
                    else if(button[boutton_multi_joueur].etat==1 && button[boutton_mono_joueur].etat==0)
                    {
                        button[boutton_mono_joueur].etat=1;
                        button[boutton_multi_joueur].etat=0;
                    }
                    else if(button[boutton_multi_joueur].etat==0 && button[boutton_mono_joueur].etat==1)
                    {
                        button[boutton_multi_joueur].etat=1;
                        button[boutton_mono_joueur].etat=0;
                    }

                    if(button[boutton_multi_joueur].etat==1 || button[boutton_mono_joueur].etat==1)
                        Mix_PlayChannel(-1,son_boutton,0);

                    SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                    coller_surface(mode_jeu,button,ecran);
                    SDL_Flip(ecran);
                    SDL_Delay(300);
                    break;
                }
                break;
            case SDLK_DOWN:
                if(ou==partie)
                {
                    if(button[boutton_nouvelle_partie].etat==0 && button[boutton_charger_partie].etat==0)
                    {
                        button[boutton_charger_partie].etat=1;
                        button[boutton_nouvelle_partie].etat=0;
                    }
                    else if(button[boutton_nouvelle_partie].etat==0 && button[boutton_charger_partie].etat==1)
                    {
                        button[boutton_nouvelle_partie].etat=1;
                        button[boutton_charger_partie].etat=0;
                    }
                    else if(button[boutton_nouvelle_partie].etat==1 && button[boutton_charger_partie].etat==0)
                    {
                        button[boutton_charger_partie].etat=1;
                        button[boutton_nouvelle_partie].etat=0;
                    }

                    if(button[boutton_nouvelle_partie].etat==1 || button[boutton_charger_partie].etat==1)
                        Mix_PlayChannel(-1,son_boutton,0);

                    SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                    coller_surface(partie,button,ecran);
                    SDL_Flip(ecran);
                    SDL_Delay(300);
                    break;
                }


                else if(ou==mode_jeu)
                {
                    if(button[boutton_mono_joueur].etat==0 && button[boutton_multi_joueur].etat==0)
                    {
                        button[boutton_mono_joueur].etat=1;
                        button[boutton_multi_joueur].etat=0;
                    }
                    else if(button[boutton_mono_joueur].etat==1 && button[boutton_multi_joueur].etat==0)
                    {
                        button[boutton_multi_joueur].etat=1;
                        button[boutton_mono_joueur].etat=0;
                    }
                    else if(button[boutton_mono_joueur].etat==0 && button[boutton_multi_joueur].etat==1)
                    {
                        button[boutton_mono_joueur].etat=1;
                        button[boutton_multi_joueur].etat=0;
                    }

                    SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                    coller_surface(mode_jeu,button,ecran);
                    SDL_Flip(ecran);
                    SDL_Delay(300);
                    break;
                }
                break;
            case SDLK_RETURN:
                if(ou==partie)
                {
                    if(button[boutton_charger_partie].etat==1)
                    {
                        Mix_PlayChannel(-1,son_boutton,0);
                        return charger_partie;
                    }
                    else if(button[boutton_nouvelle_partie].etat==1)
                    {
                        Mix_PlayChannel(-1,son_boutton,0);
                        SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                        coller_surface(mode_jeu,button,ecran);
                        SDL_Flip(ecran);
                        ou=mode_jeu;
                        SDL_Delay(500);

                    }

                }
                else if(ou==mode_jeu)
                {
                    if(button[boutton_mono_joueur].etat==1 && button[boutton_multi_joueur].etat==0)
                        return mono_joueur;
                    else if(button[boutton_multi_joueur].etat==1 && button[boutton_mono_joueur].etat==0)
                        return multi_joueur;
                }
                break;

            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(evenement.button.button==SDL_BUTTON_LEFT)
            {
                if(ou==partie)
                {
                    button[boutton_charger_partie].etat=etat_boutton_apres_clique(button[boutton_charger_partie],evenement);
                    button[boutton_nouvelle_partie].etat=etat_boutton_apres_clique(button[boutton_nouvelle_partie],evenement);

                    if(button[boutton_charger_partie].etat==1 || button[boutton_nouvelle_partie].etat==1 /*|| Button[boutton_quitter].etat==1*/)
                        Mix_PlayChannel(-1,son_boutton,0);


                    SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                    coller_surface(partie,button,ecran);
                    SDL_Flip(ecran);
                    SDL_Delay(500);

                    if(button[boutton_charger_partie].etat==1)
                    {
                        Mix_PlayChannel(-1,son_boutton,0);
                        return charger_partie;
                    }
                    else if(button[boutton_nouvelle_partie].etat==1)
                    {

                        SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                        coller_surface(mode_jeu,button,ecran);
                        SDL_Flip(ecran);
                        ou=mode_jeu;
                        SDL_Delay(500);

                    }
                }

                else if(ou==mode_jeu)
                {
                    button[boutton_mono_joueur].etat=etat_boutton_apres_clique(button[boutton_mono_joueur],evenement);
                    button[boutton_multi_joueur].etat=etat_boutton_apres_clique(button[boutton_multi_joueur],evenement);

                    if(button[boutton_charger_partie].etat==1 || button[boutton_nouvelle_partie].etat==1 )
                        Mix_PlayChannel(-1,son_boutton,0);


                    SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                    coller_surface(mode_jeu,button,ecran);
                    SDL_Flip(ecran);
                    SDL_Delay(500);

                    if(button[boutton_mono_joueur].etat==1 && button[boutton_multi_joueur].etat==0)
                    {
                        Mix_PlayChannel(-1,son_boutton,0);
                        return mono_joueur;
                    }
                    else if(button[boutton_multi_joueur].etat==1 && button[boutton_mono_joueur].etat==0)
                    {
                        Mix_PlayChannel(-1,son_boutton,0);
                        return multi_joueur;
                    }

                    break;
                }
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            if(ou==partie)
            {
                button[boutton_charger_partie].etat=etat_bouton_apres_mouvement_souris(button[boutton_charger_partie],evenement);
                button[boutton_nouvelle_partie].etat=etat_bouton_apres_mouvement_souris(button[boutton_nouvelle_partie],evenement);

                SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                coller_surface(partie,button,ecran);
                SDL_Flip(ecran);
                SDL_Delay(50);


            }
            else if(ou==mode_jeu)
            {
                button[boutton_mono_joueur].etat=etat_bouton_apres_mouvement_souris(button[boutton_mono_joueur],evenement);
                button[boutton_multi_joueur].etat=etat_bouton_apres_mouvement_souris(button[boutton_multi_joueur],evenement);

                SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
                coller_surface(mode_jeu,button,ecran);
                SDL_Flip(ecran);
                SDL_Delay(50);

            }
        }
    }
    SDL_FreeSurface(fond_ecran);
    Mix_FreeChunk(son_boutton);
}



void charger_resources_interface_choix_inputs(Boutton inputs[],SDL_Surface *ecran)
{
    inputs[keyboard].boutton_active=IMG_Load("resources/images/clavier_selectionner.png");
    inputs[keyboard].boutton_desactive=IMG_Load("resources/images/clavier_non_selectionner.png");

    inputs[souris].boutton_active=IMG_Load("resources/images/souri_selectionnes.png");
    inputs[souris].boutton_desactive=IMG_Load("resources/images/souris_non_selectionnes.png");

    inputs[mannette].boutton_active=IMG_Load("resources/images/mannette_selctionee.png");
    inputs[mannette].boutton_desactive=IMG_Load("resources/images/mannette_non_selctionee.png");

    inputs[keyboard].etat=0;
    inputs[souris].etat=0;
    inputs[mannette].etat=0;


    inputs[keyboard].position.x=((ecran->w)/3)-20;
    inputs[keyboard].position.y=(ecran->h)/3 ;

    inputs[souris].position.x=((ecran->w)/3)-20 ;
    inputs[souris].position.y=8*(ecran->h)/15 ;

    inputs[mannette].position.x=((ecran->w)/3)-20 ;
    inputs[mannette].position.y= 11*(ecran->h)/15;
}



void charger_resources_interface_choix_inputs_2(Boutton inputs[],SDL_Surface *ecran)
{
    inputs[keyboard].boutton_active=IMG_Load("resources/images/clavier_selectionner.png");
    inputs[keyboard].boutton_desactive=IMG_Load("resources/images/clavier_non_selectionner.png");

    inputs[souris].boutton_active=IMG_Load("resources/images/souri_selectionnes.png");
    inputs[souris].boutton_desactive=IMG_Load("resources/images/souris_non_selectionnes.png");

    inputs[mannette].boutton_active=IMG_Load("resources/images/mannette_selctionee.png");
    inputs[mannette].boutton_desactive=IMG_Load("resources/images/mannette_non_selctionee.png");

    inputs[keyboard].etat=0;
    inputs[souris].etat=0;
    inputs[mannette].etat=0;


    inputs[keyboard].position.x=(((ecran->w)/3)-20)+inputs[keyboard].boutton_active->w;
    inputs[keyboard].position.y=(ecran->h)/3 ;

    inputs[souris].position.x=inputs[keyboard].position.x ;
    inputs[souris].position.y=8*(ecran->h)/15 ;

    inputs[mannette].position.x=inputs[keyboard].position.x  ;
    inputs[mannette].position.y= 11*(ecran->h)/15;
}






void coller_surface_interface_inputs(Boutton inputs[],SDL_Surface *ecran,int mode_de_jeu,SDL_Surface *fond_ecran,SDL_Surface *textes[],SDL_Rect position_texte1,SDL_Rect position_texte2,Boutton inputs2[])
{
    SDL_Rect position_background;

    position_background.x=0;
    position_background.y=0;

    if(mode_de_jeu==mono_joueur)
    {
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
        SDL_BlitSurface(textes[0],NULL,ecran,&position_texte1);

        if(inputs[keyboard].etat==1)
            SDL_BlitSurface(inputs[keyboard].boutton_active,NULL,ecran,&inputs[keyboard].position);
        else
            SDL_BlitSurface(inputs[keyboard].boutton_desactive,NULL,ecran,&inputs[keyboard].position);

        if(inputs[souris].etat==1)
            SDL_BlitSurface(inputs[souris].boutton_active,NULL,ecran,&inputs[souris].position);
        else
            SDL_BlitSurface(inputs[souris].boutton_desactive,NULL,ecran,&inputs[souris].position);

        if(inputs[mannette].etat==1)
            SDL_BlitSurface(inputs[mannette].boutton_active,NULL,ecran,&inputs[mannette].position);
        else
            SDL_BlitSurface(inputs[mannette].boutton_desactive,NULL,ecran,&inputs[mannette].position);
    }
    if(mode_de_jeu==multi_joueur)
    {
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(fond_ecran,NULL,ecran,&position_background);
        SDL_BlitSurface(textes[0],NULL,ecran,&position_texte1);

        if(inputs[keyboard].etat==1)
            SDL_BlitSurface(inputs[keyboard].boutton_active,NULL,ecran,&inputs[keyboard].position);
        else
            SDL_BlitSurface(inputs[keyboard].boutton_desactive,NULL,ecran,&inputs[keyboard].position);

        if(inputs[souris].etat==1)
            SDL_BlitSurface(inputs[souris].boutton_active,NULL,ecran,&inputs[souris].position);
        else
            SDL_BlitSurface(inputs[souris].boutton_desactive,NULL,ecran,&inputs[souris].position);

        if(inputs[mannette].etat==1)
            SDL_BlitSurface(inputs[mannette].boutton_active,NULL,ecran,&inputs[mannette].position);
        else
            SDL_BlitSurface(inputs[mannette].boutton_desactive,NULL,ecran,&inputs[mannette].position);


        SDL_BlitSurface(textes[1],NULL,ecran,&position_texte2);

        if(inputs2[keyboard].etat==1)
            SDL_BlitSurface(inputs2[keyboard].boutton_active,NULL,ecran,&inputs2[keyboard].position);
        else
            SDL_BlitSurface(inputs2[keyboard].boutton_desactive,NULL,ecran,&inputs2[keyboard].position);

        if(inputs2[souris].etat==1)
            SDL_BlitSurface(inputs2[souris].boutton_active,NULL,ecran,&inputs2[souris].position);
        else
            SDL_BlitSurface(inputs2[souris].boutton_desactive,NULL,ecran,&inputs2[souris].position);

        if(inputs2[mannette].etat==1)
            SDL_BlitSurface(inputs2[mannette].boutton_active,NULL,ecran,&inputs2[mannette].position);
        else
            SDL_BlitSurface(inputs2[mannette].boutton_desactive,NULL,ecran,&inputs2[mannette].position);
    }
}




int interface_choix_input(SDL_Surface *ecran,int mode_de_jeu)
{
    TTF_Init();
    Boutton inputs[3];
    Boutton Bouton_inputs2[3];

    SDL_Surface *textes[2];
    TTF_Font *police=TTF_OpenFont("resources/polices/Enchanted Land.otf",60);
    SDL_Color couleur_textes= {0,0,0};
    SDL_Event evenement;
    int continuer=1;
    int input_choisi;
    SDL_Surface *fond_ecran=IMG_Load("resources/images/fond_ecran_option.png");

    /*chargement des ressources*/
    charger_resources_interface_choix_inputs(inputs,ecran);
    charger_resources_interface_choix_inputs_2(Bouton_inputs2,ecran);
    /*les textes player1 et player2*/
    textes[0]=TTF_RenderText_Blended(police,"player 1",couleur_textes);
    textes[1]=TTF_RenderText_Blended(police,"player 2",couleur_textes);

    SDL_Rect position_texte1,position_texte2;

    position_texte1.x=ecran->w/6-100;
    position_texte1.y=ecran->h/5;

    position_texte2.x=ecran->w-textes[1]->w-100;
    position_texte2.y=ecran->h/5;

    int x2_min=Bouton_inputs2[keyboard].position.x;
    int x_max_clavier=Bouton_inputs2[keyboard].position.x+200;
    int x_max_souris=Bouton_inputs2[souris].position.x+200;
    int x_max_mannette=Bouton_inputs2[mannette].position.x+200;

    int clavier2=0,souris2=0,mannette2=0;



    switch(mode_de_jeu)
    {
    case mono_joueur:
        coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
        SDL_Flip(ecran);
        SDL_Delay(100);
        while(continuer)
        {
            SDL_PollEvent(&evenement);

            switch(evenement.type)
            {
            case SDL_QUIT:
                continuer=0;
                return 0;
                break;
            case SDL_KEYDOWN:
                switch(evenement.key.keysym.sym)
                {
                case SDLK_LEFT:
                    if(inputs[keyboard].etat==1 && (((ecran->w)/3)-20)-200<inputs[keyboard].position.x && inputs[keyboard].position.x!=(((ecran->w)/3)-20)-200)
                    {
                        inputs[keyboard].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=keyboard;
                        break;
                    }
                    else if(inputs[souris].etat==1 && (((ecran->w)/3)-20)-200<inputs[souris].position.x && inputs[keyboard].position.x!=(((ecran->w)/3)-20)-200)
                    {
                        inputs[souris].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=mannette;
                        break;
                    }
                    else if(inputs[mannette].etat==1 && (((ecran->w)/3)-20)-200<inputs[mannette].position.x && inputs[keyboard].position.x!=(((ecran->w)/3)-20)-200)
                    {
                        inputs[mannette].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=souris;
                        break;
                    }
                    break;
                case SDLK_RIGHT:
                    if(inputs[keyboard].etat==1 && inputs[keyboard].position.x<(((ecran->w)/3)-20))
                    {
                        inputs[keyboard].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=keyboard;
                        break;
                    }
                    else if(inputs[souris].etat==1 && inputs[souris].position.x<(((ecran->w)/3)-20))
                    {
                        inputs[souris].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=mannette;
                        break;
                    }
                    else if(inputs[mannette].etat==1 && inputs[mannette].position.x<(((ecran->w)/3)-20))
                    {
                        inputs[mannette].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=souris;
                        break;
                    }
                    break;
                case SDLK_DOWN:
                    if(inputs[keyboard].etat==0 && inputs[souris].etat==0 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=1;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=0;
                    }
                    else if(inputs[keyboard].etat==1 && inputs[souris].etat==0 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=1;
                        inputs[mannette].etat=0;
                    }
                    else if(inputs[keyboard].etat==0 && inputs[souris].etat==1 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=1;
                    }
                    else if(inputs[keyboard].etat==0 && inputs[souris].etat==0 && inputs[mannette].etat==1)
                    {
                        inputs[keyboard].etat=1;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=0;
                    }
                    break;
                case SDLK_UP:
                    if(inputs[keyboard].etat==0 && inputs[souris].etat==0 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=1;
                    }
                    else if(inputs[keyboard].etat==0 && inputs[souris].etat==0 && inputs[mannette].etat==1)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=1;
                        inputs[mannette].etat=0;
                    }
                    else if(inputs[keyboard].etat==0 && inputs[souris].etat==1 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=1;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=0;
                    }
                    else if(inputs[keyboard].etat==1 && inputs[souris].etat==0 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=1;
                    }

                    coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                    SDL_Flip(ecran);
                    SDL_Delay(100);
                    break;
                case SDLK_RETURN:
                    if(inputs[keyboard].position.x==(((ecran->w)/3)-20)-200 && inputs[souris].position.x!=(((ecran->w)/3)-20)-200 && inputs[mannette].position.x!=(((ecran->w)/3)-20)-200)
                        return keyboard;
                    else if(inputs[mannette].position.x==(((ecran->w)/3)-20)-200 && inputs[souris].position.x!=(((ecran->w)/3)-20)-200 && inputs[keyboard].position.x!=(((ecran->w)/3)-20)-200)
                        return mannette;
                    else
                        break;
                    break;
                case SDLK_ESCAPE:
                    return -2;
                }
                break;
            }
            coller_surface_interface_inputs(inputs,ecran,mono_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
            SDL_Flip(ecran);
            SDL_Delay(100);
        }
        break;
    case multi_joueur:
        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
        SDL_Flip(ecran);
        SDL_Delay(100);
        while(continuer)
        {
            SDL_PollEvent(&evenement);

            switch(evenement.type)
            {
            case SDL_QUIT:
                continuer=0;
                return 0;
                break;
            case SDL_KEYDOWN:
                switch(evenement.key.keysym.sym)
                {
                /**boutton joueur 1**/
                case SDLK_a:
                    if(inputs[keyboard].etat==1 && (((ecran->w)/3)-20)-200<inputs[keyboard].position.x && inputs[keyboard].position.x!=(((ecran->w)/3)-20)-200)
                    {
                        inputs[keyboard].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=keyboard;
                        break;
                    }
                    else if(inputs[souris].etat==1 && (((ecran->w)/3)-20)-200<inputs[souris].position.x && inputs[keyboard].position.x!=(((ecran->w)/3)-20)-200)
                    {
                        inputs[souris].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=mannette;
                        break;
                    }
                    else if(inputs[mannette].etat==1 && (((ecran->w)/3)-20)-200<inputs[mannette].position.x && inputs[keyboard].position.x!=(((ecran->w)/3)-20)-200)
                    {
                        inputs[mannette].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=souris;
                        break;
                    }
                    break;

                case SDLK_d:
                    if(inputs[keyboard].etat==1 && inputs[keyboard].position.x<(((ecran->w)/3)-20))
                    {
                        inputs[keyboard].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=keyboard;
                        break;
                    }
                    else if(inputs[souris].etat==1 && inputs[souris].position.x<(((ecran->w)/3)-20))
                    {
                        inputs[souris].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=mannette;
                        break;
                    }
                    else if(inputs[mannette].etat==1 && inputs[mannette].position.x<(((ecran->w)/3)-20))
                    {
                        inputs[mannette].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                        //input_choisi=souris;
                        break;
                    }
                    break;
                case SDLK_s:
                    if(inputs[keyboard].etat==0 && inputs[souris].etat==0 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=1;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=0;
                    }
                    else if(inputs[keyboard].etat==1 && inputs[souris].etat==0 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=1;
                        inputs[mannette].etat=0;
                    }
                    else if(inputs[keyboard].etat==0 && inputs[souris].etat==1 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=1;
                    }
                    else if(inputs[keyboard].etat==0 && inputs[souris].etat==0 && inputs[mannette].etat==1)
                    {
                        inputs[keyboard].etat=1;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=0;
                    }

                    coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                    SDL_Flip(ecran);
                    SDL_Delay(100);
                    break;
                case SDLK_w:

                    if(inputs[keyboard].etat==0 && inputs[souris].etat==0 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=1;
                    }
                    else if(inputs[keyboard].etat==0 && inputs[souris].etat==0 && inputs[mannette].etat==1)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=1;
                        inputs[mannette].etat=0;
                    }
                    else if(inputs[keyboard].etat==0 && inputs[souris].etat==1 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=1;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=0;
                    }
                    else if(inputs[keyboard].etat==1 && inputs[souris].etat==0 && inputs[mannette].etat==0)
                    {
                        inputs[keyboard].etat=0;
                        inputs[souris].etat=0;
                        inputs[mannette].etat=1;
                    }

                    coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                    SDL_Flip(ecran);
                    SDL_Delay(150);
                    break;
                /**boutton joueur 2**/
                case SDLK_LEFT:
                    if(Bouton_inputs2[keyboard].etat==1 && Bouton_inputs2[keyboard].position.x>x2_min /*&& Bouton_inputs2[keyboard].position.x!=Bouton_inputs2[keyboard].position.x*/)
                    {
                        Bouton_inputs2[keyboard].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        clavier2=0;
                        SDL_Delay(100);
                        //input_choisi=keyboard;
                        break;
                    }
                    else if(Bouton_inputs2[souris].etat==1 && Bouton_inputs2[souris].position.x>x2_min /*&& Bouton_inputs2[keyboard].position.x!=Bouton_inputs2[souris].position.x*/)
                    {
                        Bouton_inputs2[souris].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        souris2=0;
                        SDL_Delay(100);
                        //input_choisi=mannette;
                        break;
                    }
                    else if(Bouton_inputs2[mannette].etat==1 && Bouton_inputs2[mannette].position.x>x2_min /*&& Bouton_inputs2[mannette].position.x!=Bouton_inputs2[mannette].position.x-200*/)
                    {
                        Bouton_inputs2[mannette].position.x-=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        mannette2=0;
                        SDL_Delay(100);
                        //input_choisi=souris;
                        break;
                    }
                    break;

                case SDLK_RIGHT:
                    if(Bouton_inputs2[keyboard].etat==1 && clavier2==0/*inputs[keyboard].position.x!=x_max_clavier && inputs[keyboard].position.x<x_max_clavier*/)
                    {
                        Bouton_inputs2[keyboard].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        clavier2=1;
                        SDL_Delay(100);
                        //input_choisi=keyboard;
                        break;
                    }
                    else if(Bouton_inputs2[souris].etat==1 && souris2==0/*inputs[souris].position.x!=x_max_souris && inputs[souris].position.x<x_max_souris*/)
                    {
                        Bouton_inputs2[souris].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        souris2=1;
                        SDL_Delay(100);
                        //input_choisi=mannette;
                        break;
                    }
                    else if(Bouton_inputs2[mannette].etat==1 && mannette2==0/*inputs[mannette].position.x!=x_max_mannette && inputs[mannette].position.x<x_max_mannette*/)
                    {
                        Bouton_inputs2[mannette].position.x+=200;
                        coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                        SDL_Flip(ecran);
                        mannette2=1;
                        SDL_Delay(100);
                        //input_choisi=souris;
                        break;
                    }
                    break;
                case SDLK_DOWN:
                    if(Bouton_inputs2[keyboard].etat==0 && Bouton_inputs2[souris].etat==0 && Bouton_inputs2[mannette].etat==0)
                    {
                        Bouton_inputs2[keyboard].etat=1;
                        Bouton_inputs2[souris].etat=0;
                        Bouton_inputs2[mannette].etat=0;
                    }
                    else if(Bouton_inputs2[keyboard].etat==1 && Bouton_inputs2[souris].etat==0 && Bouton_inputs2[mannette].etat==0)
                    {
                        Bouton_inputs2[keyboard].etat=0;
                        Bouton_inputs2[souris].etat=1;
                        Bouton_inputs2[mannette].etat=0;
                    }
                    else if(Bouton_inputs2[keyboard].etat==0 && Bouton_inputs2[souris].etat==1 && Bouton_inputs2[mannette].etat==0)
                    {
                        Bouton_inputs2[keyboard].etat=0;
                        Bouton_inputs2[souris].etat=0;
                        Bouton_inputs2[mannette].etat=1;
                    }
                    else if(Bouton_inputs2[keyboard].etat==0 && Bouton_inputs2[souris].etat==0 && Bouton_inputs2[mannette].etat==1)
                    {
                        Bouton_inputs2[keyboard].etat=1;
                        Bouton_inputs2[souris].etat=0;
                        Bouton_inputs2[mannette].etat=0;
                    }

                    coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                    SDL_Flip(ecran);
                    SDL_Delay(100);
                    break;
                case SDLK_UP:

                    if(Bouton_inputs2[keyboard].etat==0 && Bouton_inputs2[souris].etat==0 && Bouton_inputs2[mannette].etat==0)
                    {
                        Bouton_inputs2[keyboard].etat=0;
                        Bouton_inputs2[souris].etat=0;
                        Bouton_inputs2[mannette].etat=1;
                    }
                    else if(Bouton_inputs2[keyboard].etat==0 && Bouton_inputs2[souris].etat==0 && Bouton_inputs2[mannette].etat==1)
                    {
                        Bouton_inputs2[keyboard].etat=0;
                        Bouton_inputs2[souris].etat=1;
                        Bouton_inputs2[mannette].etat=0;
                    }
                    else if(Bouton_inputs2[keyboard].etat==0 && Bouton_inputs2[souris].etat==1 && Bouton_inputs2[mannette].etat==0)
                    {
                        Bouton_inputs2[keyboard].etat=1;
                        Bouton_inputs2[souris].etat=0;
                        Bouton_inputs2[mannette].etat=0;
                    }
                    else if(Bouton_inputs2[keyboard].etat==1 && Bouton_inputs2[souris].etat==0 && Bouton_inputs2[mannette].etat==0)
                    {
                        Bouton_inputs2[keyboard].etat=0;
                        Bouton_inputs2[souris].etat=0;
                        Bouton_inputs2[mannette].etat=1;
                    }

                    coller_surface_interface_inputs(inputs,ecran,multi_joueur,fond_ecran,textes,position_texte1,position_texte2,Bouton_inputs2);
                    SDL_Flip(ecran);
                    SDL_Delay(150);
                    break;
                case SDLK_RETURN:
                    if(inputs[keyboard].etat==1 && inputs[souris].etat==0 && inputs[mannette].etat==0 && Bouton_inputs2[keyboard].etat==1 && Bouton_inputs2[souris].etat==0 && Bouton_inputs2[mannette].etat==0)
                        return keyboard;
                    else
                        break;
                }
                break;

            }
        }
        break;
    }
    SDL_FreeSurface(textes[0]);
    SDL_FreeSurface(textes[1]);
    SDL_FreeSurface(fond_ecran);
    TTF_CloseFont(police);

    SDL_FreeSurface(inputs[mannette].boutton_active);
    SDL_FreeSurface(inputs[mannette].boutton_desactive);
    SDL_FreeSurface(inputs[keyboard].boutton_active);
    SDL_FreeSurface(inputs[keyboard].boutton_desactive);
    SDL_FreeSurface(inputs[souris].boutton_active);
    SDL_FreeSurface(inputs[souris].boutton_desactive);

    SDL_FreeSurface(Bouton_inputs2[mannette].boutton_active);
    SDL_FreeSurface(Bouton_inputs2[mannette].boutton_desactive);
    SDL_FreeSurface(Bouton_inputs2[keyboard].boutton_active);
    SDL_FreeSurface(Bouton_inputs2[keyboard].boutton_desactive);
    SDL_FreeSurface(Bouton_inputs2[souris].boutton_active);
    SDL_FreeSurface(Bouton_inputs2[souris].boutton_desactive);

}
