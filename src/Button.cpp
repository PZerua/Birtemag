#include "Button.h"

Button::Button(Window &gWindow, int behaviour, string name)
{

    SDL_Color color;
    color.a = 0;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    _actualState = 0;
    _behaviour = behaviour;

    _text.loadFromRenderedText(gWindow, name, color, 24);
    _hoverState.loadFromFile(gWindow, "utils/hoverButton.png");
    _clickState.loadFromFile(gWindow, "utils/clickButton.png");
    _normalState.loadFromFile(gWindow, "utils/normalButton.png");

    SDL_QueryTexture(_normalState.getTexture(), NULL, NULL, &mBox.w, &mBox.h);
    SDL_QueryTexture(_text.getTexture(), NULL, NULL, &mTextBox.w, &mTextBox.h);
}

Button::~Button()
{

}

void Button::render(Window &gWindow)
{
    if (_actualState == ButtonState::normal)
        _normalState.render(gWindow, mBox.x , mBox.y);
    else if (_actualState == ButtonState::hover)
        _hoverState.render(gWindow, mBox.x, mBox.y);
    else if (_actualState == ButtonState::click)
        _clickState.render(gWindow, mBox.x, mBox.y);
    _text.render(gWindow, mBox.x + mBox.w / 2 - mTextBox.w / 2, mBox.y + mBox.h / 2 - mTextBox.h / 2);
}

void Button::setPos(int x, int y)
{
    mBox.x = x;
    mBox.y = y;
}

void Button::activate(Editor &editor, Window gWindows[Screen::totalScreens])
{
    if (_behaviour == Behaviour::collision)
    {
        editor.changeCollision();
    }
    else if (_behaviour == Behaviour::newMap)
    {
        editor.newMap(gWindows[Screen::mainScreen]);
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

void Button::free()
{
    _normalState.free();
    _hoverState.free();
    _clickState.free();
    _text.free();
}
