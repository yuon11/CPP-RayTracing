 #ifndef Vect3_H
#define Vect3_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <algorithm>

class Vect3{


    private:
        double x, y, z;
    public:
        Vect3();
            
        Vect3(double);
            
        Vect3(double, double, double);
                
        
        // Getters
        double getx();
        double gety();
        double getz();

        /* --- operator overload functions ---*/
        
        // Multiply 

        Vect3 operator * ( double d);
        Vect3 operator * ( Vect3 v);

        // Division 

        Vect3 operator / ( double d);
        Vect3 operator / ( Vect3 v);


        // // Addition 
        Vect3 operator + ( double d);
        Vect3 operator + ( Vect3 v);

        // Plus equals operator
        Vect3 operator += ( double d);
        Vect3 operator += ( Vect3 v);


        // // Subtraction 
        Vect3 operator - ( double d);
        Vect3 operator - ( Vect3 v);


        // Dot Product
        double dot_product( Vect3 v);

        Vect3 cross_product( Vect3 v);

        double magnitude();

        // //  serves as an explicit statement of the implicit variable
        // // Setting the xyz to unit length 1
        Vect3 normalize();
        float normalize2();

        Vect3 negative();
        //friend std::ostream  operator << (std::ostream os,  Vect3 v);

};





#endif