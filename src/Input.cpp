#include "../include/Input.hxx"

Input::Input()
{
    _moveRight = false;
    _moveLeft = false;
    _moveUp = false;
    _moveDown = false;
    _quit = false;
}

Input::~Input()
{

}

void Input::checkControls(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:

        switch (event->key.keysym.sym)
        {
        case SDLK_a:
            _moveLeft = true;
            break;
        case SDLK_d:
            _moveRight = true;
            break;
        case SDLK_w:
            _moveUp = true;
            break;
        case SDLK_s:
            _moveDown = true;
            break;
        case SDLK_ESCAPE:
            _quit = true;
            break;
        }
    break;
    case SDL_KEYUP:

        switch (event->key.keysym.sym)
        {
        case SDLK_a:
            _moveLeft = false;
            break;
        case SDLK_d:
            _moveRight = false;
            break;
        case SDLK_s:
            _moveDown = false;
            break;
        case SDLK_w:
            _moveUp = false;
        }
    break;
    }
}
