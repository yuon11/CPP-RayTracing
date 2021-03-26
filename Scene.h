#ifndef __Scene__H
#define __Scene__H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Object.h"
#include "Vect3.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#include "Light.h"


using namespace std;

// The Scene Class brings together the various lights, shapes and cameras 
class Scene{

    struct RGBType
    {
        double r;
        double g;
        double b;
    };

    private:
        
        time_t progTime = time(NULL);
        time_t startTime = time(NULL);
        
        int dpi;
        int width;
        int height;
        int n;

        double aspectratio;
        double ambientlight;
        double accuracy;

        RGBType *pixels;

        Vect3 X;
        Vect3 Y;
        Vect3 Z;

        Vect3 campos;
        Vect3 look_at;
        Vect3 diff_btw;

        Vect3 camdir;
        Vect3 camright;
        Vect3 camdown;

        Camera scene_cam;

        // Color white_light;


        // Vect3 light_position;
        // Light scene_light;
        // vector<Source*> light_sources;
    public:

        Scene();

        void savebmp( const char*, int, int, int, RGBType*);

        int closestHitObject(vector<double>);

        Color getColorAt(Vect3, Vect3, vector<Object*>, int, vector<Source*>, double, double);

        int draw(vector<Object*>,vector<Source*>);

        ~Scene();
};

#endif
