#pragma once
#include "Common_libs.h"
#include "Map.h"
#include "Input.h"
#include "Window.h"
#include "LTexture.h"
#include "Collision_tile.h"
#include "Selector.h"
#include "GUI.h"

class Button;

class Editor
{
public:
	Editor(SDL_Rect &camera, map<int, Tilemap*> &tmaps);
	virtual ~Editor();

	void putTile(Input &input, Window &gWindow);
	void quitTile(Input &input, Window &gWindow);
	void saveTiles();
	void setMaps(vector<Map *> &worldMaps, Map *gameMap);
	void init( Window &gWindow, Input &input, SDL_Event &e);
	void setCamera(Input &input);
	void handleTilemap(Input &input, Window &gWindow);
	void showCollision();
	void collisionMode();
	void tileMode();
	void attributeMode();
	void putCollision(Window &gWindow);
	void newMap();
	void renderMainSelector(Input &input, Window &gWindow);
	void nextTilemap();
	void previousTilemap();
	void loadUtils();
	void nextLayer();
	void previousLayer();
	void printText();
	void changeLayerText();
	bool isInside(const SDL_Point &point, const SDL_Rect &plane);
	void manageStates(const int &behaviour);

private:

	Selector _mainSelector;
	Map *_currentMap;
	SDL_Rect _camera;
	SDL_Rect _worldRect;
	int _camVel;
	int _tileType;
	int _actualTmID;
	int _cameraOffset;
	int _buttonsOffset;
	int _currentLayer;
	int _actualX;
	int _actualY;
	int _previousIndex;
	int _selectedMode;
	int _previousMode;
	int _tilemapOffset;
	unsigned _tilemapIndex;
	map<int, Tilemap *> _tilemaps;
	vector<Map *> _worldMaps;
	LTexture _selector;
	LTexture _actualTile;
	LTexture _tileOptions;
	LTexture _layerText[2];
	LTexture _mode;
	bool _changing;
	bool _changeCollision;
	bool _collisionState;
	bool _tileSelected;
	bool _editMap;
	bool _wasSelected;
	Collision_tile _collision;
	GUI _gui;

};
