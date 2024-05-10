#ifndef CAMERAHEADER
#define CAMERAHEADER

#include <iostream>
#include "Point.h"

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
    double D_screen;
    int height;
    int width;


public:
    camera (
        point p,
        point t,
        vector u
    ) {
        this->position = p;
        this->target = t;
        this->up = u;
        this->W = (target - position).normalizar();
        this->V = up.produto_vetorial(W).normalizar();
        this->U = up.produto_vetorial(V).normalizar();
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

    void render() {}
};

#endif
