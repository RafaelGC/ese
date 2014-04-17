#include <ESE/TileEngine/Tilemap.hpp>

namespace ESE{

	Tilemap::Tilemap(){
		tileset = nullptr;
		originX=originY=0;
		width=height=0;
		tileWidth=tileHeight=0;
	
	}

	void Tilemap::setTileset(sf::Texture *tileset){
		this->tileset = tileset;
	}
	
	void Tilemap::setTilesetCoords(int number, sf::IntRect rect){
		rects[number] = rect;
	}
	
	void Tilemap::detectTilesetCoords(int tileWidth, int tileHeight){
		//No haremos nada si no hay un tileset establecido.
		if (tileset){
			//Vamos a calcular cuántos tiles tiene de ancho.
			unsigned int w = tileset->getSize().x/tileWidth;
			unsigned int h = tileset->getSize().y/tileHeight;
			
			for (unsigned int itY=0; itY<h; itY++){
				for (unsigned int itX=0; itX<w; itX++){
					setTilesetCoords(itY*w+itX+1,sf::IntRect(itX*tileWidth,itY*tileHeight,tileWidth,tileHeight));
				}
			}
			
		}
	}
	
	void Tilemap::load(std::string file){
		//Limpiamos los tiles.
		tiles.resize(0);
		
		pugi::xml_document doc;
		doc.load_file(file.c_str());
		
		//El primer y único nodo es el mapa, que contiene otros nodos.
		pugi::xml_node map = doc.first_child();
		//Este nodo tiene información útil como el tamaño del mapa en tiles así como el ancho y alto
		//de cada tile.
		width = map.attribute("width").as_int();
		height = map.attribute("height").as_int();
		tileWidth = map.attribute("tilewidth").as_int();
		tileHeight = map.attribute("tileheight").as_int();
		
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
						
						//En principio, el usuario debería haber relacionado el tipo de tile con algún IntRect que
						//se encontrará en el vector rects.
						//Vamos a meter un nuevo tile (si su tipo es distinto de 0, porque 0 representa vacío).
						if (type!=0){
							
							ESE::Tile nuevoTile;
							nuevoTile.setTexture(*tileset);
							nuevoTile.setTextureRect(rects[type]);
							nuevoTile.setPosition(auxX*tileWidth,auxY*tileHeight);
							tiles.push_back(nuevoTile);
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
	void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		for (ESE::Tile tile:tiles){
			target.draw(tile,states);
		}
	}
	
	void Tilemap::setOriginOfMap(float originX, float originY){
		//Desplazamos todos los tiles.
		for (unsigned int i=0; i<tiles.size(); i++){
			ESE::Tile t = tiles[i]; //Hacemos una copia para acceder más rápido a la posición x e y.
			float newPositionX = (originX-this->originX)+t.getPosition().x;
			float newPositionY = (originY-this->originY)+t.getPosition().y;
			tiles[i].setPosition(newPositionX,newPositionY); //Pero modificamos el
			//tile original del vector.
			
			if (newPositionX<renderingLimits.left){
				tiles[i].setVisibleInTilemap(false);
			}
			else if (newPositionY<renderingLimits.top){
				tiles[i].setVisibleInTilemap(false);
			}
			else if (newPositionX>renderingLimits.left+renderingLimits.width){
				tiles[i].setVisibleInTilemap(false);
			}
			else if (newPositionY>renderingLimits.top+renderingLimits.height){
				tiles[i].setVisibleInTilemap(false);
			}
			else{
				tiles[i].setVisibleInTilemap(true);
			}
		}
		
		this->originX = originX;
		this->originY = originY;
		
	}
	
	sf::Vector2f Tilemap::getOriginOfMap(){
		return sf::Vector2f(originX,originY);
	}
	
	void Tilemap::setRenderingLimits(float x, float y, float width, float height){
		renderingLimits.top = y-tileHeight;
		renderingLimits.left = x-tileWidth;
		renderingLimits.width = width+tileWidth;
		renderingLimits.height = height+tileHeight;
		
	}
}