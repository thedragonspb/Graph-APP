#ifndef STANDARDFUNCTIONS_H
#define STANDARDFUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ElementMenu.h"
#include "Button.h"
#include "Input.h"
#include "Keys.h"
#include "StandardFunction.h"

struct st_f
{
    StandardFunction *stFunc;
    AddButton *add;
};

struct ABC
{
    string a, b, c;
};

struct StFExample
{
    StandardFunction *stFunc;
    EditButton *edit;
    DeleteButton *del;
};

class StandardFunctions
{
    public:
        StandardFunctions(int*, int*, SDL_Renderer*, TTF_Font*);
       ~StandardFunctions();

        int DrawStFunc(SDL_Event*);
        void LoadStFunc(SDL_Renderer*, TTF_Font*);

        void ShowStFunc(SDL_Event*);

        void AddFunc(SDL_Event* ev);
        void SaveFunc(TTF_Font* font, SDL_Renderer* ren);
        void StopAddFunc();

        void DeleteFunc(int);
        void EditFunc(int);
        void SaveEdit();

        void DrawGraphs(Keys*);

        int edit;

    private:
        vector<st_f*> st_func;

        vector<StFExample*> stf;

        string str[8];

        StrElementMenu *strEl;
        Input *input[3];
        ABC tempABC;

        UpButton *ub;
        DownButton *db;
        int iterElement;

        int addFunc;
        int h;
        int *hMenu;
        int *hWind;
};

#endif // STANDARDFUNCTIONS_H
