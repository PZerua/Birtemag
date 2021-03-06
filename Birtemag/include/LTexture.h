#ifndef LTEXTURE_H
#define LTEXTURE_H
#include "Common_libs.h"

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(std::string path );

		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, int fontSize );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		// Get Texture location and dimensions
		SDL_Rect getRect();

		int getWidth();

		int getHeight();

		int getX();

		int getY();

		SDL_Texture *getTexture();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		SDL_Rect _textureRect;
};

#endif // LTEXTURE_H
