#ifndef TILE_H
#define TILE_H

#include "../include/Common_functions.hxx"
#include "../include/Common_libs.hxx"
#include "../include/LTexture.h"
#include "../include/window.h"

class Tile
{
	public:
		//Initializes position and type
		Tile( int x, int y, int tileType, bool collision, int id );
		~Tile();

		//Shows the tile
		void render(SDL_Rect& camera , SDL_Rect *gTileClips);

		void setTexture(LTexture *gTexture, int layer);

		//Get the tile type
		int getType();

		//Get the collision box
		SDL_Rect getBox();

		bool hasCollision();

		void setCollision(bool coliss = true);

		void free();

		void setType(int type, int id);

		int getTileMapID();



	private:
		//The attributes of the tile
		SDL_Rect mBox;

		LTexture *gTileTexture;

		map<int, LTexture *> _layers;

		//The tile type
		int _mType;

		int _tilemapID;

		bool _hasCollision;

};

#endif // TILE_H
