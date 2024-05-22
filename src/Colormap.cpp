#ifndef COLORMAPHEADER
#define COLORMAPHEADER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "Vector.cpp"
#include "Point.cpp"
#include "Triangle.cpp"

using namespace std;

class colormap {

public:
    map<string, vetor> mp;

    colormap(){

        // construtor: lê arquivo cores.mtl e guarda valores RGB associados a cada nome

        // OBS: atualmente está atribuindo valores RGB baseados no campo "Ka" do arquivo mtl
        // é possível que em entregas futuras, os outros atributos também serão usados

        std::ifstream mtlFile("cores.mtl");

        if (!mtlFile.is_open()) {
            std::cerr << "erro abrindo arquivo cores.mtl\n";
        }

        string line, currentMaterial;
        while (std::getline(mtlFile, line)) {
            std::istringstream iss(line);
            std::string keyword;
            iss >> keyword;

            if (keyword == "newmtl") {
                iss >> currentMaterial;
            } else if (keyword == "Ka") {
                double kaR, kaG, kaB;
                iss >> kaR >> kaG >> kaB;
                if (!currentMaterial.empty()) {
                    mp[currentMaterial] = vetor(kaR, kaG, kaB);
                }
            }
        }

    mtlFile.close();
    
    }

    vetor getColor(string& s){
        if (mp.find(s) != mp.end()) return mp[s];
        else cerr << "cor " << s << " indefinida no arquivo .mtl\n";
        return vetor(0,0,0);
    }
};

#endif