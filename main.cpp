#include <iostream>
#include <fstream>
#include <vector>
#include "src/Camera.cpp"
#include "src/Plane.cpp"
#include "src/Vector.cpp"
#include "src/Sphere.cpp"

using namespace std;

int main() {
    //IMAGEM
    
    std::vector<object*> objetos;

    //Sistema (x,z,y)

    point p_esfera(0,0,-1);
    double r_esfera = 0.5;
    vetor v1(0, 0, 1);
    vetor cor (1, 0, 0);
    vetor v2(0, 0, 1);
    // std::cout << v1.norma() << std::endl;
    point p1(1,1,-1);
    point p2(0,0,0);
    point p3(1,0,0);

    point ponto_plano(0,0,1);
    vetor normal_plano(0, 1, 0);
    

    vetor cor_plano(0, 0, 1);

    sphere esfera(p_esfera, 0.5, cor);
    sphere esfera1(p1, 0.5, cor);
    plane plano(ponto_plano, normal_plano, cor_plano);

    objetos.push_back(&esfera);
    objetos.push_back(&esfera1);
    objetos.push_back(&plano);

    camera cam(400, p2, p3, v1);
    cam.render(objetos);


    return 0;
}
