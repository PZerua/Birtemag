#include "Tile.h"

Tile::Tile( int x, int y, int tileType, bool collision, int id )
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_SIZE;
	mBox.h = TILE_SIZE;

	//Get the tile type
	_mType = tileType;

	_tilemapID = id;

	_hasCollision = collision;

}

Tile::~Tile()
{

}

void Tile::render(SDL_Rect& camera , SDL_Rect *gTileClips)
{
	//If the tile is on screen
	if( checkCollision( camera, mBox ) )
	{
		for (map<int, LTexture *>::iterator it = _layers.begin(); it != _layers.end(); ++it)
		{
			//Show the tile
			it->second->render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[_mType]);
		}
	}
}

void Tile::free()
{
	for (map<int, LTexture *>::iterator it = _layers.begin(); it != _layers.end(); ++it)
	{
		it->second->free();
	}
}

void Tile::setType(int type, int id)
{
	_mType = type;
	_tilemapID = id;
}

int Tile::getType()
{
	return _mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

void Tile::setTexture(LTexture *gTexture, int layer)
{
	if (!_layers.count(layer))
		_layers[layer] = new LTexture;
	_layers[layer] = gTexture;
}

bool Tile::hasCollision()
{
	return _hasCollision;
}

void Tile::setCollision(bool coliss)
{
	_hasCollision = coliss;
}

int Tile::getTileMapID()
{
	return _tilemapID;
}