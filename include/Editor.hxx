#ifndef EDITOR_H
#define EDITOR_H
#include "../include/Common_libs.hxx"
#include "../include/Map.h"
#include "../include/Input.hxx"

class Editor
{
    public:
        Editor();
        virtual ~Editor();

        void put_tile( Tile *tiles[], int tileType, SDL_Rect& camera );
        void save_tiles( Tile *tiles[] );
        void setMap(Map *gameMap);
        void init(Input &input, SDL_Event &e);

    protected:
    private:

        Map *_currentMap;
};

#endif // EDITOR_H
