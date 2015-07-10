#ifndef MAP_H
#define MAP_H
#include "../include/Common_libs.hxx"
#include "../include/Tilemap.hxx"

class Map
{
    public:

        Map(int Width, int Height);

        virtual ~Map();

        int LEVEL_WIDTH;

        int LEVEL_HEIGHT;

        int TOTAL_TILES;

        Tilemap *getTilemap();

    protected:

    private:
        string _name;

        Tilemap *_tilemaps;

};
#endif // MAP_H
