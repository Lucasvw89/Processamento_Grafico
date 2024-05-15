#ifndef CAMRHEADER
#define CAMRHEADER

#include <iostream>
#include "Point.cpp"
#include "Ray.cpp"
#include "Sphere.cpp"

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
    camera(){
    }
    void print() {
        cout << "camera:" << endl;
        position.print();
        target.print();
        up.print();
        W.print();
        V.print();
        U.print();
    }

    vector ray_color( ray& r, sphere& s) {
        if (s.hit_sphere(s.center,s.radius,r))
        {
            return vector(1, 0, 0);

        }
        vector unit_direction = r.direction.normalizar();
        auto a = 0.5*(unit_direction.getY() + 1.0);
        return vector(1.0, 1.0, 1.0)*(1.0-a) + vector(0.5, 0.7, 1.0)*a;
    }


    void render() 
    {
        auto aspect_ratio = 16.0 / 9.0;
        int image_width = 400;

        int image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;


        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);
        auto camera_center = point(0, 0, 0);

        auto viewport_u = vector(viewport_width, 0, 0);
        auto viewport_v = vector(0, -viewport_height, 0);

        auto pixel_delta_u = viewport_u / image_width;
        auto pixel_delta_v = viewport_v / image_height;
        auto viewport_upper_left = camera_center- vector(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v)*0.5;

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + (pixel_delta_u*i) + (pixel_delta_v*j);
                auto ray_direction = pixel_center - camera_center;
                ray r(camera_center, ray_direction);
                point p(0,0,1);
                sphere esfera(p, 0.5, vector(1,0,0));
                vector pixel_color = ray_color(r,esfera);
                pixel_color.write_color(cout);
            }
        }
        std::clog << "\rDone.                 \n";


    };
};

#endif
