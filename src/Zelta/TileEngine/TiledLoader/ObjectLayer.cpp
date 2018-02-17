#include <Zelta/TileEngine/TiledLoader/ObjectLayer.hpp>

namespace zt {
    namespace tiled {
        ObjectLayer::ObjectLayer(const std::wstring& name) : name(name) {
            
        }

        void ObjectLayer::addObject(const Object& object) {
            objects.push_back(object);
        }

        int ObjectLayer::size() const {
            return objects.size();
        }

        Object& ObjectLayer::operator[](int index) {
            return objects[index];
        }
        
        const std::wstring& ObjectLayer::getName() const {
            return name;
        }
    }
}