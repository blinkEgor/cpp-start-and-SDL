#include "WindowManager.h"

// constructor
WindowManager::WindowManager(const std::string& title, int width, int height)
: title(title), SCREEN_WIDTH(width), SCREEN_HEIGHT(height) {}

// initialize SQL 
// initialize Window
// initialize Renderer
bool WindowManager::init() {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	window = SDL_CreateWindow( title.c_str(), W_POS_X, W_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, W_FLAGS );
	if( window == nullptr ) { 
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		cleanup();
		return false;
	}

	renderer = SDL_CreateRenderer( window, D_INDEX, R_FLAGS );
	if( renderer == nullptr ) {
		printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	return true;
}

// get window
SDL_Window* WindowManager::getWindow() const { return window; }
// get renderer
SDL_Renderer* WindowManager::getRenderer() const { return renderer; }
// get window width
int WindowManager::getWidth() const { return SCREEN_WIDTH; }
// get window height
int WindowManager::getHeight() const { return SCREEN_HEIGHT; }

// set color for clear window
void WindowManager::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
	r = red; g = green; b = blue; a = alpha;
}

// clear window
void WindowManager::clearWindow() {
	SDL_SetRenderDrawColor( renderer, r, g, b, a );	// set color
	SDL_RenderClear( renderer );
}

// clean up all for close program
void WindowManager::cleanup() {
	if( renderer != nullptr ) {
		SDL_DestroyRenderer( renderer );
		renderer = nullptr;
	}

	if( window != nullptr ) {
		SDL_DestroyWindow( window );
		window = nullptr;
	}
	SDL_Quit();
}

// destructor
WindowManager::~WindowManager() { cleanup(); }