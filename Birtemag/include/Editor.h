#ifndef EDITOR_H
#define EDITOR_H
#include "Common_libs.h"
#include "Common_functions.h"
#include "Map.h"
#include "Input.h"
#include "Window.h"
#include "LTexture.h"
#include "Button.h"
#include "Collision_tile.h"
#include "Selector.h"

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
	void handleButtons(Input &input, Window &gWindow);
	void addButton(string name, int behaviour, int x, int y);
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
	void printLayer();
	void changeLayerText();

private:

	Selector _mainSelector;
	Map *_currentMap;
	SDL_Rect _camera;
	int _camVel;
	int _tileType;
	int _actualTmID;
	int _cameraOffset;
	int _buttonsOffset;
	int _currentLayer;
	map<int, Tilemap *> _tilemaps;
	vector<Button *> _buttons;
	vector<Map *> _worldMaps;
	LTexture _selector;
	LTexture _actualTile;
	LTexture _tileOptions;
	LTexture _layerText;
	int _actualX;
	int _actualY;
	int _previousIndex;
	unsigned _tilemapIndex;
	LTexture _tilemapBackground;
	LTexture _editorBackground;
	bool _changing;
	bool _changeCollision;
	bool _collisionState;
	bool _tileSelected;
	bool _editMap;
	bool _wasSelected;
	Collision_tile _collision;
	int _selectedMode;
	int _previousMode;

	enum Mode{
		tile,
		collision,
		attribute
	};


};

#endif // EDITOR_H
