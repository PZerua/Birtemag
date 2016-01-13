#include "Map.h"

Map::Map(string path)
{
	LEVEL_WIDTH = 0;

	LEVEL_HEIGHT = 0;

	TOTAL_TILES = 0;

	_mapPath = path;

	center.x = 0;
	center.y = 0;

	_hideLayer.loadFromFile("utils/hideLayer.png");
	_border.loadFromFile("utils/border.png");
	_hideLayer.setAlpha(50);

}

Map::Map(int width, int height, string name)
{
	LEVEL_WIDTH = width * TILE_SIZE;
	LEVEL_HEIGHT = height * TILE_SIZE;
	TOTAL_TILES = width * height;
	_name = name;
	_mapPath = "bitmaps/" + name + ".map";
	createMap();

	center.x = 0;
	center.y = 0;

	_hideLayer.loadFromFile("utils/hideLayer.png");
	_border.loadFromFile("utils/border.png");
	_hideLayer.setAlpha(50);
}

Map::~Map()
{

}

void Map::renderMap(SDL_Rect &camera, int currentLayer, int layersToDraw, bool showBorder)
{
	
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		_tileSet[i]->render(camera, _tmaps, layersToDraw, currentLayer);

		if (showBorder)
		{
			if (i < LEVEL_WIDTH / 64)
			{
				_border.render(i * TILE_SIZE - camera.x, -2 - camera.y);
				_border.render(i * TILE_SIZE - camera.x, LEVEL_HEIGHT - camera.y);
			}
			if (i < LEVEL_HEIGHT / 64)
			{
				_border.render(-1 - camera.x, i * TILE_SIZE - camera.y, NULL, 90, &center);
				_border.render(LEVEL_WIDTH + 1 - camera.x, i * TILE_SIZE - camera.y, NULL, 90, &center);
			}
		}
	}

}

void Map::createMap()
{

	_tileSet = new Tile*[TOTAL_TILES];

	std::ofstream Map(_mapPath);

	Map << getTilemaps().size() << "\n";

	for (map<int, Tilemap *>::iterator it = getTilemaps().begin(); it != getTilemaps().end(); ++it)
	{
		Map << it->first << "\n";
	}

	Map << LEVEL_WIDTH / TILE_SIZE << " " <<LEVEL_HEIGHT / TILE_SIZE << "\n";

	int x = 0;
	int y = 0;

	//Go through the tiles
	for (int t = 0; t < TOTAL_TILES; t++)
	{
		if (x == LEVEL_WIDTH)
		{
			x = 0;
			y += 64;
		}

		_tileSet[t] = new Tile(x, y, 0, &_hideLayer);

		if ((t % (LEVEL_WIDTH / TILE_SIZE)) == 0 && t != 0)
		{
			Map << "\n";
		}

		for (int i = 0; i < Layers::size; i++)
		{
			Map << _tileSet[t]->getTileMapID(i);
			Map << ":";

			if (_tileSet[t]->getType(i) < 10)
			{
				//Write tile type to file
				Map << 0 << _tileSet[t]->getType(i) << ":";
			}
			else Map << _tileSet[t]->getType(i) << ":";
		}
		Map << _tileSet[t]->hasCollision() << " ";

		x += 64;
	}

	//Close the file
	Map.close();
}


Tile **Map::getTiles()
{
	return _tileSet;
}

bool Map::loadMap()
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;
	char temp;
	bool collision = false;

	//Open the map
	ifstream map( _mapPath );

	//If the map couldn't be loaded
	if( map.fail() )
	{
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
	}
	else
	{
		int width = -1;
		int height = -1;

		int numberTilemaps = -1;
		int tilemapID;

		map >> numberTilemaps;

		if (numberTilemaps != -1 && numberTilemaps != 0)
		{
			for (int i = 0; i < numberTilemaps; i++)
			{
				map >> tilemapID;
				addTilemap(tilemapID);
			}
		}

		map >> width;
		map >> height;

		if (width == -1 || height == -1)
		{
			cout<<"Error reading map size"<<endl;
			return false;
		}

		LEVEL_WIDTH = width * TILE_SIZE;
		LEVEL_HEIGHT = height * TILE_SIZE;
		TOTAL_TILES = width * height;

		_tileSet = new Tile*[TOTAL_TILES];

		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;
			int tilemap = -1;

			for (int j = 0; j < Layers::size; j++)
			{
				//Read tile from map file
				map >> tilemap >> temp >> tileType >> temp;
				//If the was a problem in reading the map
				if (map.fail())
				{
					//Stop loading map
					printf("Error loading map: Unexpected end of file!\n");
					tilesLoaded = false;
					break;
				}

				if (tilemap != 0)
				{
					//If the number is a valid tile number
					if ((tileType >= 0) && (tileType < _tmaps[tilemap]->getTotalTiles()))
					{
						if (j == 0)
							_tileSet[i] = new Tile(x, y, collision, &_hideLayer);
						_tileSet[i]->setLayer(_tmaps[tilemap]->getTexture(), j, tileType, tilemap);
					}
					//If we don't recognize the tile type
					else
					{
						//Stop loading map
						cout << "Error loading map: Invalid tile type at " << i << endl;
						cout << "tilemap: " << tilemap << ", tileType: " << tileType << endl;
						tilesLoaded = false;
						break;
					}
				}
				else
				{
					if (j == 0)
						_tileSet[i] = new Tile(x, y, collision, &_hideLayer);
				}
				
				if (!tilesLoaded)
					break;
			}

			if (!tilesLoaded)
				break;

			//Move to next tile spot
			x += TILE_SIZE;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_SIZE;
			}

			map >> collision;
			_tileSet[i]->setCollision(collision);

		}

	}

	cout << "[MAP] Map loaded" << endl;

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

bool Map::touchesWall( SDL_Rect box )
{
	//Go through the tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		//If the tile is a wall type tile
		if( _tileSet[ i ]->hasCollision() )
		{
			//If the collision box touches the wall tile
			if( checkCollision( box, _tileSet[ i ]->getBox() ) )
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}

bool Map::checkCollision(SDL_Rect a, SDL_Rect b)
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


void Map::addTilemap(int tilemapID)
{
	_tmaps[tilemapID]->initTilemap();
}

string Map::getPath()
{
	return _mapPath;
}

map<int, Tilemap *> &Map::getTilemaps()
{
	return _tmaps;
}

void Map::setTilemaps(map<int, Tilemap *> &tmaps)
{
	_tmaps = tmaps;
}

bool Map::hasTilemap(const int &tilemapID)
{
	if (_tmaps.count(tilemapID))
		return true;
	else return false;
}