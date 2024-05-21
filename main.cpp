#include <complex>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "src/Camera.cpp"
#include "src/Plane.cpp"
#include "src/Vector.cpp"
#include "src/Sphere.cpp"
#include "src/Triangle.cpp"
#include "src/ObjReader.cpp"

using namespace std;

int main() {
    
    //objReader reader("input.obj");
    
    vector<object*> objs_list;

    camera cam(1080, point(0,0,0), point(1,0,0), vetor(0,1,0), 16.0/9.0, 1);

    point A(2, -1, 1);
    point B(2, 1, 0);
    point C(2, 0, 2);

    vetor normal((B-A).produto_vetorial(C-A).normalizar());

    vetor cor(1,1,1);

    point orig((A.getX() + B.getX() + C.getX()) / 3,
               (A.getY() + B.getY() + C.getY()) / 3,
               (A.getZ() + B.getZ() + C.getZ()) / 3);

    triangle teste(normal, cor, A, B, C);

    objs_list.push_back(&teste);

    cam.render(objs_list);
    

    return 0;
}
