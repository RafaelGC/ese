#ifndef TILEMAPLOADERLISTENER_HPP
#define TILEMAPLOADERLISTENER_HPP

namespace ESE{
	class TileLoadedListener{
	public:
		virtual void onTileLoaded(int type, int x, int y)=0;
		virtual void onInfoLoaded(int tileWidth, int tileHeight, int width, int height)=0;
	};
}
#endif
