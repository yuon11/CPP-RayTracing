#ifndef SQUARE_H
#define SQUARE_H

#include "Object.h"
#include "Vect3.h"
#include "Color.h"
#include "Ray.h"

class Square: public Object{

    private:
        Vect3 center;
        double length;
        double width;
        Color color;
    public:
    Square();

    Square( Vect3, double, double, Color);

    Vect3 getSquareCenter();
    double getSquareArea();
    Color getColor();

    virtual Vect3 getNormalAt(Vect3 point);
    virtual double findIntersection(Ray ray);
};
#endif