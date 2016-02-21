#include "Background.h"
#include <math.h>


Background::Background(Keys *_keys, SDL_Setup* _sdl_s)
{
    cout << "КОНСТРУКТОР С ПАРАМЕТРАМИ [ Background ]" << endl;
    keys  = _keys;
    sdl_s = _sdl_s;

    bgevent = new BGEvent(keys, sdl_s);
    coordinates = new Coordinates(keys, sdl_s);

    color[0] = { 245, 248, 245, 115 };

    menuFon = { 20, 80, 250, keys->h3 };
    outFrame = {keys->w1, keys->h1, keys->w4, keys->h4};
    inFrame  = {keys->w2, keys->h2, keys->w3, keys->h3};
}

Background::~Background()
{
    cout << "ДЕСТРУКТОР [ Background ]" << endl;
    delete bgevent;
    delete coordinates;
}

/** Функция прорисовки общих фоновых элементов */
void Background::DrawBackground()
{
    bgevent->Event();

    SDL_SetRenderDrawColor(sdl_s->GetRen(), 189, 214, 229, 100 );
    SDL_RenderClear(sdl_s->GetRen());

    outFrame = {keys->w1, keys->h1, keys->w4, keys->h4};
    inFrame  = {keys->w2, keys->h2, keys->w3, keys->h3};

    menuFon.h  = keys->h3;

    SDL_SetRenderDrawColor(sdl_s->GetRen(), 247, 250, 255, 100 );
    SDL_RenderFillRect(sdl_s->GetRen(), &outFrame);

    SDL_SetRenderDrawColor(sdl_s->GetRen(), 255, 255, 255, 255 );
    SDL_RenderFillRect(sdl_s->GetRen(), &inFrame);

    SDL_SetRenderDrawColor(sdl_s->GetRen(), 189, 214, 229, 100);
    SDL_RenderDrawRect(sdl_s->GetRen(), &inFrame);
    inFrame  = {keys->w2+1, keys->h2+1, keys->w3, keys->h3};
    SDL_RenderDrawRect(sdl_s->GetRen(), &inFrame);

    SDL_SetRenderDrawColor(sdl_s->GetRen(), color[0].r, color[0].g, color[0].b, color[0].a);
    SDL_RenderFillRect(sdl_s->GetRen(), &menuFon);

    coordinates->DrawCoordinates();
    DrawLine();
}


void Background::DrawLine()
{
    SDL_Color color1 = {220, 220, 220, 0};
    SDL_Color color2 = {240, 240, 240, 0};
    SDL_Color color3 = {250, 250, 250, 250};

    SDL_SetRenderDrawColor(sdl_s->GetRen(), color1.r, color1.b, color1.g, color1.a);

    /* Вертикальные линии */
    int plus  = keys->w4/2+290+(keys->offsetX+keys->offsetXarea)*keys->scaleX;
    int minus = keys->w4/2+290+(keys->offsetX+keys->offsetXarea)*keys->scaleX;
    bool exit1 = 0, exit2 = 0;
    int step = keys->offsetXarea < 0 ? -1*keys->offsetXarea : keys->offsetXarea;
    int i = 0;

    while(!exit1 || !exit2)
    {
        if(step % keys->step == 0)
        {
            SDL_SetRenderDrawColor(sdl_s->GetRen(), color1.r, color1.b, color1.g, color1.a);
        }
        else
            SDL_SetRenderDrawColor(sdl_s->GetRen(), color2.r, color2.b, color2.g, color2.a);

        if(plus < keys->w5)
        {
            if(plus > keys->w2)
                SDL_RenderDrawLine(sdl_s->GetRen(), plus, keys->h2+1, plus, keys->h3+47);
        }
        else
            exit1 = true;

        if(minus > keys->w2)
        {
            if(minus < keys->w5)
                SDL_RenderDrawLine(sdl_s->GetRen(), minus, keys->h2+1, minus, keys->h3+47);

        }
        else
            exit2 = true;

        plus  += keys->scaleX;
        minus -= keys->scaleX;
        step++;
    }

    /* Горизонтальные линии */
    plus  = keys->height/2+(keys->offsetY+keys->offsetYarea)*keys->scaleY;
    minus = keys->height/2+(keys->offsetY+keys->offsetYarea)*keys->scaleY;
    exit1 = 0; exit2 = 0;
    step = keys->offsetYarea < 0 ? -1*keys->offsetYarea : keys->offsetYarea;
    i = 0;
    while(!exit1 || !exit2)
    {

        if(step % keys->step == 0)
        {
             SDL_SetRenderDrawColor(sdl_s->GetRen(), color1.r, color1.b, color1.g, color1.a);
        }
        else
            SDL_SetRenderDrawColor(sdl_s->GetRen(), color2.r, color2.b, color2.g, color2.a);

        if(plus > keys->h2)
        {
            if(plus < keys->h3+47)
                SDL_RenderDrawLine(sdl_s->GetRen(), 332, plus, keys->w5, plus);
        }
        else
            exit1 = true;

        if(minus < keys->h3+47)
        {
            if(minus > keys->h2)
                SDL_RenderDrawLine(sdl_s->GetRen(), 332, minus, keys->w5, minus);

        }
        else
            exit2 = true;

        plus  -= keys->scaleY;
        minus += keys->scaleY;
        step++;
    }

    SDL_SetRenderDrawColor(sdl_s->GetRen(), 59, 127, 140, 250 );

    /* Ось Y */
    if((keys->w4)/2+290+keys->offsetX*keys->scaleX < keys->w5 && (keys->w4)/2+290+keys->offsetX*keys->scaleX > 330)
    {
        keys->offsetXarea = 0;
        SDL_RenderDrawLine(sdl_s->GetRen(), keys->w4/2+290+(keys->offsetX+keys->offsetXarea)*keys->scaleX+1, keys->h2, (keys->w4)/2+290+(keys->offsetX+keys->offsetXarea)*keys->scaleX+1, keys->h3+47);
        SDL_RenderDrawLine(sdl_s->GetRen(), keys->w4/2+290+(keys->offsetX+keys->offsetXarea)*keys->scaleX, keys->h2, (keys->w4)/2+290+(keys->offsetX+keys->offsetXarea)*keys->scaleX, keys->h3+47);
    }
    /* Ось X */
    if(keys->height/2+keys->offsetY*keys->scaleY < keys->h3+47 && keys->height/2+keys->offsetY*keys->scaleY > keys->h2)
    {
        keys->offsetYarea = 0;
        SDL_RenderDrawLine(sdl_s->GetRen(), 332, keys->height/2+(keys->offsetY+keys->offsetYarea)*keys->scaleY+1, keys->w5, keys->height/2+(keys->offsetY+keys->offsetYarea)*keys->scaleY+1);
        SDL_RenderDrawLine(sdl_s->GetRen(), 332, keys->height/2+(keys->offsetY+keys->offsetYarea)*keys->scaleY, keys->w5, keys->height/2+(keys->offsetY+keys->offsetYarea)*keys->scaleY);
    }
}
