#ifndef MAP_H
#define MAP_H
#include "../include/Common_libs.hxx"
#include "../include/Tilemap.hxx"
#include "../include/Tile.h"

class Tile;

class Map
{
    public:

        Map(string path);

        virtual ~Map();

        int LEVEL_WIDTH;

        int LEVEL_HEIGHT;

        int TOTAL_TILES;

        Tilemap *getTilemap();

        bool setTiles();

        Tile **getTileSet();

        bool touchesWall( SDL_Rect box);

        void renderMap(SDL_Rect &camera);

    protected:

    private:
        string _name;

        string _mapPath;

        Tilemap *_tilemaps;

        Tile** _tileSet;

};
#endif // MAP_H
