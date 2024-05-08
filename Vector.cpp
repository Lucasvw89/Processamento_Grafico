#include <iostream>
#include <math.h>

class Vector{
    private:
        double x;
        double y;
        double z;

    public:

        Vector(double x, double y, double z){
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        // Getters
        double getX(){
            return this->x;
        }

        double getY(){
            return this->y;
        }

        double getZ(){
            return this->z;
        }
        
        // Setters
        void setX(double x){
            this->x = x;
        }

        void setY(double y){
            this->y = y;
        }

        void setZ(double z){
            this->z = z;
        }

        /*
        Printa as coordenadas do vetor no terminal
        */
        void print(){
            std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
        }

        // Operators
        /*
        Recebe como parâmetro um vetor e retorna um >>novo vetor<< com os valores somados
        */
        Vector soma_de_vetor(Vector v){
            return Vector(this->x + v.getX(), this->y + v.getY(), this->z + v.getZ());
        }


        /*
            Recebe o vetor e retorna o produto vetorial entre eles, seguindo o cálculo da matriz
            | i j k |
            | x y z |
            | a b c |
        */
        Vector produto_vetorial(Vector v){
            return Vector(
                        (this->y * v.getZ()) - (this->z * v.getY()), // i
                        (this->z * v.getX()) - (this->x * v.getZ()), // j
                        (this->x * v.getY()) - (this->y * v.getX())  // k
                        );
        }

        /*
        Retorna a norma do vetor
        */
        double norma(){
            return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        }

        /*
        Recebe um vetor e retorna o produto escalar entre eles
        */
        double produto_escalar(Vector v){
            return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ();
        }
        
        /*
        Recebe um escalar (double) e retorna um novo Vector com os valores multiplicados
        */
        Vector multiplicar_escalar(double escalar){
            return Vector(this->x * escalar, this->y * escalar, this->z * escalar);
        }

        /*
            Recebe um Vector e retorna a projeção vetorial de V no vetor atual.
        */
        Vector projecao_vetorial(Vector v){
            double temp = this->produto_escalar(v) / this->norma()*this->norma();

            return this->multiplicar_escalar(temp);
        }
};