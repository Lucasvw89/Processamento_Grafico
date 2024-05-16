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
    double hit(ray& ray) {
        double t;

        vetor D = ray.getDirection();
        point O = ray.getOrigin();

        // Verifica se o raio é paralelo ao plano
        double denominator = this->normal.produto_escalar(D);

        // Se o denominador for zero, o raio é paralelo ao plano, então não há interseção
        if (std::abs(denominator) < 1e-6) {
            return INFINITY;
        }

        // Calcula o parâmetro t da interseção
        t = normal.produto_escalar(this->ponto - O) / denominator;

        return t;
    }
};

#endif
