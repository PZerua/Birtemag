#ifndef TILE_H
#define TILE_H

#include "Common_functions.hxx"
#include "Common_libs.hxx"
#include "LTexture.h"

class Tile
{
    public:
        //Initializes position and type
        Tile( int x, int y, int tileType );

        //Shows the tile
        void render( SDL_Rect& camera , SDL_Rect *gTileClips);

        void setTexture(LTexture *gTexture);

        //Get the tile type
        int getType();

        //Get the collision box
        SDL_Rect getBox();

    private:
        //The attributes of the tile
        SDL_Rect mBox;

        LTexture *gTileTexture;
        //The tile type
        int mType;
};

#endif // TILE_H
