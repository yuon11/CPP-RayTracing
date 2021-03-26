#include "Source.h"
#include "Vect3.h"
#include "Color.h"

class DirectionalLight: public Source {

    // Directional light will be composed of only the radiance, direction and color    
    Vect3 radiance;
    Vect3 direction;
    Color color;
    
public:
    // Default Light Constructor
    DirectionalLight();

    // Custom Construction
    DirectionalLight(Vect3, Vect3, Color);

    // Set Light color
    void setColor(Color);

    
    void setLightDirection(Vect3);
    void setRadiance(Vect3);

    // Get Radiance of light at a point
    Vect3 getRadianceAt(Vect3 x);

    // Get light direction at a given point
    Vect3 getLightDirAt(Vect3 x);

    // Return the light distance. In this case the light poisition is a set distance of 9k away
    float getDistanceFrom(Vect3 x);

    // Return the direction of this light source 
    Vect3 getLightPosition();

    // Return the color of the light source
    Color getColor();
    
};