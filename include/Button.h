#ifndef BUTTON_H
#define BUTTON_H

#include "Common_libs.hxx"
#include "LTexture.h"
#include "window.h"
#include "Common_functions.hxx"
#include "Editor.hxx"

class Editor;

class Button
{
    public:
        Button(Window &gWindow, int behaviour, string name);
        virtual ~Button();

        void render(Window &gWindow);
        void setState(int state);
        SDL_Rect getBox();
        void activate(Editor &editor);
        void free();
        void setPos(int x, int y);

    protected:
    private:

        LTexture _text;
        LTexture _normalState;
        LTexture _hoverState;
        LTexture _clickState;
        int _actualState;
        SDL_Rect mBox;
        SDL_Rect mTextBox;

        int _behaviour;


};

#endif // BUTTOM_H
