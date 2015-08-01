#include "../include/window.h"
#include "../include/timer.h"
#include "../include/Input.hxx"
#include "../include/Tile.h"
#include "../include/Common_libs.hxx"
#include "../include/Common_functions.hxx"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Editor.hxx"
#include "../include/World.h"

int main(int argc, char** argv){

    Window gWindows[ Screen::totalScreens ];

    //Start our window
    gWindows[Screen::mainScreen].init("Birtemag", 300, 300);

    if (TTF_Init() != 0)
    {
        cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
        SDL_Quit();
    }

    World world(gWindows[Screen::mainScreen]);

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
            Editor *gameEditor;
            gameEditor = new Editor(world.getCamera(), gWindows);
            gameEditor->addTilemap(gWindows, "tilesets/tile1.png");
            gameEditor->setMap(world.getMaps(), world.getCurrentMap());
            gameEditor->init(gWindows, input, e);
            delete(gameEditor);
            if (!gWindows[Screen::editScreen].isClosed())
                gWindows[Screen::editScreen].free();
            if (gWindows[Screen::mainScreen].isClosed())
                break;
        }
        gWindows[Screen::mainScreen].handleEvent(e);

        //PLAYER EVENT AND LOGIC
        world.handlePlayer();

        //RENDERING
        gWindows[Screen::mainScreen].Clear();

        world.render(gWindows[Screen::mainScreen]);

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
