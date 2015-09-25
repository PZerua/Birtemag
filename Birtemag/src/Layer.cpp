#include "Layer.h"

Layer::Layer(int id, int type)
{
	_tilemapId = id;
	_mType = type;
}

Layer::~Layer()
{

}

int Layer::getTilemapId()
{
	return _tilemapId;
}

int Layer::getType()
{
	return _mType;
}

void Layer::setType(int type, int id)
{
	_mType = type;
	_tilemapId = id;
}

void Layer::setTexture(LTexture &texture)
{
	_gTileTexture = texture;
}


void Layer::render(int x, int y, SDL_Rect *gTileClips)
{
	_gTileTexture.render(x, y, &gTileClips[_mType]);
}