#include "Frame.h"

Frame::Frame(const string &stylePath, const SDL_Rect &dim, const int &borderSize, const int &mode)
{
	_mode = mode;
	_borderSize = borderSize;
	_dimensions.x = dim.x;
	_dimensions.y = dim.y;
	_dimensions.w = dim.w;
	_dimensions.h = dim.h;

	_patch.loadFromFile(stylePath);
}

Frame::~Frame()
{

}

// Source ported from http://nick.beeuwsaert.me/sdl2/image/drawing/2014/09/16/yay-SDL2-image-drawing.html

/**
 * Renders a image with out distorting it
 *
 * @param src      the offsets from the edges of the texture to cut the image
 * @param dst      The destination where the patch will be drawn
 */
void Frame::render() {
	// Sort of like how CSS box-sizing: border-box; works
	// if we have a width of 50px, but the padding is set to 30px, then we will have a 60px wide box
	_dimensions.w = MAX(_dimensions.w, 2 * _borderSize);
	_dimensions.h = MAX(_dimensions.h, 2 * _borderSize);
	int w, h;
	SDL_QueryTexture(_patch.getTexture(), NULL, NULL, &w, &h);

	SDL_Point srcPoints[] = {
		{ 0, 0 },
		{ _borderSize, _borderSize },
		{ w - _borderSize, h - _borderSize },
		{ w, h }
	};
	SDL_Point dstPoints[] = {
		{ _dimensions.x, _dimensions.y },
		{ _dimensions.x + _borderSize, _dimensions.y + _borderSize },
		{ _dimensions.x + _dimensions.w - _borderSize, _dimensions.y + _dimensions.h - _borderSize },
		{ _dimensions.x + _dimensions.w, _dimensions.y + _dimensions.h }
	};
	//Loop trough and draw each rect
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			SDL_Rect src_ = {
				srcPoints[x].x,
				srcPoints[y].y,
				srcPoints[x + 1].x,
				srcPoints[y + 1].y
			};
			src_.w -= src_.x;
			src_.h -= src_.y;

			SDL_Rect dst_ = {
				dstPoints[x].x,
				dstPoints[y].y,
				dstPoints[x + 1].x,
				dstPoints[y + 1].y
			};
			dst_.w -= dst_.x;
			dst_.h -= dst_.y;

			SDL_RenderCopy(Window::mRenderer, _patch.getTexture(), &src_, &dst_);
		}
	}
}

int Frame::getMode()
{
	return _mode;
}