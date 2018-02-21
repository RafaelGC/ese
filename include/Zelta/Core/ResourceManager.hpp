#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <Zelta/Core/Singleton.hpp>
#include <Zelta/Core/LoadingTarget.hpp>
#include <Zelta/Core/ResourceProvider.hpp>
#include <Zelta/Core/FileNotFoundException.hpp>
#include <map>

namespace zt {

    /**
     * @brief Base class for resource managers. A resource manager acts as a
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
        struct Resource {
            X resource;
            bool isPendant;
            Resource() { isPendant = false; }
        };
        std::map <std::string, Resource> resources;
        std::string name;
        ResourceProvider* provider;
    public:
        /**
         * Constructs the ResourceManager.
         * @param name Unique name for this ResourceManager.
         */
        ResourceManager(const std::string& name) : name(name), provider(nullptr) {
        }
        
        /**
         * Get a resource by its name.
         * If the resource is not present it throws a ResourceNotFoundException.
         * @param name Name of the resource.
         * @return Resource.
         */
        X& get(const std::string & name) {
            if (resources.find(name) == resources.end()) {
                throw ResourceNotFoundException(name);
            }
            
            // If the user asks for a file that it's not loaded we
            // ask the provider for it.
            if (provider && resources[name].isPendant) {
                provider->request(this->name, name);
                // Now, the file should be loaded.
            }
            
            return resources[name].resource;
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
        
        void setProvider(ResourceProvider* provider) {
            this->provider = provider;
        }
        
        void pendant(const std::string& name, ResourceProvider& provider) {
            resources[name].isPendant = true;
            this->provider = &provider;
        }
        
        void notPendant(const std::string& name) {
            resources[name].isPendant = false;
        }
        
        bool exists(const std::string& resourceName) const {
            return resources.count(resourceName) == 1;
        }
        
        bool isLoaded(const std::string& resourceName) const {
            return exists(resourceName) && !resources.at(resourceName).isPendant;
        }

    };
}
#endif // RESOURCES_HPP
