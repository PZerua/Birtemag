#include "Editor.hxx"

Editor::Editor(SDL_Rect &camera)
{

	loadTilemaps();
	_tilemapIndex = 1;
	_previousIndex = _tilemapIndex;
	_wasSelected = false;
	_camera = camera;
	_camVel = 8;
	_tileType = 0;
	_actualID = _tilemapIndex;
	_cameraOffset = 300;
	_buttonsOffset = 10;
	_actualX = 20;
	_actualY = 56;

	_actualTile.loadFromFile("utils/Selector.png");
	_selector.loadFromFile("utils/whiteSelector.png");
	_tilemapBackground.loadFromFile("utils/Tilemap_background.png");
	_editorBackground.loadFromFile("utils/Editor_background.png");

	addButton("Colisión", Behaviour::collision);
	addButton("Nuevo Mapa", Behaviour::newMap);
	addButton(">", Behaviour::nextTilemap);
	addButton("<", Behaviour::previousTilemap);
	_selector.setAlpha(100);
	_changing = false;
	_changeCollision = false;
	_showCollision = false;
	_tileSelected = false;
	_editMap = false;

	setButtonPos();

	_buttons[2]->setPos(153, 460);
	_buttons[3]->setPos(15, 460);

	// TODO: Read all tile paths from file or something

}

Editor::~Editor()
{
	for(vector<Button *>::iterator it = _buttons.begin(); it < _buttons.end(); ++it)
	{
		delete(*it);
		it = _buttons.erase(it);
	}
	for(vector<Tilemap *>::iterator it = _tilemaps.begin(); it < _tilemaps.end(); ++it)
	{
		delete(*it);
		it = _tilemaps.erase(it);
	}
}

void Editor::setButtonPos()
{
	int xMult = 40;
	int yMult = 568;

	for (unsigned int i = 0; i < _buttons.size(); i++)
	{
		if (xMult == SCREEN_WIDTH)
		{
			xMult = 0;
			yMult += TILE_SIZE * 2;
		}

		_buttons[i]->setPos(xMult, yMult);

		xMult += TILE_SIZE * 2 + _buttonsOffset;
	}
}

void Editor::putTile(Input &input, SDL_Event &e)
{
	if (_editMap)
	{
		//Mouse offsets
		int x = 0, y = 0;

		//Get mouse offsets
		SDL_GetMouseState(&x, &y);

		if ((((x < 0) || (x > _tilemapBackground.getWidth()) || (y < 36) || (y > 36 + _tilemapBackground.getHeight()))) && (y < 528))
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
					if (input._mouseClick)
						if (e.button.button == SDL_BUTTON_LEFT)
						{
							if (_currentMap->getTiles()[t]->getTileMapID() != _actualID)
							{
								for (unsigned i = 0; i < _currentMap->getTilemaps().size(); i++)
								{
									if (_currentMap->getTilemaps()[i]->getID() == _actualID)
									{
										exist = true;
									}
								}
								if (exist)
								{
									_currentMap->getTiles()[t]->setTexture(_currentMap->getTilemaps()[_actualID]->getTexture());
								}
								else
								{
									_currentMap->addTilemap(_actualID);
									_currentMap->getTiles()[t]->setTexture(_currentMap->getTilemaps()[_actualID]->getTexture());
								}
							}
							_currentMap->getTiles()[t]->setType(_tileType, _actualID);
						}
				}
			}
		}
	}
}

void Editor::renderMainSelector(Input &input, SDL_Event &e)
{
	if(_editMap)
	{
		//Mouse offsets
		int x = 0, y = 0;

		//Get mouse offsets
		SDL_GetMouseState(&x, &y);

		if ((((x < 0) || (x > _tilemapBackground.getWidth()) || (y < 36) || (y > 36 + _tilemapBackground.getHeight()))) && (y < 528))
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
}

void Editor::saveTiles()
{
	//Open the map
	std::ofstream map( _currentMap->getPath() );

	map << _currentMap->getTilemaps().size() << "\n";

	for (unsigned i = 0; i < _currentMap->getTilemaps().size(); i++)
	{
		map << _currentMap->getTilemaps()[i]->getID() << "\n";
	}

	map << _currentMap->LEVEL_WIDTH / TILE_SIZE << " " << _currentMap->LEVEL_HEIGHT / TILE_SIZE << "\n";

	//Go through the tiles
	for( int t = 0; t < _currentMap->TOTAL_TILES; t++ )
	{
		if ( (t % (_currentMap->LEVEL_WIDTH / TILE_SIZE)) == 0 && t != 0)
		{
			map << "\n";
		}

		map << _currentMap->getTiles()[t]->getTileMapID();
		map << ":";

		if (_currentMap->getTiles()[ t ]->getType() < 10)
		{
			//Write tile type to file
			map << 0 << _currentMap->getTiles()[ t ]->getType() << ":" << _currentMap->getTiles()[ t ]->hasCollision() << " ";
		}
		else map << _currentMap->getTiles()[ t ]->getType() << ":" << _currentMap->getTiles()[ t ]->hasCollision() << " ";
	}

	//Close the file
	map.close();
}

void Editor::setMap(vector <Map *> &worldMaps, Map *gameMap)
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

void Editor::addTilemap(string tilePath, int id)
{
	Tilemap *tileE;
	tileE = new Tilemap();
	tileE->initTilemap(tilePath, id);
	_tilemaps.push_back(tileE);
}

void Editor::addButton(string name, int behaviour)
{
	Button *button;
	button = new Button(behaviour, name);
	_buttons.push_back(button);

}

void Editor::handleTilemap(Input &input, SDL_Event &e)
{

	//Mouse offsets
	int x = 0, y = 0;

	SDL_Rect temp;

	//Get mouse offsets
	SDL_GetMouseState( &x, &y );

	int posX = 20;
	int posY = 56;
	
	_tilemaps[_tilemapIndex]->getTexture()->render(posX, posY);

	if (_tileSelected)
		_actualTile.render(_actualX, _actualY);

	for(int i = 0; i < _tilemaps[_tilemapIndex]->getTotalTiles(); i++)
	{
		temp.x = _tilemaps[_tilemapIndex]->getClips()[i].x + posX;
		temp.y = _tilemaps[_tilemapIndex]->getClips()[i].y + posY;
		temp.w = TILE_SIZE;
		temp.h = TILE_SIZE;

		if( ( x > temp.x ) && ( x < temp.x + temp.w ) && ( y > temp.y ) && ( y < temp.y + temp.h ) )
		{
			_selector.render(temp.x, temp.y);
			if (input._mouseClick)
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					_previousIndex = _tilemapIndex;
					_tileSelected = true;
					_wasSelected = true;
					_editMap = true;
					_actualX = temp.x;
					_actualY = temp.y;
					_mainSelector.setTile(*_tilemaps[_tilemapIndex]->getTexture());
					_mainSelector.setClip(_tilemaps[_tilemapIndex]->getClips()[i]);
					_tileType = i;
					_actualID = _tilemapIndex;
				}
		}
	}
}

void Editor::handleButtons(Input &input, SDL_Event &e)
{
	//Mouse offsets
	int x = 0, y = 0;

	//Get mouse offsets
	SDL_GetMouseState( &x, &y );

	for(vector<Button *>::iterator it = _buttons.begin(); it != _buttons.end(); ++it)
	{
		(*it)->render();

		if( ( x > (*it)->getBox().x ) && ( x < (*it)->getBox().x + (*it)->getBox().w ) && ( y > (*it)->getBox().y ) && ( y < (*it)->getBox().y + (*it)->getBox().h ) )
		{
			(*it)->setState(ButtonState::hover);
			if (input._mouseClick && e.button.button == SDL_BUTTON_LEFT && !_changing)
			{
				_changing = true;
				(*it)->setState(ButtonState::normal);
				(*it)->activate(*this);
			}
			else (*it)->setState(ButtonState::hover);
		}
		else (*it)->setState(ButtonState::normal);
	}
	if (!input._mouseClick)
		_changing = false;
}

void Editor::showCollision()
{
	if (_showCollision)
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

void Editor::changeCollision()
{
	if (_showCollision == true)
	{
		_showCollision = false;
		_mainSelector.showTile();
		cout << "[EDITOR] Collision disabled" << endl;
	}
	else
	{
		_showCollision = true;
		_mainSelector.showTile(false);
		cout << "[EDITOR] Collision enabled" << endl;
	}
}

void Editor::putCollision()
{

	//Mouse offsets
	int x = 0, y = 0;

	//Get mouse offsets
	SDL_GetMouseState( &x, &y );

	if ((((x < 0) || (x > _tilemapBackground.getWidth()) || (y < 36) || (y > 36 + _tilemapBackground.getHeight()))) && (y < 528))
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
	if (_tilemapIndex + 1 < _tilemaps.size())
	{
		_tilemapIndex++;
		if (_tilemapIndex == _previousIndex && _wasSelected == true)
			_tileSelected = true;
		else _tileSelected = false;
	}
}

void Editor::previousTilemap()
{
	if (_tilemapIndex > 0)
	{
		_tilemapIndex--;
		if (_tilemapIndex == _previousIndex && _wasSelected == true)
			_tileSelected = true;
		else _tileSelected = false;
	}
}

void Editor::loadTilemaps()
{
	ifstream tilemaps("tilesets/tilesets.txt");

	string name;

	int id = 0;

	while (tilemaps >> name)
	{
		addTilemap("tilesets/" + name, id);
		id++;
	}

}

void Editor::init(Window &gWindow, Input &input, SDL_Event &e)
{
	_mainSelector.setTile(*_tilemaps[_tilemapIndex]->getTexture());

	while(!input._f3 && !input._quit && e.type != SDL_QUIT && !gWindow.isClosed())
	{
		if (input._mouseClick && e.button.button == SDL_BUTTON_LEFT)
		{
			if (_showCollision)
			{
				putCollision();
			}
			else
			{
				putTile(input, e);
			}
			saveTiles();
		}
		else if (!input._mouseClick)
			_changeCollision = false;

		while (SDL_PollEvent(&e) != 0)
		{
			input.checkControls(&e);

			gWindow.handleEvent(e);
		}

		setCamera(input);

		gWindow.Clear();

		_currentMap->renderMap(_camera);
		showCollision();
		renderMainSelector(input, e);
		_tilemapBackground.render(0, 36);
		_editorBackground.render(0, 528);
		handleTilemap(input, e);
		handleButtons(input, e);

		gWindow.Present();
	}
}

