#ifndef TRIANGLEHEADER
#define TRIANGLEHEADER

#include "Object.cpp"
#include "Point.cpp"

class triangle: private object {

private:
    point origem;
    point A;
    point B;
    point C;
    vetor normal;

public:
    // Construtor
    triangle(point origem, vetor& normal, vetor& color, point& A, point B, point C)
        : object(color), normal(normal), origem(origem), A(A), B(B), C(C) {}


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
        vetor v1 = B - A;
        vetor v2 = C - A;

		return t;
    }
    
    //Getters
    point getPonto() const { return this->origem; }
    point getA() const { return this->A; }
    point getB() const { return this->B; }
    point getC() const { return this->C; }

};

#endif
