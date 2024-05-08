#include <iostream>
#include "../include/Vector.hpp"


Vector::Vector(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

// Getters
double Vector::getX() const{
    return this->x;
}

double Vector::getY() const{
    return this->y;
}

double Vector::getZ() const{
    return this->z;
}

// Setters
void Vector::setX(double x){
    this->x = x;
}

void Vector::setY(double y){
    this->y = y;
}

void Vector::setZ(double z){
    this->z = z;
}

/*
Printa as coordenadas do vetor no terminal
*/
void Vector::print() const{
    std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
}

// Operators
/*
Recebe como parâmetro um vetor e retorna um >>novo vetor<< com os valores somados
*/
Vector Vector::soma_de_vetor(const Vector& v) const {
    return Vector(this->x + v.getX(), this->y + v.getY(), this->z + v.getZ());
}


/*
    Recebe o vetor e retorna o produto vetorial entre eles, seguindo o cálculo da matriz
    | i j k |
    | x y z |
    | a b c |
*/
Vector Vector::produto_vetorial(const Vector& v) const {
    return Vector(
                (this->y * v.getZ()) - (this->z * v.getY()), // i
                (this->z * v.getX()) - (this->x * v.getZ()), // j
                (this->x * v.getY()) - (this->y * v.getX())  // k
                );
}

/*
Retorna a norma do vetor
*/
double Vector::norma() const {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}


/*
Normaliza o vetor (Vetor unitário)
*/
void Vector::normalizar(){
    double norma = (1 / this->norma());
    
    this->x = this->x * norma;
    this->y = this->y * norma;
    this->z = this->z * norma;
}

/*
Recebe um vetor e retorna o produto escalar entre eles
*/
double Vector::produto_escalar(const Vector& v) const{
    return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ();
}

/*
Recebe um escalar (double) e retorna um novo Vector com os valores multiplicados
*/
Vector Vector::multiplicar_escalar(double escalar) const{
    return Vector(this->x * escalar, this->y * escalar, this->z * escalar);
}

/*
    Recebe um Vector e retorna a projeção vetorial de V no vetor atual.
*/
Vector Vector::projecao_vetorial(const Vector& v) const{
    double temp = this->produto_escalar(v) / this->norma()*this->norma();

    return this->multiplicar_escalar(temp);
}
