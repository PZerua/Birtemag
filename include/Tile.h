#ifndef TILE_H
#define TILE_H

#include "../include/Common_functions.hxx"
#include "../include/Common_libs.hxx"
#include "../include/LTexture.h"

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

        bool hasCollision();

    private:
        //The attributes of the tile
        SDL_Rect mBox;

        LTexture *gTileTexture;
        //The tile type
        int mType;

        bool _hasCollision;

};

#endif // TILE_H
