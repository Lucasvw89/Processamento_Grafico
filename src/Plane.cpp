#ifndef PLANEHEADER
#define PLANEHEADER

#include "Object.cpp"
#include "Vector.cpp"
#include "Ray.cpp"

# define M_PI 3.14159265358979323846  /* pi */
# define ANGLE_TO_RAD M_PI/180        /* Valor usado na conversão de grau para radiano */

class plane : public object {
private:
    point ponto;
    vetor normal;

    vetor kd;  // Difuso
    vetor ks;  // Specular
    vetor ke;  // Emissivo
    vetor ka;  // Ambiente
    double ns; // Brilho
    double ni; // Índice de refração
    double d;  // Opacidade

public:
    // Construtor
    plane(point origem,
          vetor normal,
          vetor& color,
          vetor& kd,
          vetor& ks,
          vetor& ke,
          vetor& ka,
          double ns,
          double ni,
          double d)

        : object(color),
          normal(normal),
          ponto(origem),
          kd(kd),
          ks(ks),
          ke(ke),
          ka(ka),
          ns(ns),
          ni(ni),
          d(d) {}

    // Método para calcular a interseção com o plano
    double intersect(ray& ray) override {
        double t;

        vetor plano_orig = vetor(this->getPonto().getX(), this->getPonto().getY(), this->getPonto().getZ());
        vetor raio_orig = vetor(ray.getOrigin().getX(), ray.getOrigin().getY(), ray.getOrigin().getZ());

        t = (normal.produto_escalar(plano_orig) - normal.produto_escalar(raio_orig))/ normal.produto_escalar(ray.getDirection());

		return t;
    }

    void translacao(double dx, double dy, double dz) override {
        this->ponto = this->ponto + point(dx, dy, dz);
    };

    void rotacao(double angle, char eixo, point centroide) override {
        point ponto_temp = this->ponto;

        this->translacao(-centroide.getX(), -centroide.getY(), -centroide.getZ());

        double matrix[3][3];
        double rad = angle * ANGLE_TO_RAD;
        double cosAngulo = cos(rad);
        double sinAngulo = sin(rad);

        if (eixo == 'X' || eixo == 'x') {
            // Matriz de rotação no eixo X
            matrix[0][0] = 1; matrix[0][1] = 0;         matrix[0][2] = 0;
            matrix[1][0] = 0; matrix[1][1] = cosAngulo; matrix[1][2] = -sinAngulo;
            matrix[2][0] = 0; matrix[2][1] = sinAngulo; matrix[2][2] = cosAngulo;
        } else if (eixo == 'Y' || eixo == 'y') {
            // Matriz de rotação no eixo Y
            matrix[0][0] = cosAngulo; matrix[0][1] = 0; matrix[0][2] = sinAngulo;
            matrix[1][0] = 0;         matrix[1][1] = 1; matrix[1][2] = 0;
            matrix[2][0] = -sinAngulo; matrix[2][1] = 0; matrix[2][2] = cosAngulo;
        } else if (eixo == 'Z' || eixo == 'z') {
            // Matriz de rotação no eixo Z
            matrix[0][0] = cosAngulo; matrix[0][1] = sinAngulo; matrix[0][2] = 0;
            matrix[1][0] = -sinAngulo; matrix[1][1] = cosAngulo;  matrix[1][2] = 0;
            matrix[2][0] = 0;         matrix[2][1] = 0;          matrix[2][2] = 1;
        } else {
            // Se o eixo for inválido, não faz nada
            return;
        }

        // Aplicando a matriz de rotação à normal do plano
        this->normal = this->normal * matrix;
        this->normal = this->normal.normalizar();

        this->translacao(centroide.getX(), centroide.getY(), centroide.getZ());
    }



    void cisalhamento(double shXY, double shXZ, double shYX, double shYZ, double shZX, double shZY) override {return;};

    // Getters
    point getPonto() override { return this->ponto; }
    virtual vetor getNormal() override { return this->normal; }

    // Getters para propriedades do material
    vetor getKd() override {return kd;}
    vetor getKs() override {return ks;}
    vetor getKe() override {return ke;}
    vetor getKa() override {return ka;}
    double getNi() override {return ni;}
    double getD() override {return d;}
    double getShininess() override { return ns; }

};

#endif
