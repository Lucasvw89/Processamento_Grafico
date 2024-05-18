#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "src/Camera.cpp"
#include "src/Plane.cpp"
#include "src/Vector.cpp"
#include "src/Sphere.cpp"

using namespace std;

int main() {
    //IMAGEM
    
    std::vector<object*> objetos;

    double r_esfera = 0.5;
    
    point p_esfera1(2,0,0);
    vetor cor1(1, 0, 0); // vermelho

    point p_esfera2(5,0,0);
    vetor cor2(0, 1, 0); // verde

    point p_esfera3(8,0,0);
    vetor cor3(0, 0, 1); // azul

    point p_esfera4(-1,0,0);
    vetor cor4(1, 1, 0); // amarelo

    point p_esfera5(0,-1,0);
    vetor cor5(0, 1, 1); // ciano

    point p_esfera6(0,0,-1);
    vetor cor6(1, 0, 1); // rosa

    //CAMERA
    point pos_cam(0,0,0);
    point target_cam(1,0.3,0);
    vetor up_cam(0,1,0);

    point ponto_plano(1,0,0);
    vetor normal_plano(1, 0, 0);
    

    vetor cor_plano(0, 0, 1);

    sphere esfera1(p_esfera1, 0.5, cor1);
    sphere esfera2(p_esfera2, 2, cor2);
    sphere esfera3(p_esfera3, 4, cor3);
    sphere esfera4(p_esfera4, r_esfera, cor4);
    sphere esfera5(p_esfera5, r_esfera, cor5);
    sphere esfera6(p_esfera6, r_esfera, cor6);

    plane plano(ponto_plano, normal_plano, cor_plano);

    objetos.push_back(&esfera1);
    objetos.push_back(&esfera2);
    objetos.push_back(&esfera3);
    objetos.push_back(&esfera4);
    objetos.push_back(&esfera5);
    objetos.push_back(&esfera6);

    camera cam(400, pos_cam, target_cam, up_cam);
    cam.render(objetos);


    return 0;
}
