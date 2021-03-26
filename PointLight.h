#include "Source.h"
#include "Vect3.h"
#include "Color.h"

// Point light start from a position and focus in a generally narrow direction, with the light's intensity the highest at its center 
class PointLight: public Source {
    
    // Point light will be composed of Position, Power and color    
    Vect3 power;
    Vect3 position;
    Color color;
    
public:
    
    // Default Point Light constructor
    PointLight();

    // Custom constructor ofr point light
    PointLight(Vect3, Vect3, Color);

    // Set Color of the point light object
    void setColor(Color);

    // Set position of the point light object
    void setLightPosition(Vect3);

    // Set power of the point light
    void setPower(Vect3);

    // Get light instensity at a certain point
    Vect3 getRadianceAt(Vect3 x);

    // Get the direction of light ray at a point
    Vect3 getLightDirAt(Vect3 x);

    // Return light position
    Vect3 getLightPosition();

    // Return the color of the object
    Color getColor();

    // Return the distance from a given point
    float getDistanceFrom(Vect3 x);
};