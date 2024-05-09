#include <iostream>
#include <cmath>

using namespace std;

class color
{
private:
	double red;
	double green;
	double blue;
public:
	
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

	// getters
	double getR(){return this->red;}
	double getG(){return this->green;}
	double getB(){return this->blue;}

	// setters
	void setR(double r){ this->red = r;}
	void setR(double g){ this->green = g;}
	void setR(double b){ this->blue = b;}
};