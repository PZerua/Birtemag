#ifndef TILEMAP_H
#define TILEMAP_H

#include "Common_libs.hxx"
#include "LTexture.h"
#include "window.h"


class Tilemap
{
	public:

		Tilemap();

		~Tilemap();

		bool loadTexture(string imagPath);

		void setClips();

		void initTilemap();

		void setData(string name, int id);

		LTexture &getTexture();

		SDL_Rect *getClips();

		int getTotalTiles();
		
		string getName();

		int getID();

		bool isInit();

	private:

		LTexture _tileTexture;

		int _totalTiles;

		int _ID;

		SDL_Rect *_tileClips;

		string _name;

		string _imgPath;

		bool _isInit;


};

#endif // TILEMAP_H
