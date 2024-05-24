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

    objReader reader("./input/piramide_de_ryei.obj", cmap);


    point pos_cam(0,0,0);
    point target_cam(0,0,0);
    vetor up_cam(0,1,0);
    camera cam(400, point(3,-2,5), point(0,0,0), vetor(0,1,0), 16.0/9.0, 1.5);

    point centro_sfer = point(0,1,0);
    vetor cor = vetor(1,1,1);
    sphere bolinha_maluka(centro_sfer, 3, cor);

    vetor normali = vetor(0,1,0);

    plane planinho(point(0,1,0), normali, cor);

    vector<object*> triangulos = reader.getTriangles();

    cam.render(triangulos);

    return 0;
}
