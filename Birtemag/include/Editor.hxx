#ifndef EDITOR_H
#define EDITOR_H
#include "Common_libs.hxx"
#include "Map.h"
#include "Input.hxx"
#include "window.h"
#include "LTexture.h"
#include "Button.h"
#include "Collision_tile.h"
#include "Selector.h"

class Button;

class Editor
{
public:
	Editor(SDL_Rect &camera);
	virtual ~Editor();

	void putTile(Input &input, SDL_Event &e);
	void saveTiles();
	void setMap(vector<Map *> &worldMaps, Map *gameMap);
	void init( Window &gWindow, Input &input, SDL_Event &e);
	void setCamera(Input &input);
	void addTilemap( string tilePath, int id);
	void handleTilemap(Input &input, SDL_Event &e);
	void handleButtons(Input &input, SDL_Event &e);
	void addButton(string name, int behaviour);
	void showCollision();
	void changeCollision();
	void putCollision();
	void setButtonPos();
	void newMap();
	void renderMainSelector(Input &input, SDL_Event &e);
	void nextTilemap();
	void previousTilemap();
	void loadTilemaps();

protected:
private:

	Selector _mainSelector;
	Map *_currentMap;
	SDL_Rect _camera;
	int _camVel;
	int _tileType;
	int _actualID;
	int _cameraOffset;
	int _buttonsOffset;
	vector<Tilemap *> _tilemaps;
	vector<Button *> _buttons;
	vector<Map *> _worldMaps;
	LTexture _selector;
	LTexture _actualTile;
	int _actualX;
	int _actualY;
	int _previousIndex;
	unsigned _tilemapIndex;
	LTexture _tilemapBackground;
	LTexture _editorBackground;
	bool _showCollision;
	bool _changing;
	bool _changeCollision;
	bool _collisionState;
	bool _tileSelected;
	bool _editMap;
	bool _wasSelected;
	Collision_tile _collision;


};

#endif // EDITOR_H
