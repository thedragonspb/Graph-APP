#include "TextClass.h"

#include "stdio.h"
#include "iostream"

TextClass::TextClass(Keys* _keys)
{
    std::cout << "КОНСТРУКТОР С ПАРАМЕТРАМИ [TextClass]" << std::endl;
    TTF_Init();
    keys = _keys;
    fontFile = "arial.ttf";
    text = new char[10];
    fontSize = 14;

    standGraphs[0] = "y = a·x + b";
    standGraphs[1] = "y = x²";
    standGraphs[2] = "y = a·x² + b·x + c";
    standGraphs[3] = "y = a / x";
    standGraphs[4] = "y = sin(x)";
    standGraphs[5] = "y = cos(x)";
    standGraphs[6] = "y = tg(x)";
    standGraphs[7] = "y = ctg(x)";
    standGraphs[8] = "y = arcsin(x)";
    standGraphs[9] = "y = arccos(x)";
}

TextClass::~TextClass()
{
    std::cout << "ДЕСТРУКТОР [TextClass]" << std::endl;
    TTF_Quit();
    delete text;
}

/** Функция отрисовки координат **/
void TextClass::Coord()
{
    if(keys->scale <= 20) { keys->step = 2; fontSize = 14; }
    else if(keys->scale <= 40) { keys->step = 2; fontSize = 14; }
            else if(keys->scale > 40){ keys->step = 1; fontSize = 14; }

    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    textColor={150,100,100, 158};

    int plus, minus;
    int temp = keys->scale*keys->step;
    int textPlus, textMinus;
    int textRectX, textRectY;

    bool exit1 = 0, exit2 = 0;

    plus  = keys->offsetX*(-1) + keys->step;
    minus = keys->offsetX*(-1);

    textPlus  =  keys->w4/2+290;
    textMinus =  keys->w4/2+290 + keys->scale*keys->step - 8;

    while(!exit1 || !exit2)
    {
        textPlus = textPlus + temp;
        if(textPlus < keys->w5+5)
        {
            sprintf(text, "%d", plus);
            SetTexture();

            textRect.w = textSurface->w;
            textRect.h = textSurface->h;

            textRect.x = textPlus;
            textRect.y = keys->h1+10;
            if(textPlus > keys->w2-14)
                SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
            FreeTexture();
            plus += keys->step;
        }
        else
            exit1 = true;

        textMinus = textMinus - temp;
        if(textMinus > keys->w2-14)
        {
            sprintf(text, "%d", minus);
            SetTexture();

            textRect.w = textSurface->w;
            textRect.h = textSurface->h;

            textRect.x = textMinus;
            textRect.y = keys->h1+10;

            if(textMinus < keys->w5+5)
                SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
            FreeTexture();
            minus -= keys->step;
        }
        else
            exit2 = true;
    }

    exit1 = 0, exit2 = 0;
    plus  = keys->offsetY;
    minus = keys->offsetY - keys->step;

    textPlus  = keys->height/2+keys->scale*keys->step-7;
    textMinus = keys->height/2-7;

    while(!exit1 || !exit)
    {
        textPlus = textPlus - temp;
        if(textPlus >= keys->h2-8)
        {
            sprintf(text, "%d", plus);
            SetTexture();

            textRect.w = textSurface->w;
            textRect.h = textSurface->h;

            textRectX = abs(plus) > 9 ? keys->w1+10 : keys->w1+20;
            textRect.x = textRectX;
            textRect.y = textPlus;

            if(textPlus <= keys->h3)
                SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
            FreeTexture();
            plus += keys->step;
        }
        else
            exit1 = true;

        if(textMinus <= keys->h3)
        {
            textMinus = textMinus + temp;
            sprintf(text, "%d", minus);
            SetTexture();

            textRect.w = textSurface->w;
            textRect.h = textSurface->h;

            textRectX = abs(minus) > 9 ? keys->w1+10 : keys->w1+20;

            textRect.x = textRectX;
            textRect.y = textMinus;

            if(textMinus >= keys->h2-8)
                SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
            FreeTexture();
            minus -= keys->step;
        }
        else
            exit2 = true;
    }

    TTF_CloseFont(font);
}

void TextClass::SetTexture()
{
    textSurface = TTF_RenderUTF8_Blended(font, text , textColor);
    textTexture = SDL_CreateTextureFromSurface(keys->setup->GetRen(), textSurface);
}

void TextClass::FreeTexture()
{
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

/** Функция отрисовки текста меню **/
/*void TextClass::Menu()
{
    font = TTF_OpenFont(fontFile.c_str(), 25);
    textColor = {245, 245, 245, 115};
    textSurface = TTF_RenderUTF8_Blended(font, "График" , textColor);
    textTexture = SDL_CreateTextureFromSurface(keys->setup->GetRen(), textSurface);
    textRect    = {20, 10 ,textSurface->w, textSurface->h};
    SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
    FreeTexture();
    TTF_CloseFont(font);

    font = TTF_OpenFont(fontFile.c_str(), 18);
    if(keys->menuBg == 0)
        textColor = {189, 214, 229, 100};
    else
        textColor = {216, 228, 232, 255};

    textSurface = TTF_RenderUTF8_Blended(font, "По точкам" , textColor);
    textTexture = SDL_CreateTextureFromSurface(keys->setup->GetRen(), textSurface);
    textRect    = {keys->rectButtonLeft.x+5, keys->rectButtonLeft.y+3 ,textSurface->w, textSurface->h};
    SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
    FreeTexture();
    if(keys->menuBg == 1)
        textColor = {189, 214, 229, 100};
    else
        textColor = {216, 228, 232, 255};

    textSurface = TTF_RenderUTF8_Blended(font, "Функция" , textColor);
    textTexture = SDL_CreateTextureFromSurface(keys->setup->GetRen(), textSurface);
    textRect    = {keys->rectButtonRight.x+5, keys->rectButtonRight.y+3, textSurface->w, textSurface->h};
    SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
    FreeTexture();
    textColor = {189, 214, 229, 100};

    textSurface = TTF_RenderUTF8_Blended(font, "Удалить" , textColor);
    textTexture = SDL_CreateTextureFromSurface(keys->setup->GetRen(), textSurface);
    textRect    = {keys->rectButtonDelete.x+5, keys->rectButtonDelete.y+3, textSurface->w, textSurface->h};
    SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
    FreeTexture();
    textSurface = TTF_RenderUTF8_Blended(font, "Добавить" , textColor);
    textTexture = SDL_CreateTextureFromSurface(keys->setup->GetRen(), textSurface);
    textRect    = {keys->rectButtonAdd.x+5, keys->rectButtonAdd.y+3, textSurface->w, textSurface->h};
    SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
    FreeTexture();
    if(keys->workspaceStatus != 0)
    {
        textSurface = TTF_RenderUTF8_Blended(font, "Назад" , textColor);
        textTexture = SDL_CreateTextureFromSurface(keys->setup->GetRen(), textSurface);
        textRect    = {keys->rectButtonBack.x+35, keys->rectButtonBack.y+3, textSurface->w, textSurface->h};
        SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
        FreeTexture();
    }

    TTF_CloseFont(font);
}

void TextClass::TextElements()
{
    font = TTF_OpenFont(fontFile.c_str(), 20);

    textRect.x = 30;
    textRect.y = 122;

    for(int i = keys->iterElement; i < keys->colElement; i ++)
    {
        if(textRect.y < keys->height - 75)
        {
            textSurface = TTF_RenderUTF8_Blended(font, standGraphs[i].c_str(), textColor);
            textTexture = SDL_CreateTextureFromSurface(keys->setup->GetRen(), textSurface);
            textRect.w = textSurface->w;
            textRect.h = textSurface->h;
            SDL_RenderCopy(keys->setup->GetRen(), textTexture, NULL , &textRect);
            textRect.y += 35;
            FreeTexture();
        }
        else
            break;
    }

    TTF_CloseFont(font);
}
*/
