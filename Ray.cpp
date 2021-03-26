#include "Ray.h"
#include "Vect3.h"

// Default constructor
Ray::Ray(){
    setRayOrigin(Vect3(0,0,0));
    setRayDirection(Vect3(1,0,0));
}

// User constructors for Vect3 and double vals
Ray::Ray(double x, double y, double z, Vect3 dir){
    setRayOrigin(Vect3(x,y,z));
    setRayDirection(dir);
}

Ray::Ray(Vect3 o, Vect3 d){
    origin=o;
    direction=d;
}

// Setters
// Set Ray origin vector
void Ray::setRayOrigin(Vect3 v)
{ 
    origin=v; 
}

// Set Ray destination vector
void Ray::setRayDirection(Vect3 v)
{ 
    direction = v; 
}

// Getters
 // Return Ray origin vector
Vect3 Ray::getRayOrigin(){ return origin; }
// Return Ray destination vector
Vect3 Ray::getRayDirection(){ return direction; }
