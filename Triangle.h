#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Vect3.h"
#include "Color.h"
#include "Ray.h"

// 2 Dimensional Triangle object
class Triangle: public Object {

    public:
        // Triangle is a one sided obj with 3 sides, a normal, a distance, and color
        Vect3 a, b, c;
        Vect3 normal;
        double distance;
        Color color;

        // Default constructor
        Triangle();

        // Custom Constructor
        Triangle(Vect3, Vect3, Vect3, Color);

        // Set Triangle Normal
        void setTriangleNormal();

        // Set Triangle Distance
        void setTriangleDistance();
        
        // Set object color
        void setColor(Color c);

        // Get Triangle Normal
        Vect3 getTriangleNormal();

        // Get Distance of triangle
        double getTriangleDistance();
        
        // Get object normal at location
        virtual Vect3 getNormalAt(Vect3 point);
        
        // Find intersection of object and ray
        virtual double findIntersection(Ray ray);
        
        // Return Color of object
        Color getColor();
};
#endif