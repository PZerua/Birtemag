#include "Tile.h"

Tile::Tile( int x, int y, int tileType, bool collision )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_SIZE;
    mBox.h = TILE_SIZE;

    //Get the tile type
    mType = tileType;

    _hasCollision = collision;

}

Tile::~Tile()
{

}

void Tile::render(SDL_Rect& camera , SDL_Rect *gTileClips)
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture->render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

void Tile::free()
{
    gTileTexture->free();
}

void Tile::setType(int type)
{
    mType = type;
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

void Tile::setTexture(LTexture *gTexture)
{
    gTileTexture = gTexture;
}

bool Tile::hasCollision()
{
    return _hasCollision;
}

void Tile::setCollision(bool coliss)
{
    _hasCollision = coliss;
}
