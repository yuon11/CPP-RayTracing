#include "Object.h"
#include "Vect3.h"
#include "Color.h"
#include "Ray.h"
#include "Cube.h"

// Cube class will be defined by 2 point, drawn as triangles for each side
// Default Constructor
Cube::Cube()
{
    setCornerA(Vect3(1,1,1));
    setCornerB(Vect3(-1,-1,-1));
    setColor(Color(1,1,1,0));
    setTriangleSides();
}

// Custom Constructor
Cube::Cube(Vect3 first_pnt, Vect3 second_pnt, Color c)
{
    setCornerA(first_pnt);
    setCornerB(second_pnt);
    setColor(c);
    setTriangleSides();
}

// Setup Triangle sides
void Cube::setTriangleSides()
{
    // First set of corners
    cornerA = Vect3(corner2.getx(), corner1.gety(), corner1.getz());
    cornerB = Vect3(corner2.getx(), corner1.gety(), corner2.getz());
    cornerC = Vect3(corner1.getx(), corner1.gety(), corner2.getz());
        
    // Second set of corners
    cornerD = Vect3(corner2.getx(), corner2.gety(), corner1.getz());
    cornerE = Vect3(corner1.getx(), corner2.gety(), corner1.getz());
    cornerF = Vect3(corner1.getx(), corner2.gety(), corner2.getz());

    // Left side
    cube_triangles.push_back(new Triangle(cornerD, cornerA, corner1, color));
    cube_triangles.push_back(new Triangle(corner1, cornerE, cornerD, color));
    // Far side
    cube_triangles.push_back(new Triangle(corner2, cornerB, cornerA, color));
    cube_triangles.push_back(new Triangle(cornerA, cornerD, corner2, color));
    // Right side
    cube_triangles.push_back(new Triangle(cornerF, cornerC, cornerB, color));
    cube_triangles.push_back(new Triangle(cornerB, corner2, cornerF, color));
    // Front side
    cube_triangles.push_back(new Triangle(cornerE, corner1, cornerC, color));
    cube_triangles.push_back(new Triangle(cornerC, cornerF, cornerE, color));
    // Top side
    cube_triangles.push_back(new Triangle(cornerD, cornerE, cornerF, color));
    cube_triangles.push_back(new Triangle(cornerF, corner2, cornerD, color));
    // Bottom side
    cube_triangles.push_back(new Triangle(corner1, cornerA, cornerB, color));
    cube_triangles.push_back(new Triangle(cornerB, cornerC, corner1, color));
}
// Setter for first corner
void Cube::setCornerA(Vect3 first_pnt)
{
    corner1 = first_pnt;
}

// Setter for second corner
void Cube::setCornerB(Vect3 second_pnt)
{
    corner2 = second_pnt;
}

void Cube::setColor(Color c)
{
    color = c;
}

//Return object normal at point
Vect3 Cube::getNormalAt(Vect3 point)
{
    return corner1.normalize();
}

// Find intersection of object and ray
// Our cube is a collection of triangles, so we will iterate triangles and take the best hit
double Cube::findIntersection(Ray ray)
{
    vector<double> cube_intersections;
    
    // Run reflection ray against scene objects and hold values  
    for (int cube_index = 0; cube_index < cube_triangles.size(); cube_index++) {
        cube_intersections.push_back(cube_triangles.at(cube_index)->findIntersection(ray));
    }

    int min_value_index;

    // skip unncecessary calculations
    if (cube_intersections.size() == 0)
    {
        return -1;
    }
    // Object is visible i.e. has intersects in view port
    else if( cube_intersections.size() == 1)
    {
        if (cube_intersections.at(0) > 0)
        {
            // if greater than 0, its our min
            return 0;
        }
        else
        {
            //only intersection is negative
            return -1;
        }          
    }
    else
    {
        //HIT
        // find Best index of the best hit by comparing intersection values
        double max = 0;

        // Determine max of object intersections
        for (int i = 0; i < cube_intersections.size(); i++)
        {
            if (max < cube_intersections.at(i))
            {
                max = cube_intersections.at(i);
            }  
        }
        // if max is greater than 0, take note of the min index of the max hit
        if (max > 0)
        {
            // Iterate through intersections again, this time finding the smallest viable max value
            for (int index = 0; index < cube_intersections.size(); index++)
            {
                if (cube_intersections.at(index) > 0 && cube_intersections.at(index) <= max)
                {
                    //  This value gets closer to 0, if viable, and more precise
                    max = cube_intersections.at(index);
                    min_value_index = index;
                }
                
            }
            // Retun the Index of the minimun viable "hit" object intersection 
            return max;
        }
        else
        {
            //all intersections negative
            return -1;
        }    
    } 
}

// Return Color of object
Color Cube::getColor()
{
    return color;
}
