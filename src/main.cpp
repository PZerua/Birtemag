#include "../include/window.h"
#include "../include/timer.h"
#include "../include/Input.hxx"
#include "../include/Tile.h"
#include "../include/Common_libs.hxx"
#include "../include/Map.h"
#include "../include/tilemaps.hxx"
#include "../include/Player.h"

SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

bool setTiles( Tile* tiles[], Map gameMap )
{
    //Success flag
    bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "bitmaps/test.map" );

    //If the map couldn't be loaded
    if( map == NULL )
    {
        printf( "Unable to load map file!\n" );
        tilesLoaded = false;
    }
    else
    {
        //Initialize the tiles
        for( int i = 0; i < gameMap.TOTAL_TILES; ++i )
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
            if( ( tileType >= 0 ) && ( tileType < Tile_prueba::TOTAL_TILE_SPRITES ) )
            {
                tiles[ i ] = new Tile( x, y, tileType );
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
            if( x >= gameMap.LEVEL_WIDTH )
            {
                //Move back
                x = 0;

                //Move to the next row
                y += TILE_SIZE;
            }
        }
        //Clip the sprite sheet
        if( tilesLoaded )
        {

            gTileClips[ Tile_prueba::TILE_RED ].x = 0;
            gTileClips[ Tile_prueba::TILE_RED ].y = 0;
            gTileClips[ Tile_prueba::TILE_RED ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_RED ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_GREEN ].x = 0;
            gTileClips[ Tile_prueba::TILE_GREEN ].y = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_GREEN ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_GREEN ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_BLUE ].x = 0;
            gTileClips[ Tile_prueba::TILE_BLUE ].y = TILE_SIZE*2;
            gTileClips[ Tile_prueba::TILE_BLUE ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_BLUE ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_TOPLEFT ].x = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_TOPLEFT ].y = 0;
            gTileClips[ Tile_prueba::TILE_TOPLEFT ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_TOPLEFT ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_LEFT ].x = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_LEFT ].y = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_LEFT ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_LEFT ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_BOTTOMLEFT ].x = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_BOTTOMLEFT ].y = TILE_SIZE*2;
            gTileClips[ Tile_prueba::TILE_BOTTOMLEFT ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_BOTTOMLEFT ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_TOP ].x = TILE_SIZE*2;
            gTileClips[ Tile_prueba::TILE_TOP ].y = 0;
            gTileClips[ Tile_prueba::TILE_TOP ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_TOP ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_CENTER ].x = TILE_SIZE*2;
            gTileClips[ Tile_prueba::TILE_CENTER ].y = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_CENTER ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_CENTER ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_BOTTOM ].x = TILE_SIZE*2;
            gTileClips[ Tile_prueba::TILE_BOTTOM ].y = TILE_SIZE*2;
            gTileClips[ Tile_prueba::TILE_BOTTOM ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_BOTTOM ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_TOPRIGHT ].x = TILE_SIZE*3;
            gTileClips[ Tile_prueba::TILE_TOPRIGHT ].y = 0;
            gTileClips[ Tile_prueba::TILE_TOPRIGHT ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_TOPRIGHT ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_RIGHT ].x = TILE_SIZE*3;
            gTileClips[ Tile_prueba::TILE_RIGHT ].y = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_RIGHT ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_RIGHT ].h = TILE_SIZE;

            gTileClips[ Tile_prueba::TILE_BOTTOMRIGHT ].x = TILE_SIZE*3;
            gTileClips[ Tile_prueba::TILE_BOTTOMRIGHT ].y = TILE_SIZE*2;
            gTileClips[ Tile_prueba::TILE_BOTTOMRIGHT ].w = TILE_SIZE;
            gTileClips[ Tile_prueba::TILE_BOTTOMRIGHT ].h = TILE_SIZE;
        }
    }

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

int main(int argc, char** argv){
    //Start our window
    try {
        Window::Init("Game");
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
        Window::Quit();
        return -1;
    }

    LTexture gTileTexture;
    Player player;
    Map *gameMap = new Map(16*64, 12*64);

    if ( !player.gPlayerTexture.loadFromFile("sprites/player.png"))
    {
        cout<<"Failed to load sprite texture!\n"<<endl;
    }

	//Load tile texture
	if( !gTileTexture.loadFromFile( "tilesets/tile1.png" ) )
	{
		cout<<"Failed to load tile set texture!\n"<<endl;
	}

	Tile* tileSet[ gameMap->TOTAL_TILES ];

	//Load tile map
	if( !setTiles( tileSet, *gameMap) )
	{
		cout<<"Failed to load tile set!\n"<<endl;
	}

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	for(int i = 0; i < gameMap->TOTAL_TILES; ++i)
    {
        tileSet[ i ]->setTexture(&gTileTexture);
    }

    //Our event structure
	SDL_Event e;
	//Our input instance
	Input input;
	//For tracking if we want to quit
	while (!input._quit && e.type != SDL_QUIT){
		//Event Polling
		SDL_PollEvent(&e);
        //input.checkControls(&e);
        player.handleEvent(e);

        //LOGIC
        player.move( tileSet, gameMap);
        player.setCamera( camera, gameMap );

        //RENDERING
        SDL_SetRenderDrawColor( Window::mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF );
        Window::Clear();

        for( int i = 0; i < gameMap->TOTAL_TILES; ++i )
        {
            tileSet[ i ]->render( camera, gTileClips );
        }

        player.render(camera);

        Window::Present();
    }

    Window::Quit();

    return 0;
}
