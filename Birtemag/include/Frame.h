#pragma once
#include "Common_libs.h"
#include "LTexture.h"
#include "Window.h"

class Frame
{
public:
	Frame(const string &stylePath, const SDL_Rect &dim, const int &borderSize, const int &mode);
	~Frame();
	void render();
	int getMode();

private:
	int _mode;
	int _borderSize;
	SDL_Rect _dimensions;
	LTexture _patch;
	
};
