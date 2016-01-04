#pragma once

#include "SDL.h"
#include <string>
#include <map>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <vector>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "cmath"

#define TILE_SIZE 64
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

using namespace std;

#define MAX(a, b) ((a)>(b) ? (a) : (b))

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

enum LayerPos
{
	Lower,
	Upper,
	All
};

enum GUI_STYLE
{
	Default,
	Border1,
	Border1_Light1,
	Light1
};

