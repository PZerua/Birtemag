#include "Collision_tile.h"



Collision_tile::Collision_tile()
{
	color.r = 255;
	color.g = 0;
	color.b = 0;
	_collisionText.loadFromRenderedText("C", color, 26);
	SDL_QueryTexture(_collisionText.getTexture(), NULL, NULL, &textBox.w, &textBox.h);
	SDL_QueryTexture(_collision.getTexture(), NULL, NULL, &mBox.w, &mBox.h);
	_collision.loadFromFile("utils/Collision.png");
	_collision.setAlpha(150);

}


Collision_tile::~Collision_tile()
{
}

void Collision_tile::render(int x, int y)
{
	_collision.render(x, y);
	_collisionText.render(x + TILE_SIZE / 2 - textBox.w / 2 , y + TILE_SIZE/ 2 - textBox.h / 2);
}