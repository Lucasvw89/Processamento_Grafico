#ifndef POINTRHEADER
#define POINTRHEADER

#include <iostream>
#include <cmath>
using namespace std;
#include "Vector.cpp"

class point
{
private:
    double x;
    double y;
    double z;
public:

    point() {}
    point(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Getters
    double getX(){
        return this->x;
    }

    double getY(){
        return this->y;
    }

    double getZ(){
        return this->z;
    }

    // Setters
    void setX(double x){
        this->x = x;
    }

    void setY(double y){
        this->y = y;
    }

    void setZ(double z){
        this->z = z;
    }

    void print(){
        cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << "\n";
    }


    inline point operator+(vetor v1)
    {
        return point(v1.getX() + this->getX(), v1.getY() + this->getY(), v1.getZ() + this->getZ());
    }

    inline point operator+(point p1)
    {
        return point(p1.getX() + this->getX(), p1.getY() + this->getY(), p1.getZ() + this->getZ());
    }

    inline point operator+(double h)
    {
        return point(h + this->getX(), h + this->getY(), h + this->getZ());
    }


    inline point operator-(vetor v1)
    {
        return point(this->getX() - v1.getX(), this->getY() - v1.getY(), this->getZ() - v1.getZ());
    }

    inline vetor operator-(point p1)
    {
        return vetor(this->getX() - p1.getX(), this->getY() - p1.getY(), this->getZ() - p1.getZ());
    }

    inline void operator=(point p1)
    {
        this->setX(p1.getX());
        this->setY(p1.getY());
        this->setZ(p1.getZ());
    }

/// ||(p1-p2)||²
    double sqr_norm(point p2)
    {
        double norm =pow(this->getX() - p2.getX(),2) + pow(this->getY() - p2.getY(),2) + pow(this->getZ() - p2.getZ(),2);
        return norm;
    }       

/// ||(p1-p2)||
    double norm(point p2)
    {
        double norm =pow(this->getX() - p2.getX(),2) + pow(this->getY() - p2.getY(),2) + pow(this->getZ() - p2.getZ(),2);
        return sqrt(norm);
    }

};

#endif