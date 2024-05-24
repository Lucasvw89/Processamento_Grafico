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
#include "src/Mesh.cpp"
#include "src/Colormap.cpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    colormap cmap;

    objReader reader("input.obj", cmap);
    
    //vector<object> objs_list;


    point pos_cam(0,0,0);
    point target_cam(0,0,0);
    vetor up_cam(0,1,0);
    camera cam(400, point(3,-1,5), point(0,0,0), vetor(0,1,0), 16.0/9.0, 1.5);

    point centro_sfer = point(0,1,0);
    vetor cor = vetor(1,1,1);
    sphere bolinha_maluka(centro_sfer, 3, cor);

    vetor normali = vetor(0,1,0);

    plane planinho(point(0,1,0), normali, cor);
    // point p = point(0,0,0);
    // double d = 10.0;
    // sphere esfera(p, d, vetor(1,0,0));

    // objs_list.push_back(&esfera);

    vector<object*> triangulos = reader.getTriangles();
    triangulos.push_back(&bolinha_maluka);
    // triangulos.push_back(&planinho);

    //for (auto t : triangulos) objs_list.push_back(&t);

    cam.render(triangulos);

    return 0;
}
