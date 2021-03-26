#ifndef Color_H
#define Color_H

// Color class is made of 4 values denoting the red, green, blue and specular values of a color
class Color{

    // Member data representing RGB ans specualr values
    double Red, Green, Blue, Special;
    private:
    
    public:

    // Default Constructor
    Color();

    // Customized constructors
    Color(double);
    Color(double, double, double, double);
    
    //
    // Getters
    //
    // Return red value of object
    double getRed();
    // Return green value of object
    double getGreen();
    // Return blue value of object
    double getBlue();
    // Return specular value of object
    double getSpecial();

   //
   // setters
   //
   // Set Red Value
   void setRed(double redVal);
   // Set Green Value
   void setGreen(double greenVal);
   // Set Blue Value
   void setBlue(double blueVal);
   // Set Special Value
   void setSpecial(double specialVal);

    // Return color brightness based on RGB averages
    double brightness();

    // Clip color - control for light rays hitting color
    Color clip();

    /* --- operator overload functions  ---*/

    Color colorScalar ( double scalar);
    Color colorAverage ( Color color);
    
    // Multiplication
    Color operator * ( double d);
    Color operator * ( Color v);

    // // Division 
    Color operator / ( double d);
    Color operator / ( Color v);

    // // Addition 
    Color operator + ( double d);
    Color operator + ( Color v);

    // // Subtraction 
    Color operator - ( double d);
    Color operator - ( Color v);

    // Helper for debugging
    // friend std::ostream & operator << (std::ostream &os,  Color double &v){
    //     os << v.Red << " " << v.Green << " " << v.Blue;
    //     return os;
    // }

};


#endif