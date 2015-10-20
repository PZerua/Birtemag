#ifndef INPUT_H
#define INPUT_H
#include "Common_libs.h"

class Input
{
	public:
	    Input();
	    virtual ~Input();
	    //void Player_Control();
	    void checkControls(SDL_Event *events);

	    bool _quit;
	    bool _mouseLClick;
		bool _mouseRClick;
	    bool _f2;
	    bool _f3;
	    bool _right;
	    bool _left;
	    bool _up;
	    bool _down;

	private:


};

#endif // INPUT_H
