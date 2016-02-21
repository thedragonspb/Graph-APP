#ifndef PARABOLA_H
#define PARABOLA_H

#include "Graph.h"


class Parabola : public Graph
{
    public:
        Parabola(double _a, double _b, double _c, Keys* _keys);
        ~Parabola();
        void DrawGraph();
    private:
        double a;
        double b;
        double c;

};

#endif // PARABOLA_H
