
#include "header1.h"



void initminimap(minimap *m,int niveau,SDL_Surface *ecran)
{

    switch(niveau)
    {
    case 1:
        m->minimp = IMG_Load("resources/images/level_1_minimap.png");
        break;
    case 2:
        m->minimp = IMG_Load("resources/images/level_2_minimap.png");
        break;
    case 3:
        m->minimp = IMG_Load("resources/images/level_3_minimap.png");
        break;
    }

    m->symbplayer = IMG_Load("resources/images/symbplayer.png");



    m->position_minimap.x=ecran->w-(m->minimp->w);
    m->position_minimap.y=0;

    m->position_symb.x= m->position_minimap.x;
    m->position_symb.y=(m->minimp->h)-50;
}


int majminimap (SDL_Rect posJ,int redimensionnement,minimap m)
{

    int x;

    x=(posJ.x*redimensionnement)/100;

    x=m.position_minimap.x+x;

    return x;
}


void afficher_minimap(minimap m,SDL_Surface *ecran)
{
    SDL_BlitSurface(m.minimp,NULL,ecran,&m.position_minimap);
    SDL_BlitSurface(m.symbplayer,NULL,ecran,&m.position_symb);
}


void free_minimap(minimap m)
{
    SDL_FreeSurface(m.minimp);
    SDL_FreeSurface(m.symbplayer);
}


void initialiser_temps(temps *t,minimap m)
{
    t->texte = NULL;
    t->position.x = /*(largeur_fenetre/2)+100*/(m.position_minimap.x);
    t->position.y = (m.minimp->h)+50/*150*/;

    strcpy(t->entree, "");
    (t->secondesEcoulees) = 0;
    time(&(t->t1)); //temps du debut
    //t->police=TTF_OpenFont("resources/polices/Enchanted Land.otf",30);
}

void afficher_temps(temps *t, SDL_Surface *screen,TTF_Font *police)
{
    SDL_Color couleurnoir = {0, 0, 0};
    //TTF_Font *police=TTF_OpenFont("resources/polices/Enchanted Land.otf",30);

    time(&(t->t2)); // temps actuel

    t->secondesEcoulees = t->t2 - t->t1;

    t->min = ((t->secondesEcoulees / 60) % 60);
    t->sec = ((t->secondesEcoulees) % 60);
    int millisecondes=SDL_GetTicks()%60;

    sprintf(t->entree, "%02d:%02d:%02d", t->min, t->sec, millisecondes);

    t->texte = TTF_RenderText_Blended(police, t->entree, couleurnoir);

    SDL_BlitSurface(t->texte, NULL, screen, &(t->position)); /* Blit du texte */
}




SDL_Color GetPixel(SDL_Surface *Background, int x, int y)
{

    SDL_Color color;
    Uint32 col = 0;
    //Determine position

    char *pixelPosition = (char *)Background->pixels;
    //Offset by Y
    pixelPosition += (Background->pitch * y);
    //Offset by X
    pixelPosition += (Background->format->BytesPerPixel * x);
    //Copy pixel data
    memcpy(&col, pixelPosition, Background->format->BytesPerPixel);
    //Convert to color
    SDL_GetRGB(col, Background->format, &color.r, &color.g, &color.b);

    return (color);
}

int collisionPP(Personnage p, SDL_Surface *Masque)
{
    SDL_Color test, couleurnoir = {0, 0, 0};

    SDL_Rect pos[8];
    pos[0].x = p.position.x;
    pos[0].y = p.position.y;
    pos[1].x = p.position.x + p.position.w / 2;
    pos[1].y = p.position.y;
    pos[2].x = p.position.x + p.position.w;
    pos[2].y = p.position.y;
    pos[3].x = p.position.x;
    pos[3].y = p.position.y + p.position.h / 2;
    pos[4].x = p.position.x;
    pos[4].y = p.position.y + p.position.h;
    pos[5].x = p.position.x + p.position.w / 2;
    pos[5].y = p.position.y + p.position.h;
    pos[6].x = p.position.x + p.position.w;
    pos[6].y = p.position.y + p.position.h;
    pos[7].x = p.position.x + p.position.w;
    pos[7].y = p.position.y + p.position.h / 2;
    int collision = 0, x, y;

    for (int i = 0; i < 8 && collision == 0; i++)
    {
        x = pos[i].x;
        y = pos[i].y;
        test = GetPixel(Masque, x, y);
        if (test.r == 0 && test.g == 0 && test.b == 0)
            collision = 1;
    }
    return collision;
}

