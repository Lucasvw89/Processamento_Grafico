#include <iostream>
#include "include/Vector.hpp"

int main() {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    std::cout << v1.norma() << std::endl;
    v1.normalizar();
    v1.print();

    return 0;
}