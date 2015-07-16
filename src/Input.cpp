#include "../include/Input.hxx"

Input::Input()
{
    _quit = false;
    _mouseClick = false;
    _f2 = false;
    _f3 = false;
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
        }
        break;
    }
}
