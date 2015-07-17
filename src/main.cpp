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
    //Start our window
    try {
        Window::Init("Birtemag");
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
        Window::Quit();
        return -1;
    }

    Player player;
    Map *gameMap = new Map("bitmaps/prueba.map");

    if ( !player.gPlayerTexture.loadFromFile("sprites/player.png"))
    {
        cout<<"Failed to load sprite texture!\n"<<endl;
    }

	//Load tile texture
	gameMap->addTile("tilesets/tile1.png");

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
            cout<<"f2"<<endl;
            input._f2 = false;
            Editor gameEditor(camera);
            gameEditor.setMap(gameMap);
            gameEditor.init(input, e);
        }
        //input.checkControls(&e);
        player.handleEvent();

        //LOGIC
        player.move( gameMap->getTileSet(), gameMap);
        player.setCamera( camera, gameMap );

        //RENDERING
        SDL_SetRenderDrawColor( Window::mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF );
        Window::Clear();

        gameMap->renderMap(camera);

        player.render(camera);

        Window::Present();
    }

    Window::Quit();

    return 0;
}
