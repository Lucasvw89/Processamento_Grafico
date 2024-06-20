#ifndef OBJECTHEADER
#define OBJECTHEADER

#include "Point.cpp"
#include "Vector.cpp"
#include "Ray.cpp"

class object {
protected:
    vetor color;

public:
    // Construtor
    object(){};
    object(const vetor& color){
        this->color = color;
    }
    
    vetor getColor() const { return color; }
    void setColor(const vetor& color) { this->color = color; }
    
    virtual point getPonto() = 0;
    virtual vetor getNormal() = 0;
    virtual double getShininess() = 0;
    virtual double intersect(ray &r) = 0;
    virtual void rotacao(double angle, char eixo, point centroide) = 0;
    virtual void translacao(double dx, double dy, double dz) = 0;
    virtual void cisalhamento(double shXY, double shXZ, double shYX, double shYZ, double shZX, double shZY) = 0;

    virtual vetor getKd() = 0;
    virtual  vetor getKs() = 0;
    virtual vetor getKe() = 0;
    virtual vetor getKa() = 0;
    virtual double getNi() = 0;
    virtual double getD() = 0;

    virtual ~object() {}
};

#endif
