#include <ESE/Core/ResourceLoader.hpp>
#include <ESE/Core/Loadable.hpp>
#include <map>

namespace ESE {
    std::map <std::string, Loadable*> ResourceLoader::resourceManagers;
}