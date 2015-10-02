#ifndef COMMON_FUNC
#define COMMON_FUNC
#include "Common_libs.h"
#include "Map.h"
#include "Tile.h"

class Tile;

bool checkCollision( SDL_Rect a, SDL_Rect b );

enum ButtonState
{
    normal,
    hover,
    click
};

enum Behaviour
{
	tile,
    collision,
	attribute,
    newMap,
	nextTilemap,
	previousTilemap,
	nextLayer,
	previousLayer
};

enum Layers
{
	ground,
	mask,
	cover,
	fringe,
	roof,
	size
};

#endif // COMMON_FUNC
