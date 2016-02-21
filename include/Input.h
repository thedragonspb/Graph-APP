#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Buffer.h"
#include "ElementMenu.h"

using namespace std;

class EntryField : public ElementMenu
{
    public:
        EntryField(string*, string*, TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
        void DrawElement();
        string* GetStr();
        void SetStr(string*);

        bool focus;

    private:
        string* str1;
};

class Input
{
    public:
        Input(SDL_Renderer*, TTF_Font*, string, int, int, string*, string*, string*);
        ~Input();

        void InputDate(SDL_Event*);

    private:
        SDL_Renderer *ren;

        EntryField *entryField[3];
        StrElementMenu *strEl;

        Buffer buffer;
        string *pStr[3];
        int colStr;
        int focusInd;
};

#endif // INPUT_H
