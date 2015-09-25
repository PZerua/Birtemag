#ifndef LAYER_H
#define LAYER_H

#include "Common_libs.hxx"
#include "Common_functions.hxx"
#include "LTexture.h"

class Layer
{
public:
	Layer(int id, int type);
	~Layer();
	int getTilemapId();
	int getType();
	void setTexture(LTexture &texture);
	void render(int x, int y, SDL_Rect *gTileClips);
	void setType(int type, int id);

private:
	LTexture _gTileTexture;
	int _tilemapId;
	int _mType;
};

#endif