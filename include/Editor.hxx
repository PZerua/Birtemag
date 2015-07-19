#ifndef EDITOR_H
#define EDITOR_H
#include "../include/Common_libs.hxx"
#include "../include/Map.h"
#include "../include/Input.hxx"
#include "../include/window.h"
#include "../include/LTexture.h"
#include "../include/Button.h"

class Button;

class Editor
{
    public:
        Editor( SDL_Rect &camera , Window gWindow[Screen::totalScreens]);
        virtual ~Editor();

        void putTile(Window &gWindow);
        void saveTiles();
        void setMap(Map *gameMap);
        void init(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);
        void setCamera(Input &input);
        void addTile(Window gWindows[Screen::totalScreens], string tilePath);
        void handleTilemap(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);
        void handleButtons(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);
        void addButton(Window &gWindow);
        void showCollision(Window &gWindow);
        void changeCollision();
        void putCollision(Window &gWindow);

    protected:
    private:

        Map *_currentMap;
        SDL_Rect _camera;
        int _camVel;
        vector<Tilemap *> _tilemapsM;
        vector<Tilemap *> _tilemapsE;
        vector<Button *> _buttons;
        LTexture Selector;
        int _tileType;
        LTexture _collision;
        bool _showCollision;
        bool _changing;
        bool _changingCol;


};

#endif // EDITOR_H
