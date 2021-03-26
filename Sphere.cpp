#include "Sphere.h"

#include <stdlib.h>
#include <stdio.h>

using namespace std;

// Default Constructor
Sphere::Sphere(){
    setSphereCenter(Vect3(0,0,0));
    setSphereRadius(1.0);
    setColor(Color(0.5,0.5,0.5, 0));
}

// Custom Sphere constructor
Sphere::Sphere(Vect3 centerVal, double rad, Color c){
    setSphereCenter(centerVal);
    setSphereRadius(rad);
    setColor(c);
}

void Sphere::setSphereCenter(Vect3 center_val)
{
    center = center_val;
}

void Sphere::setSphereRadius(double rad)
{
    radius = rad;
}

void Sphere::setColor(Color c)
{   
    color = c;
}

Vect3 Sphere::getSphereCenter(){ return center; }
double Sphere::getSphereRadius(){ return radius; }
Color Sphere::getColor(){ return color; }

Vect3 Sphere::getNormalAt(Vect3 point){
    //Sphere normal always points away from center
    Vect3 normalVec = point + (center.negative()).normalize();
    return normalVec;
}

double Sphere::findIntersection(Ray ray){
    //
    // Take Ray Origin into account
    //
    Vect3 rayOrigin = ray.getRayOrigin();
    double rayOriginX = rayOrigin.getx();
    double rayOriginY = rayOrigin.gety();
    double rayOriginZ = rayOrigin.getz();

    //
    // Take Ray Dir into account
    //
    Vect3 rayDirection = ray.getRayDirection();
    double rayDirectionX = rayDirection.getx();
    double rayDirectionY = rayDirection.gety();
    double rayDirectionZ = rayDirection.getz();

    //
    // Take Sphere Center into account
    //
    Vect3 sphereCenter = center;
    double sphereCenterX = sphereCenter.getx();
    double sphereCenterY = sphereCenter.gety();
    double sphereCenterZ = sphereCenter.getz();

    double a = 1; //normalized
    double b = (2*(rayOriginX - sphereCenterX)*rayDirectionX ) + (2*(rayOriginY - sphereCenterY)*rayDirectionY ) + (2*(rayOriginZ - sphereCenterZ)*rayDirectionZ );
    double c = pow(rayOriginX - sphereCenterX, 2) + pow(rayOriginY - sphereCenterY, 2) + pow(rayOriginZ - sphereCenterZ, 2) - (radius*radius);

    double discriminant = b*b - 4*c; 

    if (discriminant > 0)
    {
        //Ray intersects plane
        //first root
        double root1 = ((-1*b - sqrt(discriminant))/2) - 0.0000001;

        if (root1 > 0)
        {   
            return root1;
        }
        else
        {   
            // second root is smallest positive
            double root2= ((sqrt(discriminant) - b)/2) - 0.0000001;
            return root2;
        }
    }
    else
    {
        //ray missed sphere
        return -1;
    }  
}

