#ifndef CAMRHEADER
#define CAMRHEADER

#include <iostream>
#include <tuple>
#include <vector>
#include "Point.cpp"
#include "Ray.cpp"
#include "Sphere.cpp"
#include "Triangle.cpp"
#include "Light.cpp"

using namespace std;

class camera 
{
private:
    point position;
    point target;
    vetor up;
    vetor W; // Vetor direção da câmera
    vetor V; // Vetor vertical da câmera
    vetor U; // Vetor horizontal da câmera
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
        //double d = 1.0,
        double aspect_ratio = 16.0 / 9.0,
        double focal_length = 1,
        double viewport_height = 2.0
    ) {
        this->position = p;
        this->width = width;
        this->target = t;
        this->up = u.normalizar();
        //this->distance = d;
        this->aspect_ratio = aspect_ratio;
        this->focal_length = focal_length;
        this->viewport_height = viewport_height;

        // Calcula os vetores ortonormais da câmera
        this->W = (target - position).normalizar();
        this->U = up.produto_vetorial(W).normalizar();
        this->V = W.produto_vetorial(U).normalizar();
    }

    camera() {}

    void print() {
        cout << "Camera:" << endl;
        position.print();
        target.print();
        up.print();
        W.print();
        V.print();
        U.print();
    }

    double ray_color(ray& r, object& s) {
        double t = s.intersect(r);
        if (t > 0.0 && t != INFINITY) {
            return t;
        }
        return INFINITY;
    }

    // Função auxiliar para calcular o vetor refletido
    vetor reflect(const vetor& L, const vetor& N) {
        double dotProduct = L.produto_escalar(N);
        vetor temp = 2.0 * dotProduct * N;
        return (temp - L);
    }

    // Função auxiliar para calcular o vetor refratado

    vetor refract(vetor& incident, vetor& normal, double n1, double n2) {
        double coso = incident.produto_escalar(normal);
        double seno = sqrt(1 - (coso * coso));
        double senot = (n2 / n1) * seno;
        double cosot = sqrt(1 - senot * senot);
        double cons = (cosot - ((n1 / n2) * coso));
        vetor t = (incident * (n1 / n2)) - (normal * cons);
        return t;
    }

    vetor phong_shading(ray& r, vector<object*>& objetos, const vector<light>& lights, vetor ambient_light, int index)
    {
        vetor final_color(0,0,0);
        if(index<=10)    // pode ser mudado
        {   
            double t = INFINITY;
            double ind = 0;
            for(int k = 0; k < objetos.size(); k++)
            {
                double result = ray_color(r, *objetos[k]);
                if(result > 0.0 and result < t)
                {
                    t = result;
                    ind = k;
                }
            }
            if(t!=INFINITY)
            {   
                index++;
                point intersection = r.f(t);
                vetor normal = objetos[ind]->getNormal().normalizar();
                vetor objeto_color = objetos[ind]->getColor();
                
                final_color =  final_color + (objetos[ind]->getKa().getX() * ambient_light); // componente ambiente
                
                vetor view_dir = r.getDirection().normalizar();
                vetor view_spec = (r.getOrigin() - intersection).normalizar();
                for (const auto& light : lights) {
                    vetor light_dir = (light.getPosition() - intersection).normalizar();
                    
                    vetor reflect_dir = reflect(light_dir, normal);
                    
                    // Componente difusa
                    double diff = std::max(light_dir.produto_escalar(normal), 0.0);
                    final_color = final_color + ((objetos[ind]->getKd().getX() * objeto_color) * diff);                            

                    // Componente especular
                    double spec = pow(std::max(view_spec.produto_escalar(reflect_dir), 0.0), objetos[ind]->getShininess());
                    final_color = final_color + (light.getColor() * spec) * (objetos[ind]->getKs().getX());

                }

                // Componente reflexão
                if(objetos[ind]->getD() != 0) {   
                    vetor dir_reflec_ray = reflect(view_dir*(-1), normal);
                    point new_intersection = intersection + dir_reflec_ray * 0.00001;
                    ray reflec_ray(new_intersection, dir_reflec_ray);
                    vetor reflec_color = phong_shading(reflec_ray,objetos,lights, ambient_light, index);
                    reflec_color = reflec_color*objetos[ind]->getD();
                    final_color = final_color + reflec_color;

                }

                
                // Componente refração
                if (objetos[ind]->getNi() != 0) {
                    double n1 = 1; // Índice de refração do ar
                    double n2 = objetos[ind]->getNi(); // Índice de refração do objeto
                    vetor dir_refrac_ray;
                    /*if(index==1) */
                    /*{*/
                    /*    dir_refrac_ray = refract(view_spec, normal, n1, n2);*/
                    /*    dir_refrac_ray = dir_refrac_ray * -1;*/
                    /*}*/
                    dir_refrac_ray = refract(view_dir, normal, n1, n2);
                    if (dir_refrac_ray.norma() != 0) { // Verifica se não houve reflexão total
                        point new_intersection = intersection + dir_refrac_ray * 0.00001;
                        ray refrac_ray(new_intersection, dir_refrac_ray);
                        vetor refrac_color = phong_shading(refrac_ray,objetos,lights, ambient_light, index);
                        refrac_color = refrac_color * (objetos[ind]->getNi());
                        final_color = final_color + (refrac_color);
                    }
                }
            }
        }
        return final_color;
    }


    void render(vector<object*>& objetos, const vector<light>& lights, const vetor& ambient_light) {
        int image_width = this->width;
        int image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        
        double viewport_width = viewport_height * aspect_ratio;
        point camera_center = this->position;

        // Vetores que apontam as extremidades da tela
        vetor viewport_u = U * (viewport_width * -1);
        vetor viewport_v = V * (viewport_height * -1);

        // Vetores usados para calcular a posição do próximo pixel (ponto+(vetor*quantidade de pixels))
        vetor pixel_delta_u = viewport_u / image_width;
        vetor pixel_delta_v = viewport_v / image_height;

        // Ponto superior esquerdo do pixel inicial
        point viewport_upper_left = camera_center + W * focal_length - viewport_u / 2 - viewport_v / 2;

        // Calculando o ponto central do pixel
        point pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rLinhas restantes: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + pixel_delta_u * i + pixel_delta_v * j;
                auto ray_direction = pixel_center - camera_center;
                ray_direction = ray_direction.normalizar();
                ray r(camera_center, ray_direction);
                
                // tuple<int, double, vetor> pixel_info(0, 0, vetor(0, 0, 0));

                vetor final_color = phong_shading(r,objetos,lights,ambient_light,0);
                final_color.write_color(cout);
            }
        }
        std::clog << "\rDone.                 \n";
    }

};

#endif
