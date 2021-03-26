#ifndef _OBJECT_H
#define _OBJECT_H

#include "Vect3.h"
#include "Color.h"
#include "Ray.h"

// Superclass for the Various shape objects to be created
class Object{
    private:

    public:
        // Constructor
        Object(){};
        // Set the object color
        virtual void setColor(Color){};

        // virtual Return color member func 
        virtual Color getColor(){ return Color(0.0,0.0,0.0,0); }

        // virtual Function to fin normal of the object 
        virtual Vect3 getNormalAt(Vect3 point){ return Vect3(0,0,0); }

        // Intersection finding equation that must be implemented by each class
        virtual double findIntersection(Ray ray){
            return 0;
        }

};



#endif
