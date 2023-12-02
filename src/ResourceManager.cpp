#include "ResourceManager.hpp"

ResourceManager::ResourceManager(){

}

ResourceManager::ResourceManager(ResourceManager const&){

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs){
    // TODO: Aunque no necesitamos esto para un singleton
    return *this;
}

// Se instancia exactamente 1 instancia de nuestra clase
ResourceManager& ResourceManager::GetInstance(){
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath){
    // Buscamos en nuestro m_surfaces, que es un 'unordered_map',
    // si existe un archivo.
    // Y si el archivo existe, entonces devolvemos la superficie asociada.
    auto search = m_surfaces.find(filepath);
    if(search != m_surfaces.end()){
        return m_surfaces[filepath];
    }else{
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        m_surfaces.insert(std::make_pair(filepath,surface));
        return m_surfaces[filepath];
    }
    
    return nullptr;

}
