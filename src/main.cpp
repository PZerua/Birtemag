#include "../include/window.h"
#include "../include/timer.h"
#include "../include/Input.hxx"
#include "../include/Tile.h"
#include "../include/Common_libs.hxx"
#include "../include/Common_functions.hxx"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Editor.hxx"

int main(int argc, char** argv){

    Window gWindows[ Screen::totalScreens ];

    //Start our window
    gWindows[Screen::mainScreen].init("Birtemag", 300, 300);

    Player player;
    Map *gameMap = new Map("bitmaps/prueba.map");

    if ( !player.gPlayerTexture.loadFromFile(gWindows[Screen::mainScreen], "sprites/player.png"))
    {
        cout<<"Failed to load sprite texture!\n"<<endl;
    }

	//Load tile texture
	gameMap->addTile(gWindows[Screen::mainScreen], "tilesets/tile1.png");

	//Load tile map
	if( !gameMap->setTiles() )
	{
		cout<<"Failed to load tile set!\n"<<endl;
	}

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    //Our event structure
	SDL_Event e;
	//Our input instance
	Input input;
	//For tracking if we want to quit
	while (!input._quit && e.type != SDL_QUIT){
		//Event Polling
		SDL_PollEvent(&e);
        input.checkControls(&e);
        if (input._f2)
        {
            input._f2 = false;
            gWindows[Screen::editScreen].init("Editor", 320 + SCREEN_WIDTH, 300);
            Editor gameEditor(camera, gWindows[Screen::editScreen]);
            gameEditor.addTile(gWindows, "tilesets/tile1.png");
            gameEditor.setMap(gameMap);
            gameEditor.init(gWindows, input, e);
            if (!gWindows[Screen::editScreen].isClosed())
                gWindows[Screen::editScreen].free();
            if (gWindows[Screen::mainScreen].isClosed())
                break;
        }

        gWindows[Screen::mainScreen].handleEvent(e);
        //input.checkControls(&e);
        player.handleEvent();

        //LOGIC
        player.move( gameMap->getTileSet(), gameMap);
        player.setCamera( camera, gameMap );

        //RENDERING
        gWindows[Screen::mainScreen].Clear();

        gameMap->renderMap(gWindows[Screen::mainScreen], camera);

        player.render(gWindows[Screen::mainScreen], camera);

        gWindows[Screen::mainScreen].Present();
    }

    for( int i = 0; i < Screen::totalScreens; ++i )
	{
		gWindows[ i ].free();
	}

	//Quit SDL subsystems
	SDL_Quit();

    return 0;
}
