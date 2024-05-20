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
    object(const vetor& color){
        this->color = color;
    }

    void setColor(const vetor& color) { this->color = color; }
    vetor getColor() const { return color; }
    virtual double intersect(ray &r) = 0;


    virtual ~object() {}
};

#endif
