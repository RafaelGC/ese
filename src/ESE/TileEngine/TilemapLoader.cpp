#include <ESE/TileEngine/TilemapLoader.hpp>

namespace ESE{
	
	TilemapLoader::TilemapLoader(){
		listener = nullptr;
		width = height = tileWidth = tileHeight = 0;
	}
	
	void TilemapLoader::setTileLoadedListener(TileLoadedListener*listener){
		this->listener = listener;
	}
	
	void TilemapLoader::loadFromFile(std::string file){
		pugi::xml_document doc;
		if (!doc.load_file(file.c_str())){
			std::cout << "Tilemap could not be loaded." << std::endl;
		}
		
		//El primer y único nodo es el mapa, que contiene otros nodos.
		pugi::xml_node map = doc.first_child();
		//Este nodo tiene información útil como el tamaño del mapa en tiles así como el ancho y alto
		//de cada tile.
		width = map.attribute("width").as_int();
		height = map.attribute("height").as_int();
		tileWidth = map.attribute("tilewidth").as_int();
		tileHeight = map.attribute("tileheight").as_int();
		
		if (listener){
			listener->infoLoaded(tileWidth,tileHeight,width,height);
		}
		
		//Ahora recorreremos los nodos del mapa en busca de los que nos interesan.
		for (pugi::xml_node node = map.first_child(); node; node = node.next_sibling()){
			//La capa es el elemento más importante, por ahora sólo soportamos una.
			if (strcmp(node.name(),"layer")==0){
				//Dentro de la capa hay un elemento "data" que a su vez contiene un motón de
				//nodos "tile" cuyos valores son los que nos interesan.
				pugi::xml_node nodoData = node.first_child();
				if (strcmp(nodoData.name(),"data")==0){
					
					int auxX=0, auxY=0;
					//Ahora recorremos, dentro de data, todos los tiles.
					for (pugi::xml_node nodoTiles = nodoData.first_child(); nodoTiles; nodoTiles = nodoTiles.next_sibling()){
						int type = nodoTiles.attribute("gid").as_int();
						if (type!=0){
							if (listener){
								listener->tileLoaded(type,auxX,auxY);
							}
						}
						
						auxX++;
							if (auxX>width-1){
								auxX=0;
								auxY++;
							}
						}				
						
					}
					
				}
				
			}
	}
	
	int TilemapLoader::getHeight(){
		return height;
	}
	int TilemapLoader::getTileHeight(){
		return tileHeight;
	}
	int TilemapLoader::getTileWidth(){
		return tileWidth;
	}
	int TilemapLoader::getWidth(){
		return width;
	}
	
}