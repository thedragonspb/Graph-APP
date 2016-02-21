#include "BGEvent.h"

BGEvent::BGEvent(Keys* _keys, SDL_Setup* _sdl_s)
{
    keys  = _keys;
    sdl_s = _sdl_s;
    scaleX_down = false;
    scaleY_down = false;
}

BGEvent::~BGEvent()
{

}

void BGEvent::Event()
{
    switch(sdl_s->GetEv()->type)
    {
        case SDL_KEYDOWN:
        {
            switch(sdl_s->GetEv()->key.keysym.sym)
            {
                case SDLK_KP_5:
                {
                    scaleX_down = true;
                    break;
                }
                case SDLK_KP_6:
                {
                    scaleY_down = true;
                    break;
                }
            }
        }
        break;

        case SDL_KEYUP:
        {
            switch(sdl_s->GetEv()->key.keysym.sym)
            {

                case SDLK_q:
                {
                    keys->quit = true;
                    cout << keys->quit << endl;
                    break;
                }

                /* масштабирование */
                case SDLK_KP_PLUS:
                {
                    if(scaleX_down && keys->scaleX + 10 < 100)
                        keys->scaleX += 10;
                    else if(scaleY_down && keys->scaleY + 10 < 100)
                        keys->scaleY += 10;
                    else if(keys->scaleX + 10 < 100 && keys->scaleY + 10 < 100)
                    {
                        keys->scaleX += 10;
                        keys->scaleY += 10;
                    }
                    break;
                }

                case SDLK_KP_MINUS:
                {
                    if(scaleX_down && keys->scaleX - 9 > 10)
                        keys->scaleX -= 10;
                    else if(scaleY_down && keys->scaleY - 9 > 10)
                        keys->scaleY -= 10;
                    else if(keys->scaleX - 5 > 5 && keys->scaleY - 5 > 5)
                    {
                        keys->scaleX -= 5;
                        keys->scaleY -= 5;
                    }
                    break;
                }

                /* смещение по осям (кнопкна отжата) */
                case SDLK_DOWN  :
                {
                    keys->offsetY --;
                    if(keys->height/2+keys->offsetY*keys->scaleY < keys->h2 || keys->offsetYarea != 0)
                    {
                        keys->offsetYarea ++;
                    }
                    break;

                }
                case SDLK_UP    :
                {
                    keys->offsetY ++;
                    if(keys->height/2+keys->offsetY*keys->scaleY > keys->h3+47 || keys->offsetYarea != 0)
                    {
                        keys->offsetYarea --;
                    }
                    break;
                }
                case SDLK_RIGHT :
                {
                    keys->offsetX --;
                    if((keys->w4)/2+290+keys->offsetX*keys->scaleX < keys->w2 || keys->offsetXarea != 0)
                    {
                        keys->offsetXarea ++;
                    }
                    break;
                }
                case SDLK_LEFT  :
                {
                    keys->offsetX ++;
                    if((keys->w4)/2+290+keys->offsetX*keys->scaleX > keys->w5 || keys->offsetXarea != 0)
                    {
                        keys->offsetXarea --;
                    }
                    break;
                }

                case SDLK_KP_5:
                {
                    scaleX_down = false;
                    break;
                }
                case SDLK_KP_6:
                {
                    scaleY_down = false;
                    break;
                }
                default:
                    break;
            }
            break;
        }
    }
}
