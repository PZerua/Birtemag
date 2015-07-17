#include "../include/Input.hxx"

Input::Input()
{
    _quit = false;
    _mouseClick = false;
    _f2 = false;
    _f3 = false;
    _right = false;
    _left = false;
    _up = false;
    _down = false;
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
        case SDLK_ESCAPE:
            _quit = true;
            break;
        case SDLK_F2:
            _f2 = true;
            break;
        case SDLK_F3:
            _f3 = true;
            break;
        case SDLK_RIGHT:
            _right = true;
            break;
        case SDLK_LEFT:
            _left = true;
            break;
        case SDLK_UP:
            _up = true;
            break;
        case SDLK_DOWN:
            _down = true;
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        _mouseClick = true;
        break;
    case SDL_MOUSEBUTTONUP:
        _mouseClick = false;
        break;
    case SDL_KEYUP:
        switch (event->key.keysym.sym)
        {
        case SDLK_F2:
            _f2 = false;
            break;
        case SDLK_F3:
            _f3 = false;
            break;
        case SDLK_RIGHT:
            _right = false;
            break;
        case SDLK_LEFT:
            _left = false;
            break;
        case SDLK_UP:
            _up = false;
            break;
        case SDLK_DOWN:
            _down = false;
            break;
        }
        break;
    }
}
