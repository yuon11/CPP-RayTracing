
#include <iostream>
#include "Camera.h"
using namespace std;

// Get Camera Origin
Vect3 Camera::getCameraPostion(){ return cam_pos; }

// Get Camera Direction Vector
Vect3 Camera::getCameraDirection(){ return cam_dir; }

// Get Rightmost Camera Point - by default left is 0,0
Vect3 Camera::getCameraRight(){ return cam_right; }

// Get Camera Down position
Vect3 Camera::getCameraDown(){ return cam_down; }

// Default  constructor
Camera::Camera(){
    Vect3 cam_pos(0,0,0); //Origin
    Vect3 cam_dir(0,0,1); //Direction - looking at z-axis
    Vect3 cam_right(0,0,0); //right most point
    Vect3 cam_down(0,0,0); // Down directions
    //float2 tanFOV;
    //tanFOV = float2(0.5,0.5);
};

// User Constructor 
Camera::Camera(Vect3 pos, Vect3 dir, Vect3 right, Vect3 down){
    cam_pos=pos; // Origin
    cam_dir=dir; // Direction
    cam_right=right; // Right Point
    cam_down=down; // Down
}
//float2 tanFOV;

//tanFOV = float2(0.5,0.5);




