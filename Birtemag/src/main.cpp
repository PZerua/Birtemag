#include "Window.h"
#include "timer.h"
#include "Input.h"
#include "Tile.h"
#include "Common_libs.h"
#include "Common_functions.h"
#include "Map.h"
#include "Player.h"
#include "Editor.h"
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

	cout << "[INFO] Press F2 to open editor and F3 to close it" << endl;

	SDL_ShowCursor(SDL_DISABLE);

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
			SDL_ShowCursor(SDL_ENABLE);
			input._f2 = false;
			Editor *gameEditor = new Editor(world.getCamera(), world.getTilemaps());
			gameEditor->setMaps(world.getMaps(), world.getCurrentMap());
			gameEditor->init(gWindow, input, e);
			delete(gameEditor);
			SDL_ShowCursor(SDL_DISABLE);
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
