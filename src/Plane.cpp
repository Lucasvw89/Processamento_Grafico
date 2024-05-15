#ifndef PLANEHEADER
#define PLANEHEADER

#include <iostream>
#include <cmath>
#include "Vector.cpp"
#include "Point.cpp"
#include "Ray.cpp"

using namespace std;

class plane
{
public:
	vector p; // vetor ao invés de ponto para compatibilidade com operações
	vector normal;
	vector color;

	plane(vector p, vector normal, vector color)
	{
		this->p = p;
		this->normal = normal;
		this->color = color;
	}
	
	// intersessão: 
		// retorna parâmetro do vetor ray.direction em que houve intersessão,
		// ou inf
	double hit(ray raio)
	{
		double t;
		vector D = raio.direction;
		vector O(raio.origin.getX(), raio.origin.getY(), raio.origin.getZ());

		// divisão por zero com doubles retorna inf pela norma do c++: sem RTE
		t = ( normal.produto_escalar((p-O)) / normal.produto_escalar(D) );

		return t;
	}

};

#endif