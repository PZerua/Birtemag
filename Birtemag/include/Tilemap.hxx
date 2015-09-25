#ifndef TILEMAP_H
#define TILEMAP_H

#include "../include/Common_libs.hxx"
#include "../include/LTexture.h"
#include "../include/window.h"


class Tilemap
{
	public:

		Tilemap();

		~Tilemap();

		bool loadTexture(string imagPath);

		void setClips();

		void initTilemap();

		void setData(string imgPath, int id);

		LTexture &getTexture();

		SDL_Rect *getClips();

		int getTotalTiles();
		
		string getName();

		int getID();

	private:

		LTexture _tileTexture;

		int _totalTiles;

		int _ID;

		SDL_Rect *_tileClips;

		string _name;

		string _imgPath;


};

#endif // TILEMAP_H
