#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <iostream>

#include "Keys.h"
#include "Event.h"
#include "Background.h"
#include "CMenu.h"

using namespace std;

class MainClass
{
    public:
        MainClass(int, int);
       ~MainClass();

        void RunProgram();
    private:
        SDL_Setup *sdl_s;
        Keys *keys;
        Background *background;
        CMenu *menu;
};

#endif // MAINCLASS_H
