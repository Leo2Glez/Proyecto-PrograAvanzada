#include "DynamicText.hpp"
#include <iostream>

// Inicializar variables estáticas
// Debe inicializarse en falso por defecto
bool DynamicText::s_ttfInitialized = false;

// Constructor
// ejemplo: "./assets/fonts/8bitOperatorPlus8-Regular.ttf"
DynamicText::DynamicText(std::string fontfilepath, size_t fontSize){
    // Al igual que cuando inicializamos nuestro subsistema gráfico,
    // debemos hacer lo mismo para nuestro sistema de fuentes.
    if(!s_ttfInitialized && TTF_Init() == -1){
        std::cout << "No se pudo inicializar SDL2_ttf, error: " << TTF_GetError() << std::endl;
    }else if(!s_ttfInitialized){
        std::cout << "¡Sistema SDL2_ttf listo para usar!" << std::endl;
        // Inicializar el sistema TTF solo una vez, incluso si
        // tenemos múltiples objetos de texto.
        s_ttfInitialized = true;
    }  
    // Cargar nuestro archivo de fuente y establecer el tamaño de la fuente
    m_ourFont = TTF_OpenFont(fontfilepath.c_str(),fontSize);
    // Confirmar que se cargó
    if(m_ourFont == nullptr){
        std::cout << "No se pudo cargar la fuente" << std::endl;
        exit(1);
    }
}

DynamicText::~DynamicText(){
    // Destruir nuestro texto texturizado
    SDL_DestroyTexture(m_texture);

    // Cerrar nuestro subsistema de fuentes
    TTF_CloseFont(m_ourFont);	
}

void DynamicText::DrawText(SDL_Renderer* renderer, std::string text,int x, int y, int w, int h){
    // Píxeles de nuestro texto
    m_surface = TTF_RenderText_Solid(m_ourFont,text.c_str(),{255,255,255});

    // Configurar la textura
    m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);
    // Liberar la superficie
    // Ya no la necesitamos después de haberla cargado en
    // la textura
    SDL_FreeSurface(m_surface);

    // Crear un rectángulo para dibujar
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
    // Renderizar nuestro texto en un rectángulo
    SDL_RenderCopy(renderer,m_texture,NULL,&m_rectangle);

}
