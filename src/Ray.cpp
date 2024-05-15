#ifndef RAYHEADER
#define RAYHEADER

#include <iostream>
#include <cmath>
#include "Vector.cpp"
#include "Point.cpp"

using namespace std;

class ray
{
public:
	point origin; // vetor e não ponto para facilitar produto escalar no cálculo de intersessão
	vector direction;

	ray(point origin, vector direction)
	{
		this->origin = origin;
		this->direction = direction;
	}

	// função paramétrica: retornar ponto a partir de parâmetro
	point f(double t)
	{
		point O = point(origin.getX(),origin.getY(),origin.getZ());
		return O + (direction * t );
	}

};

#endif
