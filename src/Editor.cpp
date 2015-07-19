#include "Editor.hxx"

Editor::Editor(SDL_Rect &camera, Window &gWindow)
{
    _camera = camera;
    _camVel = 8;
    Selector.loadFromFile(gWindow, "utils/Selector.png");
    _tileType = 0;

    // TODO: Read all tile paths from file or something

}

Editor::~Editor()
{
    //dtor
}

void Editor::putTile(Window &gWindow)
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
                //Get rid of old tile
                delete _currentMap->getTileSet()[ t ];

                //Replace it with new one
                _currentMap->getTileSet()[ t ] = new Tile( box.x, box.y, _tileType );
                _currentMap->getTileSet()[ t ]->setTexture(_tilemapsM[0]->getTexture());
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
            map << 0 << _currentMap->getTileSet()[ t ]->getType() << " ";
        }
        else map << _currentMap->getTileSet()[ t ]->getType() << " ";

    }

    //Close the file
    map.close();
}

void Editor::setMap(Map *gameMap)
{
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

void Editor::addTile(Window gWindows[Screen::totalScreens], string tilePath)
{
    Tilemap *tileM;
    tileM = new Tilemap();
    tileM->initTilemap(gWindows[Screen::mainScreen], tilePath);
    _tilemapsM.push_back(tileM);


    Tilemap *tileE;
    tileE = new Tilemap();
    tileE->initTilemap(gWindows[Screen::editScreen], tilePath);
    _tilemapsE.push_back(tileE);
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
                Selector.render(gWindows[Screen::editScreen], temp.x, temp.y);
                if (input._mouseClick)
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        _tileType = i;
                    }
            }
        }
    }

}

void Editor::init(Window gWindows[Screen::totalScreens], Input &input, SDL_Event &e)
{
    while(!input._f3 && !input._quit && e.type != SDL_QUIT && !gWindows[Screen::editScreen].isClosed() && !gWindows[Screen::mainScreen].isClosed())
    {
        if (input._mouseClick)
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                putTile(gWindows[Screen::mainScreen]);
                saveTiles();
            }

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

        for( int i = 0; i < Screen::totalScreens; ++i )
        {
            gWindows[ i ].Present();
        }
    }
}

