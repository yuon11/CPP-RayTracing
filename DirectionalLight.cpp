#include "Source.h"
#include "DirectionalLight.h"

// Default Light Constructor
DirectionalLight::DirectionalLight()
{
    setRadiance(Vect3(0.5,0.5,0.5));
    setLightDirection(Vect3(0,0,1));
    setColor(Color(1,1,1,0));
}

// Custom Light Constructor
DirectionalLight::DirectionalLight(Vect3 dir, Vect3 rad, Color c){
    setRadiance(rad);
    setLightDirection(dir);
    setColor(c);
}

// set light Direction for directional lighting
void DirectionalLight::setLightDirection(Vect3 v)
{
    direction = v;
}

// set the color of the light source
void DirectionalLight::setColor(Color c)
{
    color = c;
}

// set the radiance of the light source
void DirectionalLight::setRadiance(Vect3 v)
{
    radiance = v;
}

// Return the direction of this light source 
Vect3 DirectionalLight::getLightPosition(){
    return direction;
}

// Return the light radiance
Vect3 DirectionalLight::getRadianceAt(Vect3 x){
    return radiance;
}

// Get light direction
Vect3 DirectionalLight::getLightDirAt(Vect3 x){
    return direction;
}

// Return the light distance. In this case the light poisition is a set distance of 9k away
float DirectionalLight::getDistanceFrom(Vect3 x){
    return 90000.0;
}


// Return the color of the light source
Color DirectionalLight::getColor()
{ 
    return color; 
}

