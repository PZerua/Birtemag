#include "Button.h"

Button::Button(int behaviour, string name)
{

    SDL_Color color;
    color.a = 0;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    _actualState = 0;
    _behaviour = behaviour;

    _text.loadFromRenderedText(name, color, 16);
    _hoverState.loadFromFile("utils/hoverButton.png");
    _normalState.loadFromFile("utils/normalButton.png");

    SDL_QueryTexture(_normalState.getTexture(), NULL, NULL, &mBox.w, &mBox.h);
    SDL_QueryTexture(_text.getTexture(), NULL, NULL, &mTextBox.w, &mTextBox.h);
}

Button::~Button()
{

}

void Button::render()
{
    if (_actualState == ButtonState::normal)
        _normalState.render(mBox.x , mBox.y);
    else if (_actualState == ButtonState::hover)
        _hoverState.render(mBox.x, mBox.y);
    _text.render(mBox.x + mBox.w / 2 - mTextBox.w / 2, mBox.y + mBox.h / 2 - mTextBox.h / 2);
}

void Button::setPos(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
}

void Button::activate(Editor &editor)
{
    if (_behaviour == Behaviour::collision)
    {
        editor.changeCollision();
    }
    else if (_behaviour == Behaviour::newMap)
    {
        editor.newMap();
    }
}

void Button::setState(int state)
{
    _actualState = state;
}

SDL_Rect Button::getBox()
{
    return mBox;
}
