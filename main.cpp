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

point calcular_centroide(std::vector<object*>& triangulos) {
    double somaX = 0;
    double somaY = 0;
    double somaZ = 0;
    int numTriangulos = triangulos.size();
    point centro;
    for (int i = 0; i < numTriangulos; i++) {
        centro = triangulos[i]->getPonto();
        somaX += centro.getX();
        somaY += centro.getY();
        somaZ += centro.getZ();
    }

    double centroComumX = somaX / numTriangulos;
    double centroComumY = somaY / numTriangulos;
    double centroComumZ = somaZ / numTriangulos;

    return point(centroComumX, centroComumY, centroComumZ);
}

void rotacao(vector<object*>& triangulos, double angle, char eixo) {
    point distancia = calcular_centroide(triangulos);
    distancia.print();
    for (int i = 0; i < triangulos.size(); i++) {
        triangulos[i]->rotacao(angle, eixo, distancia);
    }
}

void translacao(vector<object*>& triangulos, double dx, double dy, double dz) {
    for (int i = 0; i < triangulos.size(); i++) {
        triangulos[i]->translacao(dx, dy, dz);
    }
}

void cisalhamento(vector<object*>& triangulos, double shXY, double shXZ, double shYX, double shYZ, double shZX, double shZY) {
    for (int i = 0; i < triangulos.size(); i++) {
        triangulos[i]->cisalhamento(shXY, shXZ, shYX, shYZ, shZX, shZY);
    }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    colormap cmap;

    objReader reader("./input/cubo.obj", cmap);


    point pos_cam(6,2,2);
    point target_cam(0,0,0);
    vetor up_cam(0,1,0);

    camera cam(400, pos_cam, target_cam, up_cam, 16.0/9.0, 1);

    point origem_esfera(0,0,0);

    // vetor normal_plano(0,1,0);

    // vetor cor(0.4,0,0.4);
    // vetor kd = vetor(0.5, 0, 0);
    // vetor ks = vetor(0.7, 0, 0);
    // vetor ke = vetor(0.000000, 0.000000, 0.000000);
    // vetor ka = vetor(0.6, 1, 1);
    // double ns = 10.000000;
    // double ni = 1.450000;
    // double d = 1.000000;
    // sphere esfera = sphere(origem_esfera, 2, cor, kd,ks,ke,ka, ns, ni, d);
    // vector<object*> triangulos;
    // triangulos.push_back(&esfera);

    
    vector<object*> triangulos = reader.getTriangles();

    vector<light> lts;
    point lt_pos(2.2,0,0);
    vetor lt_color(0.4,0.4,0.4);
    light lt(lt_pos,lt_color);
    lts.push_back(lt);

    vetor ambiente_color(0.1,0.1,0.1);
    cam.render(triangulos, lts, ambiente_color);

    return 0;
}
