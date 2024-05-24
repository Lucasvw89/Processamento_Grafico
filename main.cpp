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

    objReader reader("./input/mamaco.obj", cmap);


    point pos_cam(0,0,0);
    point target_cam(0,0,0);
    vetor up_cam(0,1,0);
    camera cam(1080, point(3,0.5,5), point(0,0,0), vetor(0,1,0), 16.0/9.0, 5);

    point centro_sfer = point(0,1,0);
    vetor cor = vetor(1,1,1);
    sphere bolinha_maluka(centro_sfer, 3, cor);

    vetor normali = vetor(0,1,0);

    plane planinho(point(0,1,0), normali, cor);

    vector<object*> triangulos = reader.getTriangles();

    // ALEATORIZARR CORES
    // for (int i = 0; i < triangulos.size(); i++) { 
    //     double random = rand() % 255;
    //     double rand1 = random / 255.0;
    //     random = rand() % 255;
    //     double rand2 = random / 255.0;
    //     random = rand() % 255;
    //     double rand3 = random / 255.0;

    //     vetor cor(rand1, rand2, rand3);
    //     triangulos[i]->setColor(cor);
    // }

    cam.render(triangulos);

    return 0;
}
