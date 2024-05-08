#include <iostream>
#include "Vector.cpp"

int main() {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    std::cout << v1.norma() << std::endl;
    Vector v3 = v1.produto_vetorial(v2);
    v1.print();

    return 0;
}