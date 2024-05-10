#include <iostream>
#include <cmath>
using namespace std;
#include "Point.cpp"


class sphere
{
private:
    point center;
    double radius;
public:
    sphere() {}
    sphere(point center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }
};