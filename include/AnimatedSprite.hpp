#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <string>
// Librería de terceros
#include <SDL2/SDL.h> // Para Mac, usar <SDL.h>

class AnimatedSprite{
    public:
        // Constructor
        AnimatedSprite(SDL_Renderer*& renderer, std::string filepath);
        // Destructor
        ~AnimatedSprite();
        // Dibujar
        void Dibujar(int x, int y, int w, int h);

        // Seleccionar y reproducir un fotograma específico
        void ReproducirFotograma(int x, int y,int w, int h, int fotograma);

        // Actualizar en cada fotograma
        void Actualizar();
        // Renderizar
        void Renderizar(SDL_Renderer*& renderer);

    private:
        SDL_Rect m_src;         // Desde donde estamos seleccionando
        SDL_Rect m_dst;   // Donde estamos renderizando
        SDL_Texture* m_texture;
};

#endif
