#ifndef SDL_SETUP_H
#define SDL_SETUP_H

#include "SDL2/SDL.h"

class SDL_Setup
{
    public:
        SDL_Setup(bool* _quit, int* _width, int* _height);
       ~SDL_Setup();

       /** Функции, через которые осуществляется доступ к полям класса SDL_Setup **/
       SDL_Renderer* GetRen();
       SDL_Window* GetWin();
       SDL_Event* GetEv();

       void Begin();
       void End();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event *mainEvent;
};

#endif // SDL_SETUP_H
