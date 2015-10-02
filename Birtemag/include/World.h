#ifndef WORLD_H
#define WORLD_H

#include "Common_libs.h"
#include "Map.h"
#include "window.h"
#include "Player.h"

class World
{
	public:
		World();

		virtual ~World();

		void addMap(string mapPath);

		void loadTilemaps();

		Map *getCurrentMap();

		vector <Map *> &getMaps();

		Player *getPlayer();

		void handlePlayer();

		void render();

		SDL_Rect &getCamera();

		void loadMaps();

		map<int, Tilemap *> &getTilemaps();

	protected:
	private:
		vector <Map *> _worldMaps;
		map<int, Tilemap *> _tmaps;
		Map *_currentMap;
		Player *_player;
		SDL_Rect camera;

};

#endif // WORLD_H
