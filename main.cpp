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
        std::clog << "\rLinhas restantes: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            auto pixel_color = vector(double(i)/(width-1), double(j)/(height-1), 0);
            pixel_color.write_color(std::cout);
        }
    }

    return 0;
}
