#ifndef MESHHEADER
#define MESHHEADER

#include "Triangle.cpp"
#include <vector>


class mesh : public object{
    private:
        std::vector<triangle> triangles;
    public:
        mesh(){
            vetor cor(0,1,0);
            this->color = cor;
        };
        mesh(std::vector<triangle> triangles):
            triangles(triangles), object(triangles[0].getColor()){};
        
        double intersect (ray &r) override {
            double dist;
            double t = INFINITY;
            for (int i = 0; i < this->triangles.size(); i++){
                dist = this->triangles[i].intersect(r);
                if (dist > 0 && dist < t){
                    t = dist;
                }
            }
            return t;
        }

        void setColor(vetor color){
            this->color = color;
        }

        void append(triangle t){
            this->triangles.push_back(t);
        }

        void setTriangles(std::vector<triangle> triangles){
            this->triangles = triangles;
        }
};

#endif