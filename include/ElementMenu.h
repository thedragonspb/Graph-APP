#ifndef ELEMENTMENU_H
#define ELEMENTMENU_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class BaseElementMenu
{
    public:
        BaseElementMenu(SDL_Renderer* _ren, SDL_Rect* _coord, int _id)
        {
            ren     = _ren;
            coord   = *_coord;
            id      = _id;
            backlit = false;
            updown  = false;
        }

        virtual void DrawElement() = 0;

        int EventElement(SDL_Event* ev)
        {
            if( ev->button.x > coord.x && ev->button.x < coord.x + coord.w
             && ev->button.y > coord.y && ev->button.y < coord.y + coord.h )
            {
                backlit = true;

                if(ev->type == SDL_MOUSEBUTTONDOWN)
                    updown = true;

                if( ev->type == SDL_MOUSEBUTTONUP && updown)
                {
                    ev->window.event = SDL_WINDOWEVENT_EXPOSED;
                	SDL_PushEvent(ev);
                    updown = false;
                    return id;
                }
                else
                    return -1;
            }
            else
            {
                backlit = false;
                return -1;
            }
        }

    protected:
        SDL_Renderer* ren;
        SDL_Rect coord;
        SDL_Color bColor[2];
        bool backlit;

    private:
        int id;
        bool updown;
};

class ElementMenu : public BaseElementMenu
{
    public:
        ElementMenu(SDL_Renderer* ren, SDL_Rect* coord, TTF_Font* _font, int id) : BaseElementMenu(ren, coord, id)
        {
            font    =  _font;
        }

    virtual void DrawElement(){}

    protected:
        TTF_Font *font;
        SDL_Texture *elTexture;
        SDL_Surface *elSurface;
        SDL_Rect elStrCoord;
        SDL_Color tColor[3];
        string str;
};

class StrElementMenu : public ElementMenu
{
    public:
       StrElementMenu(string* _str, SDL_Renderer* ren, SDL_Rect* coord, TTF_Font* font, int id) : ElementMenu(ren, coord, font, id)
       {
            str = *_str;
            tColor[0] = { 189, 200, 229, 100 };
            tColor[1] = { 235, 238, 235, 115 };
            bColor[1] = { 189, 214, 229, 100 };
       }

       void DrawElement(bool line)
       {
            bool c = 0;

            if(line)
            {
                SDL_SetRenderDrawColor(ren, bColor[1].r, bColor[1].g, bColor[1].b, bColor[1].a);
                SDL_RenderDrawLine(ren, 25, coord.y + coord.h + 5, 266, coord.y + coord.h + 5);
                SDL_RenderDrawLine(ren, 25, coord.y + coord.h + 4, 266, coord.y + coord.h + 4);
            }
            elSurface = TTF_RenderUTF8_Blended(font, str.c_str() , tColor[c]);
            elTexture = SDL_CreateTextureFromSurface(ren, elSurface);
            elStrCoord = {coord.x, coord.y, elSurface->w, elSurface->h};
            SDL_RenderCopy(ren, elTexture, NULL, &elStrCoord);

            SDL_FreeSurface(elSurface);
            SDL_DestroyTexture(elTexture);
       }

       void SetStr(string _str)
       {
            str.assign(_str);
       }
};

#endif // ELEMENTMENU_H
