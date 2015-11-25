#include "Editor.h"

Editor::Editor(SDL_Rect &camera, map<int, Tilemap*> &tmaps)
{

	// The world's camera position
	_camera = camera;
	// The tilemaps loaded from game
	_tilemaps = tmaps;
	// Load button
	loadUtils();

	// Init layer info texture with desired color
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	_layerText.loadFromRenderedText("Ground", color, 20);

	// The default selected tilemap, it's used to show the tilemap texture in the editor
	_tilemapIndex = 2;

	// When you select a tile from a tilemap, this value changes to the index of this tile's tilemap
	// This is used to show (or not) the selector in the tile you clicked on when you change to another tilemap
	_previousIndex = _tilemapIndex;

	// This is the tilemap ID from the tile currently selected (it's not necessarily the same as _tilemapIndex)
	_actualTmID = _tilemapIndex;

	// Used to track if a tile has been selected
	_wasSelected = false;
	
	// The camera's velocity
	_camVel = 8;
	// The type of the new tile to be added
	_tileType = 0;
	
	// How far the camera can go out of the map
	_cameraOffset = 300;

	// The distance between buttons
	_buttonsOffset = 10;

	// The position of the current tile selected
	_actualX = 20;
	_actualY = 56;
	// The current layer selected, by default is Ground
	_currentLayer = Layers::ground;
	// The Mode selected in Editor, default is Tile
	_selectedMode = Mode::tile;

	// Load some utils
	// TODO load this using file (as with buttons)
	_actualTile.loadFromFile("utils/Selector.png");
	_selector.loadFromFile("utils/whiteSelector.png");
	_tilemapBackground.loadFromFile("utils/Tilemap_background.png");
	_editorBackground.loadFromFile("utils/Editor_background.png");
	_tileOptions.loadFromFile("utils/tileOptions.png");

	// Where the world is shown in the editor
	_worldRect.x = _tilemapBackground.getWidth();
	_worldRect.y = 0;
	_worldRect.w = SCREEN_WIDTH - _tilemapBackground.getWidth();
	_worldRect.h = SCREEN_HEIGHT - _editorBackground.getHeight();

	// The alpha from the selector used to select a tile in the tilemap
	_selector.setAlpha(100);
	// Variable used to track button state changes
	_changing = false;
	// Variable used to track collision state changes
	_changeCollision = false;
	// Variable used to display the current selected tile inside the selector
	_tileSelected = false;
	// You can only edit a map when a tile is selected
	_editMap = false;

}

Editor::~Editor()
{
	for (unsigned i = 0; i < _buttons.size(); i++)
	{
		delete _buttons[i];
	}
}

void Editor::putTile(Input &input, Window &gWindow)
{
	if (_editMap)
	{
		//Mouse offsets
		SDL_Point point;

		//Get mouse offsets
		SDL_GetMouseState(&point.x, &point.y);

		if (gWindow.isFullscreen())
		{
			SDL_DisplayMode desktop;
			SDL_GetDesktopDisplayMode(0, &desktop);

			point.x = (int)round(point.x * SCREEN_WIDTH / desktop.w);
			point.y = (int)round(point.y * SCREEN_HEIGHT / desktop.h);
		}

		if (isInside(point, _worldRect) && _selectedMode == Mode::tile)
		{
			//Adjust to _camera
			point.x += _camera.x;
			point.y += _camera.y;
			bool exist = false;

			//Go through tiles
			for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
			{
				//Get tile's collision box
				SDL_Rect box = _currentMap->getTiles()[t]->getBox();

				//If the mouse is inside the tile
				if (isInside(point, box))
				{
					//Replace it with new one
					if (_currentMap->getTiles()[t]->getTileMapID(_currentLayer) != _actualTmID || _currentMap->getTiles()[t]->getTileMapID(_currentLayer) == 0)
					{
						if (!_currentMap->getTilemaps().count(_actualTmID))
						{
							_currentMap->addTilemap(_actualTmID);
							_currentMap->getTiles()[t]->setLayer(_currentMap->getTilemaps()[_actualTmID]->getTexture(), _currentLayer, _tileType, _actualTmID);
						}
						else 
						{
							_currentMap->getTiles()[t]->setLayer(_currentMap->getTilemaps()[_actualTmID]->getTexture(), _currentLayer, _tileType, _actualTmID);
						}
					}
					else
					{
						_currentMap->getTiles()[t]->setLayerType(_currentLayer, _tileType, _actualTmID);
					}
					saveTiles();
				}
			}
		}
	}
}

void Editor::quitTile(Input &input, Window &gWindow)
{
	//Mouse offsets
	SDL_Point point;

	//Get mouse offsets
	SDL_GetMouseState(&point.x, &point.y);

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		point.x = (int)round(point.x * SCREEN_WIDTH / desktop.w);
		point.y = (int)round(point.y * SCREEN_HEIGHT / desktop.h);
	}

	if (isInside(point, _worldRect) && _selectedMode == Mode::tile)
	{
		//Adjust to _camera
		point.x += _camera.x;
		point.y += _camera.y;
		bool exist = false;

		//Go through tiles
		for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
		{
			//Get tile's collision box
			SDL_Rect box = _currentMap->getTiles()[t]->getBox();

			//If the mouse is inside the tile
			if (isInside(point, box))
			{
				_currentMap->getTiles()[t]->eraseLayer(_currentLayer);
				saveTiles();
			}
		}
	}
}

void Editor::renderMainSelector(Input &input, Window &gWindow)
{
	//Mouse offsets
	SDL_Point point;

	//Get mouse offsets
	SDL_GetMouseState(&point.x, &point.y);

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		point.x = (int)round(point.x * SCREEN_WIDTH / desktop.w);
		point.y = (int)round(point.y * SCREEN_HEIGHT / desktop.h);
	}

	if (isInside(point, _worldRect) && _selectedMode == Mode::tile)
	{
		//Go through tiles
		for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
		{
			//Get tile's collision box
			SDL_Rect box = _currentMap->getTiles()[t]->getBox();
			box.x = box.x - _camera.x;
			box.y = box.y - _camera.y;

			//If the mouse is inside the tile
			if (isInside(point, box))
			{
				_mainSelector.render(box.x, box.y);
			}
		}
	}
	else if (point.y < _worldRect.h && _selectedMode != Mode::tile)
	{
		//Go through tiles
		for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
		{
			//Get tile's collision box
			SDL_Rect box = _currentMap->getTiles()[t]->getBox();
			box.x = box.x - _camera.x;
			box.y = box.y - _camera.y;

			//If the mouse is inside the tile
			if (isInside(point, box))
			{
				_mainSelector.render(box.x, box.y);
			}
		}
	}
}

void Editor::saveTiles()
{

	//TODO: Save map after click button

	//Open the map
	std::ofstream Map( _currentMap->getPath() );

	Map << _currentMap->getTilemaps().size() << "\n";

	for (map<int, Tilemap *>::iterator it = _currentMap->getTilemaps().begin(); it != _currentMap->getTilemaps().end(); ++it)
	{
		Map << it->first << "\n";
	}

	Map << _currentMap->LEVEL_WIDTH / TILE_SIZE << " " << _currentMap->LEVEL_HEIGHT / TILE_SIZE << "\n";

	//Go through the tiles
	for( int t = 0; t < _currentMap->TOTAL_TILES; t++ )
	{
		if ( (t % (_currentMap->LEVEL_WIDTH / TILE_SIZE)) == 0 && t != 0)
		{
			Map << "\n";
		}

		for (int i = 0; i < Layers::size; i++)
		{
			Map << _currentMap->getTiles()[t]->getTileMapID(i);
			Map << ":";

			if (_currentMap->getTiles()[t]->getType(i) < 10)
			{
				//Write tile type to file
				Map << 0 << _currentMap->getTiles()[t]->getType(i) << ":";
			}
			else Map << _currentMap->getTiles()[t]->getType(i) << ":";
		}
		Map << _currentMap->getTiles()[t]->hasCollision() << " ";
	}

	//Close the file
	Map.close();
}

void Editor::setMaps(vector <Map *> &worldMaps, Map *gameMap)
{
	_worldMaps = worldMaps;
	_currentMap = gameMap;
}

void Editor::setCamera(Input &input)
{

	if (input._right)   _camera.x += _camVel;
	if (input._left)    _camera.x -= _camVel;
	if (input._up)      _camera.y -= _camVel;
	if (input._down)    _camera.y += _camVel;

	if( _camera.x < -_cameraOffset )
	{
		_camera.x = -_cameraOffset;
	}
	if( _camera.y < -_cameraOffset )
	{
		_camera.y = -_cameraOffset;
	}
	if( _camera.x > _currentMap->LEVEL_WIDTH - _camera.w + _cameraOffset )
	{
		_camera.x = _currentMap->LEVEL_WIDTH - _camera.w + _cameraOffset;
	}
	if( _camera.y > _currentMap->LEVEL_HEIGHT - _camera.h + _cameraOffset)
	{
		_camera.y = _currentMap->LEVEL_HEIGHT - _camera.h + _cameraOffset;
	}
}

void Editor::addButton(string name, int behaviour, int x, int y)
{
	Button *button;
	button = new Button(behaviour, name, x, y);
	_buttons.push_back(button);
}

void Editor::handleTilemap(Input &input, Window &gWindow)
{
	if (_selectedMode == Mode::tile)
	{
		//Mouse offsets
		SDL_Point point;
		SDL_Rect temp;

		//Get mouse offsets
		SDL_GetMouseState(&point.x, &point.y);

		if (gWindow.isFullscreen())
		{
			SDL_DisplayMode desktop;
			SDL_GetDesktopDisplayMode(0, &desktop);

			point.x = (int)round(point.x * SCREEN_WIDTH / desktop.w);
			point.y = (int)round(point.y * SCREEN_HEIGHT / desktop.h);
		}

		int posX = 20;
		int posY = 20;

		_tilemaps[_tilemapIndex]->getTexture().render(posX, posY);

		if (_tileSelected)
			_actualTile.render(_actualX, _actualY);

		for (int i = 0; i < _tilemaps[_tilemapIndex]->getTotalTiles(); i++)
		{
			temp.x = _tilemaps[_tilemapIndex]->getClips()[i].x + posX;
			temp.y = _tilemaps[_tilemapIndex]->getClips()[i].y + posY;
			temp.w = TILE_SIZE;
			temp.h = TILE_SIZE;

			if (isInside(point, temp))
			{
				_selector.render(temp.x, temp.y);
				if (input._mouseLClick)
				{
					_previousIndex = _tilemapIndex;
					_tileSelected = true;
					_wasSelected = true;
					_editMap = true;
					_actualX = temp.x;
					_actualY = temp.y;
					_mainSelector.setTile(_tilemaps[_tilemapIndex]->getTexture());
					_mainSelector.setClip(_tilemaps[_tilemapIndex]->getClips()[i]);
					_tileType = i;
					_actualTmID = _tilemapIndex;
				}
			}
		}
	}
}

void Editor::handleButtons(Input &input, Window &gWindow)
{
	//Mouse offsets
	SDL_Point point;

	//Get mouse offsets
	SDL_GetMouseState( &point.x, &point.y );

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		point.x = (int)round(point.x * SCREEN_WIDTH / desktop.w);
		point.y = (int)round(point.y * SCREEN_HEIGHT / desktop.h);
	}

	if (_selectedMode == Mode::tile)
	{
		_buttons[Mode::tile]->setFixedState(ButtonState::hover);
		_buttons[Mode::collision]->removeFixedState();
		_buttons[Mode::attribute]->removeFixedState();
	}
	else if (_selectedMode == Mode::collision)
	{
		_buttons[Mode::tile]->removeFixedState();
		_buttons[Mode::collision]->setFixedState(ButtonState::hover);
		_buttons[Mode::attribute]->removeFixedState();
	}
	else if (_selectedMode == Mode::attribute)
	{
		_buttons[Mode::tile]->removeFixedState();
		_buttons[Mode::collision]->removeFixedState();
		_buttons[Mode::attribute]->setFixedState(ButtonState::hover);
	}
		
	for(unsigned i = 0; i < _buttons.size(); i++)
	{

		if (_selectedMode != Mode::tile)
		{
			if (i == Behaviour::nextTilemap || i == Behaviour::previousTilemap || i == Behaviour::nextLayer || i == Behaviour::previousLayer)
				_buttons[i]->disable();
		}
		else _buttons[i]->enable();

		_buttons[i]->render();

		if(isInside(point, _buttons[i]->getBox()))
		{
			if(!_changing) 
				_buttons[i]->setState(ButtonState::hover);
			if (input._mouseLClick && !_changing)
			{
				if (i == Mode::tile)
					_selectedMode = Mode::tile;
				else if (i == Mode::collision)
					_selectedMode = Mode::collision;
				else if (i == Mode::attribute)
					_selectedMode = Mode::attribute;

				_buttons[i]->setState(ButtonState::click);
				_changing = true;
				_buttons[i]->activate(*this);
			}
		} 
		else _buttons[i]->setState(ButtonState::normal);
	}
	if (!input._mouseLClick && _changing)
	{
		_changing = false;
	}
		
}

void Editor::showCollision()
{
	if (_selectedMode == Mode::collision)
	{
		for (int i = 0; i < _currentMap->TOTAL_TILES; i++)
		{
			if(_currentMap->getTiles()[i]->hasCollision())
			{
				_collision.render(_currentMap->getTiles()[i]->getBox().x - _camera.x, _currentMap->getTiles()[i]->getBox().y - _camera.y);
			}
		}
	}
}

void Editor::collisionMode()
{
	_mainSelector.showTile(false);
}

void Editor::tileMode()
{
	_mainSelector.showTile();
}

void Editor::attributeMode()
{
	_mainSelector.showTile(false);
}

void Editor::putCollision(Window &gWindow)
{

	//Mouse offsets
	SDL_Point point;

	//Get mouse offsets
	SDL_GetMouseState( &point.x, &point.y );

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		point.x = (int)round(point.x * SCREEN_WIDTH / desktop.w);
		point.y = (int)round(point.y * SCREEN_HEIGHT / desktop.h);
	}

	if (point.y < _worldRect.h && _selectedMode == Mode::collision)
	{
		//Adjust to _camera
		point.x += _camera.x;
		point.y += _camera.y;

		//Go through tiles
		for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
		{
			//Get tile's collision box
			SDL_Rect box = _currentMap->getTiles()[t]->getBox();

			//If the mouse is inside the tile
			if (isInside(point, box))
			{
				if (!_changeCollision)
				{
					if (_currentMap->getTiles()[t]->hasCollision())
						_collisionState = false;
					else _collisionState = true;

					_changeCollision = true;
				}
				if (_collisionState)
					_currentMap->getTiles()[t]->setCollision(true);
				else
					_currentMap->getTiles()[t]->setCollision(false);
				saveTiles();
			}
		}
	}
}

void Editor::newMap()
{
	/*int width, height;
	cout << "Set width: ";
	cin >> width;
	cout << endl << "Set height: ";
	cin >> height;
	cout << endl;

	Map *newMap;
	newMap = new Map(20, 20, "test");
	newMap->addTilemap("tilesets/empty.png");
	newMap->loadMap();
	_worldMaps.push_back(newMap);
	_currentMap = newMap;*/
}

void Editor::nextTilemap()
{
	if (_tilemapIndex < _tilemaps.size())
	{
		_tilemapIndex++;
		if (!_tilemaps[_tilemapIndex]->isInit())
		{
			_tilemaps[_tilemapIndex]->initTilemap();
		}
		if (_tilemapIndex == _previousIndex && _wasSelected == true)
			_tileSelected = true;
		else _tileSelected = false;
	}
}

void Editor::previousTilemap()
{
	if (_tilemapIndex > 1)
	{
		_tilemapIndex--;
		if (!_tilemaps[_tilemapIndex]->isInit())
		{
			_tilemaps[_tilemapIndex]->initTilemap();
		}
		if (_tilemapIndex == _previousIndex && _wasSelected == true)
			_tileSelected = true;
		else _tileSelected = false;
	}
}

void Editor::nextLayer()
{
	if (_currentLayer + 1 < Layers::size)
	{
		_currentLayer++;
		changeLayerText();
	}
}

void Editor::previousLayer()
{
	if (_currentLayer > 0)
	{
		_currentLayer--;
		changeLayerText();
	}
}

void Editor::changeLayerText()
{
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	if (_currentLayer == Layers::ground)
	{
		_layerText.loadFromRenderedText("Ground", color, 20);
	}
	else if (_currentLayer == Layers::mask)
	{
		_layerText.loadFromRenderedText("Mask", color, 20);
	}
	else if (_currentLayer == Layers::cover)
	{
		_layerText.loadFromRenderedText("Cover", color, 20);
	}
	else if (_currentLayer == Layers::fringe)
	{
		_layerText.loadFromRenderedText("Fringe", color, 20);
	}
	else if (_currentLayer == Layers::roof)
	{
		_layerText.loadFromRenderedText("Roof", color, 20);
	}
}

void Editor::loadUtils()
{
	ifstream utils("utils/utils.txt");

	string type;
	string temp;
	string name;
	int x = -1;
	int y = -1;
	int behaviour = -1;

	while (utils >> type)
	{
		if (type == "Button")
		{
			utils >> name;
			utils >> temp;

			while (temp != "|")
			{
				name += " " + temp;
				utils >> temp;
			}

			utils >> x >> y >> behaviour;
			addButton(name, behaviour, x, y);
		}
	}
}

void Editor::printLayer()
{
	_layerText.render(390, 580);
}

void Editor::init(Window &gWindow, Input &input, SDL_Event &e)
{
	cout << "[INFO] Use w, a, s ,d to move camera" << endl;
	cout << "[INFO] Left click to select and put tiles/collisions" << endl;
	cout << "[INFO] Right click to quit tiles in the actual layer" << endl;

	while(!input._f3 && !input._quit && e.type != SDL_QUIT && !gWindow.isClosed())
	{
		//Mouse offsets
		int x = 0, y = 0;

		//Get mouse offsets
		
		if (input._mouseLClick)
		{
			if (_selectedMode == Mode::collision)
			{
				putCollision(gWindow);
			}
			else
			{
				putTile(input, gWindow);
			}
		}
		else if (!input._mouseLClick)
			_changeCollision = false;

		if (input._mouseRClick)
		{
			quitTile(input, gWindow);
		}

		while (SDL_PollEvent(&e) != 0)
		{
			input.checkControls(&e);

			gWindow.handleEvent(e);
		}

		setCamera(input);

		gWindow.Clear();

		_currentMap->renderMap(_camera, _currentLayer, LayerPos::All, true);
		showCollision();
		renderMainSelector(input, gWindow);
		_editorBackground.render(0, 528);
		if (_selectedMode == Mode::tile)
		{
			_tilemapBackground.render(0, 0);
			_tileOptions.render(156, 560);
			printLayer();
		}

		handleTilemap(input, gWindow);
		handleButtons(input, gWindow);

		gWindow.Present();
	}
}

bool Editor::isInside(const SDL_Point &point, const SDL_Rect &plane)
{
	if ((point.x > plane.x) && (point.x < plane.x + plane.w) &&
		(point.y > plane.y) && (point.y < plane.y + plane.h))
		return true;
	else return false;
}
