#include <ESE/TileEngine/TilemapRenderer.hpp>

namespace ESE{

	TilemapRenderer::TilemapRenderer(){
		tileset = nullptr;
		originX=originY=0;
		width=height=0;
		tileWidth=tileHeight=0;
	
	}

	void TilemapRenderer::setTileset(sf::Texture *tileset){
		this->tileset = tileset;
	}
	
	void TilemapRenderer::setTilesetCoords(int number, sf::IntRect rect){
		rects[number] = rect;
	}
	
	void TilemapRenderer::detectTilesetCoords(int tileWidth, int tileHeight){
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		
		rects.clear();
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
	
	void TilemapRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		for (ESE::TileDrawable tile:tiles){
			target.draw(tile,states);
		}
	}
	
	void TilemapRenderer::setOriginOfMap(float originX, float originY){
		//Desplazamos todos los tiles.
		for (unsigned int i=0; i<tiles.size(); i++){
			ESE::TileDrawable t = tiles[i]; //Hacemos una copia para acceder más rápido a la posición x e y.
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
	
	sf::Vector2f TilemapRenderer::getOriginOfMap(){
		return sf::Vector2f(originX,originY);
	}
	
	void TilemapRenderer::setRenderingLimits(float x, float y, float width, float height){
		renderingLimits.top = y;
		renderingLimits.left = x;
		renderingLimits.width = width;
		renderingLimits.height = height;
		
	}
	
	std::pair<int, ESE::TileDrawable*> TilemapRenderer::addTile(int type, int colX, int rowY){
		tiles.push_back(ESE::TileDrawable());
		ESE::TileDrawable* tile = &tiles.back();
		tile->setTexture(*tileset);
		tile->setTextureRect(rects[type]);
		tile->setPosition(originX+colX*tileWidth,originY+rowY*tileHeight);
		return std::make_pair(tiles.size()-1,&tiles.back());
	}
	
	ESE::TileDrawable* TilemapRenderer::tileAt(int index){
		return &(tiles[index]);
	}
	
	void TilemapRenderer::setTileDimensions(int tileWidth, int tileHeight){
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
	}
}