#ifndef TILE_H
#define TILE_H

#include "Common_libs.hxx"
#include "LTexture.h"
#include "window.h"
#include "Layer.h"
#include "Tilemap.hxx"

class Tile
{
	public:
		//Initializes position and type
		Tile( int x, int y, bool collision);
		~Tile();

		//Shows the tile
		void render(SDL_Rect& camera , SDL_Rect *gTileClips);

		void setLayer(LTexture *gTexture, int layer, int type, int id);
		//Get the tile type
		int getType(int layer);

		//Get the collision box
		SDL_Rect getBox();

		bool hasCollision();

		void setCollision(bool coliss = true);

		void free();

		int getTileMapID(int layer);

	private:
		//The attributes of the tile
		SDL_Rect mBox;

		map<int, Layer *> _layers;
		map<int, Tilemap *> _tmaps;

		//The tile type

		bool _hasCollision;

};

#endif // TILE_H
