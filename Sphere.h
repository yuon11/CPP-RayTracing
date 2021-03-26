#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Vect3.h"
#include "Color.h"
#include "Ray.h"

class Sphere: public Object{

    private:
        Vect3 center;
        double radius;
        Color color;
    public:
    Sphere();

    Sphere( Vect3, double, Color);

    void setSphereCenter(Vect3);
    void setSphereRadius(double);
    void setColor(Color);


    Vect3 getSphereCenter();
    double getSphereRadius();
    Color getColor();

    virtual Vect3 getNormalAt(Vect3 point);
    virtual double findIntersection(Ray ray);
};
#endif