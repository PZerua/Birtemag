#pragma once
#include "Common_libs.h"
#include "Button.h"
#include "Frame.h"
#include "Input.h"

struct styleInfo
{
	string path;
	int borderSize;
};

class GUI
{
public:

	GUI();
	~GUI();

	void addButton(const string &name, const SDL_Rect &dim, const int &style, const int &behaviour, const int &mode);
	void addFrame(const SDL_Rect &dim, const int &style, const int &mode);
	int handleButtons(Input &input, Window &gWindow, int &selectedMode);
	bool isInside(const SDL_Point &point, const SDL_Rect &plane);
	void renderButtons();
	void renderFrames(const int &mode);
	styleInfo checkFrameStyle(const int &style);
	styleInfo checkButtonStyle(const int &style);
	void loadUtils();

private:
	vector<Button *> _buttons;
	vector<Frame *> _frames;
	bool _changing;
	
};
