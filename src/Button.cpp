#include "Button.h"


/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StaticButton" -----------------------------------------------------**/

StaticButton::StaticButton(bool _activemode, char* bName, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, bool* _mode, int id) : ElementMenu(ren, coord, font, id)
{
    str  = bName;
    mode = _mode;
    activemode  = _activemode;

    bColor[0] = { 245, 248, 245, 115 };
    bColor[1] = { 201, 213, 217, 115 };

    tColor[0] = { 189, 214, 229, 100 };
    tColor[1] = { 235, 238, 235, 115 };
    tColor[2] = { 255, 255, 255, 255 };

    elSurface = TTF_RenderUTF8_Blended(font, str.c_str() , tColor[2]);
    elTexture = SDL_CreateTextureFromSurface(ren, elSurface);
    SDL_FreeSurface(elSurface);

    elSurface  = TTF_RenderUTF8_Blended(font, str.c_str() , tColor[1]);
    elTexture1 = SDL_CreateTextureFromSurface(ren, elSurface);

    elSurface  = TTF_RenderUTF8_Blended(font, str.c_str() , tColor[0]);
    elTexture2 = SDL_CreateTextureFromSurface(ren, elSurface);

    elStrCoord = {1, 1, elSurface->w, elSurface->h};

    SDL_FreeSurface(elSurface);
}

StaticButton::~StaticButton()
{
    SDL_DestroyTexture(elTexture);
    SDL_DestroyTexture(elTexture1);
    SDL_DestroyTexture(elTexture2);
}

void StaticButton::DrawElement()
{
    int c = (activemode == *mode) ? 0 : 1;

    SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);
    SDL_RenderFillRect(ren, &coord);

    c = (backlit && c) ? 2 : c;

    elStrCoord.x = coord.x+5;
    elStrCoord.y = coord.y+3;

    if(c == 0)
        SDL_RenderCopy(ren, elTexture2, NULL, &elStrCoord);
    else if(c == 1)
        SDL_RenderCopy(ren, elTexture1, NULL, &elStrCoord);
    else
        SDL_RenderCopy(ren, elTexture, NULL, &elStrCoord);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StaticButton" -----------------------------------------------------**/





/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "DynamicButton" -----------------------------------------------------**/

DynamicButton::DynamicButton(char* bName, int* _hMenu, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : ElementMenu(ren, coord, font, id)
{
    str = bName;
    hMenu = _hMenu;

    bColor[0] = { 245, 248, 245, 115 };
    bColor[1] = { 189, 214, 229, 100 };

    tColor[0] = { 225, 228, 225, 0 };
    tColor[1] = { 181, 193, 197, 0 };
    tColor[2] = { 255, 255, 255, 255 };

    elSurface = TTF_RenderUTF8_Blended(font, str.c_str() , tColor[1]);
    elTexture = SDL_CreateTextureFromSurface(ren, elSurface);
    SDL_FreeSurface(elSurface);

    elSurface = TTF_RenderUTF8_Blended(font, str.c_str() , tColor[0]);
    elTexture1 = SDL_CreateTextureFromSurface(ren, elSurface);

    elStrCoord = {1, 1, elSurface->w, elSurface->h};

    SDL_FreeSurface(elSurface);
}

DynamicButton::~DynamicButton()
{
    SDL_DestroyTexture(elTexture);
    SDL_DestroyTexture(elTexture1);
}

void DynamicButton::DrawElement()
{
    coord.y = *hMenu;

    bool c = backlit ? 1 : 0;

    SDL_SetRenderDrawColor(ren, bColor[1].r, bColor[1].g, bColor[1].b, bColor[1].a);
    SDL_RenderDrawLine(ren, 25, coord.y - 5, 266, coord.y - 5);
    SDL_RenderDrawLine(ren, 25, coord.y - 6, 266, coord.y - 6);

    elStrCoord.x = coord.x+20;
    elStrCoord.y = coord.y+3;


    if(backlit)
        SDL_RenderCopy(ren, elTexture, NULL, &elStrCoord);
    else
        SDL_RenderCopy(ren, elTexture1, NULL, &elStrCoord);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "DynamicButton" -----------------------------------------------------**/





/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "EditButton" -------------------------------------------------------**/

EditButton::EditButton(int* _yButton, SDL_Renderer* ren, SDL_Rect* coord, int id) : BaseElementMenu(ren, coord, id)
{
    yButton = _yButton;

    bColor[0] = { 225, 228, 225, 0 };
    bColor[1] = { 181, 193, 197, 0 };
}

void EditButton::DrawElement()
{
    coord.y = *yButton;

    bool c = backlit ? 1 : 0;

    SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);
    SDL_RenderDrawLine(ren, 200, coord.y+coord.h-15, 214, coord.y+6);
    SDL_RenderDrawLine(ren, 202, coord.y+coord.h-15, 215, coord.y+7);
    SDL_RenderDrawLine(ren, 203, coord.y+coord.h-14, 216, coord.y+8);
    SDL_RenderDrawLine(ren, 203, coord.y+coord.h-12, 217, coord.y+9);
    SDL_RenderDrawLine(ren, 198, coord.y+coord.h-10, 203, coord.y+coord.h-12);
    SDL_RenderDrawLine(ren, 200, coord.y+coord.h-15, 198, coord.y+coord.h-10);
    SDL_RenderDrawLine(ren, 197, coord.y+coord.h-10, 192, coord.y+coord.h-10);
    SDL_RenderDrawLine(ren, 214, coord.y+6, 217, coord.y+9);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "EditButton" -------------------------------------------------------**/





/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "DeleteButton" -------------------------------------------------------**/

DeleteButton::DeleteButton(int* _yButton, SDL_Renderer* ren, SDL_Rect* coord, int id) : BaseElementMenu(ren, coord, id)
{
    yButton = _yButton;

    bColor[0] = { 225, 228, 225, 0 };
    bColor[1] = { 181, 193, 197, 0 };
}


void DeleteButton::DrawElement()
{
    coord.y = *yButton;

    bool c = backlit ? 1 : 0;

    SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);

    SDL_RenderDrawLine(ren, 236, coord.y+7, 254, coord.y+coord.h-10);
    SDL_RenderDrawLine(ren, 235, coord.y+8, 253, coord.y+coord.h-9);
    SDL_RenderDrawLine(ren, 234, coord.y+9, 252, coord.y+coord.h-8);
    SDL_RenderDrawLine(ren, 234, coord.y+coord.h-10, 252, coord.y+7);
    SDL_RenderDrawLine(ren, 236, coord.y+coord.h-8, 254, coord.y+9);
    SDL_RenderDrawLine(ren, 235, coord.y+coord.h-9, 253, coord.y+8);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "DeleteButton" -------------------------------------------------------**/





/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "AddButton" -------------------------------------------------------**/

AddButton::AddButton(int* _yButton, SDL_Renderer* ren, SDL_Rect* coord, int id) : BaseElementMenu(ren, coord, id)
{
    yButton = _yButton;

    bColor[0] = { 225, 228, 225, 0 };
    bColor[1] = { 181, 193, 197, 0 };
}


void AddButton::DrawElement()
{
    coord.y = *yButton;

    bool c = backlit ? 1 : 0;

    SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);
    SDL_RenderDrawLine(ren, 243, coord.y+7, 243, coord.y+coord.h-6);
    SDL_RenderDrawLine(ren, 244, coord.y+7, 244, coord.y+coord.h-6);
    SDL_RenderDrawLine(ren, 242, coord.y+7, 242, coord.y+coord.h-6);
    SDL_RenderDrawLine(ren, 232, coord.y+17, 254, coord.y+17);
    SDL_RenderDrawLine(ren, 232, coord.y+18, 254, coord.y+18);
    SDL_RenderDrawLine(ren, 232, coord.y+19, 254, coord.y+19);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "AddButton" -------------------------------------------------------**/



/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "UpButton" -------------------------------------------------------**/

UpButton::UpButton(int* _yButton, SDL_Renderer* ren, SDL_Rect* coord, int id) : BaseElementMenu(ren, coord, id)
{
    yButton = _yButton;

    bColor[0] = { 225, 228, 225, 0 };
    bColor[1] = { 181, 193, 197, 0 };
}


void UpButton::DrawElement()
{
    coord.y = *yButton;

    bool c = backlit ? 1 : 0;

    SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);
    SDL_RenderDrawLine(ren, 200, coord.y + 3, 160, coord.y + 3);
    SDL_RenderDrawLine(ren, 199, coord.y + 4, 161, coord.y + 4);

    SDL_RenderDrawLine(ren, 198, coord.y + 3, 180, coord.y + 23);
    SDL_RenderDrawLine(ren, 199, coord.y + 3, 180, coord.y + 24);
    SDL_RenderDrawLine(ren, 200, coord.y + 3, 180, coord.y + 25);
    SDL_RenderDrawLine(ren, 162, coord.y + 3, 180, coord.y + 23);
    SDL_RenderDrawLine(ren, 161, coord.y + 3, 180, coord.y + 24);
    SDL_RenderDrawLine(ren, 160, coord.y + 3, 180, coord.y + 25);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "UpButton" -------------------------------------------------------**/



/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "DownButton" -------------------------------------------------------**/

DownButton::DownButton(int* _yButton, SDL_Renderer* ren, SDL_Rect* coord, int id) : BaseElementMenu(ren, coord, id)
{
    yButton = _yButton;

    bColor[0] = { 225, 228, 225, 0 };
    bColor[1] = { 181, 193, 197, 0 };
}


void DownButton::DrawElement()
{
    coord.y = *yButton;

    bool c = backlit ? 1 : 0;

    SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);
    SDL_RenderDrawLine(ren, 250, coord.y + 25, 210, coord.y + 25);
    SDL_RenderDrawLine(ren, 249, coord.y + 24, 211, coord.y + 24);

    SDL_RenderDrawLine(ren, 248, coord.y + 25, 230, coord.y + 5);
    SDL_RenderDrawLine(ren, 249, coord.y + 25, 230, coord.y + 4);
    SDL_RenderDrawLine(ren, 250, coord.y + 25, 230, coord.y + 3);
    SDL_RenderDrawLine(ren, 210, coord.y + 25, 230, coord.y + 3);
    SDL_RenderDrawLine(ren, 211, coord.y + 25, 230, coord.y + 4);
    SDL_RenderDrawLine(ren, 212, coord.y + 25, 230, coord.y + 5);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "DownButton" -------------------------------------------------------**/
