#pragma once
#include "Common_libs.h"
#include "LTexture.h"
#include "window.h"
#include "Frame.h"

class Button
{
public:
		Button(const string &name, const SDL_Rect &dim, const int &behaviour, const string &path, const int &borderSize, const int &mode);
	    virtual ~Button();

	    void render();
	    void setState(int state);
	    SDL_Rect getBox();
	    int getBehaviour();
	    void setPos(int x, int y);
		void setFixedState(int state);
		void removeFixedState();
		void enable();
		void disable();

private:

	    LTexture _text;
	    Frame *_normalState;
		Frame *_hoverState;
		Frame *_clickState;
	    int _actualState;
		int _fixedState;
		bool _hasFixedState;
		bool _isEnabled;
	    SDL_Rect mTextBox;
		SDL_Rect mBox;
	    int _behaviour;

};
