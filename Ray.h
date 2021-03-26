#ifndef RAY_H
#define RAY_H

#include "Vect3.h"

// Ray class is a composition of 2 Vrct3 objects
class Ray{

    // Ray origin 
    Vect3 origin;

    // Ray direction
    Vect3 direction;

    private:

    public:
        // Default constructor
        Ray();

        // User constructors for Vect3 and double vals
        Ray( double, double, double, Vect3=(1,0,0));
        Ray( Vect3, Vect3);

        //
        // Setters
        //
        // Set Ray origin vector
        void setRayOrigin(Vect3);
        
        // Return Ray destination vector
        void setRayDirection(Vect3);

        // Getters
        // Return Ray origin vector
        Vect3 getRayOrigin(); 

        // Return Ray destination vector
        Vect3 getRayDirection();

};

#endif