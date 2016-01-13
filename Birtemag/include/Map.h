#ifndef MAP_H
#define MAP_H
#include "Common_libs.h"
#include "Tilemap.h"
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

	void renderMap(SDL_Rect &camera, int currentLayer, int layersToDraw, bool showBorder = false);

	void addTilemap(int tilemapID);

	string getPath();

	void createMap();

	map<int, Tilemap *> &getTilemaps();

	void setTilemaps(map<int, Tilemap *> &tmaps);

	bool checkCollision(SDL_Rect a, SDL_Rect b);

	bool hasTilemap(const int &tilemapID);

protected:

private:
	string _name;

	string _mapPath;

	LTexture _hideLayer;

	LTexture _border;

	SDL_Point center;

	map<int, Tilemap *> _tmaps;

	Tile** _tileSet;

};
#endif // MAP_H
