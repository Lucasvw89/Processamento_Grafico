#include <iostream>
#include <fstream>
#include "src/Camera.cpp"
#include "src/Vector.cpp"
#include "src/Sphere.cpp"

int main() {
    //IMAGEM
    int width = 600;
    int height = 600;

    vector v1(1, 1, 0);
    vector v2(1, 0, 0);
    std::cout << v1.norma() << std::endl;
    point p1(1,2,3);
    point p2(4,5,7);
    point p3 = p1-v1;    
    camera cam(p1, p2, v1);
    v1 = p2-p1;
    p3.print();
    v1.print();
    cam.print();
    sphere a(p1, 1, v1);


    //RENDER
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            auto r = double(i) / (width-1);
            auto g = double(j) / (width-1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}
