#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Vect3.h"


// Default Constructor
Vect3::Vect3(){
    x=0.0; 
    y=0; 
    z=0;
}

// Custom Constructor for a single value
Vect3::Vect3(double n){
    x=n; 
    y=n; 
    z=n;
}

// Custom constructor 
Vect3::Vect3(double a, double b, double c){
    x=a; 
    y=b; 
    z=c;
}
        

// Getters
double Vect3::getx()  {return x; }
double Vect3::gety()  {return y; }
double Vect3::getz()  {return z; }

/* --- operator overload functions ---*/

// Multiply 
// Define multiplication for a Vect3 obj
Vect3 Vect3::operator * ( double d)  {
    return Vect3(x*d, y*d, z*d);
}
Vect3 Vect3::operator * ( Vect3 v){
    return Vect3(x*v.x, y*v.y, z*v.z);
}

// Division 
// Define division for a Vect3 obj
Vect3 Vect3::operator / ( double d)  {
    return Vect3(x/d, y/d, z/d);
}
Vect3 Vect3::operator / ( Vect3 v){
    return Vect3(x/v.x, y/v.y, z/v.z);
}


// Addition 
// Define Addition for a Vect3 obj
Vect3 Vect3::operator+( double d)  {
    return Vect3(x+d, y+d, z+d);
}
Vect3 Vect3::operator + ( Vect3 v){
    return Vect3(x+v.x, y+v.y, z+v.z);
}

// Addition 
// Define Add and Sum for a Vect3 obj
Vect3 Vect3::operator += ( double d)  {
    return Vect3(x += d, y += d, z += d);
}
Vect3 Vect3::operator += ( Vect3 v){
    return Vect3(x+=v.x, y+=v.y, z+=v.z);
}


// Subtraction 
// Define Subtraction for a Vect3 obj
Vect3 Vect3::operator - ( double d)  {
    return Vect3(x-d, y-d, z-d);
}
Vect3 Vect3::operator - ( Vect3 v){
    return Vect3(x-v.x, y-v.y, z-v.z);
}

// friend std::ostream  operator << (std::ostream os,  Vect3 v){
//     os << v.x << " " << v.y << " " << v.z;
//     return os;
// }

// Dot Product
// Calculate the dot product of given vectors
double Vect3::dot_product( Vect3 v)  {
    return x*v.x + y*v.y + z*v.z;
}

// Calculate the dot product of given vectors
Vect3 Vect3::cross_product( Vect3 v)  {
    return Vect3(y*v.z - z*v.y, 
    z*v.x - x*v.z, 
    x*v.y - y*v.x);
}

// Calculate the magnituge
double Vect3::magnitude()  {
    return sqrt((x*x) + (y*y) + (z*z));
}

// Use class data to normalize 
Vect3 Vect3::normalize(){
    double mag = magnitude();
    return Vect3(x/mag, y/mag, z/mag);
}

// Nomalized then applying the sqrt
float Vect3::normalize2()
{
    return x*x+y*y+z*z;
}

Vect3 Vect3::negative(){
    return Vect3(-x,-y,-z);
}

// std::ostream  operator << (std::ostream os,  Vect3 v){
//     os << v.x << " " << v.y << " " << v.z;
//     return os;
// }