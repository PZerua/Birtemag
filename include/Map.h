#ifndef MAP_H
#define MAP_H
#include "../include/Common_libs.hxx"

class Map
{
    public:
        Map(int Width, int Height);
        virtual ~Map();
        int LEVEL_WIDTH;
        int LEVEL_HEIGHT;
        int TOTAL_TILES;
    protected:
    private:
        string _name;

};
#endif // MAP_H
