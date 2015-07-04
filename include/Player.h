#ifndef PLAYER_H
#define PLAYER_H
#include "../include/Common_libs.hxx"
#include "../include/Tile.h"
#include "../include/Map.h"
#include "../include/LTexture.h"
#include "../include/Common_functions.hxx"

class Player
{
    public:
        Player();
        virtual ~Player();

        //Maximum axis velocity of the dot
        static const int PLAYER_VEL = 4;

        //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e );

        //Moves the dot and check collision against tiles
        void move( Tile *tiles[], Map *gameMap);

        //Centers the camera over the dot
        void setCamera( SDL_Rect& camera, Map *gameMap);

        //Shows the dot on the screen
        void render( SDL_Rect& camera );

        LTexture gPlayerTexture;

    private:
        unsigned int _life;
        string _name;

        //Collision box of the dot
        SDL_Rect mBox;

        //The velocity of the dot
        int mVelX, mVelY;

        int _target;
        int _nextTarget;

        float _moved;

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
