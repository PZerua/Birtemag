#ifndef TILEMAP_H
#define TILEMAP_H

#include "../include/Common_libs.hxx"
#include "../include/LTexture.h"
#include "../include/window.h"


class Tilemap
{
    public:

        Tilemap();

        ~Tilemap();

        bool loadTexture(string imagPath);

        void setClips();

        void initTilemap(string imagPath);

        LTexture *getTexture();

        SDL_Rect *getClips();

        int getTotalTiles();

    private:

        LTexture *_tileTexture;

        int _totalTiles;

        SDL_Rect *_tileClips;


};

#endif // TILEMAP_H
