#include "PointLight.h"
#include "Source.h"

PointLight::PointLight()
{
    setLightPosition(Vect3(0,0,0));
    setPower(Vect3(0,10,20));
    setColor(Color(1,1,1,0));
}

PointLight::PointLight(Vect3 pos, Vect3 pow, Color c)
{
    setLightPosition(pos);
    setPower(pow);
    setColor(c);
}

// Set Color of the point light object
void PointLight::setColor(Color c)
{
    color = c;
}

// Set position of the point light object
void PointLight::setLightPosition(Vect3 v)
{
    position = v;
}

// Set power of the point light
void PointLight::setPower(Vect3 pwr)
{
    power = pwr;
}

// Get light instensity at a certain point
Vect3 PointLight::getRadianceAt(Vect3 x){
    
    return power*(1/(x - position).normalize2() / 4 / 3.14);
}

 // Get the direction of light ray at a point
Vect3 PointLight::getLightDirAt(Vect3 x){
    return (position - x).normalize();
}
    
// Return the distance from a given point
float PointLight::getDistanceFrom(Vect3 x){
    return (position-x).magnitude();
}

// Return the color of the light source
Color PointLight::getColor()
{ 
    return color; 
}

// Return light position
Vect3 PointLight::getLightPosition()
{
    return position;
}