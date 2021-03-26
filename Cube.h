#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "Object.h"
#include "Vect3.h"
#include "Color.h"
#include "Ray.h"
#include "Triangle.h"

using namespace::std;

// Cube class will be defined by 2 point, drawn as triangles for each side
class Cube: public Object {

    public:
        // Corner1 and 2 will bound our square
        Vect3 corner1, corner2;

        // Front side
        Vect3 cornerA, cornerB, cornerC;
        
        // Backside
        Vect3 cornerD, cornerE, cornerF;

        vector<Object*> cube_triangles;

        Color color;

        Cube();
        Cube(Vect3, Vect3, Color);

        void setCornerA(Vect3);
        void setCornerB(Vect3);
        void setColor(Color c);
        void setTriangleSides();

        //Return object normal at point
        virtual Vect3 getNormalAt(Vect3 point);
        
        // Find intersection of object and ray
        virtual double findIntersection(Ray ray);
        
        // Return Color of object
        virtual Color getColor();
};
#endif