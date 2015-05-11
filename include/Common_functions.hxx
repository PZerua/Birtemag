#ifndef COMMON_FUNC
#define COMMON_FUNC
#include "Common_libs.hxx"
#include "Map.h"
#include "tilemaps.hxx"
#include "Tile.h"

class Tile;

bool checkCollision( SDL_Rect a, SDL_Rect b );
bool touchesWall( SDL_Rect box, Tile* tiles[], Map *gameMap);

#endif // COMMON_FUNC
