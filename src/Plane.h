#ifndef PLANEHEADER
#define PLANEHEADER

#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "Ray.h"

using namespace std;

class plane
{
public:
	vector p; // vetor ao invés de ponto para compatibilidade com operações
	vector normal;
	color c;

	plane(vector p, vector normal, color c)
	{
		this->p = p;
		this->normal = normal;
		this->c = c;
	}
	
	// intersessão: 
		// retorna parâmetro do vetor ray.direction em que houve intersessão,
		// ou inf
	double hit(const& ray raio)
	{
		double t;
		vector O,D;

		O = raio.origin;
		D = raio.direction;
		// divisão por zero com doubles retorna inf pela norma do c++: sem RTE
		t = ( normal.produto_escalar((p-O)) / normal.produto_escalar(D) );

		return t;
	}

};
