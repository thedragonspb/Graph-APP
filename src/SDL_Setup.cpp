#include "SDL_Setup.h"

#include "SDL2/SDL.h"
#include "iostream"

SDL_Setup::SDL_Setup(bool* _quit, int* _width, int* _height)
{
    std::cout << "КОНСТРУКТОР С ПАРАМЕТРАМИ [ SDL_Setup  ]" << std::endl;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = NULL;
    window = SDL_CreateWindow("График функции", 100, 100, *_width, *_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(window == NULL)
    {
        std::cout << "Окно не может быть создано" << std::endl;
        *_quit = true;
        return;
    }

    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
    {
        std::cout << "Окно не может быть создано" << std::endl;
        *_quit = true;
        return;
    }

    mainEvent = new SDL_Event();
}

SDL_Setup::~SDL_Setup()
{
    std::cout << "ДЕСТРУКТОР [ SDL_Setup  ]" << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete mainEvent;
    SDL_Quit();
}

SDL_Renderer* SDL_Setup::GetRen()
{
    return renderer;
}
SDL_Event* SDL_Setup::GetEv()
{
    return mainEvent;
}

SDL_Window* SDL_Setup::GetWin()
{
    return window;
}

void SDL_Setup::Begin()
{
    SDL_PollEvent(mainEvent);
    SDL_RenderClear(renderer);
}

void SDL_Setup::End()
{
    SDL_RenderPresent(renderer);
}
