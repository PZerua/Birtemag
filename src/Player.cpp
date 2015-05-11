#include "..\include\Player.h"
#include "..\include\Common_libs.hxx"
#include "..\include\Input.hxx"

Player::Player()
{
    mBox.x = 0;
    mBox.y = 0;
	mBox.w = TILE_SIZE;
	mBox.h = TILE_SIZE;

	_UP = false;
	_DOWN = false;
	_RIGHT = false;
	_LEFT = false;

	_target = TARGET::IDLE;
	_nextTarget = TARGET::IDLE;
	_moved = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;}

Player::~Player()
{
    //dtor
}

void Player::handleEvent( SDL_Event& e )
{
    //If a key was pressed+-
	if( e.type == SDL_KEYDOWN && _target == TARGET::IDLE)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            {
                _UP = true;
                break;
            }
            case SDLK_DOWN:
            {
                _DOWN = true;
                break;
            }
            case SDLK_LEFT:
            {
                _LEFT = true;
                break;
            }
            case SDLK_RIGHT:
            {
                _RIGHT = true;
                break;
            }
        }
    }
    if( e.type == SDL_KEYUP)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            {
                _UP = false;
                break;
            }
            case SDLK_DOWN:
            {
                _DOWN = false;
                break;
            }
            case SDLK_LEFT:
            {
                _LEFT = false;
                break;
            }
            case SDLK_RIGHT:
            {
                _RIGHT = false;
                break;
            }
        }
    }
}

void Player::move( Tile *tiles[], Map *gameMap)
{
    if (_UP) _target = TARGET::UP;
    else if (_DOWN) _target = TARGET::DOWN;
    if (_RIGHT) _target = TARGET::RIGHT;
    else if (_LEFT) _target = TARGET::LEFT;

    //Move the dot left or right
    if(_moved < TILE_SIZE && _target != TARGET::IDLE)
    {
        if(_target == TARGET::RIGHT) mBox.x += PLAYER_VEL;
        else if(_target == TARGET::LEFT) mBox.x -= PLAYER_VEL;

        //If the dot went too far to the left or right or touched a wall
        if( ( mBox.x < 0 ) || ( mBox.x + TILE_SIZE > gameMap->LEVEL_WIDTH ) || touchesWall( mBox, tiles, gameMap ) )
        {
            //move back
            if(_target == TARGET::RIGHT) mBox.x -= PLAYER_VEL;
            else if(_target == TARGET::LEFT) mBox.x += PLAYER_VEL;
        }

        //Move the dot up or down
        if(_target == TARGET::DOWN) mBox.y += PLAYER_VEL;
        else if(_target == TARGET::UP) mBox.y -= PLAYER_VEL;

        //If the dot went too far up or down or touched a wall
        if( ( mBox.y < 0 ) || ( mBox.y + TILE_SIZE > gameMap->LEVEL_HEIGHT ) || touchesWall( mBox, tiles, gameMap) )
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
    }
}

void Player::setCamera( SDL_Rect& camera, Map *gameMap)
{
    //Center the camera over the dot
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

void Player::render( SDL_Rect& camera )
{
    //Show the dot
    gPlayerTexture.render( mBox.x - camera.x, mBox.y - camera.y );
}
