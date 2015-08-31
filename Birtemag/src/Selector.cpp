#include "Selector.h"

Selector::Selector()
{
	_selector.loadFromFile("utils/Selector.png");
	_clip.x = 0;
	_clip.y = 0;
	_clip.w = TILE_SIZE;
	_clip.h = TILE_SIZE;
	_showTile = true;
}

Selector::~Selector()
{

}

void Selector::render(int x, int y)
{
	if(_showTile)
		_tile.render(x, y, &_clip);
	_selector.render(x, y);

}

void Selector::setTile(LTexture &texture)
{
	_tile = texture;
}

void Selector::setClip(SDL_Rect &clip)
{
	_clip = clip;
}

void Selector::showTile(bool state)
{
	_showTile = state;
}