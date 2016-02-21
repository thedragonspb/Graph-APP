#include "StandardFunction.h"

/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StandardFunction" -------------------------------------------------------**/

StandardFunction::StandardFunction(int* _yCoord, int _colStr, string* _str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : ElementMenu(ren, coord, font, id)
{
    str = *_str;

    yCoord = _yCoord;
    colStr = _colStr;

    bColor[0] = { 225, 228, 225, 0 };
    bColor[1] = { 181, 193, 197, 0 };

    tColor[0] = { 189, 214, 229, 100 };
    tColor[1] = { 181, 193, 197, 0  };
    tColor[2] = { 255, 255, 255, 255 };

    graphColor = {100 + rand() % 155, 100 + rand() % 155, 100 + rand() % 155, rand() % 255};
}


void StandardFunction::SetABC(string* _a, string* _b, string* _c)
{
    if(_a)
        a.assign(*_a);
    if(_b)
        b.assign(*_b);
    if(_c)
        c.assign(*_c);
}

void StandardFunction::SetDoubleABC(double _A, double _B, double _C)
{
    A = _A;
    B = _B;
    C = _C;
}

string* StandardFunction::GetABC(int i)
{
    if(i == 1)
        return &a;
    if(i == 2)
        return &b;
    if(i == 3)
        return &c;
}

int StandardFunction::GetType()
{
    return colStr;
}

void StandardFunction::DrawElement()
{
    bool c = backlit;

    coord.y = *yCoord;

    SDL_SetRenderDrawColor(ren, bColor[c].r, bColor[c].g, bColor[c].b, bColor[c].a);
    SDL_RenderDrawLine(ren, 25, coord.y, 266, coord.y);
    SDL_RenderDrawLine(ren, 25, coord.y+35, 266, coord.y+35);

    SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );
    SDL_RenderDrawLine(ren, 25, coord.y + 3, 25, coord.y + coord.h - 3);
    SDL_RenderDrawLine(ren, 26, coord.y + 3, 26, coord.y + coord.h - 3);

    elSurface = TTF_RenderUTF8_Blended(font, str.c_str() , tColor[c]);
    elTexture = SDL_CreateTextureFromSurface(ren, elSurface);
    elStrCoord = {coord.x+4, coord.y+5, elSurface->w, elSurface->h};
    SDL_RenderCopy(ren, elTexture, NULL, &elStrCoord);

    SDL_FreeSurface(elSurface);
    SDL_DestroyTexture(elTexture);
}

/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StandardFunction" -------------------------------------------------------**/


double StandardFunction::XX(double a, double b, double c, double d, double e, double f)
{
    return ((a-b)*(c-d))/(e-f);
}


/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StFunc1" -------------------------------------------------------**/

StFunc1::StFunc1(int* yCoord, int colStr, string* str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : StandardFunction(yCoord, colStr, str, font, ren, coord, id)
{
}

StFunc1::~StFunc1()
{
}

void StFunc1::UpdateStr()
{
    str.assign("y = " + a + "/x");
}

void StFunc1::DrawGraph(Keys* keys)
{
    SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );


    int h1 = keys->h2;
    int h2 = keys->h3 + 47;


    bool exit1 = false, exit2 = false;

    double X1 = keys->offsetXarea + 0.000001;
    double X2 = keys->offsetXarea - 0.000001;
    double Y;

    double x, y;

    Y = -1*A/X1;
    double x01 = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y01 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;


    Y = -1*A/X2;
    double x02 = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y02 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

    X1 += keys->smoothing;
    X2 -= keys->smoothing;

    do
    {
            Y = -1*A/X1;
            x = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x < keys->w5+5)
            {
                if(x > keys->w2+5)
                {
                    if(y01 >= h1 && y >= h1)
                    {
                        if(y01 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x01+1, y01, x+1, y);
                            SDL_RenderDrawLine(ren, x01  , y01, x  , y);
                        }
                        else
                        {
                            if(y01 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)+1, h2+1, x01+1, y01+1);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)  , h2  , x01  , y01  );
                            }
                            else if(y01 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)+1, h2+1, x+1, y);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)  , h2  , x  , y);
                            }
                        }
                    }
                    else if(y01 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)+1, h1+1, x01+1, y01);
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)  , h1  , x01  , y01);
                    }
                    else if(y01 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)+1, h1+1, x+1, y);
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)  , h1  , x  , y);
                    }
                }
            }
            else
                exit1 = true;

            x01 = x;
            y01 = y;
            X1 += keys->smoothing;

            Y = -1*A/X2;
            x = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x > keys->w2+5)
            {
                if(x < keys->w5+5)
                {
                    if(y02 >= h1 && y >= h1)
                    {
                        if(y02 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x02-1, y02, x-1, y);
                            SDL_RenderDrawLine(ren, x02  , y02, x  , y);
                        }
                        else
                        {
                            if(y02 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)-1, h2, x02-1, y02);
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)  , h2  , x02  , y02  );
                            }
                            else if(y02 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)-1, h2, x-1, y);
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)  , h2  , x  , y  );
                            }
                        }
                    }
                    else if(y02 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)-1, h1, x02-1, y02);
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)  , h1  , x02  , y02  );
                    }
                    else if(y02 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)-1, h1, x-1, y);
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)  , h1  , x  , y  );
                    }
                }
            }
            else
                exit2 = true;

            x02 = x;
            y02 = y;
            X2  -= keys->smoothing;

    }while(!exit1 || !exit2);
}


/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StFunc1" -------------------------------------------------------**/


/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StFunc1" -------------------------------------------------------**/

StFunc2::StFunc2(int* yCoord, int colStr, string* str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : StandardFunction(yCoord, colStr, str, font, ren, coord, id)
{
}

StFunc2::~StFunc2()
{
}

void StFunc2::UpdateStr()
{
    str.assign("y = x^" + a);
}

void StFunc2::DrawGraph(Keys* keys)
{
        SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );

    int h1 = keys->h2;
    int h2 = keys->h3 + 47;


    bool exit1 = false, exit2 = false;

    double X1 = keys->offsetXarea + 0.000001;
    double X2 = keys->offsetXarea - 0.000001;
    double Y;

    double x, y;

    Y = -1*pow(X1,A);
    double x01 = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y01 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;


    Y = -1*pow(X2,A);
    double x02 = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y02 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

    X1 += keys->smoothing;
    X2 -= keys->smoothing;

    do
    {
            Y = -1*pow(X1, A);
            x = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x < keys->w5+5)
            {
                if(x > keys->w2+5)
                {
                    if(y01 >= h1 && y >= h1)
                    {
                        if(y01 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x01+1, y01, x+1, y);
                            SDL_RenderDrawLine(ren, x01  , y01, x  , y);
                        }
                        else
                        {
                            if(y01 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)+1, h2+1, x01+1, y01+1);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)  , h2  , x01  , y01  );
                            }
                            else if(y01 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)+1, h2+1, x+1, y);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)  , h2  , x  , y);
                            }
                        }
                    }
                    else if(y01 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)+1, h1+1, x01+1, y01);
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)  , h1  , x01  , y01);
                    }
                    else if(y01 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)+1, h1+1, x+1, y);
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)  , h1  , x  , y);
                    }
                }
            }
            else
                exit1 = true;

            x01 = x;
            y01 = y;
            X1 += keys->smoothing;

            Y = -1*pow(X2, A);
            x = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x > keys->w2+5)
            {
                if(x < keys->w5+5)
                {
                    if(y02 >= h1 && y >= h1)
                    {
                        if(y02 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x02-1, y02, x-1, y);
                            SDL_RenderDrawLine(ren, x02  , y02, x  , y);
                        }
                        else
                        {
                            if(y02 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)-1, h2, x02-1, y02);
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)  , h2  , x02  , y02  );
                            }
                            else if(y02 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)-1, h2, x-1, y);
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)  , h2  , x  , y  );
                            }
                        }
                    }
                    else if(y02 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)-1, h1, x02-1, y02);
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)  , h1  , x02  , y02  );
                    }
                    else if(y02 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)-1, h1, x-1, y);
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)  , h1  , x  , y  );
                    }
                }
            }
            else
                exit2 = true;

            x02 = x;
            y02 = y;
            X2  -= keys->smoothing;

    }while(!exit1 || !exit2);
}


/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StFunc2" -------------------------------------------------------**/



/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StFunc3" -------------------------------------------------------**/


StFunc3::StFunc3(int* yCoord, int colStr, string* str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : StandardFunction(yCoord, colStr, str, font, ren, coord, id)
{
}

StFunc3::~StFunc3()
{
}

void StFunc3::UpdateStr()
{
    str.assign("y = " + a + "^X");
}

void StFunc3::DrawGraph(Keys* keys)
{
        SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );

    int h1 = keys->h2;
    int h2 = keys->h3 + 47;


    bool exit1 = false, exit2 = false;

    double X1 = keys->offsetXarea + 0.000001;
    double X2 = keys->offsetXarea - 0.000001;
    double Y;

    double x, y;

    Y = -1*pow(A,X1);
    double x01 = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y01 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;


    Y = -1*pow(A,X2);
    double x02 = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y02 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

    X1 += keys->smoothing;
    X2 -= keys->smoothing;

    do
    {
            Y = -1*pow(A,X1);
            x = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x < keys->w5+5)
            {
                if(x > keys->w2+5)
                {
                    if(y01 >= h1 && y >= h1)
                    {
                        if(y01 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x01+1, y01, x+1, y);
                            SDL_RenderDrawLine(ren, x01  , y01, x  , y);
                        }
                        else
                        {
                            if(y01 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)+1, h2+1, x01+1, y01+1);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)  , h2  , x01  , y01  );
                            }
                            else if(y01 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)+1, h2+1, x+1, y);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)  , h2  , x  , y);
                            }
                        }
                    }
                    else if(y01 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)+1, h1+1, x01+1, y01);
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)  , h1  , x01  , y01);
                    }
                    else if(y01 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)+1, h1+1, x+1, y);
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)  , h1  , x  , y);
                    }
                }
            }
            else
                exit1 = true;

            x01 = x;
            y01 = y;
            X1 += keys->smoothing;

            Y = -1*pow(A, X2);
            x = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x > keys->w2+5)
            {
                if(x < keys->w5+5)
                {
                    if(y02 >= h1 && y >= h1)
                    {
                        if(y02 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x02-1, y02, x-1, y);
                            SDL_RenderDrawLine(ren, x02  , y02, x  , y);
                        }
                        else
                        {
                            if(y02 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)-1, h2, x02-1, y02);
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)  , h2  , x02  , y02  );
                            }
                            else if(y02 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)-1, h2, x-1, y);
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)  , h2  , x  , y  );
                            }
                        }
                    }
                    else if(y02 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)-1, h1, x02-1, y02);
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)  , h1  , x02  , y02  );
                    }
                    else if(y02 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)-1, h1, x-1, y);
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)  , h1  , x  , y  );
                    }
                }
            }
            else
                exit2 = true;

            x02 = x;
            y02 = y;
            X2  -= keys->smoothing;

    }while(!exit1 || !exit2);
}


/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StFunc3" -------------------------------------------------------**/


/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StFunc4" -------------------------------------------------------**/

StFunc4::StFunc4(int* yCoord, int colStr, string* str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : StandardFunction(yCoord, colStr, str, font, ren, coord, id)
{
}

StFunc4::~StFunc4()
{
}

void StFunc4::UpdateStr()
{
    str.assign("y = " + a + "sin(" + b +"x)");
}

void StFunc4::DrawGraph(Keys* keys)
{
        SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );

    int h1 = keys->h2;
    int h2 = keys->h3 + 47;

    bool exit1 = false, exit2 = false;

    double X1 = keys->offsetXarea;
    double X2 = keys->offsetXarea;
    double Y;

    double x, y;

    Y = -1*A*sin(B*X1);
    double x01 = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y01 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;


    Y = -1*A*sin(B*X2);
    double x02 = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y02 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

    X1 += keys->smoothing;
    X2 -= keys->smoothing;

    do
    {
            Y = -1*A*sin(B*X1);
            x = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x < keys->w5+5)
            {
                if(x > keys->w2+5)
                {
                    if(y01 >= h1 && y >= h1)
                    {
                        if(y01 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x01+1, y01, x+1, y);
                            SDL_RenderDrawLine(ren, x01  , y01, x  , y);
                        }
                        else
                        {
                            if(y01 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)+1, h2+1, x01+1, y01+1);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)  , h2  , x01  , y01  );
                            }
                            else if(y01 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)+1, h2+1, x+1, y);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)  , h2  , x  , y);
                            }
                        }
                    }
                    else if(y01 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)+1, h1+1, x01+1, y01);
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)  , h1  , x01  , y01);
                    }
                    else if(y01 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)+1, h1+1, x+1, y);
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)  , h1  , x  , y);
                    }
                }
            }
            else
                exit1 = true;

            x01 = x;
            y01 = y;
            X1 += keys->smoothing;

            Y = -1*A*sin(B*X2);
            x = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x > keys->w2+5)
            {
                if(x < keys->w5+5)
                {
                    if(y02 >= h1 && y >= h1)
                    {
                        if(y02 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x02-1, y02, x-1, y);
                            SDL_RenderDrawLine(ren, x02  , y02, x  , y);
                        }
                        else
                        {
                            if(y02 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)-1, h2, x02-1, y02);
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)  , h2  , x02  , y02  );
                            }
                            else if(y02 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)-1, h2, x-1, y);
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)  , h2  , x  , y  );
                            }
                        }
                    }
                    else if(y02 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)-1, h1, x02-1, y02);
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)  , h1  , x02  , y02  );
                    }
                    else if(y02 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)-1, h1, x-1, y);
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)  , h1  , x  , y  );
                    }
                }
            }
            else
                exit2 = true;

            x02 = x;
            y02 = y;
            X2  -= keys->smoothing;

    }while(!exit1 || !exit2);
}
/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StFunc4" -------------------------------------------------------**/


/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StFunc5" -------------------------------------------------------**/

StFunc5::StFunc5(int* yCoord, int colStr, string* str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : StandardFunction(yCoord, colStr, str, font, ren, coord, id)
{
}

StFunc5::~StFunc5()
{
}

void StFunc5::UpdateStr()
{
    str.assign("y = " + a + "cos(" + b +"x)");
}

void StFunc5::DrawGraph(Keys* keys)
{
        SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );

    int h1 = keys->h2;
    int h2 = keys->h3 + 47;

    bool exit1 = false, exit2 = false;

    double X1 = keys->offsetXarea;
    double X2 = keys->offsetXarea;
    double Y;

    double x, y;

    Y = -1*A*cos(B*X1);
    double x01 = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y01 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;


    Y = -1*A*cos(B*X2);
    double x02 = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y02 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

    X1 += keys->smoothing;
    X2 -= keys->smoothing;

    do
    {
            Y = -1*A*cos(B*X1);
            x = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x < keys->w5+5)
            {
                if(x > keys->w2+5)
                {
                    if(y01 >= h1 && y >= h1)
                    {
                        if(y01 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x01+1, y01, x+1, y);
                            SDL_RenderDrawLine(ren, x01  , y01, x  , y);
                        }
                        else
                        {
                            if(y01 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)+1, h2+1, x01+1, y01+1);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)  , h2  , x01  , y01  );
                            }
                            else if(y01 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)+1, h2+1, x+1, y);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)  , h2  , x  , y);
                            }
                        }
                    }
                    else if(y01 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)+1, h1+1, x01+1, y01);
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)  , h1  , x01  , y01);
                    }
                    else if(y01 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)+1, h1+1, x+1, y);
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)  , h1  , x  , y);
                    }
                }
            }
            else
                exit1 = true;

            x01 = x;
            y01 = y;
            X1 += keys->smoothing;

            Y = -1*A*cos(B*X2);
            x = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x > keys->w2+5)
            {
                if(x < keys->w5+5)
                {
                    if(y02 >= h1 && y >= h1)
                    {
                        if(y02 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x02-1, y02, x-1, y);
                            SDL_RenderDrawLine(ren, x02  , y02, x  , y);
                        }
                        else
                        {
                            if(y02 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)-1, h2, x02-1, y02);
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)  , h2  , x02  , y02  );
                            }
                            else if(y02 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)-1, h2, x-1, y);
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)  , h2  , x  , y  );
                            }
                        }
                    }
                    else if(y02 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)-1, h1, x02-1, y02);
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)  , h1  , x02  , y02  );
                    }
                    else if(y02 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)-1, h1, x-1, y);
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)  , h1  , x  , y  );
                    }
                }
            }
            else
                exit2 = true;

            x02 = x;
            y02 = y;
            X2  -= keys->smoothing;

    }while(!exit1 || !exit2);
}
/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StFunc5" -------------------------------------------------------**/



/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StFunc6" -------------------------------------------------------**/

StFunc6::StFunc6(int* yCoord, int colStr, string* str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : StandardFunction(yCoord, colStr, str, font, ren, coord, id)
{
}

StFunc6::~StFunc6()
{
}

void StFunc6::UpdateStr()
{
    str.assign("y = " + a + "arctg(" + b +"x)");
}

void StFunc6::DrawGraph(Keys* keys)
{
        SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );

    int h1 = keys->h2;
    int h2 = keys->h3 + 47;

    bool exit1 = false, exit2 = false;

    double X1 = keys->offsetXarea;
    double X2 = keys->offsetXarea;
    double Y;

    double x, y;

    Y = -1*A*atan(B*X1);
    double x01 = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y01 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;


    Y = -1*A*atan(B*X2);
    double x02 = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y02 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

    X1 += keys->smoothing;
    X2 -= keys->smoothing;

    do
    {
            Y = -1*A*atan(B*X1);
            x = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x < keys->w5+5)
            {
                if(x > keys->w2+5)
                {
                    if(y01 >= h1 && y >= h1)
                    {
                        if(y01 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x01+1, y01, x+1, y);
                            SDL_RenderDrawLine(ren, x01  , y01, x  , y);
                        }
                        else
                        {
                            if(y01 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)+1, h2+1, x01+1, y01+1);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)  , h2  , x01  , y01  );
                            }
                            else if(y01 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)+1, h2+1, x+1, y);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)  , h2  , x  , y);
                            }
                        }
                    }
                    else if(y01 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)+1, h1+1, x01+1, y01);
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)  , h1  , x01  , y01);
                    }
                    else if(y01 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)+1, h1+1, x+1, y);
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)  , h1  , x  , y);
                    }
                }
            }
            else
                exit1 = true;

            x01 = x;
            y01 = y;
            X1 += keys->smoothing;

            Y = -1*A*atan(B*X2);
            x = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x > keys->w2+5)
            {
                if(x < keys->w5+5)
                {
                    if(y02 >= h1 && y >= h1)
                    {
                        if(y02 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x02-1, y02, x-1, y);
                            SDL_RenderDrawLine(ren, x02  , y02, x  , y);
                        }
                        else
                        {
                            if(y02 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)-1, h2, x02-1, y02);
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)  , h2  , x02  , y02  );
                            }
                            else if(y02 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)-1, h2, x-1, y);
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)  , h2  , x  , y  );
                            }
                        }
                    }
                    else if(y02 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)-1, h1, x02-1, y02);
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)  , h1  , x02  , y02  );
                    }
                    else if(y02 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)-1, h1, x-1, y);
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)  , h1  , x  , y  );
                    }
                }
            }
            else
                exit2 = true;

            x02 = x;
            y02 = y;
            X2  -= keys->smoothing;

    }while(!exit1 || !exit2);
}
/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StFunc6" -------------------------------------------------------**/


/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StFunc7" -------------------------------------------------------**/

StFunc7::StFunc7(int* yCoord, int colStr, string* str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : StandardFunction(yCoord, colStr, str, font, ren, coord, id)
{
}

StFunc7::~StFunc7()
{
}

void StFunc7::UpdateStr()
{
    str.assign("y = " + a + "arcctg(" + b +"x)");
}

void StFunc7::DrawGraph(Keys* keys)
{
        SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );

    int h1 = keys->h2;
    int h2 = keys->h3 + 47;

    bool exit1 = false, exit2 = false;

    double X1 = keys->offsetXarea;
    double X2 = keys->offsetXarea;
    double Y;

    double x, y;

    Y = -1*A*(3.14159-atan(B*X1));
    double x01 = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y01 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;


    Y = -1*A*(3.14159-atan(B*X2));
    double x02 = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y02 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

    X1 += keys->smoothing;
    X2 -= keys->smoothing;

    do
    {
            Y = -1*A*(3.14159-atan(B*X1));
            x = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x < keys->w5+5)
            {
                if(x > keys->w2+5)
                {
                    if(y01 >= h1 && y >= h1)
                    {
                        if(y01 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x01+1, y01, x+1, y);
                            SDL_RenderDrawLine(ren, x01  , y01, x  , y);
                        }
                        else
                        {
                            if(y01 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)+1, h2+1, x01+1, y01+1);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)  , h2  , x01  , y01  );
                            }
                            else if(y01 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)+1, h2+1, x+1, y);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)  , h2  , x  , y);
                            }
                        }
                    }
                    else if(y01 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)+1, h1+1, x01+1, y01);
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)  , h1  , x01  , y01);
                    }
                    else if(y01 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)+1, h1+1, x+1, y);
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)  , h1  , x  , y);
                    }
                }
            }
            else
                exit1 = true;

            x01 = x;
            y01 = y;
            X1 += keys->smoothing;

            Y = -1*A*(3.14159-atan(B*X2));
            x = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x > keys->w2+5)
            {
                if(x < keys->w5+5)
                {
                    if(y02 >= h1 && y >= h1)
                    {
                        if(y02 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x02-1, y02, x-1, y);
                            SDL_RenderDrawLine(ren, x02  , y02, x  , y);
                        }
                        else
                        {
                            if(y02 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)-1, h2, x02-1, y02);
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)  , h2  , x02  , y02  );
                            }
                            else if(y02 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)-1, h2, x-1, y);
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)  , h2  , x  , y  );
                            }
                        }
                    }
                    else if(y02 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)-1, h1, x02-1, y02);
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)  , h1  , x02  , y02  );
                    }
                    else if(y02 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)-1, h1, x-1, y);
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)  , h1  , x  , y  );
                    }
                }
            }
            else
                exit2 = true;

            x02 = x;
            y02 = y;
            X2  -= keys->smoothing;

    }while(!exit1 || !exit2);
}
/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StFunc4" -------------------------------------------------------**/



/** -------------------------------------- НАЧАЛО ОПИСАНИЯ: КЛАСС "StFunc8" -------------------------------------------------------**/

StFunc8::StFunc8(int* yCoord, int colStr, string* str, TTF_Font* font, SDL_Renderer* ren, SDL_Rect* coord, int id) : StandardFunction(yCoord, colStr, str, font, ren, coord, id)
{
}

StFunc8::~StFunc8()
{
}

void StFunc8::UpdateStr()
{
    string t1 = "x²+", t2 = "x+";
    if(b[0] == '-')
        t1 = "x²";
    if(c[0] == '-')
        t2 = "x";
        str.assign("y = " + a + t1 + b + t2 + c);
}


void StFunc8::DrawGraph(Keys* keys)
{
        SDL_SetRenderDrawColor(ren, graphColor.r, graphColor.g, graphColor.b, graphColor.a );

    int h1 = keys->h2;
    int h2 = keys->h3 + 47;


    bool exit1 = false, exit2 = false;

    double X1 = keys->offsetXarea;
    double X2 = keys->offsetXarea;
    double Y;

    double x, y;

    Y = -1*(A*X1*X1+B*X1+C);;
    double x01 = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y01 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;


    Y = -1*(A*X2*X2+B*X2+C);
    double x02 = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
    double y02 = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

    X1 += keys->smoothing;
    X2 -= keys->smoothing;

    do
    {
            Y = -1*(A*X1*X1+B*X1+C);
            x = keys->w4/2+290+keys->scaleX*X1+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x < keys->w5+5)
            {
                if(x > keys->w2+5)
                {
                    if(y01 >= h1 && y >= h1)
                    {
                        if(y01 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x01+1, y01, x+1, y);
                            SDL_RenderDrawLine(ren, x01  , y01, x  , y);
                        }
                        else
                        {
                            if(y01 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)+1, h2+1, x01+1, y01+1);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,y,h2,y,y01)  , h2  , x01  , y01  );
                            }
                            else if(y01 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)+1, h2+1, x+1, y);
                                SDL_RenderDrawLine(ren, x-XX(x,x01,h2,y,y01,y)  , h2  , x  , y);
                            }
                        }
                    }
                    else if(y01 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)+1, h1+1, x01+1, y01);
                        SDL_RenderDrawLine(ren, x-XX(x,x01,h1,y,y01,y)  , h1  , x01  , y01);
                    }
                    else if(y01 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)+1, h1+1, x+1, y);
                        SDL_RenderDrawLine(ren, x01+XX(x,x01,h1,y01,y,y01)  , h1  , x  , y);
                    }
                }
            }
            else
                exit1 = true;

            x01 = x;
            y01 = y;
            X1 += keys->smoothing;

            Y = -1*(A*X2*X2+B*X2+C);
            x = keys->w4/2+290+keys->scaleX*X2+(keys->offsetX-keys->offsetXarea)*keys->scaleX;
            y = keys->height/2+keys->scaleY*Y+(keys->offsetY-keys->offsetYarea)*keys->scaleY;

            if(x > keys->w2+5)
            {
                if(x < keys->w5+5)
                {
                    if(y02 >= h1 && y >= h1)
                    {
                        if(y02 <= h2 && y <= h2)
                        {
                            SDL_RenderDrawLine(ren, x02-1, y02, x-1, y);
                            SDL_RenderDrawLine(ren, x02  , y02, x  , y);
                        }
                        else
                        {
                            if(y02 < h2 && y > h2)
                            {
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)-1, h2, x02-1, y02);
                                SDL_RenderDrawLine(ren, x02-XX(x02,x,h2,y02,y,y02)  , h2  , x02  , y02  );
                            }
                            else if(y02 > h2 && y < h2)
                            {
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)-1, h2, x-1, y);
                                SDL_RenderDrawLine(ren, x+XX(x02,x,h2,y,y02,y)  , h2  , x  , y  );
                            }
                        }
                    }
                    else if(y02 > h1 && y < h1)
                    {
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)-1, h1, x02-1, y02);
                        SDL_RenderDrawLine(ren, x+XX(x02,x,h1,y,y02,y)  , h1  , x02  , y02  );
                    }
                    else if(y02 < h1 && y > h1)
                    {
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)-1, h1, x-1, y);
                        SDL_RenderDrawLine(ren, x02-XX(x02,x,h1,y02,y,y02)  , h1  , x  , y  );
                    }
                }
            }
            else
                exit2 = true;

            x02 = x;
            y02 = y;
            X2  -= keys->smoothing;

    }while(!exit1 || !exit2);
}
/** -------------------------------------- КОНЕЦ ОПИСАНИЯ: КЛАСС "StFunc8" -------------------------------------------------------**/
