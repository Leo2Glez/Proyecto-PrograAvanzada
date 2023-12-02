#include "SDLApp.hpp"

#include <iostream>

// Constructor
SDLApp::SDLApp(Uint32 subsystemFlags, const char* title,int x, int y, int w, int h){

    m_width= w;
    m_height= h;

    // Valor predeterminado
    m_maxFrameRate = 60;

    // Inicializar el subsistema de video.
    // Si devuelve menos de 1, se recibirá un código de error.
    if(SDL_Init(subsystemFlags) < 0){
        std::cout << "SDL no pudo inicializarse: " <<
                  SDL_GetError();
    }else{
        std::cout << "El sistema de video de SDL está listo para usar\n";
    }
    // Solicitar la creación de una ventana para nuestra plataforma
    // Los parámetros son para el título, la posición x e y,
    // y el ancho y alto de la ventana.
    m_window = SDL_CreateWindow(title,x,y,w,h,SDL_WINDOW_SHOWN);

    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
}

// Destructor
SDLApp::~SDLApp(){
    // Destruir nuestra ventana
    SDL_DestroyWindow(m_window);
    // Cerrar nuestra aplicación de SDL
    SDL_Quit();
}

// Manejar eventos
void SDLApp::SetEventCallback(std::function<void(void)> func){
    m_EventCallback = func;
}
// Manejar eventos
void SDLApp::SetUpdateCallback(std::function<void(void)> func){
    m_UpdateCallback = func;
}

// Manejar renderizado
void SDLApp::SetRenderCallback(std::function<void(void)> func){
    m_RenderCallback = func;
    
}

// Ejecutar el bucle de nuestra aplicación
void SDLApp::RunLoop(){
    while(m_gameIsRunning){
        Uint32 start = SDL_GetTicks();

        // 
        Uint32 buttons;
        buttons = SDL_GetMouseState(&m_mouseX,&m_mouseY);
        // (1) Manejar eventos primero
        // El usuario especifica qué hacer en la devolución de llamada de eventos
        m_EventCallback();

        // (2) Luego manejar cualquier actualización
        m_UpdateCallback();
        // (3) Luego manejar nuestro renderizado
        // Limpiar y dibujar la pantalla
        // Nos da un "lienzo" limpio
        SDL_SetRenderDrawColor(m_renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);

        // Realizar nuestro dibujo
        SDL_SetRenderDrawColor(m_renderer,255,255,255,SDL_ALPHA_OPAQUE);
        // Lo que el usuario especifica que suceda durante la etapa de renderizado
        // en esta función de devolución de llamada
        m_RenderCallback();
        // Finalmente mostrar lo que hemos dibujado
        SDL_RenderPresent(m_renderer);

        // Realizar el paso de limitación de fotogramas
        Uint32 elapsedTime = SDL_GetTicks() - start;
        if(elapsedTime < m_maxFrameRate){
            SDL_Delay(m_maxFrameRate - elapsedTime);
        }
    }
}

void SDLApp::SetMaxFrameRate(int frameRate){
    m_maxFrameRate = frameRate;
}

SDL_Renderer* SDLApp::GetRenderer() const{
    return m_renderer;
}

int SDLApp::GetMouseX(){
    return m_mouseX;
}
int SDLApp::GetMouseY(){
    return m_mouseY;
}

int SDLApp::GetWindowWidth(){
    return m_width;
}

int SDLApp::GetWindowHeight(){
    return m_height;
}

void SDLApp::StopAppLoop(){
    m_gameIsRunning = false;
}
