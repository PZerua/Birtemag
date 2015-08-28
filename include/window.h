#ifndef WINDOW_H
#define WINDOW_H

#include "Common_libs.hxx"

class Window
{
	public:
		//Intializes internals
		Window();

		//Creates window
		bool init(string screenTitle, int xPos, int yPos);

		//Handles window events
		void handleEvent( SDL_Event& e );

		//Focuses on window
		void focus();

		//Print render
		void Present();

        //Clear screen
		void Clear();

		//Deallocates internals
		void free();

		void setFocus(bool focus);

		//Window dimensions
		int getWidth();
		int getHeight();

		//Window focus
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();
		bool isShown();
		bool isClosed();
		SDL_Renderer *getRender();
		static SDL_Renderer* mRenderer;

	private:
		//Window data
		SDL_Window* mWindow;
		int mWindowID;

		//Window dimensions
		int mWidth;
		int mHeight;

		//Window focus
		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized;
		bool mShown;
		bool mClosed;
};

#endif
