#ifndef TRIANGLEHEADER
#define TRIANGLEHEADER

#include "Object.cpp"
#include "Point.cpp"
#include <cmath>

class triangle: public object {

private:
    point origem;
    point A;
    point B;
    point C;
    vetor normal;

public:
    // Construtor
    triangle(vetor& normal, vetor& color, point& A, point B, point C)
        : object(color), normal(normal), A(A), B(B), C(C) 
    {
        this->origem = point((A.getX() + B.getX() + C.getX()) / 3,
                             (A.getY() + B.getY() + C.getY()) / 3,
                             (A.getZ() + B.getZ() + C.getZ()) / 3);
    }


    double intersect(ray& ray) override {
        double t;

        vetor plano_orig = vetor(this->getPonto().getX(),
                                 this->getPonto().getY(),
                                 this->getPonto().getZ());

        vetor raio_orig = vetor(ray.getOrigin().getX(),
                                ray.getOrigin().getY(),
                                ray.getOrigin().getZ());

        t = (normal.produto_escalar(plano_orig) - normal.produto_escalar(raio_orig))/ normal.produto_escalar(ray.getDirection());

        point P = ray.f(t);     // ponto que intersecta o plano
        vetor v1 = B - A,
              v2 = C - A,
              v3 = P - A;

        double d00 = v1.produto_escalar(v1),
               d01 = v1.produto_escalar(v2),
               d11 = v2.produto_escalar(v2),
               d20 = v3.produto_escalar(v1),
               d21 = v3.produto_escalar(v2);

        double denom = d00 * d11 - d01 * d01;

        double v = (d11 * d20 - d01 * d21) / denom;
        double w = (d00 * d21 - d01 * d20) / denom;
        double u = 1.0f - v - w;

        if (v >= 0 && v <= 1 &&
            w >= 0 && v <= 1 &&
            u >= 0 && v <= 1)
            return t;

        else
            return INFINITY;
    }
    
    //Getters
    point getPonto() const { return this->origem; }
    point getA() const { return this->A; }
    point getB() const { return this->B; }
    point getC() const { return this->C; }

};

#endif
