#ifndef BUTTON_H
#define BUTTON_H

#include "Common_libs.h"
#include "LTexture.h"
#include "window.h"
#include "Common_functions.h"
#include "Editor.h"
#include "window.h"

class Editor;

class Button
{
    public:
        Button(int behaviour, string name, int x, int y);
        virtual ~Button();

        void render();
        void setState(int state);
        SDL_Rect getBox();
        void activate(Editor &editor);
        void setPos(int x, int y);
		void setFixedState(int state);
		void removeFixedState();
		void enable();
		void disable();

    protected:
    private:

        LTexture _text;
        LTexture _normalState;
        LTexture _hoverState;
        LTexture _clickState;
        int _actualState;
		int _fixedState;
		bool _hasFixedState;
		bool _isEnabled;
        SDL_Rect mBox;
        SDL_Rect mTextBox;

        int _behaviour;


};

#endif // BUTTOM_H
