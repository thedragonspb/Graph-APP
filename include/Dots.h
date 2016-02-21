#ifndef DOTS_H
#define DOTS_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ElementMenu.h"
#include "Button.h"
#include "Input.h"
#include "Keys.h"

using namespace std;


class Dot : public ElementMenu
{
    public:
        Dot(int*, TTF_Font* _font, SDL_Renderer*, SDL_Rect*, int);

        void DrawElement();
        void SetXY(string*, string*);

    private:
        int *yCoord;
        string x, y;
};

struct dot
{
    double X, Y;
    string x, y;
    Dot *viewDot;
    EditButton *edit;
    DeleteButton *del;
};

class Dots
{
    public:
        Dots(int*, int*, SDL_Renderer*, TTF_Font*);
       ~Dots();

        void StartAddDot();
        void AddDot(SDL_Event* ev);
        void SaveDot(TTF_Font*, SDL_Renderer*);
        void StopAddDot();

        void ToDouble(string*, string*, int*, int*);

        void DeleteDot(int);
        void EditDot(int);
        void SaveEdit();

        void ShowDots(SDL_Event*);
        void SordDots();
        void DrawDots(Keys*, SDL_Renderer*);
        double XX(double a, double b, double c, double d, double e, double f);

        int edit;

    private:
        vector<dot*> dots;
        dot tempDot;

        Input *input;

        UpButton *ub;
        DownButton *db;

        int h;
        int *hMenu;
        int *hWind;
        int iterElement;
};

#endif // DOTS_H
