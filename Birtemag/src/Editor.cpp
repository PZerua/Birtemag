#include "Editor.h"

Editor::Editor(SDL_Rect &camera, map<int, Tilemap*> &tmaps)
{

	// The world's camera position
	_camera = camera;
	// The tilemaps loaded from game
	_tilemaps = tmaps;
	// Load buttons
	loadUtils();

	// Init layer info texture with desired color
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	_layerText[0].loadFromRenderedText("Layer: ", color, 31);
	_layerText[1].loadFromRenderedText("Ground", color, 31);
	_mode.loadFromRenderedText("MODE:", color, 31);

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
	_cameraOffset = 400;
	// The tilemap separation to the borders
	_tilemapOffset = 20;

	// The distance between buttons
	_buttonsOffset = 10;

	// The position of the current tile selected
	_actualX = 20;
	_actualY = 56;
	// The current layer selected, by default is Ground
	_currentLayer = Layers::ground;
	// The Mode selected in Editor, default is Tile
	_selectedMode = Behaviour::tile;

	// Load some utils
	// TODO load this using file (as with buttons)
	_actualTile.loadFromFile("utils/Selector.png");
	_selector.loadFromFile("utils/whiteSelector.png");

	// Where the world is shown in the editor
	_worldRect.x = 296;
	_worldRect.y = 0;
	_worldRect.w = SCREEN_WIDTH - 296;
	_worldRect.h = SCREEN_HEIGHT - 192;

	// The alpha from the selector used to select a tile in the tilemap
	_selector.setAlpha(100);
	// Variable used to track collision state changes
	_changeCollision = false;
	// Variable used to display the current selected tile inside the selector
	_tileSelected = false;
	// You can only edit a map when a tile is selected
	_editMap = false;

}

Editor::~Editor()
{

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

		if (isInside(point, _worldRect) && _selectedMode == Behaviour::tile)
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

	if (isInside(point, _worldRect) && _selectedMode == Behaviour::tile)
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

	if (isInside(point, _worldRect) && _selectedMode == Behaviour::tile)
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
	else if (point.y < _worldRect.h && _selectedMode != Behaviour::tile)
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


void Editor::handleTilemap(Input &input, Window &gWindow)
{
	if (_selectedMode == Behaviour::tile)
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

		_tilemaps[_tilemapIndex]->getTexture().render(_tilemapOffset, _tilemapOffset);

		if (_tileSelected)
			_actualTile.render(_actualX, _actualY);

		for (int i = 0; i < _tilemaps[_tilemapIndex]->getTotalTiles(); i++)
		{
			temp.x = _tilemaps[_tilemapIndex]->getClips()[i].x + _tilemapOffset;
			temp.y = _tilemaps[_tilemapIndex]->getClips()[i].y + _tilemapOffset;
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



void Editor::manageStates(const int &behaviour)
{
	if (behaviour == Behaviour::tile)
	{
		tileMode();
	}
	else if (behaviour == Behaviour::collision)
	{
		collisionMode();
	}
	else if (behaviour == Behaviour::attribute)
	{
		attributeMode();
	}
	else if (behaviour == Behaviour::newMap)
	{
		newMap();
	}
	else if (behaviour == Behaviour::nextTilemap)
	{
		nextTilemap();
	}
	else if (behaviour == Behaviour::previousTilemap)
	{
		previousTilemap();
	}
	else if (behaviour == Behaviour::nextLayer)
	{
		nextLayer();
	}
	else if (behaviour == Behaviour::previousLayer)
	{
		previousLayer();
	}
}

void Editor::showCollision()
{
	if (_selectedMode == Behaviour::collision)
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

	if (point.y < _worldRect.h && _selectedMode == Behaviour::collision)
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
	/*
	//Main loop flag
	bool quit = false;

	SDL_Rect dim;
	dim.x = 200;
	dim.y = 200;
	dim.w = 200;
	dim.h = 200;

	//Event handler
	SDL_Event e;

	//Set text color as black
	SDL_Color textColor = { 0, 0xFF, 0xFF, 0xFF };

	//The current input text.
	string inputText = "Some Text";
	LTexture gInputTextTexture;
	LTexture gPromptTextTexture;
	gPromptTextTexture.loadFromRenderedText("Enter Text:", textColor, 31);
	gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor, 31);

	Frame newMapFrame("utils/frame_def.png", dim, 3);

	//Enable text input
	SDL_StartTextInput();

	//While application is running
	while (!quit)
	{
		//The rerender text flag
		bool renderText = false;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//Special key input
			else if (e.type == SDL_KEYDOWN)
			{
				//Handle backspace
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{
					//lop off character
					inputText.pop_back();
					renderText = true;
				}
				//Handle copy
				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(inputText.c_str());
				}
				//Handle paste
				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					inputText += SDL_GetClipboardText();
					renderText = true;
				}
			}
			//Special text input event
			else if (e.type == SDL_TEXTINPUT)
			{
				//Not copy or pasting
				if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{
					//Append character
					inputText += e.text.text;
					renderText = true;
				}
			}
		}

		//Rerender text if needed
		if (renderText)
		{
			//Text is not empty
			if (inputText != "")
			{
				//Render new text
				gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor, 12);
			}
			//Text is empty
			else
			{
				//Render space texture
				gInputTextTexture.loadFromRenderedText(" ", textColor, 12);
			}
		}

		//Clear screen
		SDL_RenderClear(Window::mRenderer);

		newMapFrame.render();

		//Render text textures
		gPromptTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, 0);
		gInputTextTexture.render((SCREEN_WIDTH - gInputTextTexture.getWidth()) / 2, gPromptTextTexture.getHeight());

		//Update screen
		SDL_RenderPresent(Window::mRenderer);
	}

	//Disable text input
	SDL_StopTextInput();
	*/
	/*
	Map *newMap;
	newMap = new Map(width, height, "test2");
	_worldMaps.push_back(newMap);
	newMap->setTilemaps(_tilemaps);
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
		_layerText[1].loadFromRenderedText("Ground", color, 31);
	}
	else if (_currentLayer == Layers::mask)
	{
		_layerText[1].loadFromRenderedText("Mask", color, 31);
	}
	else if (_currentLayer == Layers::cover)
	{
		_layerText[1].loadFromRenderedText("Cover", color, 31);
	}
	else if (_currentLayer == Layers::fringe)
	{
		_layerText[1].loadFromRenderedText("Fringe", color, 31);
	}
	else if (_currentLayer == Layers::roof)
	{
		_layerText[1].loadFromRenderedText("Roof", color, 31);
	}
}

void Editor::loadUtils()
{
	ifstream utils("utils/utils.txt");

	string type;
	string temp;
	string name;
	SDL_Rect dim;
	dim.h = 32;
	dim.w = 128;
	int style = -1;
	int x = -1;
	int y = -1;
	int w = -1;
	int h = -1;
	int behaviour = -1;
	int mode = -1;

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

			utils >> dim.x >> dim.y >> behaviour;
			_gui.addButton(name, dim, GUI_STYLE::Default, behaviour, mode);
		}
		else if (type == "Frame")
		{
			utils >> style >> dim.x >> dim.y >> dim.w >> dim.h >> mode;
			_gui.addFrame(dim, style, mode);
		}
	}
}

void Editor::printText()
{
	_layerText[0].render(325, 581);
	_layerText[1].render(400, 581);
	_mode.render(412, 651);
}

void Editor::init(Window &gWindow, Input &input, SDL_Event &e)
{
	cout << "[INFO] Use w, a, s ,d to move camera" << endl;
	cout << "[INFO] Left click to select and put tiles/collisions" << endl;
	cout << "[INFO] Right click to quit tiles in the actual layer" << endl;

	while(!input._f3 && !input._quit && e.type != SDL_QUIT && !gWindow.isClosed())
	{		
		if (input._mouseLClick)
		{
			if (_selectedMode == Behaviour::collision)
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

		int manageState = _gui.handleButtons(input, gWindow, _selectedMode);
		manageStates(manageState);

		setCamera(input);

		// Render

		gWindow.Clear();

		_currentMap->renderMap(_camera, _currentLayer, LayerPos::All, true);
		showCollision();
		renderMainSelector(input, gWindow);
		_gui.renderFrames(_selectedMode);
		if (_selectedMode == Behaviour::tile)
		{
			printText();
		}

		handleTilemap(input, gWindow);
		_gui.renderButtons();

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
