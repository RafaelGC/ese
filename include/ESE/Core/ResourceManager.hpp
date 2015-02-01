#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "TextureContainer.hpp"
namespace ESE {

    /**
     * @brief Gestor de recursos simple (imágenes, sonidos, fuentes...). Si el programador quiere algo más
     * avanzado puede implementar su propio gestor de recursos así como sus propios contenedores.
     * */
    class ResourceManager {
        static ResourceManager* resourceManagerInstance;
    protected:
        ESE::TextureContainer textureContainer;
    public:
        static ResourceManager* instance();
        static void release();

        ESE::TextureContainer *getTextureContainer();

    private:
        ResourceManager();
        virtual ~ResourceManager();

    };
}
#endif // RESOURCES_HPP
