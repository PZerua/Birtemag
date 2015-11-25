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
	bool isInside(const SDL_Point &point, const SDL_Rect &plane);

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
	unsigned _tilemapIndex;
	map<int, Tilemap *> _tilemaps;
	vector<Button *> _buttons;
	vector<Map *> _worldMaps;
	LTexture _selector;
	LTexture _actualTile;
	LTexture _tileOptions;
	LTexture _layerText;
	LTexture _tilemapBackground;
	LTexture _editorBackground;
	bool _changing;
	bool _changeCollision;
	bool _collisionState;
	bool _tileSelected;
	bool _editMap;
	bool _wasSelected;
	Collision_tile _collision;

	enum Mode{
		tile,
		collision,
		attribute
	};

};

#endif // EDITOR_H
