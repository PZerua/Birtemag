#include "InfoPanel.h"

InfoPanel::InfoPanel()
{

}

InfoPanel::~InfoPanel()
{


}

void InfoPanel::loadTexture(Window &gWindow, string path)
{
    _infoPanel.loadFromFile(gWindow, path);

    SDL_QueryTexture(_infoPanel.getTexture(), NULL, NULL, &mBox.w, &mBox.h);

    mBox.x = 0;
    mBox.y = SCREEN_HEIGHT - mBox.h;
}
void InfoPanel::setText(Window &gWindow, string text)
{
    SDL_Color textColor;

    textColor.r = 0;
    textColor.g = 0;
    textColor.b = 0;

    mTextBox.x = 10;
    mTextBox.y = 10;

    _infoText.loadFromRenderedText(gWindow, text, textColor, 20);
}

void InfoPanel::render(Window &gWindow)
{
    _infoPanel.render(gWindow, mBox.x, mBox.y);
    if (_infoText.getTexture() != NULL)
        _infoText.render(gWindow, mTextBox.x + mBox.x, mTextBox.y + mBox.y);
}
