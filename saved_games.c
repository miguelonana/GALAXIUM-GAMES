#include "header1.h"



int niveau1_mono_joueur_from_save(SDL_Surface *ecran)
{
    /*elements du niveau*/
    enemy mechant;
    background fond_ecran_niv1;
    Personnage joueur1;
    enigme question_corona;
    enigmesf maths;
    minimap MINI_M;
    temps time;



    /*variables de jeu*/
    int continuer=1;
    SDL_Event evenement;
    int redimensionnement=20;
    SDL_Surface *vie=IMG_Load("vie.png");

    SDL_Surface *pieces=IMG_Load("pieces.png");
    SDL_Rect position_piece;
    int pieces_presente=0;
    int t_pieces1=SDL_GetTicks(),t_pieces2;

    int temps_actuel=0,temps_precedent=0,dt;
    Uint8 *keystate = SDL_GetKeyState(NULL);
    int i,ennemi_present=0;
    SDL_Rect pos_pour_mini_map;

    int t_ennemi1=SDL_GetTicks(),t_ennemi2;//pour controller le temps dapparition des ennemis

    int enigme_present=0,niveau_termine=0;
    SDL_Surface *game_over=IMG_Load("resources/images/gameover.png"),*level_complete=IMG_Load("resources/images/level_complete.png");
    int enigme_maths_resolu=0;

    SDL_Surface *pieces_specials=IMG_Load("resources/images/pieces_special.png");
    int pieces_special_presente=0;
    int t_pieces_special_1=SDL_GetTicks(),t_pieces_special_2;
    SDL_Rect position_piece_specials;
    int jeu_en_pause=0;
    TTF_Font *police=TTF_OpenFont("resources/sons/police.ttf",20);
    int nivv;
    TTF_Font *police_t=TTF_OpenFont("resources/sons/Enchanted Land.otf",30);






    /*initialisation des element du niveau*/
    init(&joueur1,1);
    init_perso(&joueur1,ecran);

    initEnnemi(&mechant);

    init_background(&fond_ecran_niv1,ecran,1);
    initminimap(&MINI_M,1,ecran);
    initialiser_temps(&time,MINI_M);//initialisation du minimap

    load_quitter(&joueur1,&fond_ecran_niv1,&time,&nivv);


    /*variables de musique du niveau*/
    Mix_Chunk  *son_coup;
    Mix_Chunk  *son_pieces;
    Mix_Chunk  *son_pieces_speciales;
    Mix_Music *music_jeu;

    music_jeu=Mix_LoadMUS("resources/sons/game_sound.wav");//son du jeu
    son_coup=Mix_LoadWAV("resources/sons/son_coup.wav");//son apres un coup
    son_pieces=Mix_LoadWAV("resources/sons/son_pieces1.wav");//son l'orsqu'on prend une pieces jaune
    son_pieces_speciales=Mix_LoadWAV("resources/sons/son_pieces2.wav");//son l'orsqu'on prend une piece rouge

    //Mix_AllocateChannels(3);
//



//lancement musique jeu niveau1
    Mix_PlayMusic(music_jeu,-1);

    genererEnigme(&question_corona,"resources/questions.txt");
    switch(resoudre_enigme(question_corona,ecran))
    {
    case 0:
        continuer=0;
        break;
    case 1:
        joueur1.score+=1000;
        break;
    case -1:
        joueur1.nombre_vie--;
        break;
    }

    afficher_background(fond_ecran_niv1,ecran);
    MINI_M.position_symb.x=majminimap(joueur1.position,redimensionnement,MINI_M);

    afficher_minimap(MINI_M,ecran);
    afficher_temps(&time,ecran,police_t);


    joueur1.position.y+=30;
    afficher_perso(joueur1,ecran,police);
    pos_pour_mini_map=joueur1.position;
    SDL_Flip(ecran);




    while(continuer)
    {
        temps_actuel=SDL_GetTicks();
        dt=temps_actuel-temps_precedent;
        temps_precedent=temps_actuel;

        SDL_PollEvent(&evenement);

        switch(evenement.type)
        {
        case SDL_QUIT:
            if(quitter(joueur1,fond_ecran_niv1,ecran,1,time)!=annuler)
            {
                continuer=0;
                return 0;
            }
            else
                break;
            break;
        case SDL_KEYDOWN:
            if(keystate[SDLK_LEFT] && keystate[SDLK_s])
            {
                joueur1.action=sauter;

                joueur1.direction=gauche;
                saut(&joueur1);

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                SDL_BlitSurface(IMG_Load("resources/images/sauter_gauche.png"),NULL,ecran,&joueur1.position);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }
                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }
                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y+=100;
                joueur1.position.x-=100;


                scrolling(&fond_ecran_niv1,gauche,avancement_scrolling);
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                SDL_Flip(ecran);
                SDL_Delay(100);


                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }

            }
            else if(keystate[SDLK_LEFT] && keystate[SDLK_d])
            {
                Mix_PlayChannel(-1,son_coup,0);
                joueur1.position.y-=30;
                for(i=0; i<4; i++)
                {
                    joueur1.direction=gauche;
                    joueur1.action=frapper_gauche;

                    animer_perso(&joueur1);
                    afficher_background(fond_ecran_niv1,ecran);
                    MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                    afficher_minimap(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present==1)
                    {
                        updateEnnemi (&mechant,joueur1);
                        afficherEnnemi(mechant,ecran);
                    }

                    if(pieces_presente==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                    if(pieces_special_presente==1)
                        SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                    afficher_perso(joueur1,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur1.position.y+=30;
                joueur1.action=surplace_gauche;

            }
            else if(keystate[SDLK_RIGHT] && keystate[SDLK_s])
            {
                joueur1.action=sauter;

                joueur1.direction=droite;
                saut(&joueur1);
                scrolling(&fond_ecran_niv1,droite,avancement_scrolling);
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }
                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);

                SDL_BlitSurface(IMG_Load("resources/images/sauter_droite.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(100);

                joueur1.position.y+=100;
                joueur1.position.x+=100;

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }
                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(100);

                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }
            }
            else if(keystate[SDLK_RIGHT] && keystate[SDLK_d])
            {
                Mix_PlayChannel(-1,son_coup,0);
                joueur1.position.y-=30;

                for(i=0; i<4; i++)
                {
                    joueur1.direction=droite;
                    joueur1.action=frapper_droite;

                    animer_perso(&joueur1);
                    afficher_background(fond_ecran_niv1,ecran);
                    MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                    afficher_minimap(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present==1)
                    {
                        updateEnnemi (&mechant,joueur1);
                        afficherEnnemi(mechant,ecran);
                    }
                    if(pieces_presente==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                    if(pieces_special_presente==1)
                        SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                    afficher_perso(joueur1,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur1.position.y+=30;
                joueur1.action=surplace_droite;
            }
            else if(keystate[SDLK_RIGHT])
            {
                if((ennemi_present==1 || pieces_presente==1 || pieces_special_presente==1))
                {
                    joueur1.action=marcher_droite;
                    joueur1.direction=droite;
                    if(joueur1.position.x<ecran->w-60)
                        deplacer_perso(&joueur1,dt);

                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
                else if(joueur1.position.x>=ecran->w-90)
                {
                    joueur1.action=marcher_droite;
                    joueur1.direction=droite;
                    if(joueur1.position.x<ecran->w-60)
                        deplacer_perso(&joueur1,dt);

                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
                else
                {
                    joueur1.direction=droite;
                    joueur1.action=marcher_droite;
                    scrolling(&fond_ecran_niv1,droite,avancement_scrolling);
                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
            }

            else if(keystate[SDLK_LEFT])
            {

                if(joueur1.position.x>60)
                {
                    joueur1.action=marcher_gauche;
                    joueur1.direction=gauche;
                    deplacer_perso(&joueur1,dt);
                    pos_pour_mini_map.x-=3;
                    animer_perso(&joueur1);
                }
                else
                {
                    joueur1.action=marcher_gauche;
                    joueur1.direction=gauche;
                    animer_perso(&joueur1);
                }
            }
            else if(keystate[SDLK_d])
            {
                joueur1.position.y-=30;
                Mix_PlayChannel(-1,son_coup,0);
                if(joueur1.direction==gauche)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur1.direction=gauche;
                        joueur1.action=frapper_gauche;

                        animer_perso(&joueur1);
                        afficher_background(fond_ecran_niv1,ecran);
                        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                        afficher_minimap(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present==1)
                        {
                            updateEnnemi (&mechant,joueur1);
                            afficherEnnemi(mechant,ecran);
                        }
                        if(pieces_presente==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                        if(pieces_special_presente==1)
                            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                        afficher_perso(joueur1,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(100);

                    }
                    joueur1.action=surplace_gauche;
                }
                else if(joueur1.direction==droite)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur1.direction=droite;
                        joueur1.action=frapper_droite;

                        animer_perso(&joueur1);
                        afficher_background(fond_ecran_niv1,ecran);
                        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                        afficher_minimap(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present==1)
                        {
                            updateEnnemi (&mechant,joueur1);
                            afficherEnnemi(mechant,ecran);
                        }

                        if(pieces_presente==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                        if(pieces_special_presente==1)
                            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                        afficher_perso(joueur1,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(50);
                    }
                    joueur1.action=surplace_droite;
                }
                joueur1.position.y+=30;
            }
            else if(keystate[SDLK_s])
            {
                int dir=joueur1.direction;
                joueur1.direction=haut;

                joueur1.action=sauter;

                saut(&joueur1);

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                if(dir==droite)
                    SDL_BlitSurface(IMG_Load("resources/images/sauter_droite.png"),NULL,ecran,&joueur1.position);
                else if(dir==gauche)
                    SDL_BlitSurface(IMG_Load("resources/images/sauter_gauche.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y+=100;

                joueur1.direction=dir;

                if(dir==gauche)
                    joueur1.action=surplace_gauche;
                else if(dir==droite)
                    joueur1.action=surplace_droite;

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(100);



                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }
            }
            else if(keystate[SDLK_ESCAPE] && jeu_en_pause==0)//si on appuies sur echap,pause!
            {
                jeu_en_pause=1;

            }
            if(keystate[SDLK_a])
            {
                if(joueur1.acceleration<4 && joueur1.direction==droite)
                {
                    joueur1.acceleration+=0.1;
                    if(keystate[SDLK_RIGHT] && ennemi_present==0 && pieces_special_presente==0 && pieces_presente==0)
                    {
                        scrolling(&fond_ecran_niv1,droite,avancement_scrolling_rapide);
                        pos_pour_mini_map.x+=6;
                    }
                }
            }
            break;
        }
        /*pause*////////////////
        if(jeu_en_pause==1)
        {
            //int c=1;
            SDL_Event ev;
            Boutton Pause[2];

            charger_boutton_pause(Pause,ecran);
            coller_surface_pause(ecran,Pause);
            SDL_Flip(ecran);
            while(jeu_en_pause)
            {
                SDL_WaitEvent(&ev);
                switch(ev.type)
                {
                case SDL_KEYDOWN:
                    switch(ev.key.keysym.sym)
                    {
                    case SDLK_DOWN:
                        if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        else if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        coller_surface_pause(ecran,Pause);
                        SDL_Flip(ecran);
                        SDL_Delay(150);

                        break;
                    case SDLK_UP:
                        if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        else if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        coller_surface_pause(ecran,Pause);
                        SDL_Flip(ecran);
                        SDL_Delay(150);
                        break;
                    case SDLK_RETURN:
                        if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                            jeu_en_pause=0;
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            if(quitter(joueur1,fond_ecran_niv1,ecran,1,time)!=annuler)
                                return 0;//sauvegarder
                        }
                        break;
                    }
                }
            }

            SDL_FreeSurface(Pause[resume_game].boutton_active);
            SDL_FreeSurface(Pause[resume_game].boutton_desactive);

            SDL_FreeSurface(Pause[back_to_menu].boutton_active);
            SDL_FreeSurface(Pause[back_to_menu].boutton_desactive);

            time.position.x = (MINI_M.position_minimap.x);
            time.position.y = (MINI_M.minimp->h)+50;
        }
////////////////////////////

        /*correction bug position*/
        if(joueur1.position.x<=0)
            joueur1.position.x=60;
        if(joueur1.position.x>=ecran->w-25)
            joueur1.position.x=ecran->w-80;

        /**affichage apres mise a jour**/
        afficher_background(fond_ecran_niv1,ecran);
        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

        afficher_minimap(MINI_M,ecran);
        afficher_temps(&time,ecran,police_t);

        if(ennemi_present==1)
        {
            updateEnnemi (&mechant,joueur1);
            afficherEnnemi(mechant,ecran);
        }
        if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
        {
            pieces_presente=0;
            joueur1.score+=500;
            t_pieces1=SDL_GetTicks();
            t_pieces2=SDL_GetTicks();
        }

        if(pieces_presente==1)
            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
        if(pieces_special_presente==1)
            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

        afficher_perso(joueur1,ecran,police);
        SDL_Flip(ecran);
        SDL_Delay(50);

        /**annimer le joueur si il est surplace**/
        if(joueur1.action==surplace_droite || joueur1.action==surplace_gauche)
            animer_perso(&joueur1);

        /**faire deccelerer le joueur**/
        if(joueur1.acceleration>0)
            joueur1.acceleration-=0.05;

        /**incrementer le score**/
        joueur1.score+=0.1;


        /**mettre le joueur a letat de repos**/
        switch(joueur1.direction)
        {
        case gauche:
            joueur1.action=surplace_gauche;
            break;
        case droite:
            joueur1.action=surplace_droite;
            break;
        }




        /**generer les ennemis apres un certain temps**/
        t_ennemi2=SDL_GetTicks();
        if(t_ennemi2-t_ennemi1>20000 && ennemi_present!=1)
        {
            ennemi_present=1;

            mechant.poss.y=joueur1.position.y;

            if(joueur1.position.x<ecran->w/2)
                mechant.poss.x=joueur1.position.x+300;
            else
                mechant.poss.x=0;
        }

        /**generation des pieces jaunes**/
        t_pieces2=SDL_GetTicks();
        if(pieces_presente==0 && t_pieces2-t_pieces1>3000)
        {
            pieces_presente=1;
            if(joueur1.position.x>ecran->w/2)
                position_piece.x=joueur1.position.x-250;
            else
                position_piece.x=joueur1.position.x+250;
            position_piece.y=joueur1.position.y-70;
        }

        if(t_pieces2-t_pieces1>10000 && pieces_presente==1)
        {
            pieces_presente=0;
            t_pieces2=SDL_GetTicks();
            t_pieces1=SDL_GetTicks();
        }
        /////////////////////



        /**generation pieces speciales**/

        t_pieces_special_2=SDL_GetTicks();
        if(pieces_special_presente==0 && t_pieces_special_2-t_pieces_special_1>20000 && pieces_presente==0 && pieces_special_presente==0)
        {
            pieces_special_presente=1;

            if(joueur1.position.x>ecran->w/2)
                position_piece_specials.x=joueur1.position.x-250;
            else
                position_piece_specials.x=joueur1.position.x+250;

            position_piece_specials.y=joueur1.position.y-70;
        }

        if(t_pieces_special_2-t_pieces_special_1>23500 && pieces_special_presente==1)
        {
            pieces_special_presente=0;
            t_pieces_special_2=SDL_GetTicks();
            t_pieces_special_1=SDL_GetTicks();
        }




        /**si collision avec un ennemi,combat**/
        if(collisionBB(joueur1,mechant) && ennemi_present==1)
        {
            int t=0,t1=0;
            int fin=1;
            SDL_Event e;
            int battu=0;

            t1=SDL_GetTicks();
            while(fin)
            {
                t=SDL_GetTicks();
                SDL_PollEvent(&e);
                switch(e.type)
                {
                case SDL_KEYDOWN:
                    if(keystate[SDLK_d] && keystate[SDLK_RIGHT] && joueur1.position.x<mechant.poss.x)
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        for(i=0; i<4; i++)
                        {
                            joueur1.direction=droite;
                            joueur1.action=frapper_droite;

                            animer_perso(&joueur1);
                            afficher_background(fond_ecran_niv1,ecran);
                            MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                            afficher_minimap(MINI_M,ecran);
                            afficher_temps(&time,ecran,police_t);
                            if(ennemi_present==1)
                            {
                                updateEnnemi (&mechant,joueur1);
                                afficherEnnemi(mechant,ecran);
                            }

                            if(pieces_presente==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                            if(pieces_special_presente==1)
                                SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                            afficher_perso(joueur1,ecran,police);
                            SDL_Flip(ecran);
                            SDL_Delay(50);
                        }
                        ennemi_present=0;
                        joueur1.score+=1000;
                        t_ennemi1=SDL_GetTicks();
                        battu=1;
                        joueur1.position.y+=30;
                    }
                    else if(keystate[SDLK_d] && keystate[SDLK_LEFT] && joueur1.position.x>mechant.poss.x)
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        for(i=0; i<4; i++)
                        {
                            joueur1.direction=gauche;
                            joueur1.action=frapper_gauche;

                            animer_perso(&joueur1);
                            afficher_background(fond_ecran_niv1,ecran);
                            MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                            afficher_minimap(MINI_M,ecran);
                            afficher_temps(&time,ecran,police_t);
                            if(ennemi_present==1)
                            {
                                updateEnnemi (&mechant,joueur1);
                                afficherEnnemi(mechant,ecran);
                            }

                            if(pieces_presente==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                            if(pieces_special_presente==1)
                                SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                            afficher_perso(joueur1,ecran,police);
                            SDL_Flip(ecran);
                            SDL_Delay(100);

                        }
                        joueur1.action=surplace_gauche;
                        ennemi_present=0;
                        t_ennemi1=SDL_GetTicks();
                        battu=1;
                        joueur1.position.y+=30;
                    }
                    else if(keystate[SDLK_d])
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        if(joueur1.direction==gauche)
                        {
                            for(i=0; i<4; i++)
                            {
                                joueur1.direction=gauche;
                                joueur1.action=frapper_gauche;

                                animer_perso(&joueur1);
                                afficher_background(fond_ecran_niv1,ecran);
                                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                                afficher_minimap(MINI_M,ecran);
                                afficher_temps(&time,ecran,police_t);
                                if(ennemi_present==1)
                                {
                                    updateEnnemi (&mechant,joueur1);
                                    afficherEnnemi(mechant,ecran);
                                }
                                if(pieces_presente==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                                if(pieces_special_presente==1)
                                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                                afficher_perso(joueur1,ecran,police);
                                SDL_Flip(ecran);
                                SDL_Delay(100);

                            }
                            if(joueur1.position.x>mechant.poss.x)
                            {
                                joueur1.action=surplace_gauche;
                                ennemi_present=0;
                                t_ennemi1=SDL_GetTicks();
                                battu=1;
                            }

                        }
                        else if(joueur1.direction==droite)
                        {
                            for(i=0; i<4; i++)
                            {
                                joueur1.direction=droite;
                                joueur1.action=frapper_droite;

                                animer_perso(&joueur1);
                                afficher_background(fond_ecran_niv1,ecran);
                                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                                afficher_minimap(MINI_M,ecran);
                                afficher_temps(&time,ecran,police_t);
                                if(ennemi_present==1)
                                {
                                    updateEnnemi (&mechant,joueur1);
                                    afficherEnnemi(mechant,ecran);
                                }

                                if(pieces_presente==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                                if(pieces_special_presente==1)
                                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                                afficher_perso(joueur1,ecran,police);
                                SDL_Flip(ecran);
                                SDL_Delay(50);
                            }
                            if(joueur1.position.x<mechant.poss.x)
                            {
                                ennemi_present=0;
                                joueur1.score+=1000;
                                t_ennemi1=SDL_GetTicks();
                                battu=1;
                            }

                        }
                        joueur1.position.y+=30;
                    }
                    break;
                }

                if(t-t1>1000)
                    fin=0;

            }

            switch(battu)
            {
            case 0:
                ennemi_present=0;
                joueur1.nombre_vie--;
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);

                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                if(joueur1.direction==gauche)
                    SDL_BlitSurface(IMG_Load("blesse_gauche.png"),NULL,ecran,&joueur1.position);
                else if(joueur1.direction==droite)
                    SDL_BlitSurface(IMG_Load("blesse_droite.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(100);
                if(joueur1.direction==gauche)
                    joueur1.action=surplace_gauche;
                else if(joueur1.direction==droite)
                    joueur1.action=surplace_droite;

                break;
            case 1:
                joueur1.score+=500;
                if(joueur1.direction==gauche)
                    joueur1.action=surplace_gauche;
                else if(joueur1.direction==droite)
                    joueur1.action=surplace_droite;

                battu=0;
                break;
            }

        }/**fin gestion de combat**/

        /*correction bug position*/
        if(joueur1.position.x<=0)
            joueur1.position.x=60;
        if(joueur1.position.x>=ecran->w-25)
            joueur1.position.x=ecran->w-80;

        /**si le joueur est a la fin du niveau**/
        if(fond_ecran_niv1.camera_pos1.x>=fond_ecran_niv1.image->w-fond_ecran_niv1.camera_pos1.w-300 && niveau_termine==0)
        {
            int n,fin=0;

            do
            {
                n=afficherenigme(maths,ecran);
                switch(n)
                {
                case 0:
                    joueur1.nombre_vie--;
                    break;
                case 1:
                    niveau_termine=1;
                    fin=1;
                    break;
                }
                if(joueur1.nombre_vie<=0)
                    fin=1;
            }
            while(fin!=1);

        }
        /**si le joueur na plus de vie**/
        if(joueur1.nombre_vie==0)
        {
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            SDL_BlitSurface(game_over,NULL,ecran,&fond_ecran_niv1.pos_background1);
            SDL_Flip(ecran);
            SDL_Delay(2000);


            if(mise_a_jour_highscores("resources/sauvegardes/highestscores.txt",joueur1.score)==1)
            {
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(IMG_Load("resources/images/new_highest_score.png"),NULL,ecran,&fond_ecran_niv1.pos_background1);
                SDL_Delay(1000);
            }

            continuer=0;
            return 0;
        }
        if(niveau_termine==1)
        {
            if(mise_a_jour_highscores("resources/sauvegardes/highestscores.txt",joueur1.score)==1)
            {
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(IMG_Load("resources/images/new_highest_score.png"),NULL,ecran,&fond_ecran_niv1.pos_background1);
                SDL_Delay(1000);
            }


            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            SDL_BlitSurface(level_complete,NULL,ecran,&fond_ecran_niv1.pos_background1);
            SDL_Flip(ecran);
            SDL_Delay(2000);

            sauvegarde_transition(joueur1,fond_ecran_niv1,time,2);
            return 1;
        }

    }


    Mix_HaltMusic();


    /**liberation des ressources**/
    Mix_FreeChunk(son_coup);
    Mix_FreeChunk(son_pieces);
    Mix_FreeChunk(son_pieces_speciales);
    free_minimap(MINI_M);
    SDL_FreeSurface(fond_ecran_niv1.image);
    SDL_FreeSurface(fond_ecran_niv1.image);
    TTF_CloseFont(police);
    TTF_CloseFont(police_t);
    SDL_FreeSurface(joueur1.image_actuel);
    SDL_FreeSurface(game_over);
    SDL_FreeSurface(level_complete);
    SDL_FreeSurface(pieces_specials);
    SDL_FreeSurface(pieces);

    return 1;
}



int niveau2_mono_joueur_from_save(SDL_Surface *ecran)
{
    /*elements du niveau*/
    enemy mechant;
    background fond_ecran_niv1;
    Personnage joueur1;
    enigme question_corona;
    enigmesf maths;
    minimap MINI_M;
    temps time;



    /*variables de jeu*/
    int continuer=1;
    SDL_Event evenement;
    int redimensionnement=20;
    SDL_Surface *vie=IMG_Load("resources/images/vie.png");

    SDL_Surface *pieces=IMG_Load("resources/images/pieces.png");
    SDL_Rect position_piece;
    int pieces_presente=0;
    int t_pieces1=SDL_GetTicks(),t_pieces2;

    int temps_actuel=0,temps_precedent=0,dt;
    Uint8 *keystate = SDL_GetKeyState(NULL);
    int i,ennemi_present=0;
    SDL_Rect pos_pour_mini_map;

    int t_ennemi1=SDL_GetTicks(),t_ennemi2;//pour controller le temps dapparition des ennemis

    int enigme_present=0,niveau_termine=0;
    SDL_Surface *game_over=IMG_Load("resources/images/gameover.png"),*level_complete=IMG_Load("resources/images/level_complete.png");
    int enigme_maths_resolu=0;

    SDL_Surface *pieces_specials=IMG_Load("resources/images/pieces_special.png");
    int pieces_special_presente=0;
    int t_pieces_special_1=SDL_GetTicks(),t_pieces_special_2;
    SDL_Rect position_piece_specials;
    int jeu_en_pause=0;
    int niv;
    int vies_presente=0;
    int t_vies1=SDL_GetTicks(),t_vies2;
    SDL_Rect position_vies;
    TTF_Font *police=TTF_OpenFont("resources/polices/police.ttf",20);
    int nivv;
    TTF_Font *police_t=TTF_OpenFont("resources/polices/Enchanted Land.otf",30);






    /*initialisation des element du niveau*/
    init(&joueur1,1);
    init_perso(&joueur1,ecran);

    initEnnemi(&mechant);


    initminimap(&MINI_M,2,ecran);
    initialiser_temps(&time,MINI_M);//initialisation du minimap
    init_background(&fond_ecran_niv1,ecran,2);

    load_quitter(&joueur1,&fond_ecran_niv1,&time,&nivv);

    joueur1.position.x=150;
    joueur1.position.y=hauteur_fenetre-(130);

    /*variables de musique du niveau*/
    Mix_Chunk  *son_coup;
    Mix_Chunk  *son_pieces;
    Mix_Chunk  *son_pieces_speciales;
    Mix_Music *music_jeu;
    Mix_Chunk *son_vie;


    music_jeu=Mix_LoadMUS("resources/sons/game_sound.wav");//son du jeu
    son_coup=Mix_LoadWAV("resources/sons/son_coup.wav");//son apres un coup
    son_pieces=Mix_LoadWAV("resources/sons/son_pieces1.wav");//son l'orsqu'on prend une pieces jaune
    son_pieces_speciales=Mix_LoadWAV("resources/sons/son_pieces2.wav");//son l'orsqu'on prend une piece rouge
    son_vie=Mix_LoadWAV("resources/sons/son_pieces2.wav");

    //Mix_AllocateChannels(3);
//



//lancement musique jeu niveau1
    Mix_PlayMusic(music_jeu,-1);

    genererEnigme(&question_corona,"resources/questions.txt");
    switch(resoudre_enigme(question_corona,ecran))
    {
    case 0:
        continuer=0;
        break;
    case 1:
        joueur1.score+=1000;
        break;
    case -1:
        joueur1.nombre_vie--;
        break;
    }

    afficher_background(fond_ecran_niv1,ecran);
    MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

    afficher_minimap(MINI_M,ecran);
    afficher_temps(&time,ecran,police_t);


    afficher_perso(joueur1,ecran,police);
    pos_pour_mini_map=joueur1.position;
    SDL_Flip(ecran);




    while(continuer)
    {
        temps_actuel=SDL_GetTicks();
        dt=temps_actuel-temps_precedent;
        temps_precedent=temps_actuel;

        SDL_PollEvent(&evenement);

        switch(evenement.type)
        {
        case SDL_QUIT:
            if(quitter(joueur1,fond_ecran_niv1,ecran,2,time)!=annuler)
            {
                continuer=0;
                return 0;
            }
            else
                break;
            break;
        case SDL_KEYDOWN:
            if(keystate[SDLK_LEFT] && keystate[SDLK_s])
            {
                joueur1.action=sauter;

                joueur1.direction=gauche;
                saut(&joueur1);

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                SDL_BlitSurface(IMG_Load("resources/images/sauter_gauche.png"),NULL,ecran,&joueur1.position);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }
                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }
                if(collision_pieces(position_vies,joueur1) && vies_presente==1 && joueur1.nombre_vie<5)
                {
                    Mix_PlayChannel(-1,son_vie,0);
                    vies_presente=0;
                    joueur1.nombre_vie++;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }
                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y+=100;
                joueur1.position.x-=100;


                scrolling(&fond_ecran_niv1,gauche,avancement_scrolling);
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                SDL_Flip(ecran);
                SDL_Delay(100);


                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }

            }
            else if(keystate[SDLK_LEFT] && keystate[SDLK_d])
            {
                Mix_PlayChannel(-1,son_coup,0);
                joueur1.position.y-=30;
                for(i=0; i<4; i++)
                {
                    joueur1.direction=gauche;
                    joueur1.action=frapper_gauche;

                    animer_perso(&joueur1);
                    afficher_background(fond_ecran_niv1,ecran);
                    MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                    afficher_minimap(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present==1)
                    {
                        updateEnnemi (&mechant,joueur1);
                        afficherEnnemi(mechant,ecran);
                    }

                    if(pieces_presente==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                    if(pieces_special_presente==1)
                        SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                    if(vies_presente==1)
                        SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                    afficher_perso(joueur1,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur1.position.y+=30;
                joueur1.action=surplace_gauche;

            }
            else if(keystate[SDLK_RIGHT] && keystate[SDLK_s])
            {
                joueur1.action=sauter;

                joueur1.direction=droite;
                saut(&joueur1);
                scrolling(&fond_ecran_niv1,droite,avancement_scrolling);
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_vies,joueur1) && vies_presente==1 && joueur1.nombre_vie<5)
                {
                    Mix_PlayChannel(-1,son_vie,0);
                    vies_presente=0;
                    joueur1.nombre_vie++;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }
                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);

                SDL_BlitSurface(IMG_Load("resources/images/sauter_droite.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(100);

                joueur1.position.y+=100;
                joueur1.position.x+=100;

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }
                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(100);

                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }
            }
            else if(keystate[SDLK_RIGHT] && keystate[SDLK_d])
            {
                Mix_PlayChannel(-1,son_coup,0);
                joueur1.position.y-=30;

                for(i=0; i<4; i++)
                {
                    joueur1.direction=droite;
                    joueur1.action=frapper_droite;

                    animer_perso(&joueur1);
                    afficher_background(fond_ecran_niv1,ecran);
                    MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                    afficher_minimap(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present==1)
                    {
                        updateEnnemi (&mechant,joueur1);
                        afficherEnnemi(mechant,ecran);
                    }
                    if(pieces_presente==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                    if(pieces_special_presente==1)
                        SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                    if(vies_presente==1)
                        SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                    afficher_perso(joueur1,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur1.position.y+=30;
                joueur1.action=surplace_droite;
            }
            else if(keystate[SDLK_RIGHT])
            {
                if((ennemi_present==1 || pieces_presente==1 || pieces_special_presente==1 || vies_presente==1))
                {
                    joueur1.action=marcher_droite;
                    joueur1.direction=droite;
                    if(joueur1.position.x<ecran->w-60)
                        deplacer_perso(&joueur1,dt);

                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
                else if(joueur1.position.x>=ecran->w-90)
                {
                    joueur1.action=marcher_droite;
                    joueur1.direction=droite;
                    if(joueur1.position.x<ecran->w-60)
                        deplacer_perso(&joueur1,dt);

                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
                else
                {
                    joueur1.direction=droite;
                    joueur1.action=marcher_droite;
                    scrolling(&fond_ecran_niv1,droite,avancement_scrolling);
                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
            }

            else if(keystate[SDLK_LEFT])
            {

                if(joueur1.position.x>60)
                {
                    joueur1.action=marcher_gauche;
                    joueur1.direction=gauche;
                    deplacer_perso(&joueur1,dt);
                    pos_pour_mini_map.x-=3;
                    animer_perso(&joueur1);
                }
                else
                {
                    joueur1.action=marcher_gauche;
                    joueur1.direction=gauche;
                    animer_perso(&joueur1);
                }
            }
            else if(keystate[SDLK_d])
            {
                joueur1.position.y-=30;
                Mix_PlayChannel(-1,son_coup,0);
                if(joueur1.direction==gauche)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur1.direction=gauche;
                        joueur1.action=frapper_gauche;

                        animer_perso(&joueur1);
                        afficher_background(fond_ecran_niv1,ecran);
                        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                        afficher_minimap(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present==1)
                        {
                            updateEnnemi (&mechant,joueur1);
                            afficherEnnemi(mechant,ecran);
                        }
                        if(pieces_presente==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                        if(pieces_special_presente==1)
                            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                        if(vies_presente==1)
                            SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                        afficher_perso(joueur1,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(100);

                    }
                    joueur1.action=surplace_gauche;
                }
                else if(joueur1.direction==droite)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur1.direction=droite;
                        joueur1.action=frapper_droite;

                        animer_perso(&joueur1);
                        afficher_background(fond_ecran_niv1,ecran);
                        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                        afficher_minimap(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present==1)
                        {
                            updateEnnemi (&mechant,joueur1);
                            afficherEnnemi(mechant,ecran);
                        }

                        if(pieces_presente==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                        if(pieces_special_presente==1)
                            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                        if(vies_presente==1)
                            SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                        afficher_perso(joueur1,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(50);
                    }
                    joueur1.action=surplace_droite;
                }
                joueur1.position.y+=30;
            }
            else if(keystate[SDLK_s])
            {
                int dir=joueur1.direction;
                joueur1.direction=haut;

                joueur1.action=sauter;

                saut(&joueur1);

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }
                if(collision_pieces(position_vies,joueur1) && vies_presente==1 && joueur1.nombre_vie<5)
                {
                    Mix_PlayChannel(-1,son_vie,0);
                    vies_presente=0;
                    joueur1.nombre_vie++;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                if(dir==droite)
                    SDL_BlitSurface(IMG_Load("resources/images/sauter_droite.png"),NULL,ecran,&joueur1.position);
                else if(dir==gauche)
                    SDL_BlitSurface(IMG_Load("resources/images/sauter_gauche.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y+=100;

                joueur1.direction=dir;

                if(dir==gauche)
                    joueur1.action=surplace_gauche;
                else if(dir==droite)
                    joueur1.action=surplace_droite;

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(100);



                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }
            }
            else if(keystate[SDLK_ESCAPE] && jeu_en_pause==0)//si on appuies sur echap,pause!
            {
                jeu_en_pause=1;

            }
            if(keystate[SDLK_a])
            {
                if(joueur1.acceleration<4 && joueur1.direction==droite)
                {
                    joueur1.acceleration+=0.1;
                    if(keystate[SDLK_RIGHT] && ennemi_present==0 && pieces_special_presente==0 && pieces_presente==0)
                    {
                        scrolling(&fond_ecran_niv1,droite,avancement_scrolling_rapide);
                        pos_pour_mini_map.x+=6;
                    }
                }
            }
            break;
        }
        /*pause*////////////////
        if(jeu_en_pause==1)
        {
            //int c=1;
            SDL_Event ev;
            Boutton Pause[2];

            charger_boutton_pause(Pause,ecran);
            coller_surface_pause(ecran,Pause);
            SDL_Flip(ecran);
            while(jeu_en_pause)
            {
                SDL_WaitEvent(&ev);
                switch(ev.type)
                {
                case SDL_KEYDOWN:
                    switch(ev.key.keysym.sym)
                    {
                    case SDLK_DOWN:
                        if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        else if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        coller_surface_pause(ecran,Pause);
                        SDL_Flip(ecran);
                        SDL_Delay(150);

                        break;
                    case SDLK_UP:
                        if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        else if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        coller_surface_pause(ecran,Pause);
                        SDL_Flip(ecran);
                        SDL_Delay(150);
                        break;
                    case SDLK_RETURN:
                        if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                            jeu_en_pause=0;
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            if(quitter(joueur1,fond_ecran_niv1,ecran,2,time)!=annuler)
                                return 0;//sauvegarder
                        }
                        break;
                    }
                }
            }

            SDL_FreeSurface(Pause[resume_game].boutton_active);
            SDL_FreeSurface(Pause[resume_game].boutton_desactive);

            SDL_FreeSurface(Pause[back_to_menu].boutton_active);
            SDL_FreeSurface(Pause[back_to_menu].boutton_desactive);

            time.position.x = (MINI_M.position_minimap.x);
            time.position.y = (MINI_M.minimp->h)+50;
        }
////////////////////////////

        /*correction bug position*/
        if(joueur1.position.x<=0)
            joueur1.position.x=60;
        if(joueur1.position.x>=ecran->w-25)
            joueur1.position.x=ecran->w-80;

        /**affichage apres mise a jour**/
        afficher_background(fond_ecran_niv1,ecran);
        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

        afficher_minimap(MINI_M,ecran);
        afficher_temps(&time,ecran,police_t);

        if(ennemi_present==1)
        {
            updateEnnemi (&mechant,joueur1);
            afficherEnnemi(mechant,ecran);
        }
        if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
        {
            pieces_presente=0;
            joueur1.score+=500;
            t_pieces1=SDL_GetTicks();
            t_pieces2=SDL_GetTicks();
        }
        if(collision_pieces(position_vies,joueur1) && vies_presente==1 && joueur1.nombre_vie<5)
        {
            Mix_PlayChannel(-1,son_vie,0);
            vies_presente=0;
            joueur1.nombre_vie++;
            t_vies1=SDL_GetTicks();
            t_vies2=SDL_GetTicks();
        }

        if(pieces_presente==1)
            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
        if(pieces_special_presente==1)
            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
        if(vies_presente==1)
            SDL_BlitSurface(vie,NULL,ecran,&position_vies);

        afficher_perso(joueur1,ecran,police);
        SDL_Flip(ecran);
        SDL_Delay(50);

        /**annimer le joueur si il est surplace**/
        if(joueur1.action==surplace_droite || joueur1.action==surplace_gauche)
            animer_perso(&joueur1);

        /**faire deccelerer le joueur**/
        if(joueur1.acceleration>0)
            joueur1.acceleration-=0.05;

        /**incrementer le score**/
        joueur1.score+=0.1;


        /**mettre le joueur a letat de repos**/
        switch(joueur1.direction)
        {
        case gauche:
            joueur1.action=surplace_gauche;
            break;
        case droite:
            joueur1.action=surplace_droite;
            break;
        }




        /**generer les ennemis apres un certain temps**/
        t_ennemi2=SDL_GetTicks();
        if(t_ennemi2-t_ennemi1>20000 && ennemi_present!=1)
        {
            ennemi_present=1;

            mechant.poss.y=joueur1.position.y;

            if(joueur1.position.x<ecran->w/2)
                mechant.poss.x=joueur1.position.x+300;
            else
                mechant.poss.x=0;
        }

        /**generation des pieces jaunes**/
        t_pieces2=SDL_GetTicks();
        if(pieces_presente==0 && t_pieces2-t_pieces1>6000)
        {
            pieces_presente=1;
            if(joueur1.position.x>ecran->w/2)
                position_piece.x=joueur1.position.x-250;
            else
                position_piece.x=joueur1.position.x+250;
            position_piece.y=joueur1.position.y-70;
        }

        if(t_pieces2-t_pieces1>10000 && pieces_presente==1)
        {
            pieces_presente=0;
            t_pieces2=SDL_GetTicks();
            t_pieces1=SDL_GetTicks();
        }
        /////////////////////



        /**generation pieces speciales**/

        t_pieces_special_2=SDL_GetTicks();
        if(pieces_special_presente==0 && t_pieces_special_2-t_pieces_special_1>15000 && pieces_presente==0 && pieces_special_presente==0)
        {
            pieces_special_presente=1;

            if(joueur1.position.x>ecran->w/2)
                position_piece_specials.x=joueur1.position.x-250;
            else
                position_piece_specials.x=joueur1.position.x+250;

            position_piece_specials.y=joueur1.position.y-70;
        }

        if(t_pieces_special_2-t_pieces_special_1>23500 && pieces_special_presente==1)
        {
            pieces_special_presente=0;
            t_pieces_special_2=SDL_GetTicks();
            t_pieces_special_1=SDL_GetTicks();
        }

        /**generation des vies**/
        t_vies2=SDL_GetTicks();
        if(vies_presente==0 && t_vies2-t_vies1>25000 && joueur1.nombre_vie<5)
        {
            vies_presente=1;
            if(joueur1.position.x>ecran->w/2)
                position_vies.x=joueur1.position.x-250;
            else
                position_vies.x=joueur1.position.x+250;
            position_vies.y=joueur1.position.y-70;
        }

        if(t_vies2-t_vies1>30000 && vies_presente==1)
        {
            vies_presente=0;
            t_vies2=SDL_GetTicks();
            t_vies1=SDL_GetTicks();
        }

        /**si collision avec un ennemi,combat**/
        if(collisionBB(joueur1,mechant) && ennemi_present==1)
        {
            int t=0,t1=0;
            int fin=1;
            SDL_Event e;
            int battu=0;

            t1=SDL_GetTicks();
            while(fin)
            {
                t=SDL_GetTicks();
                SDL_PollEvent(&e);
                switch(e.type)
                {
                case SDL_KEYDOWN:
                    if(keystate[SDLK_d] && keystate[SDLK_RIGHT] && joueur1.position.x<mechant.poss.x)
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        for(i=0; i<4; i++)
                        {
                            joueur1.direction=droite;
                            joueur1.action=frapper_droite;

                            animer_perso(&joueur1);
                            afficher_background(fond_ecran_niv1,ecran);
                            MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                            afficher_minimap(MINI_M,ecran);
                            afficher_temps(&time,ecran,police_t);
                            if(ennemi_present==1)
                            {
                                updateEnnemi (&mechant,joueur1);
                                afficherEnnemi(mechant,ecran);
                            }

                            if(pieces_presente==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                            if(pieces_special_presente==1)
                                SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                            if(vies_presente==1)
                                SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                            afficher_perso(joueur1,ecran,police);
                            SDL_Flip(ecran);
                            SDL_Delay(50);
                        }
                        ennemi_present=0;
                        joueur1.score+=1000;
                        t_ennemi1=SDL_GetTicks();
                        battu=1;
                        joueur1.position.y+=30;
                    }
                    else if(keystate[SDLK_d] && keystate[SDLK_LEFT] && joueur1.position.x>mechant.poss.x)
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        for(i=0; i<4; i++)
                        {
                            joueur1.direction=gauche;
                            joueur1.action=frapper_gauche;

                            animer_perso(&joueur1);
                            afficher_background(fond_ecran_niv1,ecran);
                            MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                            afficher_minimap(MINI_M,ecran);
                            afficher_temps(&time,ecran,police_t);
                            if(ennemi_present==1)
                            {
                                updateEnnemi (&mechant,joueur1);
                                afficherEnnemi(mechant,ecran);
                            }

                            if(pieces_presente==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                            if(pieces_special_presente==1)
                                SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                            if(vies_presente==1)
                                SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                            afficher_perso(joueur1,ecran,police);
                            SDL_Flip(ecran);
                            SDL_Delay(100);

                        }
                        joueur1.action=surplace_gauche;
                        ennemi_present=0;
                        t_ennemi1=SDL_GetTicks();
                        battu=1;
                        joueur1.position.y+=30;
                    }
                    else if(keystate[SDLK_d])
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        if(joueur1.direction==gauche)
                        {
                            for(i=0; i<4; i++)
                            {
                                joueur1.direction=gauche;
                                joueur1.action=frapper_gauche;

                                animer_perso(&joueur1);
                                afficher_background(fond_ecran_niv1,ecran);
                                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                                afficher_minimap(MINI_M,ecran);
                                afficher_temps(&time,ecran,police_t);
                                if(ennemi_present==1)
                                {
                                    updateEnnemi (&mechant,joueur1);
                                    afficherEnnemi(mechant,ecran);
                                }
                                if(pieces_presente==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                                if(pieces_special_presente==1)
                                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                                if(vies_presente==1)
                                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                                afficher_perso(joueur1,ecran,police);
                                SDL_Flip(ecran);
                                SDL_Delay(100);

                            }
                            if(joueur1.position.x>mechant.poss.x)
                            {
                                joueur1.action=surplace_gauche;
                                ennemi_present=0;
                                t_ennemi1=SDL_GetTicks();
                                battu=1;
                            }

                        }
                        else if(joueur1.direction==droite)
                        {
                            for(i=0; i<4; i++)
                            {
                                joueur1.direction=droite;
                                joueur1.action=frapper_droite;

                                animer_perso(&joueur1);
                                afficher_background(fond_ecran_niv1,ecran);
                                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                                afficher_minimap(MINI_M,ecran);
                                afficher_temps(&time,ecran,police_t);
                                if(ennemi_present==1)
                                {
                                    updateEnnemi (&mechant,joueur1);
                                    afficherEnnemi(mechant,ecran);
                                }

                                if(pieces_presente==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                                if(pieces_special_presente==1)
                                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                                if(vies_presente==1)
                                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                                afficher_perso(joueur1,ecran,police);
                                SDL_Flip(ecran);
                                SDL_Delay(50);
                            }
                            if(joueur1.position.x<mechant.poss.x)
                            {
                                ennemi_present=0;
                                joueur1.score+=1000;
                                t_ennemi1=SDL_GetTicks();
                                battu=1;
                            }

                        }
                        joueur1.position.y+=30;
                    }
                    break;
                }

                if(t-t1>1000)
                    fin=0;

            }

            switch(battu)
            {
            case 0:
                ennemi_present=0;
                joueur1.nombre_vie--;
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                if(joueur1.direction==gauche)
                    SDL_BlitSurface(IMG_Load("resources/images/blesse_gauche.png"),NULL,ecran,&joueur1.position);
                else if(joueur1.direction==droite)
                    SDL_BlitSurface(IMG_Load("resources/images/blesse_droite.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(100);
                if(joueur1.direction==gauche)
                    joueur1.action=surplace_gauche;
                else if(joueur1.direction==droite)
                    joueur1.action=surplace_droite;

                break;
            case 1:
                joueur1.score+=500;
                if(joueur1.direction==gauche)
                    joueur1.action=surplace_gauche;
                else if(joueur1.direction==droite)
                    joueur1.action=surplace_droite;

                battu=0;
                break;
            }

        }/**fin gestion de combat**/

        /*correction bug position*/
        if(joueur1.position.x<=0)
            joueur1.position.x=60;
        if(joueur1.position.x>=ecran->w-25)
            joueur1.position.x=ecran->w-80;

        /**si le joueur est a la fin du niveau**/
        if(fond_ecran_niv1.camera_pos1.x>=fond_ecran_niv1.image->w-fond_ecran_niv1.camera_pos1.w-300 && niveau_termine==0)
        {
            int n,fin=0;

            do
            {
                n=afficherenigme(maths,ecran);
                switch(n)
                {
                case 0:
                    joueur1.nombre_vie--;
                    break;
                case 1:
                    niveau_termine=1;
                    fin=1;
                    break;
                }
                if(joueur1.nombre_vie<=0)
                    fin=1;
            }
            while(fin!=1);

        }
        /**si le joueur na plus de vie**/
        if(joueur1.nombre_vie==0)
        {
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            SDL_BlitSurface(game_over,NULL,ecran,&fond_ecran_niv1.pos_background1);
            SDL_Flip(ecran);
            SDL_Delay(2000);

            if(mise_a_jour_highscores("resources/sauvegardes/highestscores.txt",joueur1.score)==1)
            {
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(IMG_Load("resources/images/new_highest_score.png"),NULL,ecran,&fond_ecran_niv1.pos_background1);
                SDL_Delay(1000);
            }

            continuer=0;
            return 0;
        }
        if(niveau_termine==1)
        {

            if(mise_a_jour_highscores("resources/sauvegardes/highestscores.txt",joueur1.score)==1)
            {
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(IMG_Load("resources/images/new_highest_score.png"),NULL,ecran,&fond_ecran_niv1.pos_background1);
                SDL_Delay(1000);
            }


            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            SDL_BlitSurface(level_complete,NULL,ecran,&fond_ecran_niv1.pos_background1);
            SDL_Flip(ecran);
            SDL_Delay(2000);
            return 1;
        }

    }


    Mix_HaltMusic();


    /**liberation des ressources**/
    Mix_FreeChunk(son_coup);
    Mix_FreeChunk(son_pieces);
    Mix_FreeChunk(son_pieces_speciales);
    free_minimap(MINI_M);
    TTF_CloseFont(police);
    TTF_CloseFont(police_t);
    SDL_FreeSurface(fond_ecran_niv1.image);
    SDL_FreeSurface(fond_ecran_niv1.image);
    SDL_FreeSurface(joueur1.image_actuel);
    SDL_FreeSurface(game_over);
    SDL_FreeSurface(level_complete);
    SDL_FreeSurface(pieces_specials);
    SDL_FreeSurface(pieces);

    return 1;
}





int niveau3_mono_joueur_from_save(SDL_Surface *ecran)
{
    /*elements du niveau*/
    enemy mechant;
    background fond_ecran_niv1;
    Personnage joueur1;
    enigme question_corona;
    enigmesf maths;
    minimap MINI_M;
    temps time;



    /*variables de jeu*/
    int continuer=1;
    SDL_Event evenement;
    int redimensionnement=20;
    SDL_Surface *vie=IMG_Load("resources/images/vie.png");

    SDL_Surface *pieces=IMG_Load("resources/images/pieces.png");
    SDL_Rect position_piece;
    int pieces_presente=0;
    int t_pieces1=SDL_GetTicks(),t_pieces2;

    int temps_actuel=0,temps_precedent=0,dt;
    Uint8 *keystate = SDL_GetKeyState(NULL);
    int i,ennemi_present=0;
    SDL_Rect pos_pour_mini_map;

    int t_ennemi1=SDL_GetTicks(),t_ennemi2;//pour controller le temps dapparition des ennemis

    int enigme_present=0,niveau_termine=0;
    SDL_Surface *game_over=IMG_Load("resources/images/gameover.png"),*level_complete=IMG_Load("resources/images/level_complete.png");
    int enigme_maths_resolu=0;

    SDL_Surface *pieces_specials=IMG_Load("resources/images/pieces_special.png");
    int pieces_special_presente=0;
    int t_pieces_special_1=SDL_GetTicks(),t_pieces_special_2;
    SDL_Rect position_piece_specials;
    int jeu_en_pause=0;
    int niv;
    int vies_presente=0;
    int t_vies1=SDL_GetTicks(),t_vies2;
    SDL_Rect position_vies;
    SDL_Surface *end_of_game=IMG_Load("resources/images/gameover.png");
    SDL_Surface *cure=IMG_Load("resources/images/cure.png");
    int cure_taken=0;
    SDL_Rect position_cure;
    TTF_Font *police=TTF_OpenFont("resources/police/police.ttf",20);
    TTF_Font *police_t=TTF_OpenFont("resources/police/Enchanted Land.otf",30);







    /*initialisation des element du niveau*/
    init(&joueur1,1);
    init_perso(&joueur1,ecran);

    initEnnemi(&mechant);


    initminimap(&MINI_M,3,ecran);
    initialiser_temps(&time,MINI_M);//initialisation du minimap
    init_background(&fond_ecran_niv1,ecran,3);

    load_quitter(&joueur1,&fond_ecran_niv1,&time,&niv);

    joueur1.position.x=150;
    joueur1.position.y=hauteur_fenetre-(130);

    /*variables de musique du niveau*/
    Mix_Chunk  *son_coup;
    Mix_Chunk  *son_pieces;
    Mix_Chunk  *son_pieces_speciales;
    Mix_Music *music_jeu;
    Mix_Chunk *son_vie;
    //Mix_Music *son_victoire;


    music_jeu=Mix_LoadMUS("resources/sons/game_sound.wav");//son du jeu
    son_coup=Mix_LoadWAV("resources/sons/son_coup.wav");//son apres un coup
    son_pieces=Mix_LoadWAV("resources/sons/son_pieces1.wav");//son l'orsqu'on prend une pieces jaune
    son_pieces_speciales=Mix_LoadWAV("resources/sons/son_pieces2.wav");//son l'orsqu'on prend une piece rouge
    son_vie=Mix_LoadWAV("resources/sons/son_pieces2.wav");

    //Mix_AllocateChannels(3);
//



//lancement musique jeu niveau1
    Mix_PlayMusic(music_jeu,-1);

    genererEnigme(&question_corona,"resources/questions.txt");
    switch(resoudre_enigme(question_corona,ecran))
    {
    case 0:
        continuer=0;
        break;
    case 1:
        joueur1.score+=1000;
        break;
    case -1:
        joueur1.nombre_vie--;
        break;
    }

    afficher_background(fond_ecran_niv1,ecran);
    MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

    afficher_minimap(MINI_M,ecran);
    afficher_temps(&time,ecran,police_t);


    afficher_perso(joueur1,ecran,police);
    pos_pour_mini_map=joueur1.position;
    SDL_Flip(ecran);




    while(continuer)
    {
        temps_actuel=SDL_GetTicks();
        dt=temps_actuel-temps_precedent;
        temps_precedent=temps_actuel;

        SDL_PollEvent(&evenement);

        switch(evenement.type)
        {
        case SDL_QUIT:
            if(quitter(joueur1,fond_ecran_niv1,ecran,3,time)!=annuler)
            {
                continuer=0;
                return 0;
            }
            else
                break;
            break;
        case SDL_KEYDOWN:
            if(keystate[SDLK_LEFT] && keystate[SDLK_s])
            {
                joueur1.action=sauter;

                joueur1.direction=gauche;
                saut(&joueur1);

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                SDL_BlitSurface(IMG_Load("resources/images/sauter_gauche.png"),NULL,ecran,&joueur1.position);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }
                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }
                if(collision_pieces(position_vies,joueur1) && vies_presente==1 && joueur1.nombre_vie<5)
                {
                    Mix_PlayChannel(-1,son_vie,0);
                    vies_presente=0;
                    joueur1.nombre_vie++;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }
                if(collision_pieces(position_cure,joueur1) && niveau_termine==1)
                {
                    //Mix_PlayChannel(-1,son_victoire,0);
                    vies_presente=0;
                    joueur1.score+=5000;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                if(niveau_termine==1)
                    SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y+=100;
                joueur1.position.x-=100;


                scrolling(&fond_ecran_niv1,gauche,avancement_scrolling);
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }
                if(niveau_termine==1)
                    SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                SDL_Flip(ecran);
                SDL_Delay(100);


                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }

            }
            else if(keystate[SDLK_LEFT] && keystate[SDLK_d])
            {
                Mix_PlayChannel(-1,son_coup,0);
                joueur1.position.y-=30;
                for(i=0; i<4; i++)
                {
                    joueur1.direction=gauche;
                    joueur1.action=frapper_gauche;

                    animer_perso(&joueur1);
                    afficher_background(fond_ecran_niv1,ecran);
                    MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                    afficher_minimap(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present==1)
                    {
                        updateEnnemi (&mechant,joueur1);
                        afficherEnnemi(mechant,ecran);
                    }

                    if(pieces_presente==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                    if(pieces_special_presente==1)
                        SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                    if(vies_presente==1)
                        SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                    if(niveau_termine==1)
                        SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                    afficher_perso(joueur1,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur1.position.y+=30;
                joueur1.action=surplace_gauche;

            }
            else if(keystate[SDLK_RIGHT] && keystate[SDLK_s])
            {
                joueur1.action=sauter;

                joueur1.direction=droite;
                saut(&joueur1);
                scrolling(&fond_ecran_niv1,droite,avancement_scrolling);
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_vies,joueur1) && vies_presente==1 && joueur1.nombre_vie<5)
                {
                    Mix_PlayChannel(-1,son_vie,0);
                    vies_presente=0;
                    joueur1.nombre_vie++;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }
                if(collision_pieces(position_cure,joueur1) && niveau_termine==1)
                {
                    //Mix_PlayChannel(-1,son_victoire,0);
                    vies_presente=0;
                    joueur1.score+=5000;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }
                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                if(niveau_termine==1)
                    SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);

                SDL_BlitSurface(IMG_Load("resources/images/sauter_droite.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(100);

                joueur1.position.y+=100;
                joueur1.position.x+=100;

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }
                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                if(niveau_termine==1)
                    SDL_BlitSurface(cure,NULL,ecran,&position_cure);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(100);

                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }
            }
            else if(keystate[SDLK_RIGHT] && keystate[SDLK_d])
            {
                Mix_PlayChannel(-1,son_coup,0);
                joueur1.position.y-=30;

                for(i=0; i<4; i++)
                {
                    joueur1.direction=droite;
                    joueur1.action=frapper_droite;

                    animer_perso(&joueur1);
                    afficher_background(fond_ecran_niv1,ecran);
                    MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                    afficher_minimap(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present==1)
                    {
                        updateEnnemi (&mechant,joueur1);
                        afficherEnnemi(mechant,ecran);
                    }
                    if(pieces_presente==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                    if(pieces_special_presente==1)
                        SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                    if(vies_presente==1)
                        SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                    if(niveau_termine==1)
                        SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                    afficher_perso(joueur1,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur1.position.y+=30;
                joueur1.action=surplace_droite;
            }
            else if(keystate[SDLK_RIGHT])
            {
                if((ennemi_present==1 || pieces_presente==1 || pieces_special_presente==1 || vies_presente==1))
                {
                    joueur1.action=marcher_droite;
                    joueur1.direction=droite;
                    if(joueur1.position.x<ecran->w-60)
                        deplacer_perso(&joueur1,dt);

                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
                else if(joueur1.position.x>=ecran->w-90)
                {
                    joueur1.action=marcher_droite;
                    joueur1.direction=droite;
                    if(joueur1.position.x<ecran->w-60)
                        deplacer_perso(&joueur1,dt);

                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
                else
                {
                    joueur1.direction=droite;
                    joueur1.action=marcher_droite;
                    scrolling(&fond_ecran_niv1,droite,avancement_scrolling);
                    animer_perso(&joueur1);
                    pos_pour_mini_map.x+=3;
                }
            }

            else if(keystate[SDLK_LEFT])
            {

                if(joueur1.position.x>60)
                {
                    joueur1.action=marcher_gauche;
                    joueur1.direction=gauche;
                    deplacer_perso(&joueur1,dt);
                    pos_pour_mini_map.x-=3;
                    animer_perso(&joueur1);
                }
                else
                {
                    joueur1.action=marcher_gauche;
                    joueur1.direction=gauche;
                    animer_perso(&joueur1);
                }
            }
            else if(keystate[SDLK_d])
            {
                joueur1.position.y-=30;
                Mix_PlayChannel(-1,son_coup,0);
                if(joueur1.direction==gauche)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur1.direction=gauche;
                        joueur1.action=frapper_gauche;

                        animer_perso(&joueur1);
                        afficher_background(fond_ecran_niv1,ecran);
                        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                        afficher_minimap(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present==1)
                        {
                            updateEnnemi (&mechant,joueur1);
                            afficherEnnemi(mechant,ecran);
                        }
                        if(pieces_presente==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                        if(pieces_special_presente==1)
                            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                        if(vies_presente==1)
                            SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                        if(niveau_termine==1)
                            SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                        afficher_perso(joueur1,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(100);

                    }
                    joueur1.action=surplace_gauche;
                }
                else if(joueur1.direction==droite)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur1.direction=droite;
                        joueur1.action=frapper_droite;

                        animer_perso(&joueur1);
                        afficher_background(fond_ecran_niv1,ecran);
                        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                        afficher_minimap(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present==1)
                        {
                            updateEnnemi (&mechant,joueur1);
                            afficherEnnemi(mechant,ecran);
                        }

                        if(pieces_presente==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                        if(pieces_special_presente==1)
                            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                        if(vies_presente==1)
                            SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                        if(niveau_termine==1)
                            SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                        afficher_perso(joueur1,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(50);
                    }
                    joueur1.action=surplace_droite;
                }
                joueur1.position.y+=30;
            }
            else if(keystate[SDLK_s])
            {
                int dir=joueur1.direction;
                joueur1.direction=haut;

                joueur1.action=sauter;

                saut(&joueur1);

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);
                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente=0;
                    joueur1.score+=500;
                    t_pieces1=SDL_GetTicks();
                    t_pieces2=SDL_GetTicks();
                }
                if(collision_pieces(position_piece_specials,joueur1) && pieces_special_presente==1)
                {
                    Mix_PlayChannel(-1,son_pieces_speciales,0);
                    pieces_special_presente=0;
                    enigme_present=1;

                }
                if(collision_pieces(position_vies,joueur1) && vies_presente==1 && joueur1.nombre_vie<5)
                {
                    Mix_PlayChannel(-1,son_vie,0);
                    vies_presente=0;
                    joueur1.nombre_vie++;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }
                if(collision_pieces(position_cure,joueur1) && niveau_termine==1)
                {
                    //Mix_PlayChannel(-1,son_victoire,0);
                    vies_presente=0;
                    joueur1.score+=5000;
                    t_vies1=SDL_GetTicks();
                    t_vies2=SDL_GetTicks();
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                if(niveau_termine==1)
                    SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                if(dir==droite)
                    SDL_BlitSurface(IMG_Load("resources/images/sauter_droite.png"),NULL,ecran,&joueur1.position);
                else if(dir==gauche)
                    SDL_BlitSurface(IMG_Load("resources/images/sauter_gauche.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y+=100;

                joueur1.direction=dir;

                if(dir==gauche)
                    joueur1.action=surplace_gauche;
                else if(dir==droite)
                    joueur1.action=surplace_droite;

                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);
                if(niveau_termine==1)
                    SDL_BlitSurface(cure,NULL,ecran,&position_cure);

                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(100);



                if(enigme_present==1)
                {
                    enigme_present=0;
                    int e,n;
                    e=enigme_avec_ou_sans_fichier();
                    switch(e)
                    {
                    case 0:
                        genererEnigme(&question_corona,"resources/questions.txt");
                        switch(resoudre_enigme(question_corona,ecran))
                        {
                        case 0:
                            continuer=0;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        case -1:
                            joueur1.nombre_vie--;
                            break;
                        }
                        break;
                    case 1:
                        n=afficherenigme(maths,ecran);
                        switch(n)
                        {
                        case 0:
                            joueur1.nombre_vie--;
                            break;
                        case 1:
                            joueur1.score+=2000;
                            break;
                        }
                        break;
                    }
                    t_pieces_special_1=SDL_GetTicks();
                    t_pieces_special_2=SDL_GetTicks();
                }
            }
            else if(keystate[SDLK_ESCAPE] && jeu_en_pause==0)//si on appuies sur echap,pause!
            {
                jeu_en_pause=1;

            }
            if(keystate[SDLK_a])
            {
                if(joueur1.acceleration<4 && joueur1.direction==droite)
                {
                    joueur1.acceleration+=0.1;
                    if(keystate[SDLK_RIGHT]&& ennemi_present==0 && pieces_special_presente==0 && pieces_presente==0 && vies_presente==0)
                    {
                        scrolling(&fond_ecran_niv1,droite,avancement_scrolling_rapide);
                        pos_pour_mini_map.x+=6;
                    }
                }
            }
            break;
        }
        /*pause*////////////////
        if(jeu_en_pause==1)
        {
            //int c=1;
            SDL_Event ev;
            Boutton Pause[2];

            charger_boutton_pause(Pause,ecran);
            coller_surface_pause(ecran,Pause);
            SDL_Flip(ecran);
            while(jeu_en_pause)
            {
                SDL_WaitEvent(&ev);
                switch(ev.type)
                {
                case SDL_KEYDOWN:
                    switch(ev.key.keysym.sym)
                    {
                    case SDLK_DOWN:
                        if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        else if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        coller_surface_pause(ecran,Pause);
                        SDL_Flip(ecran);
                        SDL_Delay(150);

                        break;
                    case SDLK_UP:
                        if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            Pause[resume_game].etat=1;
                            Pause[back_to_menu].etat=0;
                        }
                        else if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                        {
                            Pause[resume_game].etat=0;
                            Pause[back_to_menu].etat=1;
                        }
                        coller_surface_pause(ecran,Pause);
                        SDL_Flip(ecran);
                        SDL_Delay(150);
                        break;
                    case SDLK_RETURN:
                        if(Pause[resume_game].etat==1 && Pause[back_to_menu].etat==0)
                            jeu_en_pause=0;
                        else if(Pause[resume_game].etat==0 && Pause[back_to_menu].etat==1)
                        {
                            if(quitter(joueur1,fond_ecran_niv1,ecran,3,time)!=annuler)
                                return 0;//sauvegarder
                        }
                        break;
                    }
                }
            }

            SDL_FreeSurface(Pause[resume_game].boutton_active);
            SDL_FreeSurface(Pause[resume_game].boutton_desactive);

            SDL_FreeSurface(Pause[back_to_menu].boutton_active);
            SDL_FreeSurface(Pause[back_to_menu].boutton_desactive);

            time.position.x = (MINI_M.position_minimap.x);
            time.position.y = (MINI_M.minimp->h)+50;
        }
////////////////////////////

        /*correction bug position*/
        if(joueur1.position.x<=0)
            joueur1.position.x=60;
        if(joueur1.position.x>=ecran->w-25)
            joueur1.position.x=ecran->w-80;

        /**affichage apres mise a jour**/
        afficher_background(fond_ecran_niv1,ecran);
        MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

        afficher_minimap(MINI_M,ecran);
        afficher_temps(&time,ecran,police_t);

        if(ennemi_present==1)
        {
            updateEnnemi (&mechant,joueur1);
            afficherEnnemi(mechant,ecran);
        }
        if(collision_pieces(position_piece,joueur1) && pieces_presente==1)
        {
            pieces_presente=0;
            joueur1.score+=500;
            t_pieces1=SDL_GetTicks();
            t_pieces2=SDL_GetTicks();
        }
        if(collision_pieces(position_vies,joueur1) && vies_presente==1 && joueur1.nombre_vie<5)
        {
            Mix_PlayChannel(-1,son_vie,0);
            vies_presente=0;
            joueur1.nombre_vie++;
            t_vies1=SDL_GetTicks();
            t_vies2=SDL_GetTicks();
        }
        if(collision_pieces(position_cure,joueur1) && niveau_termine==1)
        {
            //Mix_PlayChannel(-1,son_victoire,0);
            vies_presente=0;
            joueur1.score+=5000;
            t_vies1=SDL_GetTicks();
            t_vies2=SDL_GetTicks();
        }

        if(pieces_presente==1)
            SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
        if(pieces_special_presente==1)
            SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
        if(vies_presente==1)
            SDL_BlitSurface(vie,NULL,ecran,&position_vies);
        if(niveau_termine==1)
            SDL_BlitSurface(cure,NULL,ecran,&position_cure);

        afficher_perso(joueur1,ecran,police);
        SDL_Flip(ecran);
        SDL_Delay(50);

        /**annimer le joueur si il est surplace**/
        if(joueur1.action==surplace_droite || joueur1.action==surplace_gauche)
            animer_perso(&joueur1);

        /**faire deccelerer le joueur**/
        if(joueur1.acceleration>0)
            joueur1.acceleration-=0.05;

        /**incrementer le score**/
        joueur1.score+=0.1;


        /**mettre le joueur a letat de repos**/
        switch(joueur1.direction)
        {
        case gauche:
            joueur1.action=surplace_gauche;
            break;
        case droite:
            joueur1.action=surplace_droite;
            break;
        }




        /**generer les ennemis apres un certain temps**/
        t_ennemi2=SDL_GetTicks();
        if(t_ennemi2-t_ennemi1>8000 && ennemi_present!=1)
        {
            ennemi_present=1;

            mechant.poss.y=joueur1.position.y;

            if(joueur1.position.x<ecran->w/2)
                mechant.poss.x=joueur1.position.x+300;
            else
                mechant.poss.x=0;
        }

        /**generation des pieces jaunes**/
        t_pieces2=SDL_GetTicks();
        if(pieces_presente==0 && t_pieces2-t_pieces1>5000)
        {
            pieces_presente=1;
            if(joueur1.position.x>ecran->w/2)
                position_piece.x=joueur1.position.x-250;
            else
                position_piece.x=joueur1.position.x+250;
            position_piece.y=joueur1.position.y-70;
        }

        if(t_pieces2-t_pieces1>10000 && pieces_presente==1)
        {
            pieces_presente=0;
            t_pieces2=SDL_GetTicks();
            t_pieces1=SDL_GetTicks();
        }
        /////////////////////



        /**generation pieces speciales**/

        t_pieces_special_2=SDL_GetTicks();
        if(pieces_special_presente==0 && t_pieces_special_2-t_pieces_special_1>10000 && pieces_presente==0 && pieces_special_presente==0)
        {
            pieces_special_presente=1;

            if(joueur1.position.x>ecran->w/2)
                position_piece_specials.x=joueur1.position.x-250;
            else
                position_piece_specials.x=joueur1.position.x+250;

            position_piece_specials.y=joueur1.position.y-70;
        }

        if(t_pieces_special_2-t_pieces_special_1>13500 && pieces_special_presente==1)
        {
            pieces_special_presente=0;
            t_pieces_special_2=SDL_GetTicks();
            t_pieces_special_1=SDL_GetTicks();
        }

        /**generation des vies**/
        t_vies2=SDL_GetTicks();
        if(vies_presente==0 && t_vies2-t_vies1>35000 && joueur1.nombre_vie<5)
        {
            vies_presente=1;
            if(joueur1.position.x>ecran->w/2)
                position_vies.x=joueur1.position.x-250;
            else
                position_vies.x=joueur1.position.x+250;
            position_vies.y=joueur1.position.y-70;
        }

        if(t_vies2-t_vies1>38000 && vies_presente==1)
        {
            vies_presente=0;
            t_vies2=SDL_GetTicks();
            t_vies1=SDL_GetTicks();
        }

        /**si collision avec un ennemi,combat**/
        if(collisionBB(joueur1,mechant) && ennemi_present==1)
        {
            int t=0,t1=0;
            int fin=1;
            SDL_Event e;
            int battu=0;

            t1=SDL_GetTicks();
            while(fin)
            {
                t=SDL_GetTicks();
                SDL_PollEvent(&e);
                switch(e.type)
                {
                case SDL_KEYDOWN:
                    if(keystate[SDLK_d] && keystate[SDLK_RIGHT] && joueur1.position.x<mechant.poss.x)
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        for(i=0; i<4; i++)
                        {
                            joueur1.direction=droite;
                            joueur1.action=frapper_droite;

                            animer_perso(&joueur1);
                            afficher_background(fond_ecran_niv1,ecran);
                            MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                            afficher_minimap(MINI_M,ecran);
                            afficher_temps(&time,ecran,police_t);
                            if(ennemi_present==1)
                            {
                                updateEnnemi (&mechant,joueur1);
                                afficherEnnemi(mechant,ecran);
                            }

                            if(pieces_presente==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                            if(pieces_special_presente==1)
                                SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                            if(vies_presente==1)
                                SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                            afficher_perso(joueur1,ecran,police);
                            SDL_Flip(ecran);
                            SDL_Delay(50);
                        }
                        ennemi_present=0;
                        joueur1.score+=1000;
                        t_ennemi1=SDL_GetTicks();
                        battu=1;
                        joueur1.position.y+=30;
                    }
                    else if(keystate[SDLK_d] && keystate[SDLK_LEFT] && joueur1.position.x>mechant.poss.x)
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        for(i=0; i<4; i++)
                        {
                            joueur1.direction=gauche;
                            joueur1.action=frapper_gauche;

                            animer_perso(&joueur1);
                            afficher_background(fond_ecran_niv1,ecran);
                            MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                            afficher_minimap(MINI_M,ecran);
                            afficher_temps(&time,ecran,police_t);
                            if(ennemi_present==1)
                            {
                                updateEnnemi (&mechant,joueur1);
                                afficherEnnemi(mechant,ecran);
                            }

                            if(pieces_presente==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                            if(pieces_special_presente==1)
                                SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                            if(vies_presente==1)
                                SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                            afficher_perso(joueur1,ecran,police);
                            SDL_Flip(ecran);
                            SDL_Delay(100);

                        }
                        joueur1.action=surplace_gauche;
                        ennemi_present=0;
                        t_ennemi1=SDL_GetTicks();
                        battu=1;
                        joueur1.position.y+=30;
                    }
                    else if(keystate[SDLK_d])
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        if(joueur1.direction==gauche)
                        {
                            for(i=0; i<4; i++)
                            {
                                joueur1.direction=gauche;
                                joueur1.action=frapper_gauche;

                                animer_perso(&joueur1);
                                afficher_background(fond_ecran_niv1,ecran);
                                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                                afficher_minimap(MINI_M,ecran);
                                afficher_temps(&time,ecran,police_t);
                                if(ennemi_present==1)
                                {
                                    updateEnnemi (&mechant,joueur1);
                                    afficherEnnemi(mechant,ecran);
                                }
                                if(pieces_presente==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                                if(pieces_special_presente==1)
                                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                                if(vies_presente==1)
                                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                                afficher_perso(joueur1,ecran,police);
                                SDL_Flip(ecran);
                                SDL_Delay(100);

                            }
                            if(joueur1.position.x>mechant.poss.x)
                            {
                                joueur1.action=surplace_gauche;
                                ennemi_present=0;
                                t_ennemi1=SDL_GetTicks();
                                battu=1;
                            }

                        }
                        else if(joueur1.direction==droite)
                        {
                            for(i=0; i<4; i++)
                            {
                                joueur1.direction=droite;
                                joueur1.action=frapper_droite;

                                animer_perso(&joueur1);
                                afficher_background(fond_ecran_niv1,ecran);
                                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                                afficher_minimap(MINI_M,ecran);
                                afficher_temps(&time,ecran,police_t);
                                if(ennemi_present==1)
                                {
                                    updateEnnemi (&mechant,joueur1);
                                    afficherEnnemi(mechant,ecran);
                                }

                                if(pieces_presente==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                                if(pieces_special_presente==1)
                                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                                if(vies_presente==1)
                                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                                afficher_perso(joueur1,ecran,police);
                                SDL_Flip(ecran);
                                SDL_Delay(50);
                            }
                            if(joueur1.position.x<mechant.poss.x)
                            {
                                ennemi_present=0;
                                joueur1.score+=1000;
                                t_ennemi1=SDL_GetTicks();
                                battu=1;
                            }

                        }
                        joueur1.position.y+=30;
                    }
                    break;
                }

                if(t-t1>1000)
                    fin=0;

            }

            switch(battu)
            {
            case 0:
                ennemi_present=0;
                joueur1.nombre_vie--;
                afficher_background(fond_ecran_niv1,ecran);
                MINI_M.position_symb.x=majminimap(pos_pour_mini_map,redimensionnement,MINI_M);

                afficher_minimap(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                if(ennemi_present==1)
                {
                    updateEnnemi (&mechant,joueur1);
                    afficherEnnemi(mechant,ecran);
                }

                if(pieces_presente==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece);
                if(pieces_special_presente==1)
                    SDL_BlitSurface(pieces_specials,NULL,ecran,&position_piece_specials);
                if(vies_presente==1)
                    SDL_BlitSurface(vie,NULL,ecran,&position_vies);

                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                if(joueur1.direction==gauche)
                    SDL_BlitSurface(IMG_Load("resources/images/blesse_gauche.png"),NULL,ecran,&joueur1.position);
                else if(joueur1.direction==droite)
                    SDL_BlitSurface(IMG_Load("resources/images/blesse_droite.png"),NULL,ecran,&joueur1.position);
                SDL_Flip(ecran);
                SDL_Delay(100);
                if(joueur1.direction==gauche)
                    joueur1.action=surplace_gauche;
                else if(joueur1.direction==droite)
                    joueur1.action=surplace_droite;

                break;
            case 1:
                joueur1.score+=500;
                if(joueur1.direction==gauche)
                    joueur1.action=surplace_gauche;
                else if(joueur1.direction==droite)
                    joueur1.action=surplace_droite;

                battu=0;
                break;
            }

        }/**fin gestion de combat**/

        /*correction bug position*/
        if(joueur1.position.x<=0)
            joueur1.position.x=60;
        if(joueur1.position.x>=ecran->w-25)
            joueur1.position.x=ecran->w-80;

        /**si le joueur est a la fin du niveau**/
        if(fond_ecran_niv1.camera_pos1.x>=fond_ecran_niv1.image->w-100 && niveau_termine==0)
        {
            int n,fin=0;

            do
            {
                n=afficherenigme(maths,ecran);
                switch(n)
                {
                case 0:
                    joueur1.nombre_vie--;
                    break;
                case 1:
                    niveau_termine=1;
                    if(joueur1.position.x>ecran->w/2)
                        position_cure.x=joueur1.position.x-250;
                    else
                        position_cure.x=joueur1.position.x+250;

                    position_cure.y=joueur1.position.y-70;
                    fin=1;
                    break;
                }
                if(joueur1.nombre_vie<=0)
                    fin=1;
            }
            while(fin!=1);

        }
        /**si le joueur na plus de vie**/
        if(joueur1.nombre_vie==0)
        {

            if(mise_a_jour_highscores("resources/sauvegardes/highestscores.txt",joueur1.score)==1)
            {
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(IMG_Load("resources/images/new_highest_score.png"),NULL,ecran,&fond_ecran_niv1.pos_background1);
                SDL_Delay(1000);
            }

            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            SDL_BlitSurface(game_over,NULL,ecran,&fond_ecran_niv1.pos_background1);
            SDL_Flip(ecran);
            SDL_Delay(2000);
            continuer=0;
            return 0;
        }
        if(cure_taken==1)
        {
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            SDL_BlitSurface(level_complete,NULL,ecran,&fond_ecran_niv1.pos_background1);
            SDL_Flip(ecran);
            SDL_Delay(2000);

            if(mise_a_jour_highscores("resources/sauvegardes/highestscores.txt",joueur1.score)==1)
            {
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(IMG_Load("resources/images/new_highest_score.png"),NULL,ecran,&fond_ecran_niv1.pos_background1);
                SDL_Delay(1000);
            }


            return 1;
        }

    }


    Mix_HaltMusic();


    /**liberation des ressources**/
    Mix_FreeChunk(son_coup);
    Mix_FreeChunk(son_pieces);
    Mix_FreeChunk(son_pieces_speciales);
    free_minimap(MINI_M);
    SDL_FreeSurface(fond_ecran_niv1.image);
    SDL_FreeSurface(fond_ecran_niv1.image);
    TTF_CloseFont(police);
    TTF_CloseFont(police_t);
    SDL_FreeSurface(joueur1.image_actuel);
    SDL_FreeSurface(game_over);
    SDL_FreeSurface(level_complete);
    SDL_FreeSurface(pieces_specials);
    SDL_FreeSurface(pieces);

    return 1;
}
