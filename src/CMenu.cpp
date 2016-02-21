#include "CMenu.h"

CMenu::CMenu(Keys* _keys, SDL_Setup* _sdl_s)
{
    cout << "КОНСТРУКТОР С ПАРАМЕТРАМИ [ CMenu      ]" << endl;

    TTF_Init();

    keys  = _keys;
    sdl_s = _sdl_s;

    mode = 0;
    ws   = 0;

    hMenu = 100;

    srand((unsigned int)NULL);

    font[0] = TTF_OpenFont("arial.ttf", 28);
    font[1] = TTF_OpenFont("arial.ttf", 18);

    if(font[0] == NULL || font[1] == NULL || font[2])
    {
        keys->quit = true;
        cout << SDL_GetError() << endl;
    }

    buttons = new Buttons(&mode, &ws, &hMenu, sdl_s->GetRen(), font);
    dots = new Dots(&keys->h3, &hMenu, sdl_s->GetRen(), font[1]);
    stf  = new StandardFunctions(&keys->h3, &hMenu, sdl_s->GetRen(), font[1]);
}

CMenu::~CMenu()
{
    cout << "ДЕСТРУКТОР [ CMenu      ]" << endl;

    delete buttons;
    delete dots;
    delete stf;

    TTF_CloseFont(font[0]);
    TTF_CloseFont(font[1]);
    TTF_Quit();
}

void CMenu::DrawMenu()
{
    MenuEvent();

    if(!mode)
    {
        if(!ws && dots->edit < 0)
            dots->ShowDots(sdl_s->GetEv());
        else
        {
            ws = 1;
            hMenu = 220;
            dots->AddDot(sdl_s->GetEv());
        }
    }
    else
    {
        if(!ws && stf->edit < 0)
        {
            stf->ShowStFunc(sdl_s->GetEv());
        }
        else if( ws != 1 && ws != 2)
        {
            ws = 2;
            stf->AddFunc(sdl_s->GetEv());
        }

        if(ws == 1)
        {
            if( stf->DrawStFunc(sdl_s->GetEv()) >= 0)
                ws = 2;
        }
        else if(ws == 2)
        {
            stf->AddFunc(sdl_s->GetEv());
        }
    }
    stf->DrawGraphs(keys);
    buttons->DrawButtons();
    dots->DrawDots(keys, sdl_s->GetRen());
}

void CMenu::MenuEvent()
{
    if(sdl_s->GetEv()->type)
    {
        int id = buttons->ButtonsEvent(sdl_s->GetEv());
        switch(id)
        {
            case 0: /* Переход в меню "Точки" */
            {
                mode = 0;
                ws   = 0;
                break;
            }
            case 1: /* Переход в меню "Функции" */
            {
                mode = 1;
                ws   = 0;
                break;
            }
            case 2:
            {
                if(ws == 0) /* Меню "Точки"/"Функции" -> Добавить(Переход в режим добавления) */
                {
                    ws = 1;
                    hMenu = 220;
                    if(!mode)
                    {
                    }
                }
                else if(ws == 1 && mode == 1) /*Меню "Функции" -> Добавить(Переход в режим ввода коэффициентов) */
                {
                    hMenu = 190;
                    ws = 2;
                }
                else if(ws == 1) /*Меню "Точки" -> Добавить(Сохранить результат) */
                {
                    ws = 0;
                    if(dots->edit < 0)
                        dots->SaveDot(font[1], sdl_s->GetRen());
                    else
                        dots->SaveEdit();
                }
                else if(ws == 2 && mode == 1) /*Меню "Функции" -> Добавить(Сохранить результат) */
                {
                    ws = 0;
                    if(stf->edit < 0)
                        stf->SaveFunc(font[1], sdl_s->GetRen());
                    else
                        stf->SaveEdit();
                }
                break;
            }
            case 3:
            {
                if(ws == 1) /* Меню "Точки"/"Функции" -> Назад(Переход в режим просмотра) */
                {
                    ws = 0;
                    hMenu = 100;
                    if(!mode)
                    {
                        dots->StopAddDot();
                    }
                }
                else if(ws == 2) /* Меню "Функции" -> Назад(Переход из режима ввода коэффициентов обратно в меню добавления) */
                {
                    if(stf->edit < 0)
                        ws = 1;
                    else
                        ws = 0;
                    stf->StopAddFunc();
                }
                break;
            }
        }
    }
}
