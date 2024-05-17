#ifndef OBJECTHEADER
#define OBJECTHEADER

#include "Point.cpp"
#include "Vector.cpp"
#include "Ray.cpp"

class object {
protected:
    point ponto;
    vetor color;

public:
    // Construtor
    object(const point& ponto, const vetor& color){
        this->ponto = ponto;
        this->color = color;
    }

    void setColor(const vetor& color) { this->color = color; }
    void setPonto(const point& ponto) { this->ponto = ponto; }
    point getPonto() const { return ponto; }
    vetor getColor() const { return color; }
    virtual double intersect(ray &r) = 0;


    virtual ~object() {}
};

#endif
