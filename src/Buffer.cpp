#include "Buffer.h"

Buffer::Buffer()
{
    buf = false;
    pBuffer = &buffer;
}

Buffer::~Buffer()
{
}


void Buffer::SetBuffer(string* str)
{
    pBuffer = str;
}

void Buffer::BufferFunction(SDL_Event* ev)
{
    if(ev->type == SDL_KEYUP)
    {
        buffer.assign(*pBuffer);
        switch(ev->key.keysym.sym)
        {
            case SDLK_1:  { buffer += '1'; break; }
            case SDLK_2:  { buffer += '2'; break; }
            case SDLK_3:  { buffer += '3'; break; }
            case SDLK_4:  { buffer += '4'; break; }
            case SDLK_5:  { buffer += '5'; break; }
            case SDLK_6:  { buffer += '6'; break; }
            case SDLK_7:  { buffer += '7'; break; }
            case SDLK_8:  { buffer += '8'; break; }
            case SDLK_9:  { buffer += '9'; break; }

            case SDLK_KP_1: { buffer += '1'; break; }
            case SDLK_KP_2: { buffer += '2'; break; }
            case SDLK_KP_3: { buffer += '3'; break; }
            case SDLK_KP_4: { buffer += '4'; break; }
            case SDLK_KP_5: { buffer += '5'; break; }
            case SDLK_KP_6: { buffer += '6'; break; }
            case SDLK_KP_7: { buffer += '7'; break; }
            case SDLK_KP_8: { buffer += '8'; break; }
            case SDLK_KP_9: { buffer += '9'; break; }

            case SDLK_0:    { /*Add0()*/; buffer += '0'; break; }
            case SDLK_KP_0: { /*Add0()*/; buffer += '0'; break; }

            case SDLK_MINUS  : { AddMinus(); break; }
            case SDLK_PERIOD : { /*AddPeriod()*/ buffer += '.'; break; }

            case SDLK_KP_MINUS:  { AddMinus();  break; }
            case SDLK_KP_PERIOD: { /*AddPeriod()*/ buffer += '.'; break; }

            case SDLK_BACKSPACE: { if(buffer.size()) buffer.pop_back(); break; }
        }
        pBuffer->assign(buffer);
    }
}

/** Добавление нуля **/
void Buffer::Add0()
{
    if( buffer.size() > 1 )
    {
        buffer += '0';
    }
    else if( !buffer.size() || (buffer.size() == 1 && buffer[0] == '-') )
    {
        buffer += "0.";
    }
}

/** Добавление минуса **/
void Buffer::AddMinus()
{
    if( !buffer.size() )
    {
        buffer += '-';
    }
}

/** Добавление точки **/
void Buffer::AddPeriod()
{
    if( buffer.size() > 1 )
    {
        if( !strchr(buffer.c_str(), '.') )
        {
            buffer += '.';
        }
    }
    else if( !buffer.size() || (buffer.size() == 1 && buffer[0] == '-') )
    {
        buffer += "0.";
    }
}
