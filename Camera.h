#ifndef __Camera__H
#define __Camera__H

#include <iostream>
#include "Vect3.h"

// The Camera Class is used as a reference point for the user perspective when the scene is drawn
class Camera {
    
    // Camera variables are vectors representing the relative coordinates of the camera
    Vect3 cam_pos, cam_dir, cam_right, cam_down;
    
    public:

    // Default Constructor
    Camera();
    Camera(Vect3, Vect3, Vect3, Vect3);

    // Get Camera Origin
    Vect3 getCameraPostion();

    // Get Camera Direction Vector
    Vect3 getCameraDirection();
    
    // Get Rightmost Camera Point - by default left is 0,0
    Vect3 getCameraRight();

    // Get Camera Down position
    Vect3 getCameraDown();
};


#endif
