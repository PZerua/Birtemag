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

        void put_tile(Window &gWindow);
        void save_tiles();
        void setMap(Map *gameMap);
        void init(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);
        void setCamera(Input &input);
        void addTile(Window gWindows[Screen::totalScreens], string tilePath);

    protected:
    private:

        Map *_currentMap;
        SDL_Rect _camera;
        int _camVel;
        vector<Tilemap *> _tilemapsM;
        vector<Tilemap *> _tilemapsE;

};

#endif // EDITOR_H
