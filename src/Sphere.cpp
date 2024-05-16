#ifndef SPHEREHEADER
#define SPHEREHEADER
#include <iostream>
#include <cmath>
#include "Object.cpp"
#include "Vector.cpp"
#include "Point.cpp"
#include "Ray.cpp"

class sphere : public object{
    public:
        double radius;

        sphere(point center, double radius, vetor color) : object(center, color), radius(radius) {}

        point getCenter() const { return this->ponto; }

        bool hit_sphere(/*point/* &  center, double radius,*/ ray& r) {
            vetor oc = this->getCenter() - r.origin;
            auto a = r.direction.produto_escalar(r.direction);
            auto b = -2.0 * r.direction.produto_escalar(oc);
            auto c = oc.produto_escalar(oc) - radius*radius;
            auto discriminant = b*b - 4*a*c;
            return (discriminant >= 0);
        }
    
        // vetor ray_color(ray& r) {
        //     if (hit_sphere(point(0,0,-1), 0.5, r))
        //         return vetor(1, 0, 0);

        //     vetor unit_direction = r.direction.normalizar();
        //     auto a = 0.5*(unit_direction.getY() + 1.0);
        //     return vetor(1.0, 1.0, 1.0)*(1.0-a) + vetor(0.5, 0.7, 1.0)*a; 
        // }

        void render()
        {
            
        }       
};
#endif
