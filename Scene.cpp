#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Scene.h"

using namespace std;

Scene::Scene()
{
    // Dots per inch
    dpi = 72;
    
    // Scene Width
    width = 1080;
    
    // Scene Height
    height = 960;
    
    // Scene Area
    n = width * height;
    
    // Screen aspect ratio 
    aspectratio = (double)width/(double)height;

    // Ambien light setting
    ambientlight = 0.2;

    // Accuracy threshold for feature points
    accuracy = 0.00000001;

    // Pixel array to be used for image creation
    pixels = new RGBType[n];

    // Default X,Y,Z valued vectors
    X = Vect3(1,0,0);
    Y = Vect3(0,1,0);
    Z = Vect3(0,0,1);

    // Camera position
    campos = Vect3(3,1.5,-4); 

    // look at point towards origin
    look_at = Vect3(0, 0, 0);

    // Difference between position and lookat
    diff_btw =  Vect3(campos.getx() - look_at.getx(), campos.gety() - look_at.gety(), campos.getz() - look_at.getz());

    // Camera boundaries are calculated from prior variables, camdir, right, down
    camdir = diff_btw.negative().normalize();
    camright = Y.cross_product(camdir).normalize();
    camdown = camright.cross_product(camdir);

    // Scene camera data member
    scene_cam = Camera(campos, camdir, camright, camdown);
}

// Function to save output image as bitmap
void Scene::savebmp( const char *filename, int w, int h, int dpi, RGBType *data){
    
    // Filename, Height, width, file size
    FILE *f;
    int k = w*h;
    int s = 4*k;
    int filesize = 54 + s;


    // Dots Per Inch - level of detail to print in the image
    double factor = 39.375;
    int m = static_cast<int>(factor);
    int ppm = dpi*m;

    // Bitmap file header
    unsigned char bmpfileheader[14] = {'B','M',0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

    // The following rows coorespond to the 4 byte size rows necessary for the BMP info header
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

    // Write file info to header
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);

    // Iterate through the file rows painting each pixel
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

// Iterate through points intersecting a pixel, and determine which pixel is the front most
int Scene::closestHitObject(vector<double> object_intersections){
    
    // index of the closest intersection in object vector
    int min_value_index;

    // skip unncecessary calculations
    if (object_intersections.size() == 0)
    {
        return -1;
    }
    // Object is visible i.e. has intersects in view port
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
        // find Best index of the best hit by comparing intersection values
        double max = 0;

        // Determine max of object intersections
        for (int i = 0; i < object_intersections.size(); i++)
        {
            if (max < object_intersections.at(i))
            {
                max = object_intersections.at(i);
            }  
        }
        // if max is greater than 0, take note of the min index of the max hit
        if (max > 0)
        {
            // Iterate through intersections again, this time finding the smallest viable max value
            for (int index = 0; index < object_intersections.size(); index++)
            {
                if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max)
                {
                    //  This value gets closer to 0, if viable, and more precise
                    max = object_intersections.at(index);
                    min_value_index = index;
                }
                
            }
            // Retun the Index of the minimun viable "hit" object intersection 
            return min_value_index;
        }
        else
        {
            //all intersections negative
            return -1;
        }    
    }     
}

// Determine color value at a given intersection based on input light rays and object intersections
Color Scene::getColorAt(Vect3 intersection_pos, Vect3 intersecting_ray_dir, vector<Object*> scene_objects, int closest_hit_index, vector<Source*> light_sources, double accuracy, double ambient_light)
{    
    // Get normal and color for use throughout
    Color closestHitObject_color = scene_objects.at(closest_hit_index)->getColor();
    Vect3 closestHitObject_normal = scene_objects.at(closest_hit_index)->getNormalAt(intersection_pos);

    //CheckerBoard Pattern using specular value
    // This is specifically for the tile pattern plane background i.e. "floor" but is also a usable for objects
	if (closestHitObject_color.getSpecial() == 2) 
    {
        // checkered/tile floor pattern - using modulos on intersections of horozontal and depth
		int square = (int)floor(intersection_pos.getx()) + (int)floor(intersection_pos.getz());
		
		if ((square % 2) == 0) 
        {
			// black tile - by setting object RBG  
			closestHitObject_color.setRed(0);
			closestHitObject_color.setGreen(0);
			closestHitObject_color.setBlue(0);
		}
		else 
        {
			// white tile
			closestHitObject_color.setRed(1);
			closestHitObject_color.setGreen(1);
			closestHitObject_color.setRed(1);
		}
	}

    // Adjust with ambien light value
    Color final_color = closestHitObject_color.colorScalar(ambient_light);
 
    // 
    // REFLECTION CALCULATION
    // 
	if (closestHitObject_color.getSpecial() > 0 && closestHitObject_color.getSpecial() <= 1) 
    {
		// reflection from objects with specular intensity
        // Each equation represents the bounces taken by our interesecting rays, adjusting based on the normal
		double dot1 = closestHitObject_normal.dot_product(intersecting_ray_dir.negative());
		Vect3 scalar1 = closestHitObject_normal * dot1;
		Vect3 add1 = scalar1 + intersecting_ray_dir;
		Vect3 scalar2 = add1*2;
		Vect3 add2 = intersecting_ray_dir.negative() + scalar2;
		Vect3 reflection_direction = add2.normalize();
		
        // Create reflection reay based on bouncing & start the intersection slightly above the point
		Ray reflection_ray (intersection_pos + closestHitObject_normal*0.001, reflection_direction);
		
		// Vector for colorvalues of ray intersections
		vector<double> reflection_intersections;
		
        // Run reflection ray against scene objects and hold values  
		for (int reflection_index = 0; reflection_index < scene_objects.size(); reflection_index++) {
			reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
		}
		
        // Find most viable object reflection point, and take the index
		int index_of_winning_object_with_reflection = closestHitObject(reflection_intersections);
		
        // Hits are found
		if (index_of_winning_object_with_reflection != -1) {
		    
            // reflection ray missed everthing else
            if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
				
                // determine the position and direction at the point of intersection with the reflection ray
				Vect3 reflection_intersection_position = intersection_pos + (reflection_direction * (reflection_intersections.at(index_of_winning_object_with_reflection)));
				Vect3 reflection_intersection_ray_direction = reflection_direction;
				
                // the ray only affects the color if it is reflected off something so we get color at the intersection
				Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientlight);
				
                // Adjust final reflection color
				final_color = final_color + (reflection_intersection_color.colorScalar(closestHitObject_color.getSpecial()));
			}
		}
    }

    //
    //  SHADOW RAY CALCULATIONS  
    //

    // Iterate through Light sources and make shadow ray calculations
    for (int light_index = 0; light_index < light_sources.size(); light_index++)
    {
        // Determine light direction from bounce
        Vect3 light_direction = (light_sources.at(light_index)->getLightPosition()+(intersection_pos.negative())).normalize();

        float cosine_angle = closestHitObject_normal.dot_product(light_direction);
        if (cosine_angle > 0)
        {
            // Shadow boolean
            bool shadowed=false;

            // Distance to light, and magnitude
            Vect3 distance_to_light = (light_sources.at(light_index)->getLightPosition()+intersection_pos.negative()).normalize();
            float distance_to_light_mag = distance_to_light.magnitude();

            // Instantiate shadow ray & Vector for values of points intersecting with shadow ray
            // Test secondary intersections against Scene objects
            Ray shadow_ray(intersection_pos+closestHitObject_normal*0.001, light_direction);
            vector<double> secondary_intersections;
            for (int obj_index = 0; obj_index < scene_objects.size() && shadowed == false; obj_index++)
            {
                secondary_intersections.push_back(scene_objects.at(obj_index)->findIntersection(shadow_ray));
            }
            
            // Check secondary interections for accuracy threshold
            for (int c = 0; c < secondary_intersections.size(); c++ )
            {
                if (secondary_intersections.at(c) > accuracy)
                {
                    // If the value is less than or equal to magnitude of light at the given distance, its shadowed 
                    if (secondary_intersections.at(c) <= distance_to_light_mag)
                    {
                        shadowed=true;
                    }
                }
            }

            // If not shadowed adjust color with the light ans specular values assigned
            if (shadowed == false)
            {
                final_color = final_color + ((closestHitObject_color*light_sources.at(light_index)->getColor()).colorScalar(cosine_angle));

                // Second reflection calculation on objects with specularity. This blocks, similar to above, adjusts the final color with the result of a final reflection if not shadowed 
                if (closestHitObject_color.getSpecial() > 0 && closestHitObject_color.getSpecial() <= 1)
                {
                    // Reflection adjustment
                    double dot1 = closestHitObject_normal.dot_product(intersecting_ray_dir.negative());
                    Vect3 scalar1 = closestHitObject_normal*dot1;
                    Vect3 add1 = scalar1 + intersecting_ray_dir;
                    Vect3 scalar2 = add1*2;
                    Vect3 add2 = (intersecting_ray_dir.negative())+scalar2;
                    Vect3 reflection_dir = add2.normalize();

                    // Enhance color based on specular
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


// SCENE DRAW FUNCTION
// Created a file, "scene.bmp" with the rendered objects
int Scene::draw(vector<Object*> scene_objects, vector<Source*> light_sources){
    
    int thisone, aa_index;
    int aadepth = 1;
    std::cout << "\n\nrendering begin... - time "<<ctime(&progTime) << std::endl;
    std::cout << "Setting up vertices/normals etc - time "<<ctime(&progTime) << std::endl;
    
    double x_amnt, y_amnt;
    std::cout << "Finished setting up vertices/normals etc - time"<<ctime(&progTime) << std::endl;
    std::cout << "Begin applying geometry functions to vertices - time "<<ctime(&progTime) << std::endl;

    // Iterate over height and width of, adjust for aspect ratio 
	for (int x = 0; x < width; x++) 
    {
		for (int y = 0; y < height; y++) 
        {
			thisone = y*width + x;
			
			for (int aax = 0; aax < aadepth; aax++) 
            {
				for (int aay = 0; aay < aadepth; aay++) 
                {
					aa_index = aay*aadepth + aax;
					srand(time(0));
					
					// create the ray from the camera to this pixel
					if (aadepth == 1) {
					
						// start with no anti-aliasing
						if (width > height) 
                        {
							// the image is wider than it is tall
							x_amnt = ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
							y_amnt = ((height - y) + 0.5)/height;
						}
						else if (height > width) 
                        {
							// the imager is taller than it is wide
							x_amnt = (x + 0.5)/ width;
							y_amnt = (((height - y) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
						}
						else 
                        {
							// the image is square
							x_amnt = (x + 0.5)/width;
							y_amnt = ((height - y) + 0.5)/height;
						}
					}
					else {
						// anti-aliasing
						if (width > height) {
							// the image is wider than it is tall
							x_amnt = ((x + (double)aax/((double)aadepth - 1))/width)*aspectratio - (((width-height)/(double)height)/2);
							y_amnt = ((height - y) + (double)aax/((double)aadepth - 1))/height;
						}
						else if (height > width) {
							// the imager is taller than it is wide
							x_amnt = (x + (double)aax/((double)aadepth - 1))/ width;
							y_amnt = (((height - y) + (double)aax/((double)aadepth - 1))/height)/aspectratio - (((height - width)/(double)width)/2);
						}
						else {
							// the image is square
							x_amnt = (x + (double)aax/((double)aadepth - 1))/width;
							y_amnt = ((height - y) + (double)aax/((double)aadepth - 1))/height;
						}
					}
                }
            }
                        
            // Set Scene Camera
            Vect3 cam_ray_origin = scene_cam.getCameraPostion();
            Vect3 cam_ray_direction = (camdir + camright*(x_amnt-0.5) + camdown*(y_amnt-0.5)).normalize();

            // Ray projected from camera
            Ray cam_ray(cam_ray_origin, cam_ray_direction);

            // Test Camera Ray For Intersections In The Scene
            vector<double> intersections;
            for (int index = 0; index < scene_objects.size(); index++)
            {
                intersections.push_back(scene_objects.at(index)->findIntersection(cam_ray));
            }
            // std::cout << "After camera ray intersection"<< std::endl;

            // Find Closest Hit Object In The Cameras View
            int closest_hit_object_index = closestHitObject(intersections);            

            // If -1, background is hit
            if (closest_hit_object_index == -1)
            {   
                // Set background to black
                pixels[thisone].r = 0;
                pixels[thisone].g = 0;
                pixels[thisone].b = 0;
            }
            // Else if closest background hit is greater than accuracy
            else if(intersections.at(closest_hit_object_index) > accuracy)
            {
                    
                    // Adjust intersection position and ray direction of camera
                    Vect3 intersection_position = cam_ray_origin+(cam_ray_direction*intersections.at(closest_hit_object_index));
                    Vect3 intersection_ray_direction = cam_ray_direction;
                    
                    // Get color at the camera intersection index
                    Color intersectionColor = getColorAt(intersection_position, intersection_ray_direction, scene_objects, closest_hit_object_index, light_sources, accuracy, ambientlight);
                    pixels[thisone].r = intersectionColor.getRed();
                    pixels[thisone].g = intersectionColor.getGreen();
                    pixels[thisone].b = intersectionColor.getBlue();   
            }
            else
            {   
                continue;
            }
        }
    }

    // Statement to confirm the end of the render process
    std::cout << "Finished applying geometry functions to vertices - time "<<ctime(&progTime) << std::endl;
    std::cout << "Rasterization of pixels - time "<<ctime(&progTime) << std::endl;
    savebmp("scene.bmp", width, height, dpi, pixels);
    std::cout << "Finished Rasterization of pixels" << std::endl;
    return 0;
}                   

Scene::~Scene(){};