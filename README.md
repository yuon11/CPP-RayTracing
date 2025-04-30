# CPP-RayTracing

## Overview  
<p>
    This project is an attempt to explore computer graphics by making my own C++ ray tracing library. Yuon's Improvised Graphics Library (YIGL) is a library that contains basic shape and lighting object classes that can be appled onto a scene and rendered to a designated file <b>scene.bmp</b>.
</p>

## Setup/Installation
<p>
    This project should be compatible with any OS environment capable of running C++ with the MinGW-w64 toolchain. To get started installing C++ and the MinGW-w64 visit the <a href='https://code.visualstudio.com/docs/cpp/config-mingw'> Visual Studio Code</a> site and follow the listed steps. Once you're able to confirm your installation of C++ and MinGW are setup, you can compile and execute the program from the command line with the following commands:

    g++ *.cpp -o output
    ./output

    ------------------------------------------------------------------------------------------------------------------
    ---------------------------------------------Simple Shape Set Designer--------------------------------------------
    ------------------------------------------------------------------------------------------------------------------
    This Program allows a user to define simple shapes That will be rendered as via ray tracing, and saved to a BMP file.
    You May Chose To Add To The Scene Or Reset And Start Again. More shapes will increase Render time.



    The X, Y and Z coordinates are best kept in the range (-4,4). As higher values may be off screen or will not render.
    The R, G, B and Specular value range from (0,1).

    (Default Lights - 1 | Custom Lights - 2 ):
</p>

## Usage 
<p>
    Once you are able to run the compiled executable, the program will execute its main while loop and ask a series of questions that will take user input to determine the type and position of lights in the scene, as well as the color and position of the shape objects the user chooses to add into the scene. The first question after startup is the following:

    ------------------------------------------------------------------------------------------------------------------
    ---------------------------------------------Simple Shape Set Designer--------------------------------------------
    ------------------------------------------------------------------------------------------------------------------
    This Program allows a user to define simple shapes That will be rendered as via ray tracing, and saved to a BMP file.
    You May Chose To Add To The Scene Or Reset And Start Again. More shapes will increase Render time.



    The X, Y and Z coordinates are best kept in the range (-4,4). As higher values may be off screen or will not render.
    The R, G, B and Specular value range from (0,1).

    (Default Lights - 1 | Custom Lights - 2 ):

This first choice describes the dimensional limits of the scene (-4,4) and allow that user to select a default lights setup (provides one central light for a decently lit scene) or customize the X,Y, and Z values of light sources within the scene. Keep in mind that with ray tracing, each source of lighting can have a major effect on rendering time.
Once lighting has been decided for the scene, the user will be prompted to select from several options including the option to render the current scene, select shapes to add to the scene, reset the shapes/lights/scene, or end the program:

    Please Select A Shape To Render In The Scene, Or Reset The Scene.
    (Skip Iteration/Render - 0 | Sphere - 1 | Cube - 2 | Triangle - 3 | Reset Shapes - 4 | Reset Lights - 5 | Reset Scene - 6 | End Program - 7):
</p>

### Triangle
<p>
Should the user select Triangle they will be guided through the following input options

    Default Triangle - 1 | Custom Triangle - 2: 2

    Set Triangle's first point.

    SELECT THE XYZ COORDINATES FOR YOUR SHAPE:

    X Value - this controls the HORIZONTAL LOCATION: 1

    Y Value - this controls the VERTICAL LOCATION: -1

    Z Value - this controls the DEPTH: -3
    
    Set Triangle's second point.

    SELECT THE XYZ COORDINATES FOR YOUR SHAPE:

    X Value - this controls the HORIZONTAL LOCATION: -1

    Y Value - this controls the VERTICAL LOCATION: -2

    Z Value - this controls the DEPTH: -4
    
    Set Triangle's third point.

    SELECT THE XYZ COORDINATES FOR YOUR SHAPE:

    X Value - this controls the HORIZONTAL LOCATION: 1

    Y Value - this controls the VERTICAL LOCATION: 2

    Z Value - this controls the DEPTH: 3
</p>

### Cube
<p>
Should the user select Cube they will be guided through the following input options to select 2 point in the scene. The points given by the user will be used to set the OPPOSITE CORNERS of the cubes that wil be rendered with those coordinates.

    Default Cube - 1 | Custom Cube - 2: 2

    Set Cube's first Corner Point.

    SELECT THE XYZ COORDINATES FOR YOUR SHAPE:

    X Value - this controls the HORIZONTAL LOCATION: 1

    Y Value - this controls the VERTICAL LOCATION: 2

    Z Value - this controls the DEPTH: -3

    Set Cube's second point.

    SELECT THE XYZ COORDINATES FOR YOUR SHAPE:

    X Value - this controls the HORIZONTAL LOCATION: -4

    Y Value - this controls the VERTICAL LOCATION: -4

    Z Value - this controls the DEPTH: -4
</p>

 
