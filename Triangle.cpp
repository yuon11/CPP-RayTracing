#include "Triangle.h"
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

Triangle::Triangle()
{
    a = Vect3(1,0,0);
    b = Vect3(0,1,0);
    c = Vect3(0,0,1);
    setTriangleNormal();
    setTriangleDistance();
    setColor(Color(0.5,0.5,0.5,0));
}

Triangle::Triangle(Vect3 side1, Vect3 side2, Vect3 side3, Color shape_color)
{
    a = side1;
    b = side2;
    c = side3;
    setTriangleNormal();
    setTriangleDistance();
    setColor(shape_color);
}

void Triangle::setTriangleNormal()
{    
    Vect3 vertex_CA = c-a;
    Vect3 vertex_BA = b-a;
    normal = vertex_CA.cross_product(vertex_BA).normalize();
};

void Triangle::setTriangleDistance()
{
    distance = normal.dot_product(a);
}

void Triangle::setColor(Color c)
{
    color = c;
}

Vect3 Triangle::getTriangleNormal()
{
    return normal;  
};

double Triangle::getTriangleDistance()
{
    return distance;
}

Vect3 Triangle::getNormalAt(Vect3 point)
{
    return normal;
};

Color Triangle::getColor(){ return color; }

double Triangle::findIntersection(Ray ray){

    Vect3 ray_origin = ray.getRayOrigin();
    Vect3 ray_direction = ray.getRayDirection();


    double a_val = ray_direction.dot_product(normal); 
    
    // check if ray and plane are parallel ?
    if (a_val == 0) // almost 0 
    {
        //Ray Parallel to Triangle
        return -1;
    }
    else{
        // Liner Algebra EQ for intersection of Ray and Plane
        double b_val = normal.dot_product(ray.getRayOrigin()+ (normal*distance).negative());
        double dist_to_plane = -1*b_val/a_val;

        // Triangle instersection 
        Vect3 intersection = (ray_direction * dist_to_plane) + ray_origin;


        Vect3 vertex_CA = c-a;
        Vect3 edge_intersectiona = intersection - a;
        double test_val1 = vertex_CA.cross_product(edge_intersectiona).dot_product(normal);

        Vect3 vertex_BC = b - c;
        Vect3 edge_intersectionc = intersection - c;
        double test_val2 = vertex_BC.cross_product(edge_intersectionc).dot_product(normal);

        Vect3 vertex_AB = a-b;
        Vect3 edge_intersectionb = intersection - b;
        double test_val3 = vertex_AB.cross_product(edge_intersectionb).dot_product(normal);

        // cout << "\n" << "In Triangle interesect loop" <<"\n" << endl;
        // cout << "\n" << test_val1 << test_val2 << test_val3 <<"\n" << endl;

        if ((test_val1 >= 0) && (test_val2 >= 0) && (test_val3 >= 0))
        {   
            // inside triangle
            return dist_to_plane;
        }
        else
        {
            // outside Triangle
            return -1;
        }
        
    } 

};