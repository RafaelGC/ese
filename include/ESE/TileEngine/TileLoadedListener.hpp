#ifndef TILEMAPLOADERLISTENER_HPP
#define TILEMAPLOADERLISTENER_HPP

#include <string>

namespace ESE {

    class TileLoadedListener {
    public:
        virtual void onTileLoaded(int type, int x, int y) = 0;
        virtual void onInfoLoaded(int tileWidth, int tileHeight, int width, int height) = 0;
        virtual void onObjectLoaded(float x, float y, std::wstring type, std::wstring name) = 0;
        virtual void onPropertyLoaded(std::wstring name, std::wstring value) = 0;
    };
}
#endif
