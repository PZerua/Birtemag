#ifndef WORLD_H
#define WORLD_H

#include "Common_libs.hxx"
#include "Map.h"
#include "window.h"
#include "Player.h"

class World
{
	public:
		World();
		virtual ~World();

		void addMap(string mapPath);
		Map *getCurrentMap();
		vector <Map *> &getMaps();
		Player *getPlayer();
		void handlePlayer();
		void render();
		SDL_Rect &getCamera();
		void loadMaps();

	protected:
	private:
		vector <Map *> _worldMaps;
		Map *_currentMap;
		Player *_player;
		SDL_Rect camera;

};

#endif // WORLD_H
