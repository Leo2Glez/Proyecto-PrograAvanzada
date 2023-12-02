#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <functional>

// Terceros
#include <SDL2/SDL.h> // Para Mac, usar <SDL.h>

class SDLApp{
    public:
        // Constructor
        SDLApp(Uint32 subsystemFlags, const char* title,int x, int y, int w, int h);
        // Destructor
        ~SDLApp();
        // Manejar eventos
        void SetEventCallback(std::function<void(void)> func);
        // Manejar actualizaciones
        void SetUpdateCallback(std::function<void(void)> func);
        // Manejar renderizado
        void SetRenderCallback(std::function<void(void)> func);
        // Ejecutar el bucle principal de la aplicación
        void RunLoop();
        // Establecer la velocidad máxima de renderizado de cada fotograma
        // Esto es un límite de fotogramas en términos de milisegundos que
        // cada iteración de nuestro bucle principal no superará
        void SetMaxFrameRate(int frameRate);
        // Obtener el renderizador
        SDL_Renderer* GetRenderer() const;
        // Obtener las posiciones del ratón
        int GetMouseX();
        int GetMouseY();
        // Obtener las dimensiones de la ventana
        int GetWindowWidth();
        int GetWindowHeight();
        // Detener el bucle principal de nuestra aplicación
        void StopAppLoop();

    private:
            // Puntero a nuestra ventana SDL
            SDL_Window* m_window=nullptr;
            // Puntero a nuestro renderizador SDL
            SDL_Renderer* m_renderer = nullptr;
            // Establecer el límite máximo de fotogramas;
            int m_maxFrameRate;
            // Bucle infinito para nuestra aplicación
            bool m_gameIsRunning = true;
            // Almacenar las coordenadas del ratón de forma predeterminada
            int m_mouseX;
            int m_mouseY;
            // Almacenar el ancho y alto de la ventana
            int m_width;
            int m_height;
            // Almacenar nuestras funciones de devolución de llamada
            std::function<void(void)> m_EventCallback;
            std::function<void(void)> m_UpdateCallback;
            std::function<void(void)> m_RenderCallback;
};

#endif
