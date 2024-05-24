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

    objReader reader("./input/cubo.obj", cmap);


    point pos_cam(0,0,0);
    point target_cam(0,0,0);
    vetor up_cam(0,1,0);
    camera cam(400, point(3,0,5), point(0,0,0), vetor(0,1,0), 16.0/9.0, 1.5);

    vector<object*> triangulos = reader.getTriangles();
    
    for (int i = 0; i < triangulos.size(); i++){
        triangulos[i]->rotacao(45, 'Y');
    }

    cam.render(triangulos);

    return 0;
}
