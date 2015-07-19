#ifndef EDITOR_H
#define EDITOR_H
#include "../include/Common_libs.hxx"
#include "../include/Map.h"
#include "../include/Input.hxx"
#include "../include/window.h"
#include "../include/LTexture.h"

class Editor
{
    public:
        Editor( SDL_Rect &camera , Window &gWindow);
        virtual ~Editor();

        void putTile(Window &gWindow);
        void saveTiles();
        void setMap(Map *gameMap);
        void init(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);
        void setCamera(Input &input);
        void addTile(Window gWindows[Screen::totalScreens], string tilePath);
        void handleTilemap(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);

    protected:
    private:

        Map *_currentMap;
        SDL_Rect _camera;
        int _camVel;
        vector<Tilemap *> _tilemapsM;
        vector<Tilemap *> _tilemapsE;
        LTexture Selector;
        int _tileType;

};

#endif // EDITOR_H
