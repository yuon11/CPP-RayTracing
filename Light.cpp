#include "Light.h"
#include "Source.h"

// Default Constructor
Light::Light(){
    setLightPosition(Vect3(0,0,0));
    setColor(Color(1,1,1,0));
}

// Custom constructor
Light::Light(Vect3 p, Color c){
    setLightPosition(p);
    setColor(c);
}


// set light position
void Light::setLightPosition(Vect3 p)
{
    position = p;
}

// set the color of the light source
void Light::setColor(Color c)
{
    color = c;
}

// Return light direction at a given poinbt x
Vect3 Light::getLightDirAt(Vect3 x){
    return (position - x).normalize();
}

// Return light position/origin
Vect3 Light::getLightPosition()
{ 
    return position; 
}

// Return the color of the light source
Color Light::getColor()
{ 
    return color; 
}

// Return light radiance at a give point
Vect3 Light::getRadianceAt(Vect3 x)
{
    return (1/(x - position).normalize2() / 4 / 3.14);
};

// Get light distance from given point
float Light::getDistanceFrom(Vect3 x)
{
    return (position-x).magnitude();
};