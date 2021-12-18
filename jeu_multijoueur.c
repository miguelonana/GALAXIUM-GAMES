#include "header1.h"


/*fonctions du minimap et du temp modifier pour 2 joueurs*/
void initminimap2(minimap_multijoueur *m,int niveau,SDL_Surface *ecran)
{

    switch(niveau)
    {
    case 1:
        m->minimp = IMG_Load("resources/images/level_1_minimap.png");
        break;
    }

    m->symbplayer1 = IMG_Load("resources/images/symbplayer1.png");
    m->symbplayer2 = IMG_Load("resources/images/symbplayer2.png");


    m->position_minimap.x=ecran->w/3-150;
    m->position_minimap.y=100;

    m->position_symb1.x= m->position_minimap.x;
    m->position_symb1.y=m->position_minimap.y+m->minimp->h-(m->symbplayer1->h)-15;

    m->position_symb2.x= m->position_minimap.x+3;
    m->position_symb2.y=m->position_minimap.y+m->minimp->h-(m->symbplayer2->h)-15;
}


void afficher_minimap2(minimap_multijoueur m,SDL_Surface *ecran)
{
    SDL_BlitSurface(m.minimp,NULL,ecran,&m.position_minimap);
    SDL_BlitSurface(m.symbplayer1,NULL,ecran,&m.position_symb1);
    SDL_BlitSurface(m.symbplayer2,NULL,ecran,&m.position_symb2);
}


void free_minimap2(minimap_multijoueur m)
{
    SDL_FreeSurface(m.minimp);
    SDL_FreeSurface(m.symbplayer1);
    SDL_FreeSurface(m.symbplayer2);
}




void initialiser_temps2(temps *t,minimap_multijoueur m)
{
    t->texte = NULL;
    t->position.x = (m.position_minimap.x);
    t->position.y = (m.minimp->h)+85;
    strcpy(t->entree, "");
    (t->secondesEcoulees) = 0;
    time(&(t->t1)); //temps du debut
}



int majminimap2(SDL_Rect posJ,int redimensionnement,minimap_multijoueur m)
{

    int x;

    x=(posJ.x*redimensionnement)/100;

    x=m.position_minimap.x+x;

    return x;
}



////////////////////////////////////////////////////////////////////////






int niveau1_multi_joueur(SDL_Surface *ecran)/*niveau1 multijoueur*/
{
    /*elements commun du niveau*/
    temps time;
    background fond_ecran_niv1;

    /*elements du niveau joueur 1*/
    enemy mechant1;
    Personnage joueur1;
    enigme question_corona;
    enigmesf maths;
    int ennemi_present1=0,pieces_presente1=0;
    int enigme_present1=0,pieces_special_presente1=0;
    SDL_Rect position_piece1;
    int t_pieces1_1=SDL_GetTicks(),t_pieces2_1;
    int t_ennemi2_1=0,t_ennemi1_1=0;




    /*elements du niveau joueur 2*/
    enemy mechant2;
    Personnage joueur2;
    enigme question_corona2;
    enigmesf maths2;
    int ennemi_present2=0,pieces_presente2=0;
    int enigme_present2=0,pieces_special_presente2=0;
    SDL_Rect position_piece2;//position des pieces quand elle apparaissent
    int t_pieces1_2=SDL_GetTicks(),t_pieces2_2;//temps pour l'apparition des pieces
    int t_ennemi2_2=0,t_ennemi1_2=0;

    /*variables du jeu*/
    int continuer=1;
    SDL_Event evenement;
    int redimensionnement=20;
    Uint8 *keystate = SDL_GetKeyState(NULL);
    minimap_multijoueur MINI_M;
    SDL_Rect pos_pour_mini_map1,pos_pour_mini_map2;
    SDL_Surface *pieces=IMG_Load("pieces.png");
    int dt,temps_actuel=0,temps_precedent=0,i,jeu_en_pause=0;


    /**initialisation du background**/
    init_background_multijoueur(&fond_ecran_niv1,ecran,1);
    /**initialisation des personnages**/
    init(&joueur1,1);
    init(&joueur2,2);
    init_perso(&joueur1,ecran);
    init_perso2(&joueur2,ecran);


    initminimap2(&MINI_M,1,ecran);
    initialiser_temps2(&time,MINI_M);

    initEnnemi(&mechant1);
    initEnnemi(&mechant2);


    Mix_Chunk  *son_coup;
    Mix_Chunk  *son_pieces;
    //Mix_Chunk  *son_pieces_speciales;
    Mix_Music *music_jeu;

    music_jeu=Mix_LoadMUS("resources/sons/game_sound.wav");//son du jeu
    son_coup=Mix_LoadWAV("resources/sons/son_coup.wav");//son apres un coup
    son_pieces=Mix_LoadWAV("resources/sons/son_pieces1.wav");//son l'orsqu'on prend une pieces jaune
    //son_pieces_speciales=Mix_LoadWAV("resources/sons/son_pieces2.wav");//son l'orsqu'on prend une piece rouge
    TTF_Font *police=TTF_OpenFont("resources/polices/police.ttf",20);
    TTF_Font *police_t=TTF_OpenFont("resources/polices/Enchanted Land.otf",30);



    afficher_background_multijoueur(fond_ecran_niv1,ecran);
    MINI_M.position_symb1.x=majminimap2(joueur1.position,redimensionnement,MINI_M);
    MINI_M.position_symb2.x=majminimap2(joueur1.position,redimensionnement,MINI_M);
    afficher_minimap2(MINI_M,ecran);

    /*adapter la position des joueurs au background*/
    joueur1.position.y+=30;
    joueur2.position.y+=30;

    afficher_perso(joueur1,ecran,police);
    afficher_perso(joueur2,ecran,police);

    pos_pour_mini_map1.x=joueur1.position.x;
    pos_pour_mini_map2.x=joueur1.position.x;
    SDL_Flip(ecran);
    SDL_Delay(100);


    while(continuer)
    {
        temps_actuel=SDL_GetTicks();
        dt=temps_actuel-temps_precedent;
        temps_precedent=temps_actuel;

        SDL_PollEvent(&evenement);

        switch(evenement.type)
        {
        case SDL_QUIT:
            continuer=0;
            return 0;
            break;
        case SDL_KEYDOWN:
            /**boutton joueur 1**//////////////////////////////////////////////////////////////
            if(keystate[SDLK_a] && keystate[SDLK_y])//sauter a gauche
            {
                joueur1.action=sauter;

                joueur1.direction=gauche;
                saut(&joueur1);

                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb1.x=majminimap2(joueur1.position,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                SDL_BlitSurface(IMG_Load("resources/images/sauter_gauche.png"),NULL,ecran,&joueur1.position);
                animer_perso(&joueur2);
                afficher_perso(joueur2,ecran,police);
                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }
                if(collision_pieces(position_piece1,joueur1) && pieces_presente1==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente1=0;
                    joueur1.score+=500;
                    t_pieces1_1=SDL_GetTicks();
                    t_pieces2_1=SDL_GetTicks();
                }
                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);
                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y-=100;
                joueur1.position.x+=100;

                scrolling(&fond_ecran_niv1,gauche,avancement_scrolling);
                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb1.x=majminimap2(joueur1.position,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);

                animer_perso(&joueur2);
                afficher_perso(joueur2,ecran,police);

                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }

                SDL_Flip(ecran);
                SDL_Delay(100);

            }
            if(keystate[SDLK_d] && keystate[SDLK_y])//sauter a droite
            {
                joueur1.action=sauter;

                joueur1.direction=droite;
                saut(&joueur1);

                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb1.x=majminimap2(joueur1.position,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                SDL_BlitSurface(IMG_Load("resources/images/sauter_droite.png"),NULL,ecran,&joueur1.position);
                animer_perso(&joueur2);
                afficher_perso(joueur2,ecran,police);
                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }
                if(collision_pieces(position_piece1,joueur1) && pieces_presente1==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente1=0;
                    joueur1.score+=500;
                    t_pieces1_1=SDL_GetTicks();
                    t_pieces2_1=SDL_GetTicks();
                }
                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);
                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y+=100;
                joueur1.position.x+=100;

                scrolling(&fond_ecran_niv1,droite,avancement_scrolling);
                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb1.x=majminimap2(joueur1.position,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);

                animer_perso(&joueur2);
                afficher_perso(joueur2,ecran,police);

                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }

                SDL_Flip(ecran);
                SDL_Delay(100);

            }
            else if(keystate[SDLK_a] && keystate[SDLK_u])//frapper a gauche
            {
                int i;
                Mix_PlayChannel(-1,son_coup,0);
                for(i=0; i<4; i++)
                {
                    joueur1.direction=gauche;
                    joueur1.action=frapper_gauche;

                    animer_perso(&joueur1);
                    afficher_background(fond_ecran_niv1,ecran);
                    MINI_M.position_symb1.x=majminimap2(joueur1.position,redimensionnement,MINI_M);

                    afficher_minimap2(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present1==1)
                    {
                        updateEnnemi (&mechant1,joueur1);
                        afficherEnnemi(mechant1,ecran);
                    }
                    if(ennemi_present2==1)
                    {
                        updateEnnemi (&mechant2,joueur2);
                        afficherEnnemi(mechant2,ecran);
                    }

                    if(pieces_presente1==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                    if(pieces_presente2==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                    afficher_perso(joueur1,ecran,police);

                    animer_perso(&joueur2);
                    afficher_perso(joueur2,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur1.action=surplace_gauche;

            }
            else if(keystate[SDLK_d] && keystate[SDLK_u])//frapper a droite
            {
                int i;
                Mix_PlayChannel(-1,son_coup,0);
                for(i=0; i<4; i++)
                {
                    joueur1.direction=droite;
                    joueur1.action=frapper_droite;

                    animer_perso(&joueur1);
                    afficher_background(fond_ecran_niv1,ecran);
                    MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);

                    afficher_minimap2(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present1==1)
                    {
                        updateEnnemi (&mechant1,joueur1);
                        afficherEnnemi(mechant1,ecran);
                    }
                    if(ennemi_present2==1)
                    {
                        updateEnnemi (&mechant2,joueur2);
                        afficherEnnemi(mechant2,ecran);
                    }

                    if(pieces_presente1==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                    if(pieces_presente2==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                    afficher_perso(joueur1,ecran,police);

                    animer_perso(&joueur2);
                    afficher_perso(joueur2,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur1.action=surplace_gauche;

            }
            else if(keystate[SDLK_a])//perso 1 deplacement a gauche
            {
                if(joueur1.position.x>50)
                {
                    joueur1.action=marcher_gauche;
                    joueur1.direction=gauche;
                    deplacer_perso(&joueur1,dt);
                    pos_pour_mini_map1.x-=4;
                    animer_perso(&joueur1);
                }
                else
                {
                    joueur1.action=marcher_gauche;
                    joueur1.direction=gauche;
                    animer_perso(&joueur1);
                }
            }
            else if(keystate[SDLK_u])//frapper surplace
            {
                Mix_PlayChannel(-1,son_coup,0);
                if(joueur1.direction==gauche)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur1.direction=gauche;
                        joueur1.action=frapper_gauche;

                        animer_perso(&joueur1);
                        afficher_background_multijoueur(fond_ecran_niv1,ecran);
                        MINI_M.position_symb1.x=majminimap2(joueur1.position,redimensionnement,MINI_M);

                        afficher_minimap2(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present1==1)
                        {
                            updateEnnemi (&mechant1,joueur1);
                            afficherEnnemi(mechant1,ecran);
                        }
                        if(ennemi_present2==1)
                        {
                            updateEnnemi (&mechant2,joueur2);
                            afficherEnnemi(mechant2,ecran);
                        }
                        if(pieces_presente1==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                        if(pieces_presente2==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                        afficher_perso(joueur1,ecran,police);
                        afficher_perso(joueur2,ecran,police);
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
                        afficher_background_multijoueur(fond_ecran_niv1,ecran);
                        MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);

                        afficher_minimap2(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present1==1)
                        {
                            updateEnnemi (&mechant1,joueur1);
                            afficherEnnemi(mechant1,ecran);
                        }
                        if(ennemi_present2==1)
                        {
                            updateEnnemi (&mechant2,joueur2);
                            afficherEnnemi(mechant2,ecran);
                        }
                        if(pieces_presente1==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);
                        if(pieces_presente2==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                        afficher_perso(joueur1,ecran,police);
                        afficher_perso(joueur2,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(50);
                    }
                }
            }
            else if(keystate[SDLK_d])//perso 1 deplacement a droite
            {
                if((ennemi_present1==1 || pieces_presente1==1 || pieces_special_presente1==1) /*&& joueur1.position.x>=ecran->w-90*/)
                {
                    joueur1.action=marcher_droite;
                    joueur1.direction=droite;
                    deplacer_perso(&joueur1,dt);
                    animer_perso(&joueur1);
                    pos_pour_mini_map1.x+=3;
                }
                else if(joueur1.position.x>=(ecran->w/2)-90)
                {
                    joueur1.action=marcher_droite;
                    joueur1.direction=droite;
                    deplacer_perso(&joueur1,dt);
                    animer_perso(&joueur1);
                    pos_pour_mini_map1.x+=3;
                }
                else
                {
                    joueur1.direction=droite;
                    joueur1.action=marcher_droite;
                    scrolling(&fond_ecran_niv1,droite,avancement_scrolling);
                    animer_perso(&joueur1);
                    pos_pour_mini_map1.x+=3;
                }
            }
            else if(keystate[SDLK_y])//saut surplace
            {
                int dir=joueur1.direction;
                joueur1.direction=haut;

                joueur1.action=sauter;
                saut(&joueur1);

                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }

                if(collision_pieces(position_piece1,joueur1) && pieces_presente1==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente1=0;
                    joueur1.score+=500;
                    t_pieces1_1=SDL_GetTicks();
                    t_pieces2_1=SDL_GetTicks();
                }

                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);

                joueur1.image_actuel=NULL;
                afficher_perso(joueur1,ecran,police);
                if(dir==droite)
                    SDL_BlitSurface(IMG_Load("resources/images/sauter_droite.png"),NULL,ecran,&joueur1.position);
                else if(dir==gauche)
                    SDL_BlitSurface(IMG_Load("resources/images/sauter_gauche.png"),NULL,ecran,&joueur1.position);
                animer_perso(&joueur2);
                afficher_perso(joueur2,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur1.position.y+=100;

                joueur1.direction=dir;

                if(dir==gauche)
                    joueur1.action=surplace_gauche;
                else if(dir==droite)
                    joueur1.action=surplace_droite;

                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);

                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }

                animer_perso(&joueur1);
                afficher_perso(joueur2,ecran,police);
                afficher_perso(joueur1,ecran,police);
                //animer_perso(&joueur2);
                SDL_Flip(ecran);
                SDL_Delay(100);
            }

            if(keystate[SDLK_t])//acceleration joueur1
            {
                if(joueur1.acceleration<4 && joueur1.direction==droite)
                {
                    joueur1.acceleration+=0.1;
                    if(keystate[SDLK_d])
                    {
                        scrolling(&fond_ecran_niv1,droite,avancement_scrolling_rapide);
                        pos_pour_mini_map1.x+=6;
                    }
                }
            }
/////////////////////////////////////////////////////////////////////////////////////////////


            /**boutton joueur 2**/
            if(keystate[SDLK_LEFT] && keystate[SDLK_o])///sauter a  gauche joueur2
            {
                joueur2.action=sauter;

                joueur2.direction=gauche;
                saut(&joueur2);

                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb2.x=majminimap2(joueur2.position,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                joueur2.image_actuel=NULL;
                afficher_perso(joueur2,ecran,police);
                SDL_BlitSurface(IMG_Load("resources/images/perso2_saut_gauche.png"),NULL,ecran,&joueur2.position);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }
                if(ennemi_present1==1)
                {
                    updateEnnemi(&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(collision_pieces(position_piece2,joueur2) && pieces_presente2==1)
                {
                    Mix_PlayChannel(-1,son_pieces,0);
                    pieces_presente2=0;
                    joueur2.score+=500;
                    t_pieces1_2=SDL_GetTicks();
                    t_pieces2_2=SDL_GetTicks();
                }
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);
                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);

                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur2.position.y+=100;
                joueur2.position.x-=100;

                scrolling_2(&fond_ecran_niv1,gauche,avancement_scrolling);
                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb2.x=majminimap2(joueur2.position,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                animer_perso(&joueur2);
                afficher_perso(joueur2,ecran,police);

                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);

                SDL_Flip(ecran);
                SDL_Delay(100);

            }
            else if(keystate[SDLK_RIGHT] && keystate[SDLK_o])//sauter a droite joueur 2
            {
                joueur2.action=sauter;

                joueur2.direction=droite;
                saut(&joueur2);

                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb2.x=majminimap2(joueur2.position,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                joueur2.image_actuel=NULL;
                afficher_perso(joueur2,ecran,police);
                SDL_BlitSurface(IMG_Load("resources/images/perso2_saut_droite.png"),NULL,ecran,&joueur2.position);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur1);
                    afficherEnnemi(mechant2,ecran);
                }
                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(collision_pieces(position_piece2,joueur2) && pieces_presente2==1)
                {
                    pieces_presente2=0;
                    joueur2.score+=500;
                    t_pieces1_2=SDL_GetTicks();
                    t_pieces2_2=SDL_GetTicks();
                }
                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur2.position.y+=100;
                joueur2.position.x+=100;

                scrolling_2(&fond_ecran_niv1,droite,avancement_scrolling);
                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb2.x=majminimap2(joueur2.position,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                animer_perso(&joueur2);
                afficher_perso(joueur2,ecran,police);

                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);

                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur1);
                    afficherEnnemi(mechant2,ecran);
                }
                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                SDL_Flip(ecran);
                SDL_Delay(100);

            }
            else if(keystate[SDLK_LEFT] && keystate[SDLK_p])//frapper a gauche joueur2
            {
                int i;
                Mix_PlayChannel(-1,son_coup,0);
                for(i=0; i<4; i++)
                {
                    joueur2.direction=gauche;
                    joueur2.action=frapper_gauche;

                    animer_perso(&joueur2);
                    afficher_background_multijoueur(fond_ecran_niv1,ecran);
                    MINI_M.position_symb2.x=majminimap2(joueur2.position,redimensionnement,MINI_M);

                    afficher_minimap2(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present1==1)
                    {
                        updateEnnemi (&mechant1,joueur1);
                        afficherEnnemi(mechant1,ecran);
                    }
                    if(ennemi_present2==1)
                    {
                        updateEnnemi (&mechant2,joueur2);
                        afficherEnnemi(mechant2,ecran);
                    }

                    if(pieces_presente1==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                    if(pieces_presente2==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                    afficher_perso(joueur2,ecran,police);

                    animer_perso(&joueur1);
                    afficher_perso(joueur1,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur2.action=surplace_gauche;
            }
            else if(keystate[SDLK_RIGHT] && keystate[SDLK_p])//frapper a droite joueur2
            {
                int i;
                Mix_PlayChannel(-1,son_coup,0);
                for(i=0; i<4; i++)
                {
                    joueur2.direction=droite;
                    joueur2.action=frapper_droite;

                    animer_perso(&joueur2);
                    afficher_background_multijoueur(fond_ecran_niv1,ecran);
                    MINI_M.position_symb2.x=majminimap2(joueur2.position,redimensionnement,MINI_M);

                    afficher_minimap2(MINI_M,ecran);
                    afficher_temps(&time,ecran,police_t);
                    if(ennemi_present1==1)
                    {
                        updateEnnemi (&mechant1,joueur1);
                        afficherEnnemi(mechant1,ecran);
                    }
                    if(ennemi_present2==1)
                    {
                        updateEnnemi (&mechant2,joueur2);
                        afficherEnnemi(mechant2,ecran);
                    }

                    if(pieces_presente1==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                    if(pieces_presente2==1)
                        SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                    afficher_perso(joueur2,ecran,police);

                    animer_perso(&joueur1);
                    afficher_perso(joueur1,ecran,police);
                    SDL_Flip(ecran);
                    SDL_Delay(100);

                }
                joueur2.action=surplace_droite;
            }
            else if(keystate[SDLK_LEFT])//perso 2 deplacement a gauche
            {
                if(joueur2.position.x>(ecran->w/2)+80)
                {
                    joueur2.action=marcher_gauche;
                    joueur2.direction=gauche;

                    if(joueur2.position.x>(ecran->w/2)+100)
                    {
                        deplacer_perso(&joueur2,dt);
                        pos_pour_mini_map2.x-=4;
                    }
                    animer_perso(&joueur2);
                }
                else
                {
                    joueur2.action=marcher_gauche;
                    joueur2.direction=gauche;
                    animer_perso(&joueur2);
                }
            }
            else if(keystate[SDLK_RIGHT])//perso 2 deplacement a droite
            {
                if((ennemi_present2==1 || pieces_presente2==1) /*&& joueur1.position.x>=ecran->w-90*/)
                {
                    joueur2.action=marcher_droite;
                    joueur2.direction=droite;

                    if(joueur2.position.x<ecran->w-60)
                        deplacer_perso(&joueur2,dt);

                    animer_perso(&joueur2);
                    pos_pour_mini_map2.x+=3;
                }
                else if(joueur2.position.x>=(ecran->w)-90)
                {
                    joueur2.action=marcher_droite;
                    joueur2.direction=droite;
                    deplacer_perso(&joueur2,dt);
                    animer_perso(&joueur2);
                    pos_pour_mini_map2.x+=3;
                }
                else
                {
                    joueur2.direction=droite;
                    joueur2.action=marcher_droite;
                    scrolling_2(&fond_ecran_niv1,droite,avancement_scrolling);
                    animer_perso(&joueur2);
                    pos_pour_mini_map2.x+=3;
                }
            }
            else if(keystate[SDLK_p])//frapper surplace joeur 2
            {
                int i;
                Mix_PlayChannel(-1,son_coup,0);
                if(joueur1.direction==gauche)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur2.direction=gauche;
                        joueur2.action=frapper_gauche;

                        animer_perso(&joueur2);
                        afficher_background_multijoueur(fond_ecran_niv1,ecran);
                        MINI_M.position_symb2.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);

                        afficher_minimap2(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present1==1)
                        {
                            updateEnnemi (&mechant1,joueur1);
                            afficherEnnemi(mechant1,ecran);
                        }
                        if(ennemi_present2==1)
                        {
                            updateEnnemi (&mechant2,joueur2);
                            afficherEnnemi(mechant2,ecran);
                        }
                        if(pieces_presente1==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                        if(pieces_presente2==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                        animer_perso(&joueur1);
                        afficher_perso(joueur1,ecran,police);
                        afficher_perso(joueur2,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(100);

                    }
                    joueur2.action=surplace_gauche;
                }
                else if(joueur1.direction==droite)
                {
                    for(i=0; i<4; i++)
                    {
                        joueur2.direction=droite;
                        joueur2.action=frapper_droite;

                        animer_perso(&joueur2);
                        afficher_background_multijoueur(fond_ecran_niv1,ecran);
                        MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);

                        afficher_minimap2(MINI_M,ecran);
                        afficher_temps(&time,ecran,police_t);
                        if(ennemi_present1==1)
                        {
                            updateEnnemi (&mechant1,joueur1);
                            afficherEnnemi(mechant1,ecran);
                        }
                        if(ennemi_present2==1)
                        {
                            updateEnnemi (&mechant2,joueur2);
                            afficherEnnemi(mechant2,ecran);
                        }

                        if(pieces_presente1==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                        if(pieces_presente2==1)
                            SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                        afficher_perso(joueur1,ecran,police);
                        SDL_Flip(ecran);
                        SDL_Delay(50);
                    }
                }
            }
            else if(keystate[SDLK_o])
            {
                int dir=joueur2.direction;
                joueur2.direction=haut;

                joueur2.action=sauter;
                saut(&joueur2);

                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb2.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);
                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }

                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }

                if(collision_pieces(position_piece2,joueur2) && pieces_presente2==1)
                {
                    pieces_presente2=0;
                    joueur2.score+=500;
                    t_pieces1_2=SDL_GetTicks();
                    t_pieces2_2=SDL_GetTicks();
                }

                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);
                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);

                joueur2.image_actuel=NULL;
                afficher_perso(joueur2,ecran,police);
                if(dir==droite)
                    SDL_BlitSurface(IMG_Load("resources/images/perso2_saut_droite.png"),NULL,ecran,&joueur2.position);
                else if(dir==gauche)
                    SDL_BlitSurface(IMG_Load("resources/images/perso2_saut_gauche.png"),NULL,ecran,&joueur2.position);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(250);

                joueur2.position.y+=100;

                joueur2.direction=dir;

                if(dir==gauche)
                    joueur2.action=surplace_gauche;
                else if(dir==droite)
                    joueur2.action=surplace_droite;

                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb2.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);

                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);

                if(ennemi_present2==1)
                {
                    updateEnnemi (&mechant2,joueur2);
                    afficherEnnemi(mechant2,ecran);
                }
                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }
                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);
                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);

                animer_perso(&joueur2);
                afficher_perso(joueur2,ecran,police);
                animer_perso(&joueur1);
                afficher_perso(joueur1,ecran,police);
                SDL_Flip(ecran);
                SDL_Delay(100);
            }

            if(keystate[SDLK_i])
            {
                if(joueur2.acceleration<4 && joueur2.direction==droite)
                {
                    joueur1.acceleration+=0.1;
                    if(keystate[SDLK_RIGHT])
                    {
                        scrolling_2(&fond_ecran_niv1,droite,avancement_scrolling_rapide);
                        pos_pour_mini_map2.x+=6;
                    }
                }
            }
            break;
        }

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
            time.position.y = (MINI_M.minimp->h)+85;
        }


        /**correction bug position**/
        if(joueur1.position.x>ecran->w/2-30)
            joueur1.position.x=ecran->w/2-30;
        if(joueur2.position.x<ecran->w/2+10)
            joueur2.position.x=ecran->w/2+30;
        if(joueur1.position.x<5)
            joueur1.position.x=30;
        if(joueur2.position.x>ecran->w-10)
            joueur2.position.x=ecran->w-30;

        /*affichage apres les mise a jour*/
        afficher_background_multijoueur(fond_ecran_niv1,ecran);

        MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);
        MINI_M.position_symb2.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);
        afficher_minimap2(MINI_M,ecran);
        afficher_temps(&time,ecran,police_t);
        afficher_perso(joueur1,ecran,police);
        afficher_perso(joueur2,ecran,police);

        if(pieces_presente2==1)
            SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);
        if(pieces_presente1==1)
            SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);

        if(ennemi_present2==1)
        {
            updateEnnemi (&mechant2,joueur2);
            afficherEnnemi(mechant2,ecran);
        }
        if(ennemi_present1==1)
        {
            updateEnnemi (&mechant1,joueur1);
            afficherEnnemi(mechant1,ecran);
        }


        SDL_Flip(ecran);
        SDL_Delay(100);

        /*si le joueur est surplace l'animer*/////////////////////////////////////////////
        if(joueur1.action==surplace_droite || joueur1.action==surplace_gauche)
            animer_perso(&joueur1);
        if(joueur2.action==surplace_droite || joueur2.action==surplace_gauche)
            animer_perso(&joueur2);
//////////////////////////////////////////////////////////////////////////////////////////

        /*mettre le jouer a l'etat surplace*//////////////////////////////////////
        switch(joueur1.direction)
        {
        case droite:
            joueur1.action=surplace_droite;
            break;
        case gauche:
            joueur1.action=surplace_gauche;
            break;
        }

        switch(joueur2.direction)
        {
        case droite:
            joueur2.action=surplace_droite;
            break;
        case gauche:
            joueur2.action=surplace_gauche;
            break;
        }
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////
        /**generation des pieces joueur 1**/
        t_pieces2_1=SDL_GetTicks();
        if(pieces_presente1==0 && t_pieces2_1-t_pieces1_1>5000)
        {
            pieces_presente1=1;
            if(joueur1.position.x>ecran->w/4)
                position_piece1.x=joueur1.position.x-100;
            else
                position_piece1.x=joueur1.position.x+100;
            position_piece1.y=joueur1.position.y-70;
        }

        if(t_pieces2_1-t_pieces1_1>7500 && pieces_presente1==1)
        {
            pieces_presente1=0;
            t_pieces2_1=SDL_GetTicks();
            t_pieces1_1=SDL_GetTicks();
        }

        /**generation des pieces joueur 1**/
        t_pieces2_2=SDL_GetTicks();
        if(pieces_presente2==0 && t_pieces2_2-t_pieces1_2>5000)
        {
            pieces_presente2=1;
            if(joueur2.position.x>ecran->w/4)
                position_piece2.x=joueur2.position.x-100;
            else
                position_piece2.x=joueur2.position.x+100;
            position_piece2.y=joueur2.position.y-70;
        }

        if(t_pieces2_2-t_pieces1_2>7500 && pieces_presente2==1)
        {
            pieces_presente2=0;
            t_pieces2_2=SDL_GetTicks();
            t_pieces1_2=SDL_GetTicks();
        }
//////////////////////////////////////////////////////

        /**generation des ennemis pour le joueur 1**/
        t_ennemi2_1=SDL_GetTicks();
        if(t_ennemi2_1-t_ennemi1_1>10000 && ennemi_present1!=1)
        {
            ennemi_present1=1;

            mechant1.poss.y=joueur1.position.y;

            if(joueur1.position.x<ecran->w/4)
                mechant1.poss.x=joueur1.position.x+200;
            else
                mechant1.poss.x=0;
        }
        /**generation des ennemis pour le joueur 2**/
        t_ennemi2_2=SDL_GetTicks();
        if(t_ennemi2_2-t_ennemi1_2>10000 && ennemi_present2!=1)
        {
            ennemi_present2=1;

            mechant2.poss.y=joueur2.position.y;

            if(joueur2.position.x<ecran->w/4)
                mechant2.poss.x=joueur2.position.x+200;
            else
                mechant2.poss.x=ecran->w/2+40;
        }


        /**gestion de combat joueur 1**/
        if(collisionBB(joueur1,mechant1) && ennemi_present1==1)
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
                    if(keystate[SDLK_d] && keystate[SDLK_RIGHT] && joueur1.position.x<mechant1.poss.x)
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        for(i=0; i<5; i++)
                        {
                            joueur1.direction=droite;
                            joueur1.action=frapper_droite;

                            animer_perso(&joueur1);
                            afficher_background_multijoueur(fond_ecran_niv1,ecran);
                            MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);
                            MINI_M.position_symb2.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);

                            afficher_minimap2(MINI_M,ecran);
                            afficher_temps(&time,ecran,police_t);
                            if(ennemi_present1==1)
                            {
                                updateEnnemi (&mechant1,joueur1);
                                afficherEnnemi(mechant1,ecran);
                            }

                            if(pieces_presente1==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                            if(pieces_presente2==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                            afficher_perso(joueur1,ecran,police);
                            afficher_perso(joueur2,ecran,police);
                            SDL_Flip(ecran);
                            SDL_Delay(50);
                        }
                        ennemi_present1=0;
                        joueur1.score+=1000;
                        t_ennemi1_1=SDL_GetTicks();
                        battu=1;
                        joueur1.position.y+=30;
                    }
                    else if(keystate[SDLK_d] && keystate[SDLK_LEFT] && joueur1.position.x>mechant1.poss.x)
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        for(i=0; i<5; i++)
                        {
                            joueur1.direction=gauche;
                            joueur1.action=frapper_gauche;

                            animer_perso(&joueur1);
                            animer_perso(&joueur2);
                            afficher_background_multijoueur(fond_ecran_niv1,ecran);
                            MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);
                            MINI_M.position_symb2.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);
                            afficher_minimap2(MINI_M,ecran);
                            afficher_temps(&time,ecran,police_t);
                            if(ennemi_present1==1)
                            {
                                updateEnnemi (&mechant1,joueur1);
                                afficherEnnemi(mechant1,ecran);
                            }
                            if(ennemi_present2==1)
                            {
                                updateEnnemi (&mechant2,joueur2);
                                afficherEnnemi(mechant2,ecran);
                            }

                            if(pieces_presente1==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                            if(pieces_presente2==1)
                                SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                            afficher_perso(joueur1,ecran,police);
                            afficher_perso(joueur2,ecran,police);
                            SDL_Flip(ecran);
                            SDL_Delay(100);

                        }
                        joueur1.action=surplace_gauche;
                        ennemi_present1=0;
                        t_ennemi1_1=SDL_GetTicks();
                        battu=1;
                        joueur1.position.y+=30;
                    }
                    else if(keystate[SDLK_d])
                    {
                        Mix_PlayChannel(-1,son_coup,0);
                        joueur1.position.y-=30;
                        if(joueur1.direction==gauche)
                        {
                            for(i=0; i<5; i++)
                            {
                                joueur1.direction=gauche;
                                joueur1.action=frapper_gauche;

                                animer_perso(&joueur1);
                                animer_perso(&joueur2);
                                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                                MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);
                                MINI_M.position_symb2.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);
                                afficher_minimap2(MINI_M,ecran);
                                afficher_temps(&time,ecran,police_t);
                                if(ennemi_present2==1)
                                {
                                    updateEnnemi (&mechant2,joueur2);
                                    afficherEnnemi(mechant2,ecran);
                                }
                                if(ennemi_present1==1)
                                {
                                    updateEnnemi (&mechant1,joueur1);
                                    afficherEnnemi(mechant1,ecran);
                                }
                                if(pieces_presente1==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                                if(pieces_presente2==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                                afficher_perso(joueur1,ecran,police);
                                afficher_perso(joueur2,ecran,police);
                                SDL_Flip(ecran);
                                SDL_Delay(100);

                            }
                            if(joueur1.position.x>mechant1.poss.x)
                            {
                                joueur1.action=surplace_gauche;
                                ennemi_present1=0;
                                t_ennemi1_1=SDL_GetTicks();
                                battu=1;
                            }

                        }
                        else if(joueur1.direction==droite)
                        {
                            for(i=0; i<5; i++)
                            {
                                joueur1.direction=droite;
                                joueur1.action=frapper_droite;

                                animer_perso(&joueur1);
                                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                                MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);
                                MINI_M.position_symb2.x=majminimap2(pos_pour_mini_map2,redimensionnement,MINI_M);
                                afficher_minimap2(MINI_M,ecran);
                                afficher_temps(&time,ecran,police_t);
                                if(ennemi_present1==1)
                                {
                                    updateEnnemi (&mechant1,joueur1);
                                    afficherEnnemi(mechant1,ecran);
                                }
                                if(ennemi_present2==1)
                                {
                                    updateEnnemi (&mechant2,joueur2);
                                    afficherEnnemi(mechant2,ecran);
                                }

                                if(pieces_presente1==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);
                                if(pieces_presente2==1)
                                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);

                                afficher_perso(joueur1,ecran,police);
                                afficher_perso(joueur2,ecran,police);
                                SDL_Flip(ecran);
                                SDL_Delay(50);
                            }
                            if(joueur1.position.x<mechant1.poss.x)
                            {
                                ennemi_present1=0;
                                joueur1.score+=1000;
                                t_ennemi1_1=SDL_GetTicks();
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
                ennemi_present1=0;
                joueur1.nombre_vie--;
                afficher_background_multijoueur(fond_ecran_niv1,ecran);
                MINI_M.position_symb1.x=majminimap2(pos_pour_mini_map1,redimensionnement,MINI_M);

                afficher_minimap2(MINI_M,ecran);
                afficher_temps(&time,ecran,police_t);
                if(ennemi_present1==1)
                {
                    updateEnnemi (&mechant1,joueur1);
                    afficherEnnemi(mechant1,ecran);
                }

                if(pieces_presente2==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece2);
                if(pieces_presente1==1)
                    SDL_BlitSurface(pieces,NULL,ecran,&position_piece1);

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


    }
}
