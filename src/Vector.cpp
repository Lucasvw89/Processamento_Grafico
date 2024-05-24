#ifndef VECTORHEADER
#define VECTORHEADER
#include <iostream>
#include <math.h>

class vetor{
    private:
        double x;
        double y;
        double z;

    
    /*
    Recebe um escalar (double) e retorna um novo vetor com os valores multiplicados
    */
    vetor multiplicar_escalar(double escalar){
        return vetor(this->x * escalar, this->y * escalar, this->z * escalar);
    }

    public:

        vetor() {}
        vetor(double x, double y, double z){
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
            std::clog << "<" << this->x << ", " << this->y << ", " << this->z << ">" << std::endl;
        }

        // Operações

        /*
            Recebe o vetor e retorna o produto vetorial entre eles, seguindo o cálculo da matriz
            | i j k |
            | x y z |
            | a b c |
        */
        vetor produto_vetorial(vetor v){
            return vetor(
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

        vetor normalizar(){
            double norma = (1 / this->norma());
            return vetor(this->x * norma, this->y * norma, this->z * norma);
        }

        /*
        Recebe um vetor e retorna o produto escalar entre eles
        */
        double produto_escalar(vetor v){
            return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ();
        }

        /*
            Recebe um vetor e retorna a projeção vetorial de V no vetor atual.
        */
        vetor projecao_vetorial(vetor v){
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


        inline vetor operator+(vetor v1)
        {
            return vetor(v1.getX() + this->getX(), v1.getY() + this->getY(), v1.getZ() + this->getZ());
        }


        inline vetor operator-(vetor v1)
        {
            return vetor(this->getX() - v1.getX(), this->getY() - v1.getY(), this->getZ() - v1.getZ());
        }
        inline vetor operator-(double t1)
        {
            return vetor(this->getX() - t1, this->getY() - t1, this->getZ() - t1);
        }

        inline vetor operator*(double t1)
        {
            return vetor(t1 * this->getX(), t1 * this->getY(), t1 * this->getZ());
        }

        vetor operator*(const double matrix[3][3]) const {
            double newX = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z;
            double newY = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z;
            double newZ = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z;

            return vetor(newX, newY, newZ);
        }

        inline vetor operator/(double t1)
        {
            return vetor(this->getX()/t1, this->getY()/t1, this->getZ()/t1);
        }
};

#endif