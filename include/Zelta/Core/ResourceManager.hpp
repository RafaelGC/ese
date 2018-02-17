#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <Zelta/Core/Singleton.hpp>
#include <Zelta/Core/Loadable.hpp>
#include <Zelta/Core/ResourceLoader.hpp>
#include <Zelta/Core/FileNotFoundException.hpp>
#include <map>

namespace zt {

    template <class X>
    class ResourceManager : public Loadable {
        protected:
        std::map <std::string, X> resources;
        std::string name;
        ResourceManager(const std::string& name) : name(name) {
            
        }
        
        public:

        X& get(const std::string & name) {
            if (resources.find(name) == resources.end()) {
                throw FileNotFoundException();
            }

            return resources[name];
        }
        
        X& operator[](const std::string& name) {
            return get(name);
        }
        
        const std::string& getName() const {
            return name;
        }

    };
}
#endif // RESOURCES_HPP
