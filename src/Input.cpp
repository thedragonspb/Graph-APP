#include "Input.h"

Input::Input(SDL_Renderer* _ren, TTF_Font* font, string _str, int _colStr, int mode, string* pStr1, string* pStr2 , string* pStr3)
{
    ren = _ren;

    pStr [0] = pStr1;
    pStr [1] = pStr2;
    pStr [2] = pStr3;
    colStr = _colStr;
    focusInd = 0;
    int h = mode ? 100 : 140;

    SDL_Rect rect = { 25 , h, 196, 30 };
    strEl = new StrElementMenu(&_str, _ren, &rect, font, -1);

    string  array[2][3] =  {{"a = ", "b = ", "c = "}, {"X = ", "Y = ", "\0"}};

    rect = { 70 , h+40, 196, 30 };
    for(int i = 0; pStr[i] != NULL && i < colStr; i++)
    {
        entryField[i] = new EntryField(&array[mode][i], pStr[i], font, ren, &rect, 100+i);
        rect.y += 35;
    }
}

Input::~Input()
{
    delete strEl;
    for(int i = 0; pStr[i] != NULL && i < colStr; i++)
        delete entryField[i];
}

void Input::InputDate(SDL_Event* ev)
{
    int id;
    strEl->DrawElement(true);
    buffer.BufferFunction(ev);

    for(int i = 0; pStr[i] != NULL && i < colStr; i++)
    {
        id = entryField[i]->EventElement(ev);
        if(id == 100+i)
        {
            entryField[focusInd]->focus = false;
            entryField[i]->focus = true;
            focusInd = i;
            buffer.SetBuffer(entryField[i]->GetStr());
        }
        entryField[i]->DrawElement();
    }
}



EntryField::EntryField(string* _str, string* _str1, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : ElementMenu(ren, coord, font, id)
{
    str  = *_str;
    str1 = _str1;

    focus = false;

    bColor[0] = { 245, 248, 245, 115 };
    bColor[1] = { 201, 213, 217, 115 };

    tColor[0] = { 189, 214, 229, 100 };
    tColor[1] = { 235, 238, 235, 115 };
    tColor[2] = { 255, 255, 255, 255 };
}

void EntryField::DrawElement()
{
    bool c = (backlit || focus) ? 1 : 0;

    if(backlit && !focus)
    {
        SDL_SetRenderDrawColor(ren, tColor[1].r, tColor[1].g, tColor[1].b, tColor[1].a);
        SDL_RenderDrawLine( ren, coord.x, coord.y + coord.h, coord.x + coord.w, coord.y + coord.h );
    }

    if(focus)
    {
        SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);
        SDL_RenderDrawLine( ren, coord.x, coord.y + coord.h, coord.x + coord.w, coord.y + coord.h );
    }

    c = 0;

    elSurface = TTF_RenderUTF8_Blended(font, str.c_str() , tColor[c]);
    elTexture = SDL_CreateTextureFromSurface(ren, elSurface);
    elStrCoord = {coord.x-40, coord.y+8, elSurface->w, elSurface->h};
    SDL_RenderCopy(ren, elTexture, NULL, &elStrCoord);

    SDL_FreeSurface(elSurface);
    SDL_DestroyTexture(elTexture);

    if(str1->size())
    {
        elSurface = TTF_RenderUTF8_Blended(font, str1->c_str() , tColor[c]);
        elTexture = SDL_CreateTextureFromSurface(ren, elSurface);
        elStrCoord = {coord.x+2, coord.y+8, elSurface->w, elSurface->h};
        SDL_RenderCopy(ren, elTexture, NULL, &elStrCoord);
        SDL_FreeSurface(elSurface);
        SDL_DestroyTexture(elTexture);
    }
}

string* EntryField::GetStr()
{
    return str1;
}

void EntryField::SetStr(string* _str)
{
    str1 = _str;
}
