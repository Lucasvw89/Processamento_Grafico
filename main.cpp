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



    vetor v1(0, 1, 0);
    vetor v2(1, 0, 0);
    // std::cout << v1.norma() << std::endl;
    point p1(100,0,0);
    point p2(1,0,0);

    sphere esfera(p1, 5, v1);
    plane plano(p2, v1, v2);

    objetos.push_back(&esfera);
    objetos.push_back(&plano);

    camera cam(400,p1, p2, v1);
    cam.render(objetos);


    return 0;
}
