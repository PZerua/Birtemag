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
	_moved = 0.0;

    keystate = SDL_GetKeyboardState(NULL);

    _clip.x = TILE_SIZE;
    _clip.y = 0;
    _clip.h = TILE_SIZE;
    _clip.w = TILE_SIZE;
}

Player::~Player()
{
    //dtor
}

void Player::handleEvent()
{
    //If a key was pressed+-
	if(keystate[SDL_SCANCODE_UP])
    {
        _UP = true;
        _RIGHT = false;
        _LEFT = false;
        _DOWN = false;
    }
    else if (!keystate[SDL_SCANCODE_UP])
        _UP = false;
    if(keystate[SDL_SCANCODE_DOWN])
    {
        _DOWN = true;
        _UP = false;
        _LEFT = false;
        _RIGHT = false;
    }
    else if (!keystate[SDL_SCANCODE_DOWN])
        _DOWN = false;
    if(keystate[SDL_SCANCODE_LEFT])
    {
        _LEFT = true;
        _RIGHT = false;
        _UP = false;
        _DOWN = false;
    }
    else if (!keystate[SDL_SCANCODE_LEFT])
        _LEFT = false;
    if(keystate[SDL_SCANCODE_RIGHT])
    {
        _RIGHT = true;
        _LEFT = false;
        _UP = false;
        _DOWN = false;
    }
    else if (!keystate[SDL_SCANCODE_RIGHT])
        _RIGHT = false;

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
            if (_UP) _target = TARGET::UP;
            else if (_DOWN) _target = TARGET::DOWN;
            else if (_RIGHT) _target = TARGET::RIGHT;
            else if (_LEFT) _target = TARGET::LEFT;
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
            if (_UP) _nextTarget = TARGET::UP;
            else if (_DOWN) _nextTarget = TARGET::DOWN;
            else if (_RIGHT) _nextTarget = TARGET::RIGHT;
            else if (_LEFT) _nextTarget = TARGET::LEFT;
        }

        //Move the dot left or right
        if(_moved < TILE_SIZE && _target != TARGET::IDLE)
        {
            if(_target == TARGET::RIGHT) mBox.x += PLAYER_VEL;
            else if(_target == TARGET::LEFT) mBox.x -= PLAYER_VEL;

            //If the dot went too far to the left or right or touched a wall
            if( ( mBox.x < 0 ) || ( mBox.x + TILE_SIZE > gameMap->LEVEL_WIDTH ) || gameMap->touchesWall( mBox) )
            {
                //move back
                if(_target == TARGET::RIGHT) mBox.x -= PLAYER_VEL;
                else if(_target == TARGET::LEFT) mBox.x += PLAYER_VEL;
            }

            //Move the dot up or down
            if(_target == TARGET::DOWN)
            {
                mBox.y += PLAYER_VEL;
                if (_moved < TILE_SIZE / 2) _clip.x = 0;
                if (_moved < TILE_SIZE && _moved > TILE_SIZE / 2) _clip.x = 2 * TILE_SIZE;

            }
            else if(_target == TARGET::UP) mBox.y -= PLAYER_VEL;

            //If the dot went too far up or down or touched a wall
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
    gPlayerTexture.render( mBox.x - camera.x, mBox.y - camera.y, &_clip );
}
