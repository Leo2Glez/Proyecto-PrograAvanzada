#include <iostream>
#include <Mascota.hpp>

int main(int argc, char const *argv[])
{
    // Mascota m1;
    // Mascota m2;
    // m1.Comer();
    // m2.Comer();
    std::cout << "int: " << sizeof(int) << std::endl;
    std::cout << "char: " << sizeof(char) << std::endl;
    std::cout << "bool: " << sizeof(bool) << std::endl;
    std::cout << "float: " << sizeof(float) << std::endl;
    std::cout << "double: " << sizeof(double) << std::endl;
    std::cout << "Mascota: " << sizeof(Mascota) << std::endl;

    std::cout << std::endl
              << std::endl;
    std::cout << "Direcciones de memoria" << std::endl;
    int a = 7;
    std::cout << "Tamaño: " << sizeof(a) << std::endl;
    std::cout << "Contenido: " << a << std::endl;
    std::cout << "Direccion: " << &a << std::endl;

    void *puntero = malloc(32);

    std::cout << std::endl
              << std::endl;
    std::cout << "Direcciones de memoria" << std::endl;
    std::cout << "sizeof: " << sizeof(puntero) << std::endl;
    std::cout << "puntero: " << puntero << std::endl;
    std::cout << "puntero: " << &puntero << std::endl;

    free(puntero);

    void *mascota = malloc(sizeof(Mascota));
    free(mascota);

    // C - Memoria dinamica
    std::cout << std::endl
              << std::endl;
    std::cout << "Mascota en C: " << std::endl;
    Mascota *mascotaC = (Mascota *)malloc(sizeof(Mascota));
    mascotaC->Inicializar();
    mascotaC->Decirnombre();
    mascotaC->Destruir();
    free(mascotaC);

    // C++ - Memoria dinamica
    std::cout << std::endl
              << std::endl;
    std::cout << "Mascota en C++: " << std::endl;
    Mascota *mascotaCPP = new Mascota();
    mascotaCPP->Decirnombre();
    delete mascotaCPP;

    return 0;
}