#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "Common_libs.hxx"
#include "LTexture.h"
#include "window.h"

class InfoPanel
{
    public:
        InfoPanel();
        virtual ~InfoPanel();

        void loadTexture(Window &gWindow, string path);
        void setText(Window &gWindow, string text);
        void render(Window &gWindow);
    protected:
    private:

        LTexture _infoPanel;
        LTexture _infoText;
        SDL_Rect mBox;
        SDL_Rect mTextBox;
};

#endif // INFOPANEL_H
