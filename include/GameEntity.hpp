#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <string>
#include <vector>

// Terceros
#include <SDL2/SDL.h> // Para Mac, usar <SDL.h>

#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"

class GameEntity{
    public:
        // Constructores
        GameEntity();
        GameEntity(SDL_Renderer* renderer);
        // Destructores
        ~GameEntity();
        // Actualizar (llamado en cada iteración)
        void Update();
        // Renderizar nuestra entidad de juego (en la parte de renderizado)
        void Render();
        // Agregar componentes de rectángulo texturizado
        void AddTexturedRectangleComponent(std::string spritepath);
        // Agregar un componente de rectángulo con transparencia
        void AddTexturedRectangleComponent(std::string spritepath, int redcolorkey, int greencolorkey, int bluecolorkey);
        // Agregar otro colisionador de caja a nuestro objeto
        void AddBoxCollider2D();
        // Obtener componentes
        TexturedRectangle& GetTexturedRectangle();
        BoxCollider2D& GetBoxCollider2D(size_t index);
        // Actualizar
        // Nota: Establece la posición de nuestra entidad de juego
        //       Esto funciona moviendo también la posición de todos los
        //       componentes para que se actualicen.
        void SetPosition(int x, int y); 
        // Establece todas las dimensiones de los componentes a un valor especificado
        void SetDimensions(int w, int h); 

    private:
        // Componentes
        TexturedRectangle* m_sprite; 
        std::vector<BoxCollider2D*> m_colliders;
        // Puntero al renderizador al que el objeto renderizará
        // los componentes.
        SDL_Renderer* m_renderer;
};


#endif
