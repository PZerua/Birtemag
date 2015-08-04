#include "Editor.hxx"

Editor::Editor(SDL_Rect &camera, Window gWindows[Screen::totalScreens])
{

    gWindows[Screen::mainScreen].setFocus(false);
    _camera = camera;
    _camVel = 8;
    _tileType = 0;
    _selector.loadFromFile(gWindows[Screen::editScreen], "utils/Selector.png");
    _mainSelector.loadFromFile(gWindows[Screen::mainScreen], "utils/Selector.png");
    _infoPanel.loadTexture(gWindows[Screen::editScreen], "utils/infoPanel.png");
    _infoPanel.setText(gWindows[Screen::editScreen], "jur");
    addButton(gWindows[Screen::editScreen], "Colisión", Behaviour::collision);
    addButton(gWindows[Screen::editScreen], "Nuevo Mapa", Behaviour::newMap);
    _collision.loadFromFile(gWindows[Screen::mainScreen], "utils/Collision.png");
    _collision.setAlpha(150);
    _changing = false;
    _changeCollision = false;
    _showCollision = false;

    setButtonPos();

    // TODO: Read all tile paths from file or something

}

Editor::~Editor()
{
    for(vector<Button *>::iterator it = _buttons.begin(); it < _buttons.end(); ++it)
    {
        (*it)->free();
        delete(*it);
        it = _buttons.erase(it);
    }
    for(vector<Tilemap *>::iterator it = _tilemapsE.begin(); it < _tilemapsE.end(); ++it)
    {
        delete(*it);
        it = _tilemapsE.erase(it);
    }

    _collision.free();

}

void Editor::setButtonPos()
{
    int xMult = 0;
    int yMult = 0;

    for (unsigned int i = 0; i < _buttons.size(); i++)
    {
        if (xMult == SCREEN_WIDTH)
        {
            xMult = 0;
            yMult += TILE_SIZE * 2;
        }

        _buttons[i]->setPos(xMult, yMult);

        xMult += TILE_SIZE * 2;
    }
}

void Editor::putTile(Window &gWindow, Input &input, SDL_Event &e)
{
    if (gWindow.hasMouseFocus())
    {
        //Mouse offsets
        int x = 0, y = 0;

        //Get mouse offsets
        SDL_GetMouseState( &x, &y );

        //Adjust to _camera
        x += _camera.x;
        y += _camera.y;

        //Go through tiles
        for( int t = 0; t < _currentMap->TOTAL_TILES; t++ )
        {
            //Get tile's collision box
            SDL_Rect box = _currentMap->getTileSet()[ t ]->getBox();

            //If the mouse is inside the tile
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                _mainSelector.render(gWindow, box.x, box.y);
                //Replace it with new one
                if (input._mouseClick)
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        _currentMap->getTileSet()[ t ]->setType(_tileType);
                    }
            }
        }
    }
}

void Editor::renderMainSelector(Window &gWindow, Input &input, SDL_Event &e)
{
    if (gWindow.hasMouseFocus())
    {
        //Mouse offsets
        int x = 0, y = 0;

        //Get mouse offsets
        SDL_GetMouseState( &x, &y );

        //Adjust to _camera
        x += _camera.x;
        y += _camera.y;

        //Go through tiles
        for( int t = 0; t < _currentMap->TOTAL_TILES; t++ )
        {
            //Get tile's collision box
            SDL_Rect box = _currentMap->getTileSet()[ t ]->getBox();

            //If the mouse is inside the tile
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                _mainSelector.render(gWindow, box.x, box.y);
            }
        }
    }
}

void Editor::saveTiles( )
{

    //Open the map
    std::ofstream map( _currentMap->getPath() );

    map << _currentMap->LEVEL_WIDTH / TILE_SIZE << " " << _currentMap->LEVEL_HEIGHT / TILE_SIZE << "\n";

    //Go through the tiles
    for( int t = 0; t < _currentMap->TOTAL_TILES; t++ )
    {
        if ( (t % (_currentMap->LEVEL_WIDTH / TILE_SIZE)) == 0 && t != 0)
        {
            map << "\n";
        }

        if (_currentMap->getTileSet()[ t ]->getType() < 10)
        {
            //Write tile type to file
            map << 0 << _currentMap->getTileSet()[ t ]->getType() << ":" << _currentMap->getTileSet()[ t ]->hasCollision() << " ";
        }
        else map << _currentMap->getTileSet()[ t ]->getType() << ":" << _currentMap->getTileSet()[ t ]->hasCollision() << " ";

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

    if( _camera.x < 0 )
    {
        _camera.x = 0;
    }
    if( _camera.y < 0 )
    {
        _camera.y = 0;
    }
    if( _camera.x > _currentMap->LEVEL_WIDTH - _camera.w )
    {
        _camera.x = _currentMap->LEVEL_WIDTH - _camera.w;
    }
    if( _camera.y > _currentMap->LEVEL_HEIGHT - _camera.h )
    {
        _camera.y = _currentMap->LEVEL_HEIGHT - _camera.h;
    }
}

void Editor::addTilemap(Window gWindows[Screen::totalScreens], string tilePath)
{
    Tilemap *tileE;
    tileE = new Tilemap();
    tileE->initTilemap(gWindows[Screen::editScreen], tilePath);
    _tilemapsE.push_back(tileE);
}

void Editor::addButton(Window &gWindow, string name, int behaviour)
{
    Button *button;
    button = new Button(gWindow, behaviour, name);
    _buttons.push_back(button);

}

void Editor::handleTilemap(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e)
{

    //Mouse offsets
    int x = 0, y = 0;

    SDL_Rect temp;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    int posX = SCREEN_WIDTH/2 - _tilemapsE[0]->getTexture()->getWidth() / 2;
    int posY = SCREEN_HEIGHT/2 - _tilemapsE[0]->getTexture()->getHeight() / 2;

    _tilemapsE[0]->getTexture()->render(gWindows[Screen::editScreen], posX, posY);


    for(int i = 0; i < _tilemapsE[0]->getTotalTiles(); i++)
    {
        temp.x = _tilemapsE[0]->getClips()[i].x + posX;
        temp.y = _tilemapsE[0]->getClips()[i].y + posY;
        temp.w = TILE_SIZE;
        temp.h = TILE_SIZE;

        if (!gWindows[Screen::mainScreen].hasMouseFocus())
        {
            if( ( x > temp.x ) && ( x < temp.x + temp.w ) && ( y > temp.y ) && ( y < temp.y + temp.h ) )
            {
                _selector.render(gWindows[Screen::editScreen], temp.x, temp.y);
                if (input._mouseClick)
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        _tileType = i;
                    }
            }
        }
    }
}

void Editor::handleButtons(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e)
{
    //Mouse offsets
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    for(vector<Button *>::iterator it = _buttons.begin(); it != _buttons.end(); ++it)
    {
        (*it)->render(gWindows[Screen::editScreen]);

        if (!gWindows[Screen::mainScreen].hasMouseFocus())
        {
            if( ( x > (*it)->getBox().x ) && ( x < (*it)->getBox().x + (*it)->getBox().w ) && ( y > (*it)->getBox().y ) && ( y < (*it)->getBox().y + (*it)->getBox().h ) )
            {
                (*it)->setState(ButtonState::hover);
                if (input._mouseClick && e.button.button == SDL_BUTTON_LEFT && !_changing)
                {
                    _changing = true;
                    (*it)->setState(ButtonState::click);
                    (*it)->activate(*this, gWindows);
                }
                else (*it)->setState(ButtonState::hover);
            }
            else (*it)->setState(ButtonState::normal);
        }
    }
    if (!input._mouseClick)
        _changing = false;
}

void Editor::showCollision(Window &gWindow)
{
    if (_showCollision)
    {
        for (int i = 0; i < _currentMap->TOTAL_TILES; i++)
        {
            if(_currentMap->getTileSet()[i]->hasCollision())
            {
                _collision.render(gWindow, _currentMap->getTileSet()[i]->getBox().x - _camera.x , _currentMap->getTileSet()[i]->getBox().y - _camera.y);
            }
        }
    }
}

void Editor::changeCollision()
{
    if (_showCollision == true)
        _showCollision = false;
    else _showCollision = true;
}

void Editor::putCollision(Window &gWindow)
{
    if (gWindow.hasMouseFocus())
    {
        //Mouse offsets
        int x = 0, y = 0;

        //Get mouse offsets
        SDL_GetMouseState( &x, &y );

        //Adjust to _camera
        x += _camera.x;
        y += _camera.y;

        //Go through tiles
        for( int t = 0; t < _currentMap->TOTAL_TILES; t++ )
        {
            //Get tile's collision box
            SDL_Rect box = _currentMap->getTileSet()[ t ]->getBox();

            //If the mouse is inside the tile
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ))
            {
                if (!_changeCollision)
                {
                    if (_currentMap->getTileSet()[ t ]->hasCollision())
                        _collisionState = false;
                    else _collisionState = true;

                    _changeCollision = true;
                }
                if (_collisionState)
                    _currentMap->getTileSet()[ t ]->setCollision(true);
                else
                    _currentMap->getTileSet()[ t ]->setCollision(false);
            }
        }
    }
}

void Editor::newMap(Window &gWindow)
{
    /*int width, height;
    cout << "Set width: ";
    cin >> width;
    cout << endl << "Set height: ";
    cin >> height;
    cout << endl;*/

    Map *newMap;
    newMap = new Map(20, 20, "test");
    newMap->addTilemap(gWindow, "tilesets/empty.png");
    newMap->setTiles();
    _worldMaps.push_back(newMap);
    _currentMap = newMap;

}

void Editor::init(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e)
{
    while(!input._f3 && !input._quit && e.type != SDL_QUIT && !gWindows[Screen::editScreen].isClosed() && !gWindows[Screen::mainScreen].isClosed())
    {
        if (input._mouseClick && e.button.button == SDL_BUTTON_LEFT)
        {
            if (_showCollision)
                putCollision(gWindows[Screen::mainScreen]);
            else putTile(gWindows[Screen::mainScreen], input, e);
        }
        else if (!input._mouseClick)
            _changeCollision = false;

        SDL_PollEvent(&e);
        input.checkControls(&e);

        for( int i = 0; i < Screen::totalScreens; ++i )
        {
            gWindows[ i ].handleEvent(e);
        }

        setCamera(input);

        for( int i = 0; i < Screen::totalScreens; ++i )
        {
            gWindows[ i ].Clear();
        }

        _currentMap->renderMap(gWindows[Screen::mainScreen], _camera);
        handleTilemap(gWindows, input, e);
        handleButtons(gWindows, input, e);
        renderMainSelector(gWindows[Screen::mainScreen], input, e);
        _infoPanel.render(gWindows[Screen::editScreen]);
        showCollision(gWindows[Screen::mainScreen]);

        for( int i = 0; i < Screen::totalScreens; ++i )
        {
            gWindows[ i ].Present();
        }
    }
}

