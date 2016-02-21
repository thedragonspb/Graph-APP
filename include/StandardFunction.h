#ifndef STANDARDFUNCTION_H
#define STANDARDFUNCTION_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ElementMenu.h"
#include "Button.h"
#include "Input.h"
#include "Keys.h"

class StandardFunction : public ElementMenu
{
    public:
        StandardFunction(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);

        void DrawElement();
        virtual void DrawGraph(Keys*){};
        void SetABC(string*, string*, string*);
        int GetType();
        string* GetABC(int);
        virtual void UpdateStr(){};
        void SetDoubleABC(double, double, double);
        double XX(double a, double b, double c, double d, double e, double f);

    protected:
        int *yCoord;
        int colStr;
        string a, b, c;
        double A, B, C;
        SDL_Color graphColor;
};

class StFunc1 : public StandardFunction
{
    public:
        StFunc1(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~StFunc1();

        void UpdateStr();
        void DrawGraph(Keys*);
};

class StFunc2 : public StandardFunction
{
    public:
        StFunc2(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~StFunc2();

        void UpdateStr();
        void DrawGraph(Keys*);
};

class StFunc3 : public StandardFunction
{
    public:
        StFunc3(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~StFunc3();

        void UpdateStr();
        void DrawGraph(Keys*);
};


class StFunc4 : public StandardFunction
{
    public:
        StFunc4(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~StFunc4();

        void UpdateStr();
        void DrawGraph(Keys*);
};

class StFunc5 : public StandardFunction
{
    public:
        StFunc5(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~StFunc5();

        void UpdateStr();
        void DrawGraph(Keys*);
};

class StFunc6 : public StandardFunction
{
    public:
        StFunc6(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~StFunc6();

        void UpdateStr();
        void DrawGraph(Keys*);
};

class StFunc7 : public StandardFunction
{
    public:
        StFunc7(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~StFunc7();

        void UpdateStr();
        void DrawGraph(Keys*);
};



class StFunc8 : public StandardFunction
{
    public:
        StFunc8(int*, int, string*,  TTF_Font*, SDL_Renderer*, SDL_Rect*, int);
       ~StFunc8();

        void UpdateStr();
        void DrawGraph(Keys*);
};
#endif // STANDARDFUNCTION_H
