#include "Parabola.h"

#include "iostream"
#include "SDL2/SDL.h"

Parabola::Parabola(double _a, double _b, double _c, Keys* _keys) : Graph(_keys)
{
    std::cout << "КОНСТРУКТОР С ПАРАМЕТРАМИ [Parabola]" << std::endl;
    a = _a;
    b = _b;
    c = _c;
}

Parabola::~Parabola()
{
    std::cout << "ДЕСТРУКТОР [Parabola]" << std::endl;

}

void Parabola::DrawGraph()
{
    exit1 = false;
    exit2 = false;
    bool temp = false;
    X1 = -0.01;
    X2 = 0.01;
    SDL_SetRenderDrawColor(keys->setup->GetRen(), 255, 20, 10, 0 );
    Y = -(a*X1*X1+b*X1+c);
    x1_0 = (int)(keys->w4/2+keys->w1+keys->scale*X1)+keys->offsetX*keys->scale;
    y1_0 = (int)(keys->height/2+keys->scale*Y)+keys->offsetY*keys->scale;
    Y = -(a*X2*X2+b*X2+c);
    x2_0 = (int)(keys->w4/2+keys->w1+keys->scale*X2)+keys->offsetX*keys->scale;
    y2_0 = (int)(keys->height/2+keys->scale*Y)+keys->offsetY*keys->scale;

    do
    {
        if(!exit1)
        {
            Y = -(a*X1*X1+b*X1+c);
            x1 = (int)(keys->w4/2+keys->w1+keys->scale*X1)+keys->offsetX*keys->scale;
            y1 = (int)(keys->height/2+keys->scale*Y)+keys->offsetY*keys->scale;

            if(x1 > keys->w2)
            {
                SDL_RenderDrawLine(keys->setup->GetRen(), x1_0, y1_0, x1, y1);
            }
            else
                exit1 = true;

            x1_0 = x1;
            y1_0 = y1;
        }
      if(!exit2)
        {
            Y = -(a*X2*X2+b*X2+c);
            x1 = (int)(keys->w4/2+keys->w1+keys->scale*X2)+keys->offsetX*keys->scale;
            y1 = (int)(keys->height/2+keys->scale*Y)+keys->offsetY*keys->scale;

            if(x1 < keys->w5)
            {
                SDL_RenderDrawLine(keys->setup->GetRen(), x2_0, y2_0, x1, y1);
            }
            else
                exit2 = true;

            x2_0 = x1;
            y2_0 = y1;
        }

          if(keys->scale < 25)
          {
            X1 -= 0.01;
            X2 += 0.01;
          }
          else
          {
            X1 -= 0.01;
            X2 += 0.01;
          }


    }while(!exit1 || !exit2);
}
