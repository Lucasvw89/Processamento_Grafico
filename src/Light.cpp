#ifndef LIGHTHEADER
#define LIGHTHEADER
#include "Point.cpp"


class light{
    private:
        point position;
        vetor color;

    public:
        light(point position, vetor color){
            this->position = position;
            this->color = color;
        }

        point getPosition() const { return position; }
        vetor getColor() const { return color; }
};

#endif