#include "Keys.h"

Keys::Keys(int _width, int _height)
{
    cout << "КОНСТРУКТОР С ПАРАМЕТРАМИ [ Keys       ]" << endl;

    width  = _width;
    height = _height;

    quit = false;

    /** КООРДИНАТНАЯ ПЛОСКОСТЬ **/
    /* Инициализация границ области построения графика и отображения координат */
    h1 = 10;
    h2 = 48;
    h3 = height-92;
    h4 = height-20;
    w1 = 290;
    w2 = 330;
    w3 = width-290-90;
    w4 = width-290-10;
    w5 = width-53;

    /* смещения по X и  Y, масштаб */
    offsetX = 0;
    offsetY = 0;
    offsetXarea = 0;
    offsetYarea = 0;
    scaleX   = 15;
    scaleY   = 15;

    /* шаг вывода координат */
    step = 4;
    /** координатная плоскость **/
}

Keys::~Keys()
{
    cout << "ДЕСТРУКТОР [ Keys       ]" << endl;
}

/** Функция динамического вычисления и переопределения ключевых значений в зависемости от размера окна**/

void Keys::ChangeKeys(SDL_Window* win)
{
    SDL_GetWindowSize(win, &width, &height);

    if( width < 600 || height < 300 )
    {
        if( width < 600 )
            width = 600;
        if( height < 300 )
            height = 300;
        SDL_SetWindowSize(win, width, height);
    }

    if(scaleX < 20)
    {
        step = 4;
        smoothing = 0.2;
    }
    else if(scaleX < 40)
    {
        step = 2;
        smoothing = 0.1;
    }
    else
    {
        smoothing = 0.05;
        step = 1;
    }

    h3 = height-92;
    h4 = height-20;

    w3 = width-290-90;
    w4 = width-290-10;
    w5 = width-53;
}
