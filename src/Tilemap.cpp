#include "../include/Tilemap.hxx"


Tilemap::Tilemap()
{
    _totalTiles = 0;
    _tileTexture = new LTexture;
    _tileClips = NULL;
}

Tilemap::~Tilemap()
{


}

bool Tilemap::loadTexture(string imagPath)
{
    _tileTexture->loadFromFile( imagPath );

    if( _tileTexture->getWidth() % TILE_SIZE != 0 || _tileTexture->getHeight() % TILE_SIZE != 0)
    {
        cout<<"Wrong tile texture size"<<endl;
        return false;
    }

    _totalTiles = (_tileTexture->getHeight() / 64 ) * (_tileTexture->getWidth() / 64);

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
            if (yMult == _tileTexture->getHeight() / 64)
            {
                xMult++;
                yMult = 0;
            }

            _tileClips[i].x = xMult * TILE_SIZE;
            _tileClips[i].y = yMult * TILE_SIZE;
            _tileClips[i].h = TILE_SIZE;
            _tileClips[i].w = TILE_SIZE;

            yMult++;
        }
    }
    else cout<<"Error cliping, there is no texture loaded"<<endl;
}

void Tilemap::initTilemap(string imagPath)
{
    if(loadTexture(imagPath))
    {
        _tileClips = new SDL_Rect[_totalTiles];
        setClips();
    }
    else cout<<"Cannot init tilemap: "<<imagPath<<endl;
}

LTexture *Tilemap::getTexture()
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
