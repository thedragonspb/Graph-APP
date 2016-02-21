#ifndef EVENT_H
#define EVENT_H

#include "Keys.h"

class Event
{
    public:
        Event(Keys* _keys);
       ~Event();

        /** Функция для обработки событий **/
        void PollEvent();

    private:
        Keys *keys;
        bool tab;
        bool sdlk_down, sdlk_up, sdlk_left, sdlk_right;
        bool buttUpDown;
};

#endif // EVENT_H
