#ifndef CAMRHEADER
#define CAMRHEADER

#include <iostream>
#include "Point.cpp"

using namespace std;

class camera 
{
private:
    point position;
    point target;
    vector up;
    vector W;
    vector V;
    vector U;
    double distance;
    int height;
    int width;
    double focal_lenght;


public:
    camera (
        int height,
        int width,
        double focal_lenght,
        point p,
        point t,
        vector u,
        double d = 10.0
    ) {
        this->position = p;
        this->target = t;
        this->up = u;
        this->W = (target - position).normalizar();
        this->V = up.produto_vetorial(W).normalizar();
        this->U = up.produto_vetorial(V).normalizar();
        this->distance = d;
    };

    void print() {
        cout << "camera:" << endl;
        position.print();
        target.print();
        up.print();
        W.print();
        V.print();
        U.print();
    }

    void render() {};
};

#endif
