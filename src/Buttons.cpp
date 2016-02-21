#include "Buttons.h"

Buttons::Buttons(bool* _mode, int* _ws, int* _hMenu, SDL_Renderer* ren, TTF_Font** font)
{
    mode = _mode;
    ws   = _ws;
    hMenu = _hMenu;

    SDL_Rect rect = { 20 , 50, 120, 30 };
    StaticButton *bDot = new StaticButton(0, "Точки", font[1], ren, &rect, mode, 0);

    rect = { 140, 50, 130, 30 };
    StaticButton *bFunc = new StaticButton(1, "Функции", font[1], ren, &rect, mode, 1);

    rect = { 25 , 185, 115, 30 };
    DynamicButton *bAdd  = new DynamicButton("Добавить", hMenu, font[1], ren, &rect, 2);

    rect = { 143, 185, 123, 30 };
    DynamicButton *bBack = new DynamicButton("Назад", hMenu, font[1], ren, &rect, 3);

    buttons.push_back(bDot);
    buttons.push_back(bFunc);
    buttons.push_back(bAdd);
    buttons.push_back(bBack);
}

Buttons::~Buttons()
{
    int i = buttons.size()-1;
    while(buttons.size())
    {
        delete buttons[i];
        buttons.pop_back();
        i--;
    }
}

void Buttons::DrawButtons()
{
    buttons[0]->DrawElement();
    buttons[1]->DrawElement();

    if(*ws == 1 || *ws== 2)
    {
        buttons[3]->DrawElement();
    }
    if((*ws != 1 && *mode) || !*mode)
        buttons[2]->DrawElement();

}

int Buttons::ButtonsEvent(SDL_Event* ev)
{
    int id = -1;
    for( int i = 0; i < buttons.size(); i++)
    {
        id = buttons[i]->EventElement(ev);
        if( id >= 0 )
            return id;
    }
    return id;
}
