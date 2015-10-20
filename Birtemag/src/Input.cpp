#include "Input.h"

Input::Input()
{
	_quit = false;
	_mouseLClick = false;
	_mouseRClick = false;
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
	case SDL_QUIT:
		_quit = true;
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
	    case SDLK_d:
	        _right = true;
	        break;
	    case SDLK_a:
	        _left = true;
	        break;
	    case SDLK_w:
	        _up = true;
	        break;
	    case SDLK_s:
	        _down = true;
	        break;
	    }
	    break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
			_mouseLClick = true;
		else if (event->button.button == SDL_BUTTON_RIGHT)
			_mouseRClick = true;
	    break;
	case SDL_MOUSEBUTTONUP:
		if (event->button.button == SDL_BUTTON_LEFT)
			_mouseLClick = false;
		else if (event->button.button == SDL_BUTTON_RIGHT)
			_mouseRClick = false;
		break;
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
	    case SDLK_d:
	        _right = false;
	        break;
	    case SDLK_a:
	        _left = false;
	        break;
	    case SDLK_w:
	        _up = false;
	        break;
	    case SDLK_s:
	        _down = false;
	        break;
	    }
	    break;
	}
}
