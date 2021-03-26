#include "Color.h"

// Default color constructor is Grey
Color::Color(){ 
    Red=0.5;
    Green=0.5; 
    Blue=0.5;
    Special=0.0;
}

// Set all values for the color to n
Color::Color(double n){
    Red=n; 
    Green=n; 
    Blue=n; 
    Special=n;
}

// Each value is specified, as well as the special
Color::Color(double R, double G, double B, double S){
    
    Red=R; 
    Green=G; 
    Blue=B; 
    Special=S;
}


// Getters
// Return red value of object
double Color::getRed()  { return Red; }

// Return green value of object
double Color::getGreen()  { return Green; }

// Return Blue value of object
double Color::getBlue()  { return Blue; }

// Return Special value of object
double Color::getSpecial() { return Special; }


// setters
// Return Red value of object
void Color::setRed(double redVal) { Red=redVal; }

// Return Green value of object
void Color::setGreen(double greenVal) { Green=greenVal; }

// Return Blue value of object
void Color::setBlue(double blueVal) { Blue=blueVal; }

// Return Special value of object
void Color::setSpecial(double specialVal) { Special=specialVal; }

// Brightness is determined by RGB average
double Color::brightness(){
    return(Red + Green + Blue)/3;
}

// Clipping determines how the color is affected by incoming light & lightcolor and how/whether to shade it
Color Color::clip(){

    // sum light values
    double alllight = Red + Green + Blue;
    double excessLight = alllight-3;
    
    // If there is excess light, this area is colored, and hit by light so return color
    if (excessLight>0)
    {
        Red=Red + excessLight*(Red/alllight);
        Green=Green + excessLight*(Green/alllight);
        Blue=Blue + excessLight*(Blue/alllight);
    }

    // Bound colors high or low to a specified range
    if(Red > 1) {Red = 1;}
    if(Green > 1) {Green = 1;}
    if(Blue > 1) {Blue = 1;}
    if(Red < 0) {Red = 0;}
    if(Green < 0) {Green = 0;}
    if(Blue < 0) {Blue = 0;}

    return Color(Red, Green, Blue, Special);
}

/* --- operator overload functions ADD Special PARAM ---*/

// Multiply Color RGB by a scalar value
Color Color::colorScalar ( double scalar)  {
    return Color(Red*scalar, Green*scalar, Blue*scalar, Special);
}

// Compute Average of 2 colors
Color Color::colorAverage ( Color color)  {
    return Color((Red + color.getRed())/2, (Green + color.getGreen())/2, (Blue + color.getBlue())/2, Special);
}

// MultiplGreen 
// Multiply Color RGB by a scalar value - Overload multiplication
Color Color::operator * ( double d)  {
    return Color(Red*d, Green*d, Blue*d, Special);
}

Color Color::operator * ( Color v){
    return Color(Red*v.Red, Green*v.Green, Blue*v.Blue, Special);
}

// Division 
// Divide Color RGB by a scalar or color value - Overload Division symbol
Color Color::operator / ( double d)  {
    return Color(Red/d, Green/d, Blue/d, Special);
}

Color Color::operator / ( Color v){
    return Color(Red/v.Red, Green/v.Green, Blue/v.Blue, Special);
}

// Addition 
// Add to RGB by a scalar or color value - Overload Addition symbol
Color Color::operator + ( double d)  {
    return Color(Red+d, Green+d, Blue+d, Special);
}
Color Color::operator + ( Color v){
    return Color(Red+v.Red, Green+v.Green, Blue+v.Blue, Special);
}

// Subtraction 
// Subtract Color RGB by a scalar or color value - Overload Subtraction symbol
Color Color::operator - ( double d)  {
    return Color(Red-d, Green-d, Blue-d, Special);
}

Color Color::operator - ( Color v){
    return Color(Red-v.Red, Green-v.Green, Blue-v.Blue, Special);
}

// friend std::ostream & operator << (std::ostream &os,  Color double &v){
//     os << v.Red << " " << v.Green << " " << v.Blue;
//     return os;
// }

