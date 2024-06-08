#ifndef SPHEREHEADER
#define SPHEREHEADER
#include <iostream>
#include <cmath>
#include "Object.cpp"
#include "Vector.cpp"
#include "Point.cpp"
#include "Ray.cpp"

class sphere : public object{
    private:
        double ta;
        ray* ra;

    public:
        point center;
        double radius;

        sphere(point center, double radius, vetor color) : object(color), radius(radius), center(center) {}

        point getPonto() override { return this->center; }

        double intersect(ray &r) override {
            double t;

            vetor oc = (r.origin) - (this->getPonto());
            double a = r.direction.produto_escalar(r.direction);
            double b = 2.0 * oc.produto_escalar(r.direction);
            double c = oc.produto_escalar(oc) - (this->radius * this->radius);
            double delta = (b * b) - (4 * a * c);
            if (delta >= 0)
            {
                t = (-b - sqrt(delta)) / 2 * a;

                if (t < 0){
                    t = (-b + sqrt(delta)) / 2 * a;
                }
            }
            else{
                t = -1;
            }
            this->ra = &r;
            this->ta = t;
            
            return t;
            
        }

        virtual vetor getNormal() override {
            point ponto_intersecao = ra->f(this->ta);
            return (ponto_intersecao - this->center).normalizar();
        };

        void translacao(double dx, double dy, double dz){
            this->center = this->center + point(dx, dy, dz);
        }

        void rotacao(double angle, char eixo, point centroide){};
        void cisalhamento(double shXY, double shXZ, double shYX, double shYZ, double shZX, double shZY){};
};
#endif
