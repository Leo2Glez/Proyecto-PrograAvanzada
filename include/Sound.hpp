#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>

// Terceros
#include <SDL2/SDL.h> // Para Mac, usar <SDL.h>

// Interfaz para Audio
class ISound{
    public:
        // El destructor es virtual para nuestra interfaz
        virtual ~ISound() {};
        // Funciones miembro que deben ser implementadas
        virtual void PlaySound() = 0;
        virtual void StopSound() = 0;
};

class Sound : public ISound{

    public:
        // Constructor
        Sound(std::string filepath);
        // Destructor
        ~Sound();
        // Reproducir sonido
        void PlaySound();
        // Detener el sonido
        void StopSound();
        // Específico para la API de SDL_Audio
        void SetupDevice();

    private: // (variables miembro privadas)
        // Dispositivo en el que se reproducirá el sonido
        // NOTA: Esto podría moverse a alguna configuración,
        //       por ejemplo, una clase 'AudioManager' de nivel superior
        SDL_AudioDeviceID m_device;

        // Propiedades del archivo Wave que se carga
        SDL_AudioSpec m_audioSpec;
        Uint8*        m_waveStart;
        Uint32        m_waveLength;
};

#endif
