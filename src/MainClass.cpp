#include "MainClass.h"

MainClass::MainClass(int w, int h)
{
    cout << "КОНСТРУКТОР С ПАРАМЕТРАМИ [ MainClass  ]" << endl;
    keys = new Keys(w, h);
    sdl_s = new SDL_Setup(&keys->quit, &w, &h);
    background = new Background(keys, sdl_s);
    menu = new CMenu(keys, sdl_s);
}

MainClass::~MainClass()
{
    cout << "ДЕСТРУКТОР [ MainClass  ]" << endl;

    delete keys;
    delete sdl_s;
    delete menu;
    delete background;
}

void MainClass::RunProgram()
{
    while( !keys->quit && sdl_s->GetEv()->type != SDL_QUIT)
    {
        while(SDL_PollEvent(sdl_s->GetEv()))
        {
            sdl_s->Begin();
            keys->ChangeKeys(sdl_s->GetWin());
            background->DrawBackground();
            menu->DrawMenu();
            sdl_s->End();
        }
    }
}
