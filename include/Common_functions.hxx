#ifndef COMMON_FUNC
#define COMMON_FUNC
#include "../include/Common_libs.hxx"
#include "../include/Map.h"
#include "../include/tilemaps.hxx"
#include "../include/Tile.h"

class Tile;

bool checkCollision( SDL_Rect a, SDL_Rect b );
bool touchesWall( SDL_Rect box, Tile* tiles[], Map *gameMap);

#endif // COMMON_FUNC
