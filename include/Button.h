#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ElementMenu.h"

using namespace std;

class StaticButton : public ElementMenu
{
    public:
        StaticButton(bool, char*, TTF_Font*, SDL_Renderer*, SDL_Rect*, bool*, int);
       ~StaticButton();
        void DrawElement();
    private:
        bool activemode;
        bool *mode;
        SDL_Texture *elTexture1;
        SDL_Texture *elTexture2;
};

class DynamicButton : public ElementMenu
{
    public:
        DynamicButton(char*, int*,TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~DynamicButton();
        void DrawElement();
    private:
        SDL_Texture *elTexture1;
        int *hMenu;
};

class EditButton : public BaseElementMenu
{
    public:
        EditButton(int*, SDL_Renderer*, SDL_Rect*, int);

        void DrawElement();
    private:
        int *yButton;
};

class DeleteButton : public BaseElementMenu
{
    public:
        DeleteButton(int*, SDL_Renderer*, SDL_Rect*, int);

        void DrawElement();
    private:
        int *yButton;
};

class AddButton : public BaseElementMenu
{
    public:
        AddButton(int*, SDL_Renderer*, SDL_Rect*, int);

        void DrawElement();
    private:
        int *yButton;
};

class UpButton : public BaseElementMenu
{
    public:
        UpButton(int*, SDL_Renderer*, SDL_Rect*, int);

        void DrawElement();
    private:
        int *yButton;
};

class DownButton : public BaseElementMenu
{
    public:
        DownButton(int*, SDL_Renderer*, SDL_Rect*, int);

        void DrawElement();
    private:
        int *yButton;
};

#endif // BUTTON_H
