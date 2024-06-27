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

    vetor reflection(ray& r, vector<object*>& objetos, int index){
        if(index < 3)
        {
            vetor cor;
            index++;
            for (int k = 0; k < objetos.size(); k++) {
                double tt = ray_color(r, *objetos[k]);
                if(tt!=INFINITY) {
                    vetor cor = objetos[k]->getColor();
                    point intersection = r.f(tt);
                    // clog << "intersection: " << intersection.getX() << " " << intersection.getY() << " " << intersection.getZ() << endl;
                    vetor dir_reflecray = reflect(r.getDirection().normalizar(), objetos[k]->getNormal());
                    intersection = intersection + dir_reflecray * 0.001;
                    ray reflected = ray(intersection, dir_reflecray);

                
                    cor = cor + ((reflection(reflected, objetos, index)*objetos[k]->getD()));

                    return cor;
                }
            }
        }
        return vetor(0,0,0);
    }




    // vetor refract(const vetor& incidentt, const vetor& normall, double n1, double n2) {
    //         vetor normal = normall;
    //         vetor incident = incidentt;
    //         double cosi = max(-1.0, min(1.0, incident.produto_escalar(normal)));
    //         cosi = cosi *-1.0;
    //         if (cosi < 0) {
    //             return refract(incident, normal*-1, n2, n1);
    //         }
    //         double eta = n1 / n2;
    //         double k = 1 - eta * eta * (1 - cosi * cosi);
    //         if (k < 0) {
    //             return {0, 0, 0}; // Total Internal Reflection
    //         } else {
    //             vetor refratado = incident * eta + normal * (eta * cosi - sqrt(k)); 
    //             return refratado;
    //         }
    // }

    vetor refract(const vetor& incident, const vetor& normal, double n1, double n2) {
        vetor norm = normal;
        double coso = incident.produto_escalar(normal);
        double seno = sqrt(1 - (coso * coso));
        double senot = (n2 / n1) * seno;
        double aa = senot * senot;
        double cosot = sqrt(1 - aa);
        vetor incid = incident;
        vetor t = (incid * (n1 / n2));
        double cons = (cosot - ((n1 / n2) * coso));
        vetor normall = norm * cons;
        t = t - normall; 
        return t;
    }

    vetor refraction(ray& r, vector<object*>& objetos, int index) {
        vetor final_colorr(0, 0, 0);
        if(index < 3)
        {
            index++;
            for (int k = 0; k < objetos.size(); k++) {
                double tt = ray_color(r, *objetos[k]);
                if(tt!=INFINITY) {
                    point intersection = r.f(tt);
                    vetor dir_refracray = refract(r.getDirection().normalizar(), objetos[k]->getNormal(), 1.0, objetos[k]->getNi());
                    dir_refracray = dir_refracray *-1;
                    intersection = intersection + dir_refracray * 0.1;
                    ray refracted = ray(intersection, dir_refracray);
                    vetor refrac_color = (refraction(refracted, objetos, index)*objetos[k]->getNi()); 
                    final_colorr = final_colorr + refrac_color;
                }   
            }
        } 
        return final_colorr;
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
                
                tuple<int, double, vetor> pixel_info(0, 0, vetor(0, 0, 0));

                for (int k = 0; k < objetos.size(); k++) {
                    double t = ray_color(r, *objetos[k]);
                    
                    if (t != INFINITY) {
                        // Calcular a iluminação Phong aqui
                        point intersection = r.f(t);
                        vetor normal = objetos[k]->getNormal().normalizar();
                        vetor objeto_color = objetos[k]->getColor();
                        
                        vetor final_color = objeto_color;
                        final_color = final_color + (objetos[k]->getKa().getX() * ambient_light); // componente ambiente
                        
                        vetor view_dir = (camera_center - intersection).normalizar();
                        for (const auto& light : lights) {
                            vetor light_dir = (light.getPosition() - intersection).normalizar();
                            
                            vetor reflect_dir = reflect(light_dir, normal);
                            
                            // Componente difusa
                            double diff = std::max(light_dir.produto_escalar(normal), 0.0);
                            final_color = final_color + ((objetos[k]->getKa().getX() * light.getColor()) * diff);                            

                            // Componente especular
                            double spec = pow(std::max(view_dir.produto_escalar(reflect_dir), 0.0), objetos[k]->getShininess());
                            final_color = final_color + (light.getColor() * spec) * (objetos[k]->getKs().getX());

                        }

                        // Componente reflexão
                        if(objetos[k]->getD() != 0) {   
                        vetor dir_reflec_ray = reflect(view_dir, normal);
                        intersection = intersection + dir_reflec_ray * 0.001;
                        ray reflec_ray(intersection, dir_reflec_ray);
                        final_color = final_color + (reflection(reflec_ray, objetos, 0)*objetos[k]->getD());
                        }

                        
                        // Componente refração
                        if (objetos[k]->getNi() != 1) {
                            double n1 = 1; // Índice de refração do ar
                            double n2 = objetos[k]->getNi(); // Índice de refração do objeto
                            vetor dir_refrac_ray = refract(view_dir, normal, n1, n2);
                            dir_refrac_ray = dir_refrac_ray * -1;
                            if (dir_refrac_ray.getX() != 0 || dir_refrac_ray.getY() != 0 || dir_refrac_ray.getZ() != 0) { // Verifica se não houve reflexão total
                                intersection = intersection + dir_refrac_ray * 0.1;
                                ray refrac_ray(intersection, dir_refrac_ray);
                                // vetor refrac_color = refraction(refrac_ray, objetos, 0);
                                for(int v=0; v<objetos.size(); v++) {
                                    if(ray_color(refrac_ray, *objetos[v]) != INFINITY) {
                                        final_color = final_color + (objetos[v]->getColor() * (objetos[k]->getNi()));
                                    }
                                }
                                // refrac_color = refrac_color * (objetos[k]->getNi());
                                // final_color = final_color + (refrac_color);
                            }
                        }

                        if (t < get<1>(pixel_info) || get<1>(pixel_info) == 0) {
                            pixel_info = make_tuple(k, t, final_color);
                        }
                        // vetor curr = objetos[k]->getNormal().normalizar();
                        // double cos = abs(W.produto_escalar(curr));
                        // vetor cor = objetos[k]->getColor() * cos;
                        // if (t < get<1>(pixel_info) || get<1>(pixel_info) == 0) {
                        //     pixel_info = make_tuple(k, t, cor);
                        // }
                    }
                }
                get<2>(pixel_info).write_color(cout);
            }
        }
        std::clog << "\rDone.                 \n";
    }



};

#endif
