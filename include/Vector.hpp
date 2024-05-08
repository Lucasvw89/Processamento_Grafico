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
    Vector soma_de_vetor(const Vector& v) const;      // Soma dois vetores e retorna o resultado
    Vector produto_vetorial(const Vector& v) const;   // Calcula o produto vetorial com outro vetor
    double norma() const;                             // Calcula a norma do vetor
    double produto_escalar(const Vector& v) const;    // Calcula o produto escalar com outro vetor
    Vector multiplicar_escalar(double escalar) const; // Multiplica o vetor por um escalar
    Vector projecao_vetorial(const Vector& v) const;  // Calcula a projeção vetorial deste vetor em outro vetor
    void normalizar();                                // Normaliza o vetor
};

#endif // VECTOR_HPP
