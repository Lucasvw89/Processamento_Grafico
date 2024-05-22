#ifndef OBJREADERHEADER
#define OBJREADERHEADER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Vector.cpp"
#include "Point.cpp"
#include "Triangle.cpp"
#include "Colormap.cpp"

struct Face{
    int verticeIndice[3];
    int normalIndice[3];
    vetor cor;
};

class objReader {
    
    private:

    std::ifstream file;
    std::vector<point> vertices;
    std::vector<vetor> normals;
    std::vector<Face> faces;
    std::vector<triangle> triangles;
    vetor curColor; // processa um objeto por vez, guarda nessa variável

    public:
        //Getters
        std::vector<triangle> getTriangles(){
            return this->triangles;
        }
        
        objReader(string filename, colormap& cmap) {

            // Abre o arquivo
            file.open(filename);
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir o arquivo: "<< filename << std::endl;
                return;
            }

            // Leitura do arquivo
            std::string line,mtlfile, colorname;
            while (std::getline(file, line)){
                std::istringstream iss(line);       //É um std::cin, mas de objetos
                std::string prefix; //Vai armazenar a primeira palavra (identificador da linha)
                iss >> prefix;
                
                if (prefix == "usemtl")
                {
                    iss >> colorname;

                    cerr << "colorname: " << colorname << endl;
                    
                    curColor = cmap.getColor(colorname);

                }
                else if (prefix == "v") {
                    //Lê os vértices    
                    double x, y, z;
                    point vertex;
                    iss >> x >> y >> z;
                    
                    vertex = point(x, y, z);
                    vertices.push_back(vertex);

                    vertex.print();
                } else if (prefix == "vn") {
                    //Lê os vetores normais
                    double x, y, z;
                    vetor normal;
                    iss >> x >> y >> z;
                    
                    normal = vetor(x, y, z);
                    normal.print();
                    normals.push_back(normal);
                } else if (prefix == "f") {
                    Face face;
                    char slash;
                    for (int i = 0; i < 3; ++i) {
                        int _;
                        iss >> face.verticeIndice[i] >> slash >> _ >> slash >> face.normalIndice[i];
                        
                        // cor do objeto atual
                        face.cor = curColor;
                        //Os arquivos OBJ utilizam a notação de 1 a N, então é necessário subtrair 1 de cada indice
                        face.verticeIndice[i]--;
                        face.normalIndice[i]--;
                    }
                    faces.push_back(face);
                }
            }
            
            for (int i = 0; i < faces.size(); i++) {
                point a = vertices[faces[i].verticeIndice[0]];
                point b = vertices[faces[i].verticeIndice[1]];
                point c = vertices[faces[i].verticeIndice[2]];
                vetor ab = b - a;
                vetor ac = c - a;
                vetor normal = ac.produto_vetorial(ab).normalizar();
                // cor passada como argumento
                triangle tri(normal, faces[i].cor, vertices[faces[i].verticeIndice[0]], vertices[faces[i].verticeIndice[1]], vertices[faces[i].verticeIndice[2]]);
                triangles.push_back(tri);
            };
            file.close();
        };

        //Getters
        std::vector<point> getVertices(){
            return vertices;
        }

        std::vector<vetor> getNormals(){
            return normals;
        }

        std::vector<Face> getFaces(){
            return faces;
        }

};

#endif