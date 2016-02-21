#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Keys.h"
#include "string"


class TextClass
{
    public:
        TextClass(Keys* _keys);
        ~TextClass();
        void Coord();
        void SetTexture();
        void FreeTexture();
        void TextElements();
        void Menu();
    private:
        Keys         *keys;
        TTF_Font     *font;
        SDL_Surface  *textSurface;
        SDL_Texture  *textTexture;
        SDL_Color     textColor;
        SDL_Rect      textRect;
        int           fontSize;
        std::string   fontFile;
        std::string   standGraphs[10];
        char         *text;
};

#endif // TEXTCLASS_H
