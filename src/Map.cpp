#include "../include/Map.h"

Map::Map(int Width, int Height)
{
    LEVEL_WIDTH = Width;
    LEVEL_HEIGHT = Height;
    TOTAL_TILES = (LEVEL_WIDTH/TILE_SIZE) * (LEVEL_HEIGHT/TILE_SIZE);
    _tilemaps = new Tilemap;
}

Map::~Map()
{
    //dtor
}

Tilemap *Map::getTilemap()
{
    return _tilemaps;
}
