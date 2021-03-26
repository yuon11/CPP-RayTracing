#ifndef _SOURCE_H
#define _SOURCE_H

#include "Color.h"
#include "Vect3.h"

class Source{
    public:

    Source(){};

    virtual Vect3 getLightPosition(){ return Vect3(0,0,0); }
    virtual Color getColor() { return Color(1,1,1,0); }
    virtual Vect3 getLightDirAt(Vect3 x){ return Vect3(0,0,0); }

    virtual Vect3 getRadianceAt(Vect3 x)=0;

    virtual float getDistanceFrom(Vect3 x)=0;
};

#endif