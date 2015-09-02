#ifndef MAP_H
#define MAP_H
#include "Common_libs.hxx"
#include "Common_functions.hxx"
#include "Tilemap.hxx"
#include "Tile.h"
#include "window.h"

class Tile;

class Map
{
public:

	Map(string path);
	Map(int width, int height, string name);

	virtual ~Map();

	int LEVEL_WIDTH;

	int LEVEL_HEIGHT;

	int TOTAL_TILES;

	bool loadMap();

	Tile **getTiles();

	bool touchesWall( SDL_Rect box);

	void renderMap(SDL_Rect &camera);

	void addTilemap(int tilemapID);

	string getPath();

	void createMap();

	map<int, Tilemap *> &getMap();

protected:

private:
	string _name;

	string _mapPath;

	map<int, Tilemap *> _tmaps;

	Tile** _tileSet;

};
#endif // MAP_H
