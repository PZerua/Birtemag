#include "LTexture.h"
#include "window.h"
LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	_textureRect.x = 0;
	_textureRect.y = 0;
	_textureRect.w = 0;
	_textureRect.h = 0;
}

LTexture::~LTexture()
{
	// Deallocate
	free();
}

bool LTexture::loadFromFile(string path )
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		// Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		// Create texture from surface pixels
	    newTexture = SDL_CreateTextureFromSurface( Window::mRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			// Get image dimensions
			SDL_QueryTexture(newTexture, NULL, NULL, &_textureRect.w, &_textureRect.h);
		}

		// Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	// Return success
	mTexture = newTexture;

	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, int fontSize )
{
	// Get rid of preexisting texture
	free();
	TTF_Font *gFont = TTF_OpenFont("fonts/monaco.ttf", fontSize);
	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended( gFont, textureText.c_str(), textColor);
	if( textSurface != NULL )
	{
		// Create texture from surface pixels
	    mTexture = SDL_CreateTextureFromSurface( Window::mRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			// Get image dimensions
			SDL_QueryTexture(mTexture, NULL, NULL, &_textureRect.w, &_textureRect.h);
		}

		// Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	// Return success
	return mTexture != NULL;
}

void LTexture::free()
{
	// Free texture if it exists
	if( mTexture != NULL )
	{	
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		_textureRect.x = 0;
		_textureRect.y = 0;
		_textureRect.w = 0;
		_textureRect.h = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	// Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	// Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	// Set rect pos
	_textureRect.x = x;
	_textureRect.y = y;

	// Set rendering space and render to screen
	SDL_Rect renderQuad = _textureRect;

	// Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(Window::mRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

SDL_Rect LTexture::getRect()
{
	return _textureRect;
}

int LTexture::getWidth()
{
	return _textureRect.w;
}

int LTexture::getHeight()
{
	return _textureRect.h;
}

int LTexture::getX()
{
	return _textureRect.x;
}

int LTexture::getY()
{
	return _textureRect.y;
}

SDL_Texture *LTexture::getTexture()
{
	return mTexture;
}