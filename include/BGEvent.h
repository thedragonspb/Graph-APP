#ifndef BGEVENT_H
#define BGEVENT_H

#include <iostream>

#include <SDL2/SDL.h>

#include "Keys.h"
#include "SDL_Setup.h"

class BGEvent
{
    public:
        BGEvent(Keys*, SDL_Setup*);
        ~BGEvent();

    void Event();

    private:
        Keys *keys;
        SDL_Setup *sdl_s;
        bool scaleX_down;
        bool scaleY_down;
};

#endif // BGEVENT_H
