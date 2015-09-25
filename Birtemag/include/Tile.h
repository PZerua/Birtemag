#ifndef TILE_H
#define TILE_H

#include "Common_libs.hxx"
#include "Layer.h"
#include "Tilemap.hxx"

class Layer;

class Tile
{
	public:
		//Initializes position and type
		Tile( int x, int y, bool collision, LTexture *hideLayer);
		~Tile();

		//Shows the tile
		void render(SDL_Rect& camera , map<int, Tilemap *> &tmaps, int currentLayer);

		void setLayer(LTexture *gTexture, int layer, int type, int id);
		//Get the tile type
		int getType(int layer);

		//Get the collision box
		SDL_Rect getBox();

		bool hasCollision();

		void setCollision(bool coliss = true);

		void free();

		int getTileMapID(int layer);

		void setLayerType(int layer, int type, int id);

		void eraseLayer(int layer);

	private:
		//The attributes of the tile
		SDL_Rect mBox;

		map<int, Layer *> _layers;

		LTexture *_hideLayer;

		//The tile type

		bool _hasCollision;

};

#endif // TILE_H
