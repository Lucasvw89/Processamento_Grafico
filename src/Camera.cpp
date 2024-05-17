#ifndef CAMRHEADER
#define CAMRHEADER

#include <iostream>
#include <tuple>
#include <vector>
#include "Point.cpp"
#include "Ray.cpp"
#include "Sphere.cpp"

using namespace std;

class camera 
{
private:

    point position;
    point target;
    vetor up;
    vetor W;
    vetor V;
    vetor U;
    double distance;
    int height;
    int width;
    double aspect_ratio;
    double focal_length;
    double viewport_height;


public:

        point getPosition() const { return position; }
        point getTarget() const { return target; }
        vetor getUp() const { return up; }
        vetor getW() const { return W; }
        vetor getV() const { return V; }
        vetor getU() const { return U; }
        double getDistance() const { return distance; }
        int getHeight() const { return height; }
        int getWidth() const { return width; }
        double getAspectRatio() const { return aspect_ratio; }
        double getFocalLength() const { return focal_length; }
        double getViewportHeight() const { return viewport_height; }
    camera (
        int width,
        point p,
        point t,
        vetor u,
        double d = 1.0,
        double aspect_ratio = 16.0 / 9.0,
        double focal_length=0.2,
        double viewport_height = 2.0
    ) {
        this->position = p;
        this->width= width;
        this->target = t;
        this->up = u;
        this->W = (target - position).normalizar();
        this->V = up.produto_vetorial(W).normalizar();
        this->U = up.produto_vetorial(V).normalizar();
        this->distance = d;
        this->aspect_ratio = aspect_ratio;
        this->focal_length = focal_length;
        this->viewport_height= viewport_height;
    };
    camera(){
    }
    void print() {
        cout << "Camera:" << endl;
        position.print();
        target.print();
        up.print();
        W.print();
        V.print();
        U.print();
    }

    double ray_color( ray& r, object& s) {
        double t = s.intersect(r);
        if (t > 0.0) {
            return t;
        }
        vetor unit_direction = r.direction.normalizar();
        auto a = 0.5*(unit_direction.getY() + 1.0);
        return INFINITY;
    }


    void render(vector<object *> objetos) 
    {

        int image_width = this->width;
        int image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        auto viewport_width = viewport_height * (double(image_width)/image_height);
        auto camera_center = this->position;

        auto viewport_u = vetor(viewport_width, 0, 0);
        auto viewport_v = vetor(0, -viewport_height, 0);

        auto pixel_delta_u = viewport_u / image_width;
        auto pixel_delta_v = viewport_v / image_height;
        auto viewport_upper_left = camera_center- vetor(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v)*0.5;

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rLinhas restantes: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + (pixel_delta_u*i) + (pixel_delta_v*j);
                auto ray_direction = pixel_center - camera_center;
                ray r(camera_center, ray_direction);
                
                tuple <int, double, vetor> pixel_info (0, 0, vetor(0,0,0));

                for (int k = 0; k < objetos.size(); k++){
                    double t = ray_color(r, *objetos[k]);
                    
                    if (t != INFINITY) {
                        if (t < get<1>(pixel_info) || get<1>(pixel_info) == 0){
                            pixel_info = make_tuple(k, t, objetos[k]->getColor());
                        }
                    }
                }
                get<2>(pixel_info).write_color(cout);
            }
        }
        std::clog << "\rDone.                 \n";


    };
};

#endif
