#ifndef COLORHEADER
#define COLORHEADER

#include <iostream>
#include <cmath>

using namespace std;

class color
{
public:
	double red;
	double green;
	double blue;
	
	// valor padrão cinza pra objeto não ficar invisível: pode trocar depois
	color()
	{
		this->red = 0.5;
		this->green = 0.5;
		this->blue = 0.5; 
	}

	color(double r, double g, double b)
	{
		this->red = r;
		this->green = g;
		this->blue = b; 
	}
};

#endif
