#include "GUI.h"

GUI::GUI()
{
	// Variable used to track button state changes
	_changing = false;
}

GUI::~GUI()
{
	vector<Button*>::iterator iterB;
	for (iterB = _buttons.begin(); iterB != _buttons.end(); iterB++)
	{
		delete *iterB;
	}
	vector<Frame*>::iterator iterF;
	for (iterF = _frames.begin(); iterF != _frames.end(); ++iterF)
	{
		delete *iterF;
	}
	_buttons.clear();
	_frames.clear();
}

void GUI::addButton(const string &name, const SDL_Rect &dim, const int &style, const int &behaviour, const int &mode)
{
	styleInfo info = checkButtonStyle(style);

	Button *button = new Button(name, dim, behaviour, info.path, info.borderSize, mode);

	_buttons.push_back(button);
}

void GUI::addFrame(const SDL_Rect &dim, const int &style, const int &mode)
{
	styleInfo info = checkFrameStyle(style);

	Frame *frame = new Frame(info.path, dim, info.borderSize, mode);

	_frames.push_back(frame);
}

int GUI::handleButtons(Input &input, Window &gWindow, int &selectedMode)
{
	//Mouse offsets
	SDL_Point point;

	//Get mouse offsets
	SDL_GetMouseState(&point.x, &point.y);

	if (gWindow.isFullscreen())
	{
		SDL_DisplayMode desktop;
		SDL_GetDesktopDisplayMode(0, &desktop);

		point.x = (int)round(point.x * SCREEN_WIDTH / desktop.w);
		point.y = (int)round(point.y * SCREEN_HEIGHT / desktop.h);
	}

	if (selectedMode == Behaviour::tile)
	{
		_buttons[Behaviour::tile]->setFixedState(ButtonState::hover);
		_buttons[Behaviour::collision]->removeFixedState();
		_buttons[Behaviour::attribute]->removeFixedState();
	}
	else if (selectedMode == Behaviour::collision)
	{
		_buttons[Behaviour::tile]->removeFixedState();
		_buttons[Behaviour::collision]->setFixedState(ButtonState::hover);
		_buttons[Behaviour::attribute]->removeFixedState();
	}
	else if (selectedMode == Behaviour::attribute)
	{
		_buttons[Behaviour::tile]->removeFixedState();
		_buttons[Behaviour::collision]->removeFixedState();
		_buttons[Behaviour::attribute]->setFixedState(ButtonState::hover);
	}

	for (unsigned i = 0; i < _buttons.size(); i++)
	{

		if (selectedMode != Behaviour::tile)
		{
			if (i == Behaviour::nextTilemap || i == Behaviour::previousTilemap || i == Behaviour::nextLayer || i == Behaviour::previousLayer)
				_buttons[i]->disable();
		}
		else _buttons[i]->enable();

		if (SDL_PointInRect(&point, &_buttons[i]->getBox()))
		{
			if (!_changing)
				_buttons[i]->setState(ButtonState::hover);
			if (input._mouseLClick && !_changing)
			{
				if (i == Behaviour::tile)
					selectedMode = Behaviour::tile;
				else if (i == Behaviour::collision)
					selectedMode = Behaviour::collision;
				else if (i == Behaviour::attribute)
					selectedMode = Behaviour::attribute;

				_buttons[i]->setState(ButtonState::click);
				_changing = true;
				int behaviour = _buttons[i]->getBehaviour();
				if (behaviour != -1)
					return behaviour;
			}
		}
		else _buttons[i]->setState(ButtonState::normal);
	}
	if (!input._mouseLClick && _changing)
	{
		_changing = false;
	}
	return -1;
}

void GUI::renderButtons()
{
	for (unsigned i = 0; i < _buttons.size(); i++)
		_buttons[i]->render();
}

void GUI::renderFrames(const int &mode)
{
	for (unsigned i = 0; i < _frames.size(); i++)
	{
		if (mode == _frames[i]->getMode())
			_frames[i]->render();
		else if (_frames[i]->getMode() == -1)
			_frames[i]->render();
	}
}

styleInfo GUI::checkFrameStyle(const int &style)
{
	styleInfo info;

	if (style == GUI_STYLE::Default)
	{
		info.path = "utils/frame_def.png";
		info.borderSize = 2;
	}
	else if (style == GUI_STYLE::Border1)
	{
		info.path = "utils/frame_border1.png";
		info.borderSize = 3;
	}
	else if (style == GUI_STYLE::Light1)
	{
		info.path = "utils/frame_light1.png";
		info.borderSize = 2;
	}
	
	return info;
}

styleInfo GUI::checkButtonStyle(const int &style)
{
	styleInfo info;

	if (style == GUI_STYLE::Default)
	{
		info.path = "def";
		info.borderSize = 6;
	}

	return info;
}