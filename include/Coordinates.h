#ifndef COORDINATES_H
#define COORDINATES_H

#include <iostream>
#include <string>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Keys.h"
#include "SDL_Setup.h"

class Coordinates
{
    public:
        Coordinates(Keys*, SDL_Setup*);
       ~Coordinates();

        void DrawCoordinates();
        void NewTexture(int);

    private:
        Keys *keys;
        SDL_Setup *sdl_s;

        TTF_Font *font;

        SDL_Surface *surface;
        SDL_Texture *texture;
        SDL_Color coordColor;
        SDL_Rect rect;

        int plus, minus;
        string str;
};

#endif // COORDINATES_H
