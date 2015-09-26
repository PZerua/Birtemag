#include "Tilemap.hxx"


Tilemap::Tilemap()
{
	_totalTiles = 0;
	_tileClips = NULL;
	_isInit = false;
}

Tilemap::~Tilemap()
{
	delete[] _tileClips;
}

bool Tilemap::loadTexture(string imagPath)
{

	_name = imagPath;

	_tileTexture.loadFromFile(imagPath);

	if( _tileTexture.getWidth() % TILE_SIZE != 0 || _tileTexture.getHeight() % TILE_SIZE != 0)
	{
		cout<<"Wrong tile texture size"<<endl;
		return false;
	}

	_totalTiles = (_tileTexture.getHeight() / TILE_SIZE ) * (_tileTexture.getWidth() / TILE_SIZE);

	return true;

}

void Tilemap::setClips()
{
	int xMult = 0;
	int yMult = 0;

	if (_totalTiles != 0)
	{
		for(int i = 0; i < _totalTiles; i++)
		{
			if (xMult == _tileTexture.getWidth() / TILE_SIZE)
			{
				yMult++;
				xMult = 0;
			}

			_tileClips[i].x = xMult * TILE_SIZE;
			_tileClips[i].y = yMult * TILE_SIZE;
			_tileClips[i].h = TILE_SIZE;
			_tileClips[i].w = TILE_SIZE;

			xMult++;
		}
	}
	else cout<<"Error cliping, there is no texture loaded"<<endl;
}

void Tilemap::initTilemap()
{
	if(loadTexture(_imgPath))
	{
		_tileClips = new SDL_Rect[_totalTiles];
		setClips();
		_isInit = true;
	}
	else cout<<"Cannot init tilemap: "<<_imgPath<<endl;
}

void Tilemap::setData(string name, int id)
{
	_name = name;
	_imgPath = "tilesets/" + name;
	_ID = id;
}

LTexture &Tilemap::getTexture()
{
	return _tileTexture;
}

SDL_Rect *Tilemap::getClips()
{
	return _tileClips;
}

int Tilemap::getTotalTiles()
{
	return _totalTiles;
}

string Tilemap::getName()
{
	return _name;
}

int Tilemap::getID()
{
	return _ID;
}

bool Tilemap::isInit()
{
	return _isInit;
}