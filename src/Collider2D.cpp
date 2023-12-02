#include "Collider2D.hpp"

// TODO: iostream por ahora para
//       reportar errores. Debería
//       registrar en otro búfer
#include <iostream>

BoxCollider2D::BoxCollider2D()
{
    m_colliderRectangle = new SDL_Rect;
    m_colliderRectangle->x = 0;
    m_colliderRectangle->y = 0;
    m_colliderRectangle->w = 0;
    m_colliderRectangle->h = 0; 
}


BoxCollider2D::~BoxCollider2D(){

}

SDL_Rect& BoxCollider2D::GetColliderBoundingBox() {
    return *m_colliderRectangle;
}

// Detectar colisión
SDL_bool BoxCollider2D::IsColliding(BoxCollider2D& collider)
{

    if(m_colliderRectangle==nullptr){
        return SDL_FALSE;
    }
    const SDL_Rect* temp = collider.m_colliderRectangle;
    if(temp==nullptr){
        return SDL_FALSE;
    }
    return SDL_HasIntersection(m_colliderRectangle,temp);
}

void BoxCollider2D::SetAbsolutePosition(int x, int y){
    m_colliderRectangle->x = x;
    m_colliderRectangle->y = y;
}
void BoxCollider2D::SetDimensions(int w, int h){
    m_colliderRectangle->w = w;
    m_colliderRectangle->h = h; 
}

Vector2D BoxCollider2D::SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b){
    
    if(surface==nullptr){
        std::cerr << "SetBoundingBoxAutomatically: nullptr detectado para la superficie del cuadro delimitador" << std::endl;
    }
    SDL_LockSurface(surface);
    int w= surface->w;
    int h= surface->h;
    int pitch = surface->pitch;
    int colorchannels = pitch/w;  // típicamente 3 o 4 
    // Importante obtener el tipo de píxel correcto aquí
    Uint8* pixels = (Uint8*)surface->pixels; 
    
//    std::cout << "w: " << w << std::endl;
//    std::cout << "h: " << h << std::endl;
//    std::cout << "pitch: " << pitch << std::endl;
//    std::cout << "colorchannels: " << colorchannels << std::endl;
//    std::cout << SDL_GetPixelFormatName(surface->format->format) << std::endl;

    SDL_UnlockSurface(surface);
    

    // Establecer valores mayores que el tamaño de una imagen
    int xmin= w; // Valor más pequeño en el eje x que no forma parte de la clave de color
    int xmax= 0; // Valor más grande en el eje x que no forma parte de la clave de color
    int ymin= h;
    int ymax= 0;

    for(int y =0; y < h; y++){
        for(int x=0; x < w*colorchannels; x+=colorchannels){ 

            if(pixels[y*(w*colorchannels)+x+0] == b &&
               pixels[y*(w*colorchannels)+x+1] == g &&
               pixels[y*(w*colorchannels)+x+2] == r){
                // el píxel debe ser transparente
            }else{
                // Actualizar los valores más pequeños y más grandes
                // de los píxeles no transparentes
                xmin = std::min(x,xmin);
                xmax = std::max(x,xmax);

                ymin = std::min(ymin,y);
                ymax = std::max(ymax,y);
            }
        }
    }


    // Actualizar nuestro cuadro delimitador
    // Tener en cuenta que el máximo siempre será mayor que
    // el valor mínimo
    // Para el ancho, necesitamos dividir por el paso de nuestro objeto
    int scale = (1200/300);
    m_colliderRectangle->w = ((xmax/colorchannels - xmin/colorchannels)/(scale));
    m_colliderRectangle->h = (ymax - ymin)/scale;
//    m_colliderRectangle->x = m_colliderRectangle->x;
//    m_colliderRectangle->y = m_colliderRectangle->y;

//    std::cout << "m_col.w: " << m_colliderRectangle->w << std::endl;
//    std::cout << "m_col.h: " << m_colliderRectangle->h << std::endl;
//    std::cout << "xmin: " << xmin << std::endl;
//    std::cout << "xmax: " << xmax << std::endl;
//    std::cout << "ymin: " << ymin << std::endl;
//    std::cout << "ymax: " << ymax << std::endl;

    Vector2D result;
    result.x = xmin/(colorchannels*scale);
    result.y = ymin/scale;
    return result;
}

void BoxCollider2D::Update(){
}

void BoxCollider2D::Render(){

}
