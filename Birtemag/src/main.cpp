#include "window.h"
#include "timer.h"
#include "Input.hxx"
#include "Tile.h"
#include "Common_libs.hxx"
#include "Common_functions.hxx"
#include "Map.h"
#include "Player.h"
#include "Editor.hxx"
#include "World.h"

int main(int argc, char** argv)
{
    //Create window
    Window gWindow;

    //Start our window
    gWindow.init("Birtemag", 300, 250);


    //Init font library
    if (TTF_Init() != 0)
    {
        cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
        SDL_Quit();
    }

    //Create World
    World world;

    //Our event structure
	SDL_Event e;
	//Our input instance
	Input input;
	//For tracking if we want to quit
	while (!input._quit)
    {
		//Event Polling
		SDL_PollEvent(&e);
		//Check keyboard input
        input.checkControls(&e);

        if (input._f2)
        {
            //Goes into Editor
            input._f2 = false;
            Editor *gameEditor = new Editor(world.getCamera());
            gameEditor->setMap(world.getMaps(), world.getCurrentMap());
            gameEditor->init(gWindow, input, e);
            delete(gameEditor);
            //If the window has been closed exits the loop
            if (gWindow.isClosed())
            {
                break;
            }
        }
        //Check window event
        gWindow.handleEvent(e);

        //PLAYER EVENT AND LOGIC
        world.handlePlayer();

        //RENDERING
        gWindow.Clear();

        //Render everything
        world.render();

        //Draw the world
        gWindow.Present();
    }

    //Free window
    gWindow.free();

	//Quit SDL subsystems
	SDL_Quit();

    return 0;
}
