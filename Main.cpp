
#include <iostream>
#include <string>
#include <vector>

// CUSTOM HEADER FILES
#include "Object.h"
#include "Source.h"
#include "Vect3.h"
#include "Color.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Cube.h"
#include "Scene.h"
#include "PointLight.h"
#include "DirectionalLight.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

Color white_light(1.0, 1.0, 1.0, 0);
Color blue_light(0, 0, 1.0, 0);
Color red_light(0, 0, 1.0, 0);
Color green_light(0, 1.0, 0, 0);


// Reuasble Function to create a user specified Color based on input
Color selectColor()
{   
    // User Color selection
    int color_selection = 0;
    cout << "\nRed - 1 | Green - 2 | Blue - 3 | Custom - 4: ";
    cin >> color_selection;
    
    /* Red */
    if (color_selection == 1)
    {
        return Color(1,0,0,0);
    }
    /* Green */
    else if (color_selection == 2)
    {
        return Color(0,1,0,0);
    }
    /* Blue */
    else if (color_selection == 3)
    {
        return Color(0,0,1,0);
    }
    /* Custom Color */
    else if (color_selection == 4)
    {   
        //
        // Values to hold user selection for RBG and Specular value
        //
        double red_val = 0;
        double green_val = 0;
        double blue_val = 0;
        double spec_val = 0;

        //
        // USer Prompt sequence
        //
        cout << "\nSELECT THE RGB & SPECULAR VALUES FOR YOUR SHAPE:" << endl;
        cout << "Red Value: ";
        cin >> red_val;
        cout << "Green Value: ";
        cin >> green_val;
        cout << "Blue Value: ";
        cin >> blue_val;
        cout << "Specular Value: ";
        cin >> spec_val;

        return Color(red_val,green_val,blue_val,spec_val);
    }
    else{
        cout << "\nUnsupported option. Please try again.\n" << endl;
    }  
}

// Reusable Function to take in Coordinate specifications and output a vector 
Vect3 setCoordinates()
{
    double x = 0;
    double y = 0;
    double z = 0;

    cout << "\nSELECT THE XYZ COORDINATES FOR YOUR SHAPE:" << endl;
    cout << "\nX Value - this controls the HORIZONTAL LOCATION: ";
    cin >> x;
    cout << "\nY Value - this controls the VERTICAL LOCATION: ";
    cin >> y;
    cout << "\nZ Value - this controls the DEPTH: ";
    cin >> z;

    return Vect3(x,y,z);
}

// Function ecapsulating the prompts for a custom user sphere
Sphere* createUserSphere()
{
    // Variable for sphere selection
    int sphere_selection = 1;
    cout << "\n(Default Sphere - 1 | Custom Sphere - 2): ";
    cin >> sphere_selection;

    // Default Sphere selection
    if (sphere_selection == 1)
    {   
        Vect3 sphere_loc = setCoordinates();
        return new Sphere(sphere_loc, 1, Color(0.5,0.5,0.5,0.5));
    }
    // Custom Sphere Selection
    else if (sphere_selection == 2)
    {   
        Vect3 sphere_loc = setCoordinates();
        Color sphere_color = selectColor();

        // Here the user gets to specify the Sphere radius
        double sphere_radius = 1;
        cout << "Set Sphere Radius: ";
        cin >> sphere_radius;

        return new Sphere (sphere_loc, sphere_radius, sphere_color);;
    }
    else
    {
        cout << "\nUnsupported option. Please try again.\n" << endl;
    }   
}
//
// Function to Create Triangle object based on user input
//
Triangle* createUserTriangle()
{
    // User selects default or Custom triangle
    int triangle_selection = 1;
    cout << "\nDefault Triangle - 1 | Custom Triangle - 2: \n";
    cin >> triangle_selection;
    
    //
    // 3 Sets of questions to gather Triangle coordinates
    //
    cout << "Set Triangle's first point. " << endl;
    Vect3 triangle_pointA = setCoordinates();

    cout << "Set Triangle's second point. " << endl;
    Vect3 triangle_pointB = setCoordinates();

    cout << "Set Triangle's third point. " << endl;
    Vect3 triangle_pointC = setCoordinates();
    
    // If default, set color and return
    if (triangle_selection == 1)
    {   
        return new Triangle(triangle_pointA, triangle_pointB, triangle_pointC, Color(0.5,0.5,0.5,0.5));
    }
    // If custom, ask for user color selection then return
    else if (triangle_selection == 2)
    {   
        Color sphere_color = selectColor();
        return new Triangle(triangle_pointA, triangle_pointB, triangle_pointC, sphere_color);
    }
    else
    {
        cout << "\nUnsupported option. Please try again.\n" << endl;
    }
    
}
//
// Function to Create Triangle object based on user input
//
Cube* createUserCube()
{
    // User selects default or Custom triangle
    int cube_selection = 1;
    cout << "\nDefault Cube - 1 | Custom Cube - 2: \n";
    cin >> cube_selection;
    
    //
    // 3 Sets of questions to gather Triangle coordinates
    //
    cout << "Set Cube's first Corner Point. " << endl;
    Vect3 cube_pointA = setCoordinates();

    cout << "Set Cube's second point. " << endl;
    Vect3 cube_pointB = setCoordinates();


    // If default, set color and return
    if (cube_selection == 1)
    {   
        return new Cube(cube_pointA, cube_pointB, Color(0.5,0.5,0.5,0.5));
    }
    // If custom, ask for user color selection then return
    else if (cube_selection == 2)
    {   
        Color cube_color = selectColor();
        return new Cube(cube_pointA, cube_pointB, cube_color);
    }
    else
    {
        cout << "\nUnsupported option. Please try again.\n" << endl;
    }
    
}
//
// Create an Area Light
//
Light* createAreaLight()
{
    cout << "\nSET LIGHT ORIGIN POSITION\n";
    Vect3 light_position = setCoordinates();
    
    Color light_color = selectColor();
    return new Light(light_position, light_color);
}
//
// Create PointLight
//
PointLight* createPointLight()
{
    cout << "\nSET LIGHT ORIGIN POSITION\n";
    Vect3 light_position = setCoordinates();
    
    cout << "\nSet Power for Point Light. This refers to the light intensity on a given axis.\n";
    Vect3 light_pow = setCoordinates();
    Color light_color = selectColor();

    return new PointLight(light_position, light_pow, light_color);
}
//
// Create Directional light
//
DirectionalLight* createDirectionalLight()
{
    cout << "\nSET LIGHT ORIGIN POSITION\n";
    Vect3 light_position = setCoordinates();

    cout << "\nSet Direction for Direction Light. This refers to where the light is focused.\n";
    Vect3 light_dir = setCoordinates();
    Color light_color = selectColor();

    return new DirectionalLight(light_position, light_dir, light_color);
}


int main()
{
    //
    // PROGRAM START BANNER
    //

    // User instructions
    cout << "------------------------------------------------------------------------------------------------------------------\n";
    cout << "---------------------------------------------Simple Shape Set Designer--------------------------------------------\n";
    cout << "------------------------------------------------------------------------------------------------------------------\n";
    cout << "This Program allows a user to define simple shapes That will be rendered as via ray tracing, and saved to a BMP file.\n";
    cout << "You May Chose To Add To The Scene Or Reset And Start Again. More shapes will increase Render time.\n\n" << endl;

    cout << "\nThe X, Y and Z coordinates are best kept in the range (-4,4). As higher values may be off screen or will not render.\n";
    cout << "The R, G, B and Specular value range from (0,1)." << endl;

    //
    // Instantiate Scene, Light Sources, and Objects Vector
    //
    Scene UserScene = Scene();
    vector<Source*> light_sources;
    vector<Object*> scene_objects;
    
    int shape_selection = 1;

    do
    {
        // Take user light select. Either default or custom
        int light_selection = 1;
        cout << "\n(Default Lights - 1 | Custom Lights - 2 ): ";
        cin >> light_selection;

        //
        // Light Creation Loop
        //
        if (light_selection == 1)
        {   
            Vect3 light_position(-7,10,-10);
            light_sources.push_back(dynamic_cast<Source*>(new Light(light_position, white_light)));
        }
        //
        // Custom Light Selection
        else if (light_selection == 2)
        {   
            // Limit Scene lights to 5
            int light_limit =0;
            int cust_light_selection = 1;

            cout << "\nADD UP TO 5 LIGHTS WITHIN THE SCENE.\n";
            while (light_limit < 5)
            {
                //
                // User Light Options
                //
                cout << "\n( AreaLight - 1 | PointLight - 2 | DirectionalLight - 3 | Continue - 4 ): ";
                cin >> cust_light_selection;

                //
                // Create Area Light 
                //
                if ( cust_light_selection == 1)
                {
                    light_sources.push_back(dynamic_cast<Source*>(createAreaLight()));
                    light_limit++;
                }
                //
                // Create Point Light 
                //
                else if ( cust_light_selection == 2)
                {
                    light_sources.push_back(dynamic_cast<Source*>(createPointLight()));
                    light_limit++;
                }
                //
                // Create Directional Light
                //
                else if (cust_light_selection == 3)
                {
                    light_sources.push_back(dynamic_cast<Source*>(createDirectionalLight()));
                    light_limit++;
                }
                //
                // Continue past light setup
                //
                else if (cust_light_selection == 4)
                {
                    cout << "\nLight Setup Complete.\n" << endl;
                    break;
                }
                //
                // Unsupported option 
                //
                else
                {
                    cout << "\nUnsupported option. Exiting Lights Setup.\n" << endl;
                } 
            }
        }
        //
        // Setup Default Lights if no appropriate option is selected
        //
        else
        {
            cout << "\nUnsupported option. Default Light Setup Returned.\n" << endl;
            Vect3 light_position(-7,10,-10);
            light_sources.push_back(dynamic_cast<Source*>(new Light(light_position, white_light)));
        }

        //
        //  User Shape Creation Loop
        //

        // Setting the default Background for shapes to be drawn    
        scene_objects.push_back(dynamic_cast<Object*>(new Plane(Vect3(0,1,0), -3, Color(1,1,1,2))));

        do
        {
            //
            // User selects shapes to add to scene until resetting, or ending the program
            //
            cout << "\nPlease Select A Shape To Render In The Scene, Or Reset The Scene. "<<endl;
            cout << "(Skip Iteration/Render - 0 | Sphere - 1 | Cube - 2 | Triangle - 3 | Reset Shapes - 4 | Reset Lights - 5 | Reset Scene - 6 | End Program - 7): "; 
            cin >> shape_selection;

            if (shape_selection == 0)
            {
                /*
                 Skip Current Loop Iteration and Re-Render
                */
                cout << "\nRE-RENDERING SCENE\n" << endl;
                int draw_result = UserScene.draw(scene_objects, light_sources);
                continue;
            }
            //
            // Create Sphere 
            //
            if (shape_selection == 1)
            {
                /*Sphere*/
                scene_objects.push_back(dynamic_cast<Object*>(createUserSphere()));
            }
            //
            //  Create Cube
            //
            else if (shape_selection == 2)
            {
                /* cube */
                scene_objects.push_back(dynamic_cast<Object*>(createUserCube()));
            }
            //
            // Create Triangle
            //
            else if (shape_selection == 3)
            {
                /* triangle */
                scene_objects.push_back(dynamic_cast<Object*>(createUserTriangle()));
            }
            //
            // Reset Objects
            //
            else if (shape_selection == 4)
            {
                /* Clear Shape Vector */
                cout << "\nCLEARING SHAPES VECTOR\n" << endl;
                scene_objects.clear();
                
                // Setting the default Background for shapes to be drawn    
                scene_objects.push_back(dynamic_cast<Object*>(new Plane(Vect3(0,1,0), -3, Color(1,1,1,2))));
            }    
            else if (shape_selection == 5)
            {
                /* Clear Shape Vector */
                cout << "\nCLEARING LIGHTS VECTOR. THIS WILL DRAMATICALLY DARKEN THE SCENE.\n" << endl;
                light_sources.clear();
            }
            else if (shape_selection == 6)
            {
                /* Clear Shape Vector */
                cout << "\nCLEARING SHAPES AND LIGHTS VECTORS.\n" << endl;
                scene_objects.clear();
                light_sources.clear();
            }
            else if (shape_selection == 7)
            {
                /* Clear Shape Vector */
                cout << "\nENDING RENDER PROGRAM.\n" << endl;
                return 0;
            }            
            else
            {
                cout << "\nUnsupported option. Please try again.\n" << endl;
            }
            
            // Draw Scene
            int draw_result = UserScene.draw(scene_objects, light_sources);
        } while (shape_selection != 6 && shape_selection != 7 );

    } while (shape_selection != 7);
    
}