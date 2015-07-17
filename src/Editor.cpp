#include "Editor.hxx"

Editor::Editor(SDL_Rect &camera)
{
    _camera = camera;
    _camVel = 6;
}

Editor::~Editor()
{
    //dtor
}

void Editor::put_tile( Tile *tiles[], int tileType)
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
        SDL_Rect box = tiles[ t ]->getBox();

        //If the mouse is inside the tile
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            //Get rid of old tile
            delete tiles[ t ];

            //Replace it with new one
            tiles[ t ] = new Tile( box.x, box.y, tileType );
        }
    }
}

void Editor::save_tiles( Tile *tiles[] )
{
    //Open the map
    std::ofstream map( _currentMap->getPath() );

    //Go through the tiles
    for( int t = 0; t < _currentMap->TOTAL_TILES; t++ )
    {
        if ( (t % _currentMap->LEVEL_WIDTH) == 0)
            map << "\n";
        //Write tile type to file
        map << tiles[ t ]->getType() << " ";
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

void Editor::init(Input &input, SDL_Event &e)
{
    while(!input._f3 && e.type != SDL_QUIT)
    {
        if (input._mouseClick)
            if (e.button.button == SDL_BUTTON_LEFT)
                cout<<"Works"<<endl;

        SDL_PollEvent(&e);
        input.checkControls(&e);

        setCamera(input);

        Window::Clear();

        _currentMap->renderMap(_camera);

        Window::Present();
    }
}

