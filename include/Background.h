#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>

#include <SDL2/SDL.h>

#include "Keys.h"
#include "SDL_Setup.h"
#include "BGEvent.h"
#include "Coordinates.h"

using namespace std;

class Background
{
    public:
        Background(Keys*, SDL_Setup*);
        ~Background();

        void DrawBackground();
        void DrawLine();
        void DrawGraph();

    private:
        Keys *keys;
        SDL_Setup *sdl_s;
        BGEvent *bgevent;
        Coordinates *coordinates;

        SDL_Rect menuFon;
        SDL_Rect outFrame;
        SDL_Rect inFrame;
        SDL_Color color[2];
};

#endif // BACKGROUND_H
