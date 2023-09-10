#include <iostream>
#include <string>
#include <cstdio>

class Mascota
{
private:
    std::string nombre;
public:
    Mascota(/* args */) {
        std::cout << "Ha nacido una nueva Mascota: " << std::endl;
        this -> nombre = "TUPU";
    }
    ~Mascota() {
        std::cout << "Adios mundo cruel" << std::endl;
    }
    void Destruir()
    {
        std::cout << "Adios mundo cruel" << std::endl;
    }
    void Inicializar()
    {
        std::cout << "Ha nacido una nueva Mascota: " << std::endl;
        this -> nombre = "TUPU";
    }
    void Decirnombre()
    {
        std::cout << "Mi nombre es: " << this -> nombre << std::endl;
    }
};