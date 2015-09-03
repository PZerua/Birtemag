#include "Map.h"

Map::Map(string path)
{
	LEVEL_WIDTH = 0;

	LEVEL_HEIGHT = 0;

	TOTAL_TILES = 0;

	_mapPath = path;

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
			//Read tile from map file
			map >> tilemap >> temp >> tileType >> temp >> collision;
			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < _tmaps[tilemap]->getTotalTiles()))
			{
				_tileSet[i] = new Tile(x, y, collision);
				_tileSet[i]->setLayer(_tmaps[tilemap]->getTexture(), Layers::ground, tileType, tilemap);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			if (!tilesLoaded)
				break;

			//Move to next tile spot
			x += TILE_SIZE;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_SIZE;
			}
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

void Map::renderMap(SDL_Rect &camera)
{
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		_tileSet[ i ]->render(camera, _tmaps[_tileSet[i]->getTileMapID(0)]->getClips() );
	}
}

void Map::addTilemap(int tilemapID)
{
	Tilemap *tilemap;
	tilemap = new Tilemap();

	ifstream tilemaps("tilesets/tilesets.txt");

	int id = 0;
	string temp;

	while (tilemaps >> temp)
	{
		if (id == tilemapID)
		{
			tilemap->initTilemap("tilesets/" + temp, tilemapID);
			_tmaps[tilemapID] = tilemap;
			break;
		}
		id++;
	}
    
}

string Map::getPath()
{
	return _mapPath;
}

map<int, Tilemap *> &Map::getMap()
{
	return _tmaps;
}