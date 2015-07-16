#include "Editor.hxx"

Editor::Editor()
{
    //ctor
}

Editor::~Editor()
{
    //dtor
}

void Editor::put_tile( Tile *tiles[], int tileType, SDL_Rect& camera )
{
    //Mouse offsets
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;

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

void Editor::init(Input &input, SDL_Event &e)
{
    while(!input._f3)
    {
        if (input._mouseClick)
            if (e.button.button == SDL_BUTTON_LEFT)
                cout<<"Works"<<endl;
        SDL_PollEvent(&e);
        input.checkControls(&e);
    }
}
