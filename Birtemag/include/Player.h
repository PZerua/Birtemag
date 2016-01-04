#ifndef PLAYER_H
#define PLAYER_H

#include "Common_libs.h"
#include "Tile.h"
#include "Map.h"
#include "LTexture.h"
#include "window.h"

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
	    void render(SDL_Rect& camera );

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

		bool _mUP;
	    bool _mDOWN;
	    bool _mLEFT;
	    bool _mRIGHT;

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
