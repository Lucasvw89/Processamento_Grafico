#include <algorithm>
#include <cmath>
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


vector<object*> create_torus(double R, double r, int small_rad_sub, int big_rad_sub, vetor kd, vetor ks, vetor ke, vetor ka, double ns, double ni, double d) {

    const double PI = 3.1415926;

    triangle* tri1;
    triangle* tri2;

    vector<object*> torus_triangles;
    vector<vector<point> > points(big_rad_sub);

    double small_angle_increment = (2*PI) / small_rad_sub;
    double big_angle_increment = (2*PI) / big_rad_sub;

    if (r == R) { r += 0.0000001; }

    // create torus points
    for (int i = 0; i < big_rad_sub; i++) {
        double curr_big_angle = i * big_angle_increment;

        // create polygon points
        for (int j = 0; j < small_rad_sub; j++) {
            double curr_small_angle = j * small_angle_increment;

            double x_pos = ((cos(curr_small_angle) * r) + R) * cos(curr_big_angle);
            double y_pos = (sin(curr_small_angle) * r);
            double z_pos = ((cos(curr_small_angle) * r) + R) * sin(curr_big_angle);

            point new_point(x_pos, y_pos, z_pos);
            new_point.print();

            points[i].push_back(new_point);
        }

    }

    // create all trangles
    for (int i = 0; i < big_rad_sub; i++) {
        for (int j = 0; j < small_rad_sub; j++) {

            vetor norm(0,0,0);

            point a1 = points[i][j];
            point b1 = points[(i+1) % big_rad_sub][j];
            point c1 = points[(i+1) % big_rad_sub][(j+1) % small_rad_sub];

            point a2 = points[i][j];
            point b2 = points[i][(j+1) % small_rad_sub];
            point c2 = points[(i+1) % big_rad_sub][(j+1) % small_rad_sub];

            /*a1.print();*/

            tri1 = new triangle(norm, a1, c1, b1, kd, ks, ke, ka, ns, ni, d);
            tri2 = new triangle(norm, a2, b2, c2, kd, ks, ke, ka, ns, ni, d);
            torus_triangles.push_back(tri1);
            torus_triangles.push_back(tri2);

        }

    }

    return torus_triangles;
}


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

    objReader reader("./input/mamaco.obj", cmap);


    point pos_cam(6,0,8);
    point target_cam(0,0,0);
    vetor up_cam(-1,1,-1);

    /*point pos_cam(0,8,0);*/
    /*point target_cam(0,0,0);*/
    /*vetor up_cam(-1,0,0);*/

    camera cam(1920, pos_cam, target_cam, up_cam, 16.0/9.0, 2.2);

    // point origem_esfera1(1,0,2);
    point origem_esfera1(4,1,2);    
    point origem_esfera2(0,0.2,0);    
    point origem_esfera3(1.5,-0.5,-2);

    // vetor normal_plano(0,1,0);

    vetor cor(1,0,0);
    vetor cor2(0.4,0.4,0.4);
    vetor cor3(0,0,0.5);
    vetor kd = vetor(1, 0, 0);
    vetor ks = vetor(1, 0, 0);
    vetor ke = vetor(0.000000, 0.000000, 0.000000);
    vetor ka = vetor(1, 1, 1);
    double ns = 10.000000;
    vetor k_esfera = vetor(0,0,0);
    //vector <object*> triangulos;
    vector<object*> mamaco = reader.getTriangles();
    vector<object*> triangulos = create_torus(2, 0.2, 50, 50, kd, ks, ke, ka, ns, 1.0, 0.0);
    vector<object*> toro = create_torus(3.5, 0.3, 50, 50, kd, ks, ke, ka, ns, 1.0, 0.0);

    for (auto i : mamaco) { triangulos.push_back(i); }

    rotacao(toro, 90.0, 'x');

    for (auto i : toro) { triangulos.push_back(i); }

    sphere esfera1 = sphere(origem_esfera2, 3, vetor(0,0,0), kd,k_esfera,ke,k_esfera, ns, 1.0, 0.0);
    triangulos.push_back(&esfera1);
    sphere esfera2 = sphere(origem_esfera2, 0.5, cor, kd,ks,ke,ka, ns, 0.0, 0.0);
    triangulos.push_back(&esfera2);
    /*sphere esfera3 = sphere(origem_esfera1,0.5, vetor(0,0,0.5), kd,ks,ke,ka, ns, 0.0, 1.0);*/
    // triangulos.push_back(&esfera3);
    // sphere esfera4 = sphere(origem_esfera2, 0.5, cor3, kd,ks,ke,ka, ns, 0.0, 0.0);
    // triangulos.push_back(&esfera4);

    // sphere esfera3 = sphere(origem_esfera3, 1, cor3, kd,ks,ke,ka, ns, ni, 0.0);
    // triangulos.push_back(&esfera3);
    // rotacao(triangulos, 45.0, 'X');
    // rotacao(triangulos, 45.0, 'Y');
    // rotacao(triangulos, 45.0, 'Z');
    // translacao(triangulos, 0, 3, 0);

    point origem_plano(0,-4,0);
    vetor ka_plano = vetor(0,0,0);
    vetor cor_plano(0.1,0.1,0.1);
    plane plano = plane(origem_plano, vetor(0, 1, 0), cor_plano, kd,ks,ke,ka_plano, ns, 0.0, 1.0);
    triangulos.push_back(&plano);

    vector<light> lts;
    point lt_pos(7, 3, 2);
    point lt_pos2(0, 100, -100);
    vetor lt_color(0.4,0.4,0.4);
    light lt(lt_pos,lt_color);
    light lt2(lt_pos2, lt_color);
    lts.push_back(lt);
    lts.push_back(lt2);

    vetor ambiente_color(0.1,0.1,0.1);

    translacao(triangulos, 0,0.2,0);

    cam.render(triangulos, lts, ambiente_color);

    return 0;
}
