#ifndef SELECTOR_H
#define SELECTOR_H
#include "Common_libs.hxx"
#include "LTexture.h"

class Selector
{
public:
	Selector();
	~Selector();
	void render(int x, int y);
	void setTile(LTexture &texture);
	void setClip(SDL_Rect &clip);
private:
	LTexture _selector;
	LTexture _tile;
	SDL_Rect _clip;
};

#endif