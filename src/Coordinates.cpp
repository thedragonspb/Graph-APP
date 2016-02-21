#include "Coordinates.h"

Coordinates::Coordinates(Keys* _keys, SDL_Setup* _sdl_s)
{
    TTF_Init();
    keys  = _keys;
    sdl_s = _sdl_s;
    coordColor = { 59, 127, 140, 0 };
    font = TTF_OpenFont("arial.ttf", 16);
    if(font == NULL)
    {
        keys->quit = true;
        cout << SDL_GetError() << endl;
    }
}

Coordinates::~Coordinates()
{
    TTF_CloseFont(font);
    TTF_Quit();
}

void Coordinates::NewTexture(int temp)
{
    sprintf((char*)str.c_str(), "%d", temp);
    surface = TTF_RenderUTF8_Blended(font, str.c_str() , coordColor);
    texture = SDL_CreateTextureFromSurface(sdl_s->GetRen(), surface);
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FreeSurface(surface);
}

void Coordinates::DrawCoordinates()
{
    int temp = keys->scaleX;
    int textPlus, textMinus;
    bool exit1 = 0, exit2 = 0;

    plus  = keys->offsetXarea;
    minus = keys->offsetXarea-1;

    textPlus  =  keys->w4/2+290+(keys->offsetX+keys->offsetXarea)*keys->scaleX;
    textMinus =  keys->w4/2+290+(keys->offsetX+keys->offsetXarea)*keys->scaleX-4;

    int i = 0;

    while(!exit1 || !exit2)
    {
        if(textPlus < keys->w5)
        {
            NewTexture(plus);
            rect.x = textPlus;
            rect.y = keys->h1+10;
            if(textPlus > keys->w2 && plus % keys->step == 0)
                SDL_RenderCopy(sdl_s->GetRen(), texture, NULL , &rect);

            SDL_DestroyTexture(texture);
            plus ++;
            textPlus = textPlus + temp;
        }
        else
            exit1 = true;

        if(textMinus > keys->w2 + 30)
        {
            textMinus = textMinus - temp;
            NewTexture(minus);

            rect.x = textMinus;
            rect.y = keys->h1+10;

            if(textMinus < keys->w5 && minus % keys->step == 0)
                SDL_RenderCopy(sdl_s->GetRen(), texture, NULL , &rect);

            SDL_DestroyTexture(texture);
            minus --;
        }
        else
            exit2 = true;
    }


    exit1 = 0, exit2 = 0;
    plus  = -1*keys->offsetYarea;
    minus = -1*keys->offsetYarea-1;

    textPlus  = keys->height/2+(keys->offsetY+keys->offsetYarea)*keys->scaleY-7;
    textMinus = keys->height/2+(keys->offsetY+keys->offsetYarea)*keys->scaleY-7;

    while(!exit1 || !exit2)
    {
        if(textPlus >= keys->h2-8)
        {
            NewTexture(plus);

            rect.x = abs(plus) > 9 ? keys->w1+10 : keys->w1+20;
            rect.y = textPlus;

            if(textPlus <= keys->h3+15 && plus % keys->step == 0)
                SDL_RenderCopy(sdl_s->GetRen(), texture, NULL , &rect);
            SDL_DestroyTexture(texture);
            plus ++;
            textPlus = textPlus - temp;
        }
        else
            exit1 = true;

        if(textMinus <= keys->h3+15)
        {
            textMinus = textMinus + temp;
            NewTexture(minus);

            rect.x = abs(minus) > 9 ? keys->w1+10 : keys->w1+20;
            rect.y = textMinus;

            if(textMinus >= keys->h2-8 && minus % keys->step == 0)
                SDL_RenderCopy(sdl_s->GetRen(), texture, NULL , &rect);
            SDL_DestroyTexture(texture);
            minus --;
        }
        else
            exit2 = true;
    }
}
