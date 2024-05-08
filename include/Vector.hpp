#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cmath>

class Vector {
private:
    double x; // Componente x do vetor
    double y; // Componente y do vetor
    double z; // Componente z do vetor

public:
    // Construtor da classe Vector
    Vector(double x, double y, double z);

    // Getters
    double getX() const;
    double getY() const;
    double getZ() const;

    // Setters
    void setX(double x); 
    void setY(double y); 
    void setZ(double z); 

    // Imprime as coordenadas do vetor no terminal
    void print() const;

    // Operações
    void normalizar();                                // Normaliza o vetor
    double norma() const;                             // Calcula a norma do vetor
    double produto_escalar(const Vector& v) const;    // Calcula o produto escalar com outro vetor
    Vector projecao_vetorial(const Vector& v) const;  // Calcula a projeção vetorial deste vetor em outro vetor
    Vector produto_vetorial(const Vector& v) const;   // Calcula o produto vetorial com outro vetor
};

#endif // VECTOR_HPP
