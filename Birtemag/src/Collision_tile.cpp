#include "Collision_tile.h"



Collision_tile::Collision_tile()
{
	color.r = 255;
	color.g = 0;
	color.b = 0;
	_collisionText.loadFromRenderedText("C", color, 26);
	_collision.loadFromFile("utils/Collision.png");
	_collision.setAlpha(150);

	mBox.w = _collision.getWidth();
	mBox.h = _collision.getHeight();
	mTextBox.w = _collisionText.getWidth();
	mTextBox.h = _collisionText.getHeight();
}


Collision_tile::~Collision_tile()
{

}

void Collision_tile::render(int x, int y)
{
	_collision.render(x, y);
	_collisionText.render(x + TILE_SIZE / 2 - mTextBox.w / 2 , y + TILE_SIZE/ 2 - mTextBox.h / 2);
}