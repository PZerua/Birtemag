#ifndef WORLD_H
#define WORLD_H

#include "Common_libs.hxx"
#include "Map.h"
#include "window.h"
#include "Player.h"

class World
{
    public:
        World(Window &gWindow);
        virtual ~World();

        void addMap(string mapPath);
        Map *getCurrentMap();
        vector <Map *> getMaps();
        Player *getPlayer();
        void handlePlayer(SDL_Rect &camera);
        void render(Window &gWindow, SDL_Rect &camera);

    protected:
    private:
        vector <Map *> _worldMaps;
        Map *_currentMap;
        Player *_player;

};

#endif // WORLD_H
