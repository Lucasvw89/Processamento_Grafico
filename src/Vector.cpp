#ifndef VECTORHEADER
#define VECTORHEADER
#include <iostream>
#include <math.h>

class vector{
    private:
        double x;
        double y;
        double z;

    
    /*
    Recebe um escalar (double) e retorna um novo vector com os valores multiplicados
    */
    vector multiplicar_escalar(double escalar){
        return vector(this->x * escalar, this->y * escalar, this->z * escalar);
    }

    public:

        vector() {}
        vector(double x, double y, double z){
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

        // Operações

        /*
            Recebe o vetor e retorna o produto vetorial entre eles, seguindo o cálculo da matriz
            | i j k |
            | x y z |
            | a b c |
        */
        vector produto_vetorial(vector v){
            return vector(
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

        vector normalizar(){
            double norma = (1 / this->norma());
            return vector(this->x * norma, this->y * norma, this->z * norma);
        }

        /*
        Recebe um vetor e retorna o produto escalar entre eles
        */
        double produto_escalar(vector v){
            return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ();
        }

        /*
            Recebe um vector e retorna a projeção vetorial de V no vetor atual.
        */
        vector projecao_vetorial(vector v){
            double temp = this->produto_escalar(v) / (this->norma()*this->norma());

            return this->multiplicar_escalar(temp);
        }


        //Converte o vetor unitario de cor para o formato RGB, pronto para ser escrito no PPM
        void write_color(std::ostream& out) {
            auto r = this->getX();
            auto g = this->getY();
            auto b = this->getZ();

            // Write out the pixel color components.
            int rbyte = int(255.999 * r);
            int gbyte = int(255.999 * g);
            int bbyte = int(255.999 * b);

            // Write out the pixel color components.
            out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
        }


        inline vector operator+(vector v1)
        {
            return vector(v1.getX() + this->getX(), v1.getY() + this->getY(), v1.getZ() + this->getZ());
        }

        inline vector operator-(vector v1)
        {
            return vector(this->getX() - v1.getX(), this->getY() - v1.getY(), this->getZ() - v1.getZ());
        }

        inline vector operator*(double t1)
        {
            return vector(t1 * this->getX(), t1 * this->getY(), t1 * this->getZ());
        }

        inline vector operator/(double t1)
        {
            return vector(this->getX()/t1, this->getY()/t1, this->getZ()/t1);
        }
};

#endif