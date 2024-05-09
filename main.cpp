#include <iostream>
#include "src/Vector.cpp"

int main() {
    Vector v1(1, 1, 0);
    Vector v2(1, 0, 0);
    std::cout << v1.norma() << std::endl;
    Vector v3 = v2.projecao_vetorial(v1);
    v3.print();

    return 0;
}