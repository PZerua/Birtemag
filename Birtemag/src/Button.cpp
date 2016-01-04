#include "Button.h"

Button::Button(const string &name, const SDL_Rect &dim, const int &behaviour, const string &path, const int &borderSize, const int &mode)
{

	mBox.x = dim.x;
	mBox.y = dim.y;
	mBox.w = dim.w;
	mBox.h = dim.h;

	SDL_Color color;
	color.a = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	_actualState = 0;
	_behaviour = behaviour;
	_isEnabled = true;

	_text.loadFromRenderedText(name, color, 31);
	_hoverState = new Frame("utils/hoverButton_" + path + ".png", dim, borderSize, mode);
	_normalState = new Frame("utils/normalButton_" + path + ".png", dim, borderSize, mode);
	_clickState = new Frame("utils/clickButton_" + path + ".png", dim, borderSize, mode);

	mTextBox.w = _text.getWidth();
	mTextBox.h = _text.getHeight();
}

Button::~Button()
{
	delete _normalState;
	delete _hoverState;
	delete _clickState;
}

void Button::render()
{
	if (_isEnabled)
	{
		if (_actualState == ButtonState::normal)
			_normalState->render();
		else if (_actualState == ButtonState::hover)
			_hoverState->render();
		else if (_actualState == ButtonState::click)
			_clickState->render();
		_text.render(mBox.x + mBox.w / 2 - mTextBox.w / 2, mBox.y + mBox.h / 2 - mTextBox.h / 2);
	}
}

void Button::setPos(int x, int y)
{
	mBox.x = x;
	mBox.y = y;
}

int Button::getBehaviour()
{
	if (_isEnabled)
	{
		return _behaviour;
	}
	else return -1;
}

void Button::setState(int state)
{
	if(!_hasFixedState)
		_actualState = state;
}

SDL_Rect Button::getBox()
{
	return mBox;
}

void Button::setFixedState(int state)
{
	_actualState = state;
	_hasFixedState = true;
}

void Button::removeFixedState()
{
	_hasFixedState = false;
}

void Button::enable()
{
	_isEnabled = true;
}

void Button::disable()
{
	_isEnabled = false;
}