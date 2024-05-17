#ifndef PLANEHEADER
#define PLANEHEADER

#include "Object.cpp"
#include "Vector.cpp"
#include "Ray.cpp"

class plane : public object {
private:
    vetor normal;

public:
    // Construtor
    plane(point origem, vetor& normal, vetor& color)
        : object(origem, color), normal(normal) {}

    // Método para calcular a interseção com o plano
    double intersect(ray& ray) override {
        double t;
        vetor D = ray.getDirection();
        point O = ray.getOrigin();

        vetor plano_orig = vetor(this->getPonto().getX(), this->getPonto().getY(), this->getPonto().getZ());
        vetor raio_orig = vetor(ray.getOrigin().getX(), ray.getOrigin().getY(), ray.getOrigin().getZ());

        t = normal.produto_escalar(plano_orig) - normal.produto_escalar(raio_orig)/ normal.produto_escalar(ray.getDirection());

		return t;
    }
};

#endif
