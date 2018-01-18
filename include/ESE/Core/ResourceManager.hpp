#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <ESE/Core/Singleton.hpp>
#include <ESE/Core/Loadable.hpp>
#include <ESE/Core/ResourceLoader.hpp>
#include <map>

namespace ESE {

    template <class X>
    class ResourceManager : public Loadable {
        protected:
        std::map <std::string, X> resources;
        std::string name;
        ResourceManager(const std::string& name) : name(name) {
            ResourceLoader::registerResourceManager(name, *this);
        }
        
        public:

        X* getResource(const std::string & name) {

            if (resources.find(name) == resources.end()) {
                return nullptr;
            }

            return &resources[name];
        }
        
        const std::string& getName() const {
            return name;
        }

    };
}
#endif // RESOURCES_HPP
