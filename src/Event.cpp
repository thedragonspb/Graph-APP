#include "Event.h"

#include "iostream"

Event::Event(Keys* _keys)
{
   std::cout << "КОНСТРУКТОР С ПАРАМЕТРАМИ [Event]" << std::endl;
   keys = _keys;
   tab = 0;
   sdlk_down  = 0;
   sdlk_up    = 0;
   sdlk_left  = 0;
   sdlk_right = 0;
   buttUpDown = 0;
}

Event::~Event()
{
   std::cout << "ДЕСТРУКТОР [Event]" << std::endl;
}

void Event::PollEvent()
{
        switch(keys->setup->GetEv()->type)
        {
            case SDL_KEYDOWN:
            {
                switch(keys->setup->GetEv()->key.keysym.sym)
                {
                    case SDLK_ESCAPE : { keys->quit = true; break; }
                    case SDLK_TAB    : { tab = 1;           break; }

                    /* масштабирование */
                    case SDLK_1: { if(keys->scale + 10 < 70 ) { keys->scale += 10; } break; }
                    case SDLK_2: { if(keys->scale - 10 > 10 ) { keys->scale -= 10; } break; }

                    /* смещение по осям (кнопкна нажата) */
                    case SDLK_DOWN  :  { sdlk_down  = 1; break; }
                    case SDLK_UP    :  { sdlk_up    = 1; break; }
                    case SDLK_RIGHT :  { sdlk_right = 1; break; }
                    case SDLK_LEFT  :  { sdlk_left  = 1; break; }

                    default:
                        break;
                }
                break;
            }

            case SDL_KEYUP:
            {
                switch(keys->setup->GetEv()->key.keysym.sym)
                {
                    case SDLK_TAB: { if(tab == 1) { keys->menuBg = !(keys->menuBg); tab = 0; keys->workspaceStatus = 0; } break; }

                    /* смещение по осям (кнопкна отжата) */
                    case SDLK_DOWN  :  { if( sdlk_down  ) { keys->offsetY -=keys->step; sdlk_down  = 0; } break; }
                    case SDLK_UP    :  { if( sdlk_up    ) { keys->offsetY +=keys->step; sdlk_up    = 0; } break; }
                    case SDLK_RIGHT :  { if( sdlk_right ) { keys->offsetX -=keys->step; sdlk_right = 0; } break; }
                    case SDLK_LEFT  :  { if( sdlk_left  ) { keys->offsetX +=keys->step; sdlk_left  = 0; } break; }

                    default:
                        break;
                }
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                switch(keys->setup->GetEv()->button.button)
                {
                    case SDL_BUTTON_LEFT:
                    {
                        /** Область расположениия всех кнопок **/
                        if(  keys->setup->GetEv()->button.x > keys->workspace.x
                            &&  keys->setup->GetEv()->button.x < keys->workspace.w )
                        {
                            /* Кнопки левого ряда */
                            if ( keys->setup->GetEv()->button.x < keys->rectButtonLeft.x + keys->rectButtonLeft.w )
                            {
                                /* Кнопки 'Вверх' и 'Вниз' */
                                if( keys->setup->GetEv()->button.y > keys->rectButtonScrollUp.y &&  keys->setup->GetEv()->button.y < keys->rectButtonScrollUp.y + keys->rectButtonScrollUp.h && keys->scroll )
                                {
                                    if( keys->setup->GetEv()->button.x < keys->rectButtonScrollUp.x + keys->rectButtonScrollUp.w )
                                    {
                                        buttUpDown = 1;
                                    }
                                    if( keys->setup->GetEv()->button.x > keys->rectButtonScrollDown.x )
                                    {
                                        buttUpDown = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            case SDL_MOUSEBUTTONUP:
            {
                switch(keys->setup->GetEv()->button.button)
                {
                    case SDL_BUTTON_LEFT:
                    {
                        /** Область расположениия всех кнопок **/
                        if(  keys->setup->GetEv()->button.x > keys->workspace.x
                         &&  keys->setup->GetEv()->button.x < keys->workspace.w )
                        {
                            /* Кнопки левого ряда */
                            if ( keys->setup->GetEv()->button.x < keys->rectButtonLeft.x + keys->rectButtonLeft.w )
                            {
                                /* Кнопка 'По точкам' */
                                if( keys->setup->GetEv()->button.y > keys->rectButtonLeft.y && keys->setup->GetEv()->button.y < keys->rectButtonLeft.y + keys->rectButtonLeft.h && keys->menuBg )
                                {
                                    keys->menuBg = !(keys->menuBg);
                                    keys->workspaceStatus = 0;
                                    keys->scroll = 0;
                                }
                                /* Кнопка 'Добавить' */
                                if( keys->setup->GetEv()->button.y > keys->rectButtonAdd.y &&  keys->setup->GetEv()->button.y < keys->rectButtonAdd.y + keys->rectButtonAdd.h )
                                {
                                    keys->workspaceStatus = 1;
                                }
                                /* Кнопки 'Вверх' и 'Вниз' */
                                if( keys->setup->GetEv()->button.y > keys->rectButtonScrollUp.y &&  keys->setup->GetEv()->button.y < keys->rectButtonScrollUp.y + keys->rectButtonScrollUp.h && keys->scroll && buttUpDown)
                                {
                                    if( keys->setup->GetEv()->button.x < keys->rectButtonScrollUp.x + keys->rectButtonScrollUp.w && keys->scroll >= 2)
                                    {
                                        keys->iterElement --;
                                    }
                                    if( keys->setup->GetEv()->button.x > keys->rectButtonScrollDown.x && keys->scroll <= 2)
                                    {
                                        keys->iterElement ++;
                                    }
                                    buttUpDown = 0;
                                }

                            }
                            /* Кнопки правого ряда */
                            if( keys->setup->GetEv()->button.x > keys->rectButtonRight.x )
                            {
                                /* Кнопка 'Функция' */
                                if( keys->setup->GetEv()->button.y < keys->rectButtonRight.y + keys->rectButtonRight.h && keys->setup->GetEv()->button.y > keys->rectButtonRight.y && !keys->menuBg)
                                {
                                    keys->menuBg = !(keys->menuBg);
                                    keys->workspaceStatus = 0;
                                }
                                /* Кнопка 'Удалить' */
                                if( keys->setup->GetEv()->button.y > keys->rectButtonDelete.y && keys->setup->GetEv()->button.y < keys->rectButtonDelete.y + keys->rectButtonDelete.h )
                                {
                                    keys->workspaceStatus = 2;
                                    keys->scroll = 0;
                                }
                                /* Кнопка 'Назад' */
                                if( keys->setup->GetEv()->button.y > keys->rectButtonBack.y  && keys->setup->GetEv()->button.y < keys->rectButtonBack.y + keys->rectButtonBack.h )
                                {
                                    keys->workspaceStatus = 0;
                                    keys->scroll = 0;

                                }
                            }
                        }
                    }
                }
            }
    }
}
