#ifndef PLAYER_H
#define PLAYER_H
#include "../include/Common_libs.hxx"
#include "../include/Tile.h"
#include "../include/Map.h"
#include "../include/LTexture.h"
#include "../include/Common_functions.hxx"
#include "../include/window.h"

class Player
{
    public:
        Player();
        virtual ~Player();

        //Maximum axis velocity of the player
        static const int PLAYER_VEL = 4;

        //Takes key presses and adjusts the player's velocity
        void handleEvent();

        //Moves the player and check collision against tiles
        void move( Tile *tiles[], Map *gameMap);

        //Centers the camera over the player
        void setCamera( SDL_Rect& camera, Map *gameMap);

        //Shows the player on the screen
        void render( Window &gWindow, SDL_Rect& camera );

        LTexture gPlayerTexture;

        void nextXClip();

    private:
        unsigned int _life;
        string _name;

        //Collision box of the player
        SDL_Rect mBox;
        SDL_Rect _clip;

        int _target;
        int _nextTarget;

        int _moved;
        int _lastClip;

        bool _UP;
        bool _DOWN;
        bool _LEFT;
        bool _RIGHT;

        const Uint8* keystate;

        enum TARGET
        {
            IDLE,
            RIGHT,
            LEFT,
            UP,
            DOWN
        };

};

#endif // PLAYER_H
