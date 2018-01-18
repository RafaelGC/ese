#include <Zelta/Core/ResourceLoader.hpp>
#include <Zelta/Core/Loadable.hpp>
#include <map>

namespace zt {
    std::map <std::string, Loadable*> ResourceLoader::resourceManagers;
}