#pragma once
#include "Common_libs.hxx"
#include "LTexture.h"

class Collision_tile
{
public:
	Collision_tile();
	~Collision_tile();
	void render(int x, int y);
private:
	LTexture _collision;
	LTexture _collisionText;
	SDL_Rect mBox;
	SDL_Rect textBox;
	SDL_Color color;

};

