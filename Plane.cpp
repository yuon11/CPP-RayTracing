#include "Vect3.h"
#include "Color.h"
#include "Ray.h"
#include "Plane.h"


// Default plane constructor
Plane::Plane(){
    normal= Vect3(1,0,0);
    distance=0;
    color=Color(0.5,0.5,0.5, 0);
}

// Custom plane constructor
Plane::Plane(Vect3 normalVal, double dist, Color c){
    setPlaneNormal(normalVal);
    setPlaneDistance(dist);
    setColor(c);
}

// Set distance valuse of plane
void Plane::setPlaneDistance(double dist)
{
    distance=dist;
}

// Set Plane normal
void Plane::setPlaneNormal(Vect3 normVal)
{
    normal=normVal;
}

// Set Color of plane
void Plane::setColor(Color c)
{
    color=c;
}

// Return Plane distance 
double Plane::getPlaneDistance(){ return distance; }

// Return Pane Color
Color Plane::getColor(){ return color; }

// Return Normal of plane at given ppoint
Vect3 Plane::getNormalAt(Vect3 point){
    return normal;
}

// Find if given Ray intersects plane
double Plane::findIntersection(Ray ray) {
    
    // Ray direction, where its coming from
    Vect3 ray_direction = ray.getRayDirection();

    // dot product
    double a = ray_direction.dot_product(normal);

    // Teast if ray is parallel to plane
    if (a == 0)
    {
        //Ray Parallel to plane
        return -1;
    }
    else{
        // Liner Algebra EQ for intersection of Ray and Plane
        double b = normal.dot_product(ray.getRayOrigin()+ (normal*distance).negative());
        return -1*b/a;
    }
    
}
