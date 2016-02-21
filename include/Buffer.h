#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <string>
#include <string.h>

#include <SDL2/SDL.h>

using namespace std;

class Buffer
{
    public:
        Buffer();
       ~Buffer();

        void BufferFunction(SDL_Event*);
        void SetBuffer(string*);

        void Add0();
        void AddPeriod();
        void AddMinus();

    private:
        bool buf;
        string buffer;
        string *pBuffer;
};

#endif // BUFFER_H
