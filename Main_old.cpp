#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Object.h"
#include "Vect3.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#include "Source.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

using namespace std;

time_t progTime = time(NULL);
time_t startTime = time(NULL);

struct RGBType
{
    double r;
    double g;
    double b;
};

void savebmp( const char *filename, int w, int h, int dpi, RGBType *data){
    FILE *f;
    int k = w*h;
    int s = 4*k;
    int filesize = 54 + s;

    double factor = 39.375;
    int m = static_cast<int>(factor);

    int ppm = dpi*m;

    unsigned char bmpfileheader[14] = {'B','M',0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

    bmpfileheader[ 2] = (unsigned char) (filesize);
    bmpfileheader[ 3] = (unsigned char) (filesize>>8);
    bmpfileheader[ 4] = (unsigned char) (filesize>>16);
    bmpfileheader[ 5] = (unsigned char) (filesize>>24);

    bmpinfoheader[ 4] = (unsigned char) (w);
    bmpinfoheader[ 5] = (unsigned char) (w>>8);
    bmpinfoheader[ 6] = (unsigned char) (w>>16);
    bmpinfoheader[ 7] = (unsigned char) (w>>24);

    bmpinfoheader[ 8] = (unsigned char) (h);
    bmpinfoheader[ 9] = (unsigned char) (h>>8);
    bmpinfoheader[10] = (unsigned char) (h>>16);
    bmpinfoheader[11] = (unsigned char) (h>>24);

    bmpinfoheader[21] = (unsigned char) (s);
    bmpinfoheader[22] = (unsigned char) (s>>8);
    bmpinfoheader[23] = (unsigned char) (s>>16);
    bmpinfoheader[24] = (unsigned char) (s>>24);

    bmpinfoheader[25] = (unsigned char) (ppm);
    bmpinfoheader[26] = (unsigned char) (ppm>>8);
    bmpinfoheader[27] = (unsigned char) (ppm>>16);
    bmpinfoheader[28] = (unsigned char) (ppm>>24);

    
    bmpinfoheader[29] = (unsigned char) (ppm);
    bmpinfoheader[30] = (unsigned char) (ppm>>8);
    bmpinfoheader[31] = (unsigned char) (ppm>>16);
    bmpinfoheader[32] = (unsigned char) (ppm>>24);

    f = fopen(filename, "wb");

    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    
    for (int i = 0; i < k; i++)
    {
        RGBType rgb = data[i];

        double red = (data[i].r)*255;
        double green = (data[i].g)*255;
        double blue = (data[i].b)*255;

        unsigned char color[3] = {
            (int)floor(blue), 
            (int)floor(green), 
            (int)floor(red)
        };

        fwrite(color,1,3,f);
    }
    fclose(f);
}

int closestHitObject(vector<double> object_intersections){
    //closest intersection
    int min_value_index;

    //skip inncecessary calcs
    if (object_intersections.size() == 0)
    {
        return -1;
    }
    else if( object_intersections.size() == 1)
    {
        if (object_intersections.at(0) > 0)
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
        // find Min
        double max = 0;
        for (int i = 0; i < object_intersections.size(); i++)
        {
            if (max < object_intersections.at(i))
            {
                max = object_intersections.at(i);
            }  
        }
        if (max > 0)
        {
            for (int index = 0; index < object_intersections.size(); index++)
            {
                if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max)
                {
                    max = object_intersections.at(index);
                    min_value_index = index;
                }
                
            }
            return min_value_index;
        }
        else
        {
            //all intersections negative
            return -1;
        }
        
           
    }     
}


Color getColorAt(Vect3 intersection_pos, Vect3 intersecting_ray_dir, vector<Object*> scene_objects, int closest_hit_index, vector<Source*> light_sources, double accuracy, double ambient_light){
    
    Color closestHitObject_color = scene_objects.at(closest_hit_index)->getColor();
    Vect3 closestHitObject_normal = scene_objects.at(closest_hit_index)->getNormalAt(intersection_pos);

    // Add code for reflections and anti-aliasing calcualtions

    // // Code to add checker pattern to plane
    if (closestHitObject_color.getSpecial() == 2)
    {
        int square = (int)floor(intersection_pos.getx());

        if ((square % 2) == 0)
        {
            closestHitObject_color.setRed(0);
            closestHitObject_color.setGreen(0);
            closestHitObject_color.setBlue(0);
        }
        else
        {
            closestHitObject_color.setRed(1);
            closestHitObject_color.setGreen(1);
            closestHitObject_color.setBlue(1);
        }
        
    }
    
    Color final_color = closestHitObject_color.colorScalar(ambient_light);

    // Reflections


    for (int light_index = 0; light_index < light_sources.size(); light_index++)
    {
        Vect3 light_direction = (light_sources.at(light_index)->getLightPosition()+(intersection_pos.negative())).normalize();

        float cosine_angle = closestHitObject_normal.dot_product(light_direction);

        if (cosine_angle > 0){
            //Shadow
            bool shadowed=false;

            Vect3 distance_to_light = (light_sources.at(light_index)->getLightPosition()+intersection_pos.negative()).normalize();
            float distance_to_light_mag = distance_to_light.magnitude();

            Ray shadow_ray(intersection_pos, (light_sources.at(light_index)->getLightPosition() +intersection_pos.negative()).normalize());
                  
            vector<double> secondary_intersections;

            for (int obj_index = 0; obj_index < secondary_intersections.size(); obj_index++ && shadowed == false)
            {
                secondary_intersections.push_back(scene_objects.at(obj_index)->findIntersection(shadow_ray));
            }
            
            for (int c = 0; c < secondary_intersections.size(); c++ )
            {
                if (secondary_intersections.at(c) > accuracy)
                {
                    if (secondary_intersections.at(c) <= distance_to_light_mag)
                    {
                        shadowed=true;
                    }
                }
                break;
                
            }
            if (shadowed == false)
            {
                final_color = final_color + ((closestHitObject_color*light_sources.at(light_index)->getColor()).colorScalar(cosine_angle));
            
                if (closestHitObject_color.getSpecial() > 0 && closestHitObject_color.getSpecial() <= 1){
                    double dot1 = closestHitObject_normal.dot_product(intersecting_ray_dir.negative());
                    Vect3 scalar1 = closestHitObject_normal*dot1;
                    Vect3 add1 = scalar1 + intersecting_ray_dir;
                    Vect3 scalar2 = add1*2;
                    Vect3 add2 = (intersecting_ray_dir.negative())+scalar2;
                    Vect3 reflection_dir = add2.normalize();

                    double specular = reflection_dir.dot_product(light_direction);
                    if (specular > 0)
                    {
                        specular = pow(specular, 10);
                        final_color = final_color + (light_sources.at(light_index)->getColor().colorScalar(specular*closestHitObject_color.getSpecial()));
                    }
                    
                }
            }
        }
    }      
    return final_color.clip();
}

int thisone;

int main( int argc, char *argv[]){
    std::cout << "rendering begin... - time "<<ctime(&progTime) << std::endl;
    std::cout << "Setting up vertices/normals etc - time "<<ctime(&progTime) << std::endl;
    int dpi = 72;
    int width = 1080;
    int height = 960;
    int n = width * height;

    double aspectratio = (double)width/(double)height;
    double ambientlight = 0.2;
    double accuracy = 0.000001;

    RGBType *pixels = new RGBType[n];

    Vect3 X (1,0,0);
    Vect3 Y (0,1,0);
    Vect3 Z (0,0,1);

    Vect3 campos(3,1.5,-4);
    Vect3 look_at (0, 0, 0);
    Vect3 diff_btw (campos.getx() - look_at.getx(), campos.gety() - look_at.gety(), campos.getz() - look_at.getz());

    Vect3 camdir = diff_btw.negative().normalize();
    Vect3 camright = Y.cross_product(camdir).normalize();
    Vect3 camdown = camright.cross_product(camdir);

    Camera scene_cam(campos, camdir, camright, camdown);

    Color white_light(1.0, 1.0, 1.0, 0);
    Color pretty_green(0.5, 1.0, 0.5, 0.3);
    Color maroon(0.5, 0.25, 0.25, 0);

    Color tile_floor(1, 1, 1, 2);

    Color gray(0.5, 0.5, 0.5, 0);
    Color black(0, 0, 0, 0);

    Vect3 light_position(-7,10,-10);
    Light scene_light(light_position, white_light);
    vector<Source*> light_sources;
    light_sources.push_back(dynamic_cast<Source*>(&scene_light));


    //SCENE OBJECTS
    Sphere sphere_obj(Vect3(-2.5,0,0),1, pretty_green);
    Sphere sphere_obj2(Vect3(0.5,0,1),1, pretty_green);
    
    Triangle triangle_obj(Vect3(1,0,0),Vect3(0,1,0),Vect3(0,0,1), pretty_green);

    Plane plane_obj(Y, -1, tile_floor);
    
    //our vector of objects in the scene
    vector<Object*> scene_objects;
    scene_objects.push_back(dynamic_cast<Object*>(&plane_obj));

    scene_objects.push_back(dynamic_cast<Object*>(&sphere_obj));
    scene_objects.push_back(dynamic_cast<Object*>(&sphere_obj2));
    scene_objects.push_back(dynamic_cast<Object*>(&triangle_obj));

    double x_amnt, y_amnt;
    std::cout << "Finished setting up vertices/normals etc - time"<<ctime(&progTime) << std::endl;
    std::cout << "Begin applying geometry functions to vertices - time "<<ctime(&progTime) << std::endl;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            thisone = y*width + x;

            //No Anti-aliasing to start
            if (width > height)
            {
                //Wider than it is tall
                x_amnt = ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
                y_amnt = ((height - y) + 0.5)/height;
            }
            else if(height > width)
            {
                //taller than is wide
                x_amnt = (x+0.5)/width;
                y_amnt = (((height - y) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
            }
            else
            {
                //square image
                x_amnt=(x + 0.5)/width;
                y_amnt = ((height - y) + 0.5)/height;
            }
            
            
            Vect3 cam_ray_origin = scene_cam.getCameraPostion();
            Vect3 cam_ray_direction = (camdir + camright*(x_amnt-0.5) + camdown*(y_amnt-0.5)).normalize();

            Ray cam_ray(cam_ray_origin, cam_ray_direction);

            // Intersections
            vector<double> intersections;
            for (int index = 0; index < scene_objects.size(); index++)
            {
                intersections.push_back(scene_objects.at(index)->findIntersection(cam_ray));
            }

            int closest_hit_object_index = closestHitObject(intersections);            

            if (closest_hit_object_index == -1)
            {   
                // Set backgroub black
                pixels[thisone].r = 0;
                pixels[thisone].g = 0;
                pixels[thisone].b = 0;
            }
            else
            {        
                if(intersections.at(closest_hit_object_index) > accuracy){
                    // Index is object in scene
                    Vect3 intersection_position = cam_ray_origin+(cam_ray_direction*intersections.at(closest_hit_object_index));
                    Vect3 intersection_ray_direction = cam_ray_direction;
                    
                    Color intersectionColor = getColorAt(intersection_position, intersection_ray_direction, scene_objects, closest_hit_object_index, light_sources, accuracy, ambientlight);
                    pixels[thisone].r = intersectionColor.getRed();
                    pixels[thisone].g = intersectionColor.getGreen();
                    pixels[thisone].b = intersectionColor.getBlue();   
                }
            }
            
        }
        
    }
    std::cout << "Finished applying geometry functions to vertices - time "<<ctime(&progTime) << std::endl;

    std::cout << "Rasterization of pixels - time "<<ctime(&progTime) << std::endl;
    savebmp("scene.bmp", width, height, dpi, pixels);
    std::cout << "Finished Rasterization of pixels" << std::endl;
    return 0;
}                        