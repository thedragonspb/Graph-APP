#ifndef BUTTONS_H
#define BUTTONS_H

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ElementMenu.h"
#include "Button.h"
#include "Dots.h"
#include "StandardFunctions.h"

using namespace std;

class Buttons
{
    public:
        Buttons(bool*, int*, int*, SDL_Renderer*, TTF_Font**);
       ~Buttons();

        void DrawButtons();
        int ButtonsEvent(SDL_Event*);

    private:
        vector<ElementMenu*> buttons;
        bool *mode;
        int  *ws;
        int  *hMenu;
};

#endif // BUTTONS_H
