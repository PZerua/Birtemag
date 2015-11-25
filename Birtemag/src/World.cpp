#include "World.h"

World::World()
{
	loadTilemaps();
	camera.x = 0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	_player = new Player();
	cout << "[WORLD] Player created" << endl;

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

	for (map<int, Tilemap *>::iterator it = _tmaps.begin(); it != _tmaps.end(); it++)
	{
		delete it->second;
		it = _tmaps.erase(it);
	}

	delete _player;
}

void World::addMap(string mapPath)
{
	Map *newMap = new Map(mapPath);
	newMap->setTilemaps(getTilemaps());
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
	// Second parameter is used in Editor to hide layers
	_currentMap->renderMap(camera, -1, LayerPos::Lower);

	_player->render(camera);

	_currentMap->renderMap(camera, -1, LayerPos::Upper);
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
	cout << "[WORLD] Maps loaded" << endl;
}

void World::loadTilemaps()
{
	ifstream tilemaps("tilesets/tilesets.txt");

	string name;

	int id = 1;

	while (tilemaps >> name)
	{
		Tilemap *tilemap;
		tilemap = new Tilemap();

		tilemap->setData(name, id);
		_tmaps[id] = tilemap;
		id++;
	}
}

map<int, Tilemap *> &World::getTilemaps()
{
	return _tmaps;
}