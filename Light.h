#ifndef LIGHT_H
#define LIGHT_H

#include "Vect3.h"
#include "Color.h"
#include "Source.h"

// Light Class is a Subclass of Source. This particular light is sun lgiht source
class Light: public Source{

    // Light position and Color. 
    Vect3 position;
    Color color;

    private:

    public:

    // Default Constructor
    Light();

    // Light Position and Color are given in this constructor
    Light( Vect3, Color);

    //
    // Setter
    //

    // Return light position
    void setLightPosition(Vect3);

    // Return the color of the light source
    void setColor(Color);

    //
    // Getter
    //

    // Return light position
    Vect3 getLightPosition();

    // Return the color of the light source
    Color getColor();

    // Member Functions

    // Return light direction at a given poinbt x
    Vect3 getLightDirAt(Vect3 x);

    // Return light radiance at a given point
    Vect3 getRadianceAt(Vect3 x);

    // Return distance from given point
    float getDistanceFrom(Vect3 x);
};

#endif