#include <stdexcept>
#include <memory>
#include "../include/Common_libs.hxx"

#include "../include/window.h"

//Initialize the unique_ptr's deleters here
std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> Window::mWindow
	= std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> Window::mRenderer
	= std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
//other static members
SDL_Rect Window::mBox;

Window::Window(){
}
Window::~Window(){
}
void Window::Init(std::string title){
    //initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL Init Failed");
    if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");

    //Create our window
    mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
    //Make sure it created ok
    if (mWindow == nullptr)
        throw std::runtime_error("Failed to create window");
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        std::cout<<"Warning: Linear texture filtering not enabled!"<<std::endl;
    }

    //Create the renderer
    mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    //Make sure it created ok
    if (mRenderer == nullptr)
        throw std::runtime_error("Failed to create renderer");
    //Initialize renderer color
    SDL_SetRenderDrawColor( mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }
}
void Window::Quit(){
    TTF_Quit();
    SDL_Quit();
}
void Window::Clear(){
    SDL_RenderClear(mRenderer.get());
}
void Window::Present(){
    SDL_RenderPresent(mRenderer.get());
}
