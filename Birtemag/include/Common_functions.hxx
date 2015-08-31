#ifndef COMMON_FUNC
#define COMMON_FUNC
#include "../include/Common_libs.hxx"
#include "../include/Map.h"
#include "../include/Tile.h"

class Tile;

bool checkCollision( SDL_Rect a, SDL_Rect b );

enum Screen
{
    mainScreen,
    editScreen,
    totalScreens
};

enum ButtonState
{
    normal,
    hover,
    click
};

enum Behaviour
{
    collision,
    newMap,
	nextTilemap,
	previousTilemap
};

#endif // COMMON_FUNC
