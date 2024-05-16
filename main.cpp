#include <iostream>
#include <fstream>
#include "src/Camera.cpp"
#include "src/Vector.cpp"
#include "src/Sphere.cpp"
using namespace std;



int main() {
    //IMAGEM

    vector v1(1, 1, 0);
    vector v2(1, 0, 0);
    // std::cout << v1.norma() << std::endl;
    point p1(1,2,3);
    point p2(4,5,7);
    camera cam(400,p1, p2, v1);
    cam.render();


    return 0;
}
