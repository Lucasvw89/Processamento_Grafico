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

struct Face {
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
    std::vector<object*> triangles;
    MaterialProperties curMaterial; // Guarda as propriedades do material atual
    colormap cmap;

public:
    // Getters
    std::vector<object*> getTriangles() {
        return this->triangles;
    }

    objReader(std::string filename, colormap& cmap) : cmap(cmap) {

        // Abre o arquivo
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
            return;
        }

        // Leitura do arquivo
        std::string line, mtlfile, colorname, filename_mtl;
        while (std::getline(file, line)) {
            std::istringstream iss(line); // É um std::cin, mas de objetos
            std::string prefix; // Vai armazenar a primeira palavra (identificador da linha)
            iss >> prefix;

            if (prefix == "mtllib") {
                iss >> filename_mtl;
                cmap = colormap("./input/" + filename_mtl);
            } else if (prefix == "usemtl") {
                iss >> colorname;
                curMaterial = cmap.getMaterialProperties(colorname);
            } else if (prefix == "v") {
                // Lê os vértices    
                double x, y, z;
                point vertex;
                iss >> x >> y >> z;
                vertex = point(x, y, z);
                vertices.push_back(vertex);
            } else if (prefix == "vn") {
                // Lê os vetores normais
                double x, y, z;
                vetor normal;
                iss >> x >> y >> z;
                normal = vetor(x, y, z);
                normals.push_back(normal);
            } else if (prefix == "f") {
                Face face;
                char slash;
                for (int i = 0; i < 3; ++i) {
                    int _;
                    iss >> face.verticeIndice[i] >> slash >> _ >> slash >> face.normalIndice[i];
                    // cor do objeto atual
                    face.cor = curMaterial.ka; // Escolha apropriada do vetor de cor
                    // Os arquivos OBJ utilizam a notação de 1 a N, então é necessário subtrair 1 de cada indice
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

            // Passar propriedades do material
            triangle* tri_pointer = new triangle(
                normal, 
                a, b, c, 
                curMaterial.kd, 
                curMaterial.ks, 
                curMaterial.ke, 
                curMaterial.ka, 
                curMaterial.ns, 
                curMaterial.ni, 
                curMaterial.d
            );
            triangles.push_back(tri_pointer);
        }
        file.close();
    };

    // Getters
    std::vector<point> getVertices() {
        return vertices;
    }

    std::vector<vetor> getNormals() {
        return normals;
    }

    std::vector<Face> getFaces() {
        return faces;
    }

};

#endif
