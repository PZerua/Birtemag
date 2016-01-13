#include "Tile.h"

Tile::Tile(const int &x, const int &y, bool collision, LTexture *hideLayer)
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

void Tile::render(SDL_Rect& camera , map<int, Tilemap *> &tmaps, const int &layersToDraw, const int &currentLayer)
{
	int begin, end;
	bool hide = true;

	if (layersToDraw == LayerPos::Lower)
	{
		begin = Layers::ground;
		end = Layers::cover;
	}
	else if (layersToDraw == LayerPos::Upper)
	{
		begin = Layers::fringe;
		end = Layers::roof;
	}
	else if (layersToDraw == LayerPos::All)
	{
		begin = Layers::ground;
		end = Layers::roof;
	}
	
	// If the tile is on screen
	if( checkCollision( camera, mBox ) )
	{
		for (int i = begin; i < end; i++)
		{
			if (_layers.count(i))
			{
				// Show the tile
				_layers[i]->render(mBox.x - camera.x, mBox.y - camera.y, tmaps[_layers[i]->getTilemapId()]->getClips());
				// Hide lower layers when changing current layer (only in Editor mode)
				// BLACK MAGIC!! wtf is going on here
				if (i < currentLayer)
				{
					for (int j = i + 1; j < currentLayer; j++)
					{
						if (_layers.count(j))
							hide = false;
					}
					if (hide)
						_hideLayer->render(mBox.x - camera.x, mBox.y - camera.y);
				}
			}
			hide = true;
		}
	}
}

bool Tile::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}


void Tile::free()
{
	for (map<int, Layer *>::iterator it = _layers.begin(); it != _layers.end(); it++)
	{
		delete it->second;
		it = _layers.erase(it);
	}

	delete _hideLayer;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

void Tile::setLayer(LTexture &gTexture, const int &layer, const int &type, const int &tilemapID)
{
	if (!_layers.count(layer))
	{
		_layers[layer] = new Layer(tilemapID, type);
		_layers[layer]->setTexture(gTexture);
	}
	else
	{
		_layers[layer]->setTexture(gTexture);
		_layers[layer]->setType(type, tilemapID);
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

int Tile::getTileMapID(const int &layer)
{
	if(_layers.count(layer))
		return _layers[layer]->getTilemapId();
	else return 0;
}

bool Tile::hasTilemap(const int &layer, const int &tilemapID)
{
	if (getTileMapID(layer) != tilemapID || getTileMapID(layer) == 0)
		return true;
	else return false;
}

int Tile::getType(int layer)
{
	if(_layers.count(layer))
		return _layers[layer]->getType();
	else return 0;
}

void Tile::setLayerType(const int &layer, const int &type, const int &tilemapID)
{
	if (_layers.count(layer))
		_layers[layer]->setType(type, tilemapID);
}

void Tile::eraseLayer(const int &layer)
{
	_layers.erase(layer);
}