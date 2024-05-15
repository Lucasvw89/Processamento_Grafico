#ifndef SPHEREHEADER
#define SPHEREHEADER
#include <iostream>
#include <cmath>
#include "Vector.cpp"
#include "Point.cpp"
#include "Ray.cpp"

class sphere{
    private:
        point center;
        double radius;
        vector color;
    
    public:
        sphere(point center, double radius, vector color){
            this->center = center;
            this->radius = radius;
            this->color = color;
        }

        sphere(){};

        double hit(ray raio){
            double t;

            vector OC = raio.origin - center;
        }
    
};
#endif