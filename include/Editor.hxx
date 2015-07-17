#ifndef EDITOR_H
#define EDITOR_H
#include "../include/Common_libs.hxx"
#include "../include/Map.h"
#include "../include/Input.hxx"
#include "../include/window.h"

class Editor
{
    public:
        Editor( SDL_Rect &camera );
        virtual ~Editor();

        void put_tile( Tile *tiles[], int tileType);
        void save_tiles( Tile *tiles[] );
        void setMap(Map *gameMap);
        void init(Input &input, SDL_Event &e);
        void setCamera(Input &input);

    protected:
    private:

        Map *_currentMap;
        SDL_Rect _camera;
        int _camVel;
};

#endif // EDITOR_H
