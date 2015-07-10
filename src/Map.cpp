#include "../include/Map.h"

Map::Map(string path, int Width, int Height)
{
    LEVEL_WIDTH = Width;

    LEVEL_HEIGHT = Height;

    TOTAL_TILES = (LEVEL_WIDTH/TILE_SIZE) * (LEVEL_HEIGHT/TILE_SIZE);

    _tileSet = new Tile*[TOTAL_TILES];

    _tilemaps = new Tilemap;

    _mapPath = path;
}

Map::~Map()
{
    //dtor
}

Tilemap *Map::getTilemap()
{
    return _tilemaps;
}

bool Map::setTiles()
{
    //Success flag
    bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    ifstream map( _mapPath );

    //If the map couldn't be loaded
    if( map == NULL )
    {
        printf( "Unable to load map file!\n" );
        tilesLoaded = false;
    }
    else
    {
        //Initialize the tiles
        for( int i = 0; i < TOTAL_TILES; ++i )
        {
            //Determines what kind of tile will be made
            int tileType = -1;
            //Read tile from map file
            map >> tileType;

            //If the was a problem in reading the map
            if( map.fail() )
            {
                //Stop loading map
                printf( "Error loading map: Unexpected end of file!\n" );
                tilesLoaded = false;
                break;
            }

            //If the number is a valid tile number
            if( ( tileType >= 0 ) && ( tileType < getTilemap()[0].getTotalTiles() ) )
            {
                _tileSet[ i ] = new Tile( x, y, tileType );
            }
            //If we don't recognize the tile type
            else
            {
                //Stop loading map
                printf( "Error loading map: Invalid tile type at %d!\n", i );
                tilesLoaded = false;
                break;
            }
            //Move to next tile spot
            x += TILE_SIZE;

            //If we've gone too far
            if( x >= LEVEL_WIDTH )
            {
                //Move back
                x = 0;

                //Move to the next row
                y += TILE_SIZE;
            }
        }
    }

    // TODO: Add multiple tilemap support

    for(int i = 0; i < TOTAL_TILES; ++i)
    {
        _tileSet[ i ]->setTexture(_tilemaps[0].getTexture());
    }

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

Tile **Map::getTileSet()
{
    return _tileSet;
}

bool Map::touchesWall( SDL_Rect box)
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( _tileSet[ i ]->hasCollision() )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, _tileSet[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

void Map::renderMap(SDL_Rect &camera)
{
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        _tileSet[ i ]->render( camera, _tilemaps[0].getClips() );
    }
}
