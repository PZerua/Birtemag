#ifndef MAP_H
#define MAP_H
#include "../include/Common_libs.hxx"
#include "../include/Tilemap.hxx"
#include "../include/Tile.h"
#include "../include/window.h"

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

        Tilemap *getTilemap();

        bool setTiles();

        Tile **getTiles();

        bool touchesWall( SDL_Rect box);

        void renderMap(SDL_Rect &camera);

        void addTilemap(string tilePath);

        string getPath();

        void createMap();

    protected:

    private:
        string _name;

        string _mapPath;

        vector<Tilemap *> _tilemaps;

        Tile** _tileSet;

};
#endif // MAP_H
