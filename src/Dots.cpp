#include "Dots.h"

/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "Dots" -------------------------------------------------------**/


Dots::Dots(int* _hWind, int* _hMenu, SDL_Renderer* ren, TTF_Font* font)
{
    input = new Input(ren, font, "Введите координаты", 2, 1, &tempDot.x, &tempDot.y, NULL);
    hMenu = _hMenu;
    hWind = _hWind;
    iterElement = 0;
    h = 100;
    edit = -1;

    SDL_Rect rect = { 160 , 185, 40, 25 };
    ub = new UpButton(_hMenu, ren, &rect, 1);

    rect = { 210 , 185, 40, 25 };
    db = new DownButton(_hMenu, ren, &rect, 1);
}

Dots::~Dots()
{
    int i = dots.size()-1;
    while(dots.size())
    {
        delete dots[i]->viewDot;
        delete dots[i]->edit;
        delete dots[i]->del;
        delete dots[i];
        dots.pop_back();
        i--;
    }
    delete input;
    delete ub;
    delete db;
}

void Dots::AddDot(SDL_Event* ev)
{
    input->InputDate(ev);
}


void Dots::SaveDot(TTF_Font* font, SDL_Renderer* ren)
{
    dot *temp = new dot;

    temp->x = tempDot.x;
    temp->y = tempDot.y;

    temp->X = atof(temp->x.c_str());
    temp->Y = atof(temp->y.c_str());

    for(int i = 0; i <dots.size(); i++)
    {
        if(dots[i]->X > temp->X)
        {
            cout << "Yes" << endl;
            double X    = dots[i]->X;
            double Y    = dots[i]->Y;
            string x    = dots[i]->x;
            string y    = dots[i]->y;
            dots[i]->x  = temp->x;
            dots[i]->y  = temp->y;
            dots[i]->X  = temp->X;
            dots[i]->Y  = temp->Y;
            temp->X     = X;
            temp->Y     = Y;
            temp->x     = x;
            temp->y     = y;
        }
    }

    SDL_Rect rect = { 25 , h, 266, 35};
    temp->viewDot = new Dot(&h, font, ren, &rect, 1);

    rect = { 185, h, 37, 35};
    temp->edit = new EditButton(&h, ren, &rect, 1);

    rect = { 225, h, 37, 35};
    temp->del = new DeleteButton(&h, ren, &rect, 1);

    dots.push_back(temp);
    StopAddDot();
}

void Dots::StopAddDot()
{
    tempDot.x.clear();
    tempDot.y.clear();
    edit = -1;
}

void Dots::DeleteDot(int i)
{
    delete dots[i]->viewDot;
    delete dots[i]->edit;
    delete dots[i]->del;
    delete dots[i];
    dots.erase(dots.begin()+i);
}

void Dots::EditDot(int i)
{
    edit = i;
    tempDot.x = dots[i]->x;
    tempDot.y = dots[i]->y;
}

void Dots::SaveEdit()
{
    dots[edit]->x = tempDot.x;
    dots[edit]->y = tempDot.y;

    dots[edit]->X = atof(dots[edit]->x.c_str());
    dots[edit]->Y = atof(dots[edit]->y.c_str());

    StopAddDot();
    edit = -1;
}

void Dots::ShowDots(SDL_Event* ev)
{
    h = 60;
    int del  = -1;
    int edit = -1;;
    int i;

    for( i = iterElement; i < dots.size() && h < *hWind - 40; i++)
    {
        h += 40;

        if(dots[i]->edit->EventElement(ev) == true)
            edit = i;
        dots[i]->edit->DrawElement();

        if(dots[i]->del->EventElement(ev) == true)
            del = i;
        dots[i]->del->DrawElement();

        dots[i]->viewDot->SetXY(&dots[i]->x, &dots[i]->y);
        dots[i]->viewDot->DrawElement();
        dots[i]->viewDot->EventElement(ev);
    }

    if(i < dots.size() && iterElement + 1 < dots.size())
    {
        ub->DrawElement();
        if(ub->EventElement(ev) == true )
            iterElement++;
    }

    if(iterElement > 0 && iterElement - 1 >= 0)
    {
        db->DrawElement();
        if(db->EventElement(ev) == true )
            iterElement--;
    }

    *hMenu = h + 45;

    if(del >= 0)
        DeleteDot(del);
    if(edit >= 0)
        EditDot(edit);
}

double Dots::XX(double a, double b, double c, double d, double e, double f)
{
    return ((a-b)*(c-d))/(e-f);
}

void Dots::DrawDots(Keys* keys, SDL_Renderer* ren)
{
    if(dots.size() > 1)
    {
        SDL_Rect r0{1,1,4,4};
        SDL_Rect r {1,1,4,4};

        int h1 = keys->h2;
        int h2 = keys->h3+47;
        int w1 = 332;
        int w2 = keys->w5;

        double tempx, tempy;
        double x, y;

        double x0 = keys->w4/2+290 + dots[0]->X*keys->scaleX + (keys->offsetX-keys->offsetXarea)*keys->scaleX;
        double y0 = keys->height/2 + -1*dots[0]->Y*keys->scaleY + (keys->offsetY-keys->offsetYarea)*keys->scaleY;

        for( int i = 1; i < dots.size(); i++)
        {
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
            x = keys->w4/2+290 + dots[i]->X*keys->scaleX + (keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2 + -1*dots[i]->Y*keys->scaleY + (keys->offsetY-keys->offsetYarea)*keys->scaleY;
            tempx = x; tempy = y;

            if(y > h2)
            {
                x = x0-XX(x0,x,h2,y0,y,y0);
                y = h2;
            }
            if(y0 > h2)
            {
                x0 = x+XX(x0,x,h2,y,y0,y);
                y0 = h2;
            }
            if(y < h1)
            {
                x = x+XX(x0,x,h1,y,y0,y);
                y = h1;
            }
            if(y0 < h1)
            {
                x0 = x0-XX(x0,x,h1,y0,y,y0);
                y0 = h1;
            }
            if(x0 < w1)
            {
                y0 = y0+XX(y,y0,w1,x0,x,x0);
                x0 = w1;
            }
            if(x < w1)
            {
                y = y+XX(y0,y,w1,x,x0,x);
                x = w1;
            }
            if(x > w2)
            {
                y = y-XX(y,y0,x,w2,x,x0);
                x = w2;
            }
            if(x0 > w2)
            {
                y0 = y0-XX(y0,y,x0,w2,x0,x);
                x0 = w2;
            }

            if( y0 >= h1 && y >= h1 && y0 <= h2 && y <= h2 )
            {
                SDL_RenderDrawLine(ren, x0-1, y0, x-1, y);
                SDL_RenderDrawLine(ren, x0  , y0, x  , y);
            }

           /* SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
            SDL_RenderFillRect(ren, &r);
            r.x  = x-2;  r.y  = y-2;
            SDL_RenderFillRect(ren, &r);
*/
            x0 = tempx;
            y0 = tempy;
        }
    }
}


/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "Dots" -------------------------------------------------------**/




/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "Dot" -------------------------------------------------------**/


Dot::Dot(int* _yCoord, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : ElementMenu(ren, coord, font, id)
{
    yCoord = _yCoord;

    bColor[0] = { 225, 228, 225, 0 };
    bColor[1] = { 181, 193, 197, 0 };

    tColor[1] = { 181, 193, 197, 0 };
    tColor[0] = { 189, 214, 229, 100 };
    tColor[2] = { 255, 255, 255, 255 };
}

void Dot::SetXY(string* _x, string* _y)
{
    x.assign("x:"+*(_x));
    y.assign("y:"+*(_y));
}

void Dot::DrawElement()
{
    coord.y = *yCoord;

    bool c = backlit ? 1 : 0;

    elSurface = TTF_RenderUTF8_Blended(font, x.c_str() , tColor[c]);
    elTexture = SDL_CreateTextureFromSurface(ren, elSurface);
    elStrCoord = {coord.x+3, coord.y+7, elSurface->w, elSurface->h};
    SDL_RenderCopy(ren, elTexture, NULL, &elStrCoord);

    SDL_FreeSurface(elSurface);
    SDL_DestroyTexture(elTexture);

    elSurface = TTF_RenderUTF8_Blended(font, y.c_str() , tColor[c]);
    elTexture = SDL_CreateTextureFromSurface(ren, elSurface);
    elStrCoord = {coord.x+85, coord.y+7, elSurface->w, elSurface->h};
    SDL_RenderCopy(ren, elTexture, NULL, &elStrCoord);

    SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);
    SDL_RenderDrawLine(ren, 25, coord.y, 266, coord.y);
    SDL_RenderDrawLine(ren, 25, coord.y+35, 266, coord.y+35);

    SDL_FreeSurface(elSurface);
    SDL_DestroyTexture(elTexture);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "Dot" -------------------------------------------------------**/
