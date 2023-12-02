#include "Sound.hpp"

// Para la salida de errores
#include <iostream>

Sound::Sound(std::string filepath){
    if(SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength) == nullptr){
        std::cerr << "error al cargar el sonido: " << SDL_GetError() << std::endl;
    }
}

Sound::~Sound(){
    SDL_FreeWAV(m_waveStart);
    SDL_CloseAudioDevice(m_device);
}

void Sound::PlaySound(){
    // Encolar el audio (para reproducir cuando esté disponible,
    // en lugar de una función de devolución de llamada)
    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength);
    SDL_PauseAudioDevice(m_device,0);
}

void Sound::StopSound(){
    SDL_PauseAudioDevice(m_device,1);
}

void Sound::SetupDevice(){
    // Solicitar el dispositivo predeterminado más razonable
    // Establecer el dispositivo para reproducción en 0, o '1' para grabación.
    m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    // Mensaje de error si no se encuentra ningún dispositivo adecuado para reproducir
    // audio en.
    if(0 == m_device){
        std::cerr << "error del dispositivo de sonido: " << SDL_GetError() << std::endl; 
    }
}
