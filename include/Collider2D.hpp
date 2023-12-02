#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SDL2/SDL.h>

#include "TexturedRectangle.hpp"
#include "Vector2D.hpp"

class ICollider2D{
public:
    virtual void Update()=0;
    virtual void Render()=0;
};

// Un box collider es un collider 2D, por lo que heredamos
// de esa interfaz
class BoxCollider2D : public ICollider2D{
    public:
        // Constructor por defecto
        BoxCollider2D();
        // Destructor
        ~BoxCollider2D();
        // Obtener el rectángulo del bounding box
        SDL_Rect& GetColliderBoundingBox();
        // Detectar colisión
        // TODO: Podríamos considerar si vamos a manejar
        //       un objeto 'ICollider2D', o manejar diferentes
        //       colliders más adelante. Esto significa pasar
        //       un puntero más adelante y detectar el tipo en
        //       tiempo de ejecución, lo cual podría ser costoso.
        SDL_bool IsColliding(BoxCollider2D& collider);
        // Establecer la posición del collider (esquina superior izquierda del bounding box)
        void SetAbsolutePosition(int x, int y);
        // Establecer las dimensiones del bounding box
        void SetDimensions(int w, int h);
        // Función especial para establecer automáticamente el bounding box
        // Esta función examinará una superficie y creará
        // un bounding box ajustado alrededor de los valores mínimos y máximos
        // de x e y de la superficie.
        Vector2D SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b); 
        
        void Update();
        void Render();
    private:
        SDL_Rect* m_colliderRectangle;
};

#endif
