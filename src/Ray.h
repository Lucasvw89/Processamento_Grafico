#ifndef RAYHEADER
#define RAYHEADER

#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Point.h"
#include "Color.h"

using namespace std;

class ray
{
public:
	vector origin; // vetor e não ponto para facilitar produto escalar no cálculo de intersessão
	vector direction;

	ray(vector origin, vector direction)
	{
		this->origin = origin;
		this->direction = direction;
	}

	// função paramétrica: retornar ponto a partir de parâmetro
	point f(double t)
	{
		point O = point(origin.getX(),origin.getY(),origin.getZ());
		return O + (direction.multiplicar_escalar(t));
	}

};

#endif
