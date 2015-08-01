#include "World.h"

World::World(Window &gWindow)
{

    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;

    _player = new Player();
    addMap("bitmaps/prueba.map");
    _worldMaps[0]->addTilemap(gWindow, "tilesets/tile1.png");

    if( !_worldMaps[0]->setTiles() )
	{
		cout<<"Failed to load tile set!\n"<<endl;
	}
	_currentMap = _worldMaps[0];

	if ( !_player->gPlayerTexture.loadFromFile(gWindow, "sprites/player.png"))
    {
        cout<<"Failed to load sprite texture!\n"<<endl;
    }
}

World::~World()
{
    for(vector<Map *>::iterator it = _worldMaps.begin(); it < _worldMaps.end(); ++it)
    {
        delete(*it);
        it = _worldMaps.erase(it);
    }

    delete _player;
}

void World::addMap(string mapPath)
{
    Map *newMap = new Map(mapPath);
    _worldMaps.push_back(newMap);

}

Map *World::getCurrentMap()
{
    return _currentMap;
}

vector<Map *> &World::getMaps()
{
    return _worldMaps;
}

Player *World::getPlayer()
{
    return _player;
}

void World::handlePlayer()
{
    //EVENT
    _player->handleEvent();

    //LOGIC
    _player->move(_currentMap->getTileSet(), _currentMap);
    _player->setCamera(camera, _currentMap);
}

void World::render(Window &gWindow)
{
    _currentMap->renderMap(gWindow, camera);

    _player->render(gWindow, camera);
}

SDL_Rect &World::getCamera()
{
    return camera;
}
