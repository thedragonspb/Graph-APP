#ifndef CMENU_H
#define CMENU_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Keys.h"
#include "SDL_Setup.h"
#include "Buttons.h"
#include "Dots.h"
#include "StandardFunctions.h"

using namespace std;

class CMenu
{
    public:
        CMenu(Keys*, SDL_Setup*);
       ~CMenu();

       void DrawMenu();
       void MenuEvent();

    private:
        Keys *keys;
        SDL_Setup *sdl_s;
        TTF_Font *font[2];

        Buttons *buttons;

        Dots *dots;

        StandardFunctions *stf;

        bool mode;
        int ws;

        int hMenu;
};

#endif // CMENU_H
