#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "Vect3.h"
#include "Color.h"
#include "Ray.h"


// The plane class inherits from Object, and implements its virtual functions
// Thjis class is primarialy a background
class Plane: public Object{

    // Plane Data members are Normal vector, Distance, and Color
    Vect3 normal;
    double distance;
    Color color;

    private:

    public:

    // Default constructor
    Plane();

    // Custom constructor
    Plane( Vect3, double, Color);

    //
    // Setters
    //

    // Set distance value of plane - distance from camera
    void setPlaneDistance(double);

    // Set Color of plane
    void setPlaneNormal(Vect3);

    // Set Color of plane
    void setColor(Color);

    //
    // Getters 
    //

    // Return distance valuse of plane
    double getPlaneDistance();

    // Return Color of plane
    Color getColor();

    // Return plane normal at a given point
    Vect3 getNormalAt(Vect3 point);

    // Find ray plane intersection
    double findIntersection(Ray ray);
};

#endif