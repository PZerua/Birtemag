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
}

Map::~Map()
{

}

void Map::renderMap(SDL_Rect &camera, int currentLayer, bool showBorder)
{
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		for (int j = 0; j < Layers::size; j++)
			if (_tileSet[i]->getTileMapID(j) != 0)
				_tileSet[i]->render(camera, _tmaps, currentLayer);
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
	ofstream newMap(_mapPath);

	int width, height;

	width = LEVEL_WIDTH / TILE_SIZE;
	height = LEVEL_HEIGHT / TILE_SIZE;

	newMap << width << " " << height << "\n";

	for (int i = 0; i < TOTAL_TILES; i++)
	{
		if ( (i % width) == 0 && i != 0)
			newMap << "\n";
		newMap << "00:0 ";
	}
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