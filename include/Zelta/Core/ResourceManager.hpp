#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <Zelta/Core/Singleton.hpp>
#include <Zelta/Core/LoadingTarget.hpp>
#include <Zelta/Core/ResourceLoader.hpp>
#include <Zelta/Core/FileNotFoundException.hpp>
#include <map>

namespace zt {

    /**
     * @brief Base class for resources managers. A resource manager acts as a
     * container for a specific resource type (e.g.: a sf::Texture, sf::SoundBuffer).
     * 
     * ResourceManager inherits from LoadingTarget. That means that ResourceManager
     * is something you can load resources into.
     * All resources in the resource manager are identified by a name that should
     * be unique. You'll request those resources by using that name.
     * 
     * Resources managers also have a unique name which will help the
     * ResourceLoader to determine to which resource manager load certain resource.
     */
    template <class X>
    class ResourceManager : public LoadingTarget {
        protected:
        std::map <std::string, X> resources;
        std::string name;
        
    public:
        /**
         * Constructs the ResourceManager.
         * @param name Unique name for this ResourceManager.
         */
        ResourceManager(const std::string& name) : name(name) { }
        
        /**
         * Get a resource by its name.
         * If the resource is not present it throws a FileNotFoundException.
         * @param name Name of the resource.
         * @return Resource.
         */
        X& get(const std::string & name) {
            if (resources.find(name) == resources.end()) {
                throw FileNotFoundException();
            }

            return resources[name];
        }
        
        /**
         * Equivalent to get().
         * @see get()
         * @param name Name of the resource.
         * @return Resource.
         */
        X& operator[](const std::string& name) {
            return get(name);
        }
        
        /**
         * Returns the name of this resource manager.
         * @return 
         */
        const std::string& getName() const {
            return name;
        }

    };
}
#endif // RESOURCES_HPP
