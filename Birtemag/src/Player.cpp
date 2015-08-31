#include "Player.h"
#include "Common_libs.hxx"
#include "Input.hxx"

Player::Player()
{
    mBox.x = 640;
    mBox.y = 384;
	mBox.w = TILE_SIZE;
	mBox.h = TILE_SIZE;

	_mUP = false;
	_mDOWN = false;
	_mRIGHT = false;
	_mLEFT = false;

	_target = TARGET::IDLE;
	_nextTarget = TARGET::IDLE;
	_moved = 0;
	_lastClip = 0;

    keystate = SDL_GetKeyboardState(NULL);

    _clip.x = TILE_SIZE;
    _clip.y = 0;
    _clip.h = TILE_SIZE;
    _clip.w = TILE_SIZE;
}

Player::~Player()
{

}

void Player::handleEvent()
{
	if(keystate[SDL_SCANCODE_UP])
    {
        _mUP = true;
        _mRIGHT = false;
        _mLEFT = false;
        _mDOWN = false;
    }
    else if (!keystate[SDL_SCANCODE_UP])
        _mUP = false;
    if(keystate[SDL_SCANCODE_DOWN])
    {
        _mDOWN = true;
        _mUP = false;
        _mLEFT = false;
        _mRIGHT = false;
    }
    else if (!keystate[SDL_SCANCODE_DOWN])
        _mDOWN = false;
    if(keystate[SDL_SCANCODE_LEFT])
    {
        _mLEFT = true;
        _mRIGHT = false;
        _mUP = false;
        _mDOWN = false;
    }
    else if (!keystate[SDL_SCANCODE_LEFT])
        _mLEFT = false;
    if(keystate[SDL_SCANCODE_RIGHT])
    {
        _mRIGHT = true;
        _mLEFT = false;
        _mUP = false;
        _mDOWN = false;
    }
    else if (!keystate[SDL_SCANCODE_RIGHT])
        _mRIGHT = false;

}

void Player::move( Tile *tiles[], Map *gameMap)
{

    if (_moved == 0)
    {
        if (_nextTarget != TARGET::IDLE)
        {
             if (_target != _nextTarget) _target = _nextTarget;
             _nextTarget = TARGET::IDLE;
        }
        else
        {
            if (_mUP) _target = TARGET::UP;
            else if (_mDOWN) _target = TARGET::DOWN;
            else if (_mRIGHT) _target = TARGET::RIGHT;
            else if (_mLEFT) _target = TARGET::LEFT;
        }
    }

    /*
    if (_UP) cout<<"UP"<<endl;
    if (_DOWN) cout<<"DOWN"<<endl;
    if (_RIGHT) cout<<"RIGHT"<<endl;
    if (_LEFT) cout<<"LEFT"<<endl;
    */

    /*
    if (_nextTarget == TARGET::UP) cout<<"UP"<<endl;
    else if (_nextTarget == TARGET::DOWN) cout<<"DOWN"<<endl;
    else if (_nextTarget == TARGET::RIGHT) cout<<"RIGHT"<<endl;
    else if (_nextTarget == TARGET::LEFT) cout<<"LEFT"<<endl;
    */

    if (_target != TARGET::IDLE)
    {
        if (_moved > TILE_SIZE/2)
        {
            // TODO: Fix movement (when pressing two keys at once)
            if (_mUP) _nextTarget = TARGET::UP;
            else if (_mDOWN) _nextTarget = TARGET::DOWN;
            else if (_mRIGHT) _nextTarget = TARGET::RIGHT;
            else if (_mLEFT) _nextTarget = TARGET::LEFT;
        }

        //Move the dot left or right
        if(_moved < TILE_SIZE && _target != TARGET::IDLE)
        {
            if(_target == TARGET::RIGHT) mBox.x += PLAYER_VEL;
            else if(_target == TARGET::LEFT) mBox.x -= PLAYER_VEL;

            //If the player went too far to the left or right or touched a wall
            if( ( mBox.x < 0 ) || ( mBox.x + TILE_SIZE > gameMap->LEVEL_WIDTH ) || gameMap->touchesWall( mBox) )
            {
                //move back
				if (_target == TARGET::RIGHT) {
					mBox.x -= PLAYER_VEL;
				}
                else if(_target == TARGET::LEFT) mBox.x += PLAYER_VEL;
            }

            //Move the player up or down
            if(_target == TARGET::DOWN)
            {
                mBox.y += PLAYER_VEL;
                if (_moved % 32 == 0) nextXClip();

            }
            else if(_target == TARGET::UP) mBox.y -= PLAYER_VEL;

            //If the player went too far up or down or touched a wall
            if( ( mBox.y < 0 ) || ( mBox.y + TILE_SIZE > gameMap->LEVEL_HEIGHT ) || gameMap->touchesWall( mBox) )
            {
                //move back
                if(_target == TARGET::DOWN) mBox.y -= PLAYER_VEL;
                else if(_target == TARGET::UP) mBox.y += PLAYER_VEL;
            }
            _moved += PLAYER_VEL;
        }
        if(_moved >= TILE_SIZE)
        {
            _moved = 0;
            _target = TARGET::IDLE;
            _clip.x = TILE_SIZE;
        }
    }
}

void Player::setCamera( SDL_Rect& camera, Map *gameMap)
{
    //Center the camera over the player
    camera.x = ( mBox.x + TILE_SIZE / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( mBox.y + TILE_SIZE / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > gameMap->LEVEL_WIDTH - camera.w )
    {
        camera.x = gameMap->LEVEL_WIDTH - camera.w;
    }
    if( camera.y > gameMap->LEVEL_HEIGHT - camera.h )
    {
        camera.y = gameMap->LEVEL_HEIGHT - camera.h;
    }
}

void Player::render(SDL_Rect& camera )
{
    //Show the player
    gPlayerTexture.render(mBox.x - camera.x, mBox.y - camera.y, &_clip );
}

void Player::nextXClip()
{
    if (_clip.x == TILE_SIZE)
    {
        if (_lastClip == 0)
            _clip.x = 2 * TILE_SIZE;
        else if (_lastClip == 2 * TILE_SIZE)
            _clip.x = 0;
        _lastClip = _clip.x;
    }
    else if (_clip.x == TILE_SIZE * 2) _clip.x = TILE_SIZE;
    else if (_clip.x == 0) _clip.x = TILE_SIZE;
}
