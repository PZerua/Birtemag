#include "Button.h"

Button::Button(int behaviour, string name, int x, int y)
{

	mBox.x = x;
	mBox.y = y;
	SDL_Color color;
	color.a = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	_actualState = 0;
	_behaviour = behaviour;
	_isEnabled = true;

	_text.loadFromRenderedText(name, color, 16);
	_hoverState.loadFromFile("utils/hoverButton.png");
	_normalState.loadFromFile("utils/normalButton.png");
	_clickState.loadFromFile("utils/clickButton.png");

	SDL_QueryTexture(_normalState.getTexture(), NULL, NULL, &mBox.w, &mBox.h);
	SDL_QueryTexture(_text.getTexture(), NULL, NULL, &mTextBox.w, &mTextBox.h);
}

Button::~Button()
{

}

void Button::render()
{
	if (_isEnabled)
	{
		if (_actualState == ButtonState::normal)
			_normalState.render(mBox.x, mBox.y);
		else if (_actualState == ButtonState::hover)
			_hoverState.render(mBox.x, mBox.y);
		else if (_actualState == ButtonState::click)
			_clickState.render(mBox.x, mBox.y);
		_text.render(mBox.x + mBox.w / 2 - mTextBox.w / 2, mBox.y + mBox.h / 2 - mTextBox.h / 2);
	}
}

void Button::setPos(int x, int y)
{
	mBox.x = x;
	mBox.y = y;
}

void Button::activate(Editor &editor)
{
	if (_isEnabled)
	{
		if (_behaviour == Behaviour::tile)
		{
			editor.tileMode();
		}
		else if (_behaviour == Behaviour::collision)
		{
			editor.collisionMode();
		}
		else if (_behaviour == Behaviour::attribute)
		{
			editor.attributeMode();
		}
		else if (_behaviour == Behaviour::newMap)
		{
			editor.newMap();
		}
		else if (_behaviour == Behaviour::nextTilemap)
		{
			editor.nextTilemap();
		}
		else if (_behaviour == Behaviour::previousTilemap)
		{
			editor.previousTilemap();
		}
		else if (_behaviour == Behaviour::nextLayer)
		{
			editor.nextLayer();
		}
		else if (_behaviour == Behaviour::previousLayer)
		{
			editor.previousLayer();
		}
	}
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