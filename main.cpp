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

    objReader reader("untitled.obj", cmap);
    
    //vector<object> objs_list;


    point pos_cam(0,0,0);
    point target_cam(0,0,0);
    vetor up_cam(0,1,0);
    camera cam(1080, point(3,-1,5), point(0,0,0), vetor(0,1,0), 16.0/9.0, 1.5);

    // point p = point(0,0,0);
    // double d = 10.0;
    // sphere esfera(p, d, vetor(1,0,0));

    // objs_list.push_back(&esfera);

    vector<triangle> triangulos = reader.getTriangles();

    //for (auto t : triangulos) objs_list.push_back(&t);

    cam.render(triangulos);

    return 0;
}
