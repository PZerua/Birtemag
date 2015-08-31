#include "World.h"

World::World()
{

	camera.x = 0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	_player = new Player();
	loadMaps();

	if( !_worldMaps[0]->loadMap() )
	{
		cout<<"Failed to load tile set!\n"<<endl;
	}
	_currentMap = _worldMaps[0];

	if ( !_player->gPlayerTexture.loadFromFile("sprites/player.png"))
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
	_player->move(_currentMap->getTiles(), _currentMap);
	_player->setCamera(camera, _currentMap);
}

void World::render()
{
	_currentMap->renderMap(camera);

	_player->render(camera);
}

SDL_Rect &World::getCamera()
{
	return camera;
}

void World::loadMaps()
{
	ifstream maps("bitmaps/maps.txt");
	
	string name;

	while (maps >> name)
	{
		addMap("bitmaps/" + name);
	}

}