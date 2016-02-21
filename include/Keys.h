#ifndef KEYS_H
#define KEYS_H

#include <iostream>

#include <SDL2/SDL.h>

using namespace std;

class Keys
{
    public:
        Keys(int, int);
       ~Keys();

        /** Функция динамического вычисления и переопределения ключевых значений в зависемости от размера окна **/
        void ChangeKeys(SDL_Window*);

        /* размеры окна */
        int width;          // ширина окна
        int height;         // высота окна

        bool quit;

        /* границы области построения графика и отображения координат */
        int h1, h2, h3, h4;
        int w1, w2, w3, w4, w5;
        int hmenu;

        /* смещения по X и  Y, масштаб */
        int offsetX;        // смещение по оси X
        int offsetY;        // смещение по оси Y
        int offsetXarea;
        int offsetYarea;
        int scaleX;
        int scaleY;    // масштаб

       /* шаг вывода координат */
        int step;

        double smoothing;
};

#endif // KEYS_H
