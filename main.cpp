#include <iostream>
#include "src/Point.cpp"

int main() {
    Vector v1(1, 1, 0);
    Vector v2(1, 0, 0);
    std::cout << v1.norma() << std::endl;
    point p1(1,2,3);
    point p2(4,5,7);
    point p3 = p1-v1;    
    v1 = p2-p1;
    p3.print();
    v1.print();


    return 0;
}