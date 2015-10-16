#include "Editor.h"

Editor::Editor(SDL_Rect &camera, map<int, Tilemap*> &tmaps)
{

	_tilemaps = tmaps;
	loadUtils();

	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	_tilemapIndex = 2;
	_previousIndex = _tilemapIndex;
	_wasSelected = false;
	_camera = camera;
	_camVel = 8;
	_tileType = 0;
	_actualTmID = _tilemapIndex;
	_cameraOffset = 300;
	_buttonsOffset = 10;
	_actualX = 20;
	_actualY = 56;
	_currentLayer = Layers::ground;
	_selectedMode = Mode::tile;
	_layerText.loadFromRenderedText("Ground", color, 20);

	_actualTile.loadFromFile("utils/Selector.png");
	_selector.loadFromFile("utils/whiteSelector.png");
	_tilemapBackground.loadFromFile("utils/Tilemap_background.png");
	_editorBackground.loadFromFile("utils/Editor_background.png");
	_tileOptions.loadFromFile("utils/tileOptions.png");

	_selector.setAlpha(100);
	_changing = false;
	_changeCollision = false;
	_tileSelected = false;
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
		int x = 0, y = 0;

		//Get mouse offsets
		SDL_GetMouseState(&x, &y);

		if (gWindow.isFullscreen())
		{
			SDL_DisplayMode desktop;
			SDL_GetDesktopDisplayMode(0, &desktop);

			x = (int)round(x * SCREEN_WIDTH / desktop.w);
			y = (int)round(y * SCREEN_HEIGHT / desktop.h);
		}

		if ((((x < 0) || (x > _tilemapBackground.getWidth()) || (y < 36) || (y > 36 + _tilemapBackground.getHeight()))) && (y < 528) && _selectedMode == Mode::tile)
		{
			//Adjust to _camera
			x += _camera.x;
			y += _camera.y;
			bool exist = false;

			//Go through tiles
			for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
			{
				//Get tile's collision box
				SDL_Rect box = _currentMap->getTiles()[t]->getBox();

				//If the mouse is inside the tile
				if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
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
	int x = 0, y = 0;

	//Get mouse offsets
	SDL_GetMouseState(&x, &y);

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		x = (int)round(x * SCREEN_WIDTH / desktop.w);
		y = (int)round(y * SCREEN_HEIGHT / desktop.h);
	}

	if ((((x < 0) || (x > _tilemapBackground.getWidth()) || (y < 36) || (y > 36 + _tilemapBackground.getHeight()))) && (y < 528) && _selectedMode == Mode::tile)
	{
		//Adjust to _camera
		x += _camera.x;
		y += _camera.y;
		bool exist = false;

		//Go through tiles
		for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
		{
			//Get tile's collision box
			SDL_Rect box = _currentMap->getTiles()[t]->getBox();

			//If the mouse is inside the tile
			if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
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
	int x = 0, y = 0;

	//Get mouse offsets
	SDL_GetMouseState(&x, &y);

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		x = (int)round(x * SCREEN_WIDTH / desktop.w);
		y = (int)round(y * SCREEN_HEIGHT / desktop.h);
	}

	if ((((x < 0) || (x > _tilemapBackground.getWidth()) || (y < 36) || (y > 36 + _tilemapBackground.getHeight()))) && (y < 528) && _selectedMode == Mode::tile)
	{
		//Go through tiles
		for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
		{
			//Get tile's collision box
			SDL_Rect box = _currentMap->getTiles()[t]->getBox();

			//If the mouse is inside the tile
			if ((x > box.x - _camera.x) && (x < box.x + box.w - _camera.x) && (y > box.y - _camera.y) && (y < box.y + box.h - _camera.y))
			{
				_mainSelector.render(box.x - _camera.x, box.y - _camera.y);
			}
		}
	}
	else if (y < 528 && _selectedMode != Mode::tile)
	{
		//Go through tiles
		for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
		{
			//Get tile's collision box
			SDL_Rect box = _currentMap->getTiles()[t]->getBox();

			//If the mouse is inside the tile
			if ((x > box.x - _camera.x) && (x < box.x + box.w - _camera.x) && (y > box.y - _camera.y) && (y < box.y + box.h - _camera.y))
			{
				_mainSelector.render(box.x - _camera.x, box.y - _camera.y);
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
		int x = 0, y = 0;

		SDL_Rect temp;

		//Get mouse offsets
		SDL_GetMouseState(&x, &y);

		if (gWindow.isFullscreen())
		{
			SDL_DisplayMode desktop;
			SDL_GetDesktopDisplayMode(0, &desktop);

			x = (int)round(x * SCREEN_WIDTH / desktop.w);
			y = (int)round(y * SCREEN_HEIGHT / desktop.h);
		}

		int posX = 20;
		int posY = 56;

		_tilemaps[_tilemapIndex]->getTexture().render(posX, posY);

		if (_tileSelected)
			_actualTile.render(_actualX, _actualY);

		for (int i = 0; i < _tilemaps[_tilemapIndex]->getTotalTiles(); i++)
		{
			temp.x = _tilemaps[_tilemapIndex]->getClips()[i].x + posX;
			temp.y = _tilemaps[_tilemapIndex]->getClips()[i].y + posY;
			temp.w = TILE_SIZE;
			temp.h = TILE_SIZE;

			if ((x > temp.x) && (x < temp.x + temp.w) && (y > temp.y) && (y < temp.y + temp.h))
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
	int x = 0, y = 0;

	//Get mouse offsets
	SDL_GetMouseState( &x, &y );

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		x = (int)round(x * SCREEN_WIDTH / desktop.w);
		y = (int)round(y * SCREEN_HEIGHT / desktop.h);
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

		if( ( x > _buttons[i]->getBox().x ) && ( x < _buttons[i]->getBox().x + _buttons[i]->getBox().w ) && 
			( y > _buttons[i]->getBox().y ) && ( y < _buttons[i]->getBox().y + _buttons[i]->getBox().h ) )
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
	int x = 0, y = 0;

	//Get mouse offsets
	SDL_GetMouseState( &x, &y );

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		x = (int)round(x * SCREEN_WIDTH / desktop.w);
		y = (int)round(y * SCREEN_HEIGHT / desktop.h);
	}

	if (y < 528 && _selectedMode == Mode::collision)
	{
		//Adjust to _camera
		x += _camera.x;
		y += _camera.y;

		//Go through tiles
		for (int t = 0; t < _currentMap->TOTAL_TILES; t++)
		{
			//Get tile's collision box
			SDL_Rect box = _currentMap->getTiles()[t]->getBox();

			//If the mouse is inside the tile
			if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
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

		_currentMap->renderMap(_camera, _currentLayer, true);
		showCollision();
		renderMainSelector(input, gWindow);
		_editorBackground.render(0, 528);
		if (_selectedMode == Mode::tile)
		{
			_tilemapBackground.render(0, 36);
			_tileOptions.render(156, 560);
			printLayer();
		}

		handleTilemap(input, gWindow);
		handleButtons(input, gWindow);

		gWindow.Present();
	}
}