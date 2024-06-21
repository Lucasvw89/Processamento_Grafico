#ifndef TRIANGLEHEADER
#define TRIANGLEHEADER

#include "Object.cpp"
#include "Point.cpp"
#include <math.h>

# define M_PI 3.14159265358979323846  /* pi */
# define ANGLE_TO_RAD M_PI/180        /* Valor usado na conversão de grau para radiano */

class triangle: public object {

private:
    point origem;
    point A;
    point B;
    point C;
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
    triangle(vetor& normal,
             point& A,
             point& B,
             point& C,
             vetor& kd,
             vetor& ks,
             vetor& ke,
             vetor& ka,
             double ns,
             double ni,
             double d)

           : object(kd),
             normal(normal),
             A(A),
             B(B),
             C(C),
             kd(kd),
             ks(ks),
             ke(ke),
             ka(ka),
             ns(ns),
             ni(ni),
             d(d)
    {
        this->origem = point((A.getX() + B.getX() + C.getX()) / 3,
                            (A.getY() + B.getY() + C.getY()) / 3,
                            (A.getZ() + B.getZ() + C.getZ()) / 3);
        this->normal = (B-C).produto_vetorial(C-A).normalizar();
    }

    // Construtor sem cor
    triangle(vetor& normal, point& A, point B, point C)
        : object(vetor(1, 1, 1)), normal(normal), A(A), B(B), C(C)
    {
        this->origem = point((A.getX() + B.getX() + C.getX()) / 3,
                            (A.getY() + B.getY() + C.getY()) / 3,
                            (A.getZ() + B.getZ() + C.getZ()) / 3);
        this->normal = (B-C).produto_vetorial(C-A).normalizar();
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

    void rotacao(double angle, char eixo, point centroide) override {
        this->translacao(-centroide.getX(), -centroide.getY(), -centroide.getZ());

        double matrix[3][3] = {0};

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
            matrix[0][0] = cosAngulo; matrix[0][1] = -sinAngulo; matrix[0][2] = 0;
            matrix[1][0] = sinAngulo; matrix[1][1] = cosAngulo;  matrix[1][2] = 0;
            matrix[2][0] = 0;         matrix[2][1] = 0;          matrix[2][2] = 1;
        } else {
            return; // Eixo inválido
        }

        this->A = this->A * matrix;
        this->B = this->B * matrix;
        this->C = this->C * matrix;

        this->origem = this->calcularOrigem();
        this->normal = (B - C).produto_vetorial(C - A).normalizar();

        this->translacao(centroide.getX(), centroide.getY(), centroide.getZ());
    }

    void translacao(double dx, double dy, double dz) override {
        this->A = this->A + point(dx, dy, dz);
        this->B = this->B + point(dx, dy, dz);
        this->C = this->C + point(dx, dy, dz);
        this->origem = calcularOrigem();
    }

    void cisalhamento(double shXY, double shXZ, double shYX, double shYZ, double shZX, double shZY) override {
        double matrix[3][3];

        // Matriz de cisalhamento
        // | 1     shXY  shXZ |
        // | shYX  1     shYZ |
        // | shZX  shZY  1    |
        matrix[0][0] = 1;   matrix[0][1] = shXY; matrix[0][2] = shXZ;
        matrix[1][0] = shYX; matrix[1][1] = 1;   matrix[1][2] = shYZ;
        matrix[2][0] = shZX; matrix[2][1] = shZY; matrix[2][2] = 1;

        this->A = this->A * matrix;
        this->B = this->B * matrix;
        this->C = this->C * matrix;

        this->origem = calcularOrigem();
        this->normal = (B-C).produto_vetorial(C-A).normalizar();
    }

    point calcularOrigem() {
        return point((A.getX() + B.getX() + C.getX()) / 3,
                    (A.getY() + B.getY() + C.getY()) / 3,
                    (A.getZ() + B.getZ() + C.getZ()) / 3);
    }
    
    // Getters
    point getPonto() override { return this->origem; }
    point getA() const { return this->A; }
    point getB() const { return this->B; }
    point getC() const { return this->C; }
    vetor getNormal() override { return this->normal; }

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
