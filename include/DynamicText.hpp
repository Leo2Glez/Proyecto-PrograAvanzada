// ARCHIVO: /c:/Users/Lenovo/OneDrive/Documentos/Escuela/LIZETTE/UNI/3Er Semestre/PROGRAMACIÓN AVANZADA/Proyecto-PrograAvanzada-1/include/DynamicText.hpp
#ifndef DYNAMICTEXT_HPP
#define DYNAMICTEXT_HPP

/*!
    Los objetos DynamicText pueden cambiar, pero son más costosos
    de usar, porque las texturas se recrean constantemente en cada fotograma.
*/

#include <SDL2/SDL.h>
// La biblioteca de fuentes SDL2_ttf para dibujar texto
#include <SDL2/SDL_ttf.h>

#include <string>

class DynamicText{
    public:

        // Constructor
        // ejemplo: "./assets/fonts/8bitOperatorPlus8-Regular.ttf"
        DynamicText(std::string fontfilepath, size_t fontSize);
        // Destructor
        ~DynamicText();
        // Función para dibujar texto
        void DrawText(SDL_Renderer* renderer, std::string text,int x, int y, int w, int h);

    private:
        // Rectángulo, textura y superficie en las que dibujamos nuestra fuente.
        SDL_Rect m_rectangle;
        SDL_Texture* m_texture;
        SDL_Surface* m_surface;
        // La fuente real
        TTF_Font* m_ourFont;
        // Su propósito es asegurarse de que la biblioteca TTF se inicialice solo una vez
        static bool s_ttfInitialized;

};



#endif
