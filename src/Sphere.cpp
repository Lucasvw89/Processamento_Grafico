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

        bool hit_sphere(point/* & */ center, double radius, ray& r) {
            vector oc = center - r.origin;
            auto a = r.direction.produto_escalar(r.direction);
            auto b = -2.0 * r.direction.produto_escalar(oc);
            auto c = oc.produto_escalar(oc) - radius*radius;
            auto discriminant = b*b - 4*a*c;
            return (discriminant >= 0);
        }
    
        vector ray_color(ray& r) {
            if (hit_sphere(point(0,0,-1), 0.5, r))
                return vector(1, 0, 0);

            vector unit_direction = r.direction.normalizar();
            auto a = 0.5*(unit_direction.getY() + 1.0);
            return vector(1.0, 1.0, 1.0)*(1.0-a) + vector(0.5, 0.7, 1.0)*a; 
    }

};
#endif
