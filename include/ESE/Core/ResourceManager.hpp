#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <ESE/Core/Singleton.hpp>
#include <map>

namespace ESE {

    template <class X>
    class ResourceManager {
        friend class Singleton<ResourceManager>;
        
        protected:
        std::map <std::string, X> resources;
        ResourceManager() {}
        
        public:

        virtual void loadFromFile(const std::string & name, const std::string & path) = 0;

        X* getResource(const std::string & name) {

            if (resources.find(name) == resources.end()) {
                return nullptr;
            }

            return &resources[name];
        }

    };
}
#endif // RESOURCES_HPP
