#include "Tile.h"

Tile::Tile( int x, int y, bool collision, LTexture *hideLayer)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_SIZE;
	mBox.h = TILE_SIZE;
	
	_hideLayer = hideLayer;

	_hasCollision = collision;

}

Tile::~Tile()
{
	free();
}

void Tile::render(SDL_Rect& camera , map<int, Tilemap *> &tmaps, int currentLayer)
{
	//If the tile is on screen
	if( checkCollision( camera, mBox ) )
	{
		for (map<int, Layer *>::iterator it = _layers.begin(); it != _layers.end(); ++it)
		{
			//Show the tile
			it->second->render(mBox.x - camera.x, mBox.y - camera.y, tmaps[it->second->getTilemapId()]->getClips());
			if (it->first < currentLayer)
			{
				for (int i = it->first; i < currentLayer; i++)
					_hideLayer->render(mBox.x - camera.x, mBox.y - camera.y);
			}
				
		}
	}
}

void Tile::free()
{

}

SDL_Rect Tile::getBox()
{
	return mBox;
}

void Tile::setLayer(LTexture &gTexture, int layer, int type, int id)
{
	if (!_layers.count(layer))
	{
		_layers[layer] = new Layer(id, type);
		_layers[layer]->setTexture(gTexture);
	}
	else
	{
		_layers[layer]->setTexture(gTexture);
		_layers[layer]->setType(type, id);
	}
}

bool Tile::hasCollision()
{
	return _hasCollision;
}

void Tile::setCollision(bool coliss)
{
	_hasCollision = coliss;
}

int Tile::getTileMapID(int layer)
{
	if(_layers.count(layer))
		return _layers[layer]->getTilemapId();
	else return 0;
}

int Tile::getType(int layer)
{
	if(_layers.count(layer))
		return _layers[layer]->getType();
	else return 0;
}

void Tile::setLayerType(int layer, int type, int id)
{
	if (_layers.count(layer))
		_layers[layer]->setType(type, id);
}

void Tile::eraseLayer(int layer)
{
	_layers.erase(layer);
}