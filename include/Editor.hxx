#ifndef EDITOR_H
#define EDITOR_H
#include "../include/Common_libs.hxx"
#include "../include/Map.h"
#include "../include/Input.hxx"
#include "../include/window.h"
#include "../include/LTexture.h"
#include "../include/Button.h"
#include "../include/InfoPanel.h"


class Button;

class Editor
{
    public:
        Editor( SDL_Rect &camera , Window gWindow[Screen::totalScreens]);
        virtual ~Editor();

        void putTile(Window &gWindow, Input &input, SDL_Event &e);
        void saveTiles();
        void setMap(vector<Map *> &worldMaps, Map *gameMap);
        void init(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);
        void setCamera(Input &input);
        void addTilemap(Window gWindows[Screen::totalScreens], string tilePath);
        void handleTilemap(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);
        void handleButtons(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e);
        void addButton(Window &gWindow, string name, int behaviour);
        void showCollision(Window &gWindow);
        void changeCollision();
        void putCollision(Window &gWindow);
        void setButtonPos();
        void newMap(Window &gWindow);

    protected:
    private:

        Map *_currentMap;
        SDL_Rect _camera;
        int _camVel;
        int _tileType;
        vector<Tilemap *> _tilemapsE;
        vector<Button *> _buttons;
        vector<Map *> _worldMaps;
        LTexture _collision;
        LTexture _selector;
        LTexture _mainSelector;
        InfoPanel _infoPanel;
        bool _showCollision;
        bool _changing;
        bool _changeCollision;
        bool _collisionState;


};

#endif // EDITOR_H
