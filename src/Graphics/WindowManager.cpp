#include "WindowManager.h"

// constructor
WindowManager::WindowManager( const std::string& title, int width, int height ) : 
	m_title( title ), 
	m_screen_width( width ), 
	m_screen_height( height ) 
{}

// initialize SQL 
// initialize Window
// initialize Renderer
bool WindowManager::init() {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		logError( "SDL could not initialize! SDL_Error: " + std::string( SDL_GetError() ), LogLevel::ERROR );
		return false;
	} else {
		logError( "SDL initialization: successful", LogLevel::INFO );
	}

	m_window = SDL_CreateWindow( m_title.c_str(), W_POS_X, W_POS_Y, m_screen_width, m_screen_height, W_FLAGS );
	if( m_window == nullptr ) {
		logError( "Window could not be created! SDL_Error: " + std::string( SDL_GetError() ), LogLevel::ERROR );
		cleanup();
		return false;
	} else {
		logError( "Window initialization: successful", LogLevel::INFO );
	}

	m_renderer = SDL_CreateRenderer( m_window, D_INDEX, R_FLAGS );
	if( m_renderer == nullptr ) {
		logError( "Renderer could not be created! SDL_Error: " + std::string( SDL_GetError() ), LogLevel::ERROR );
		cleanup();
		return false;
	} else {
		logError( "Renderer initialization: successful", LogLevel::INFO );
	}

	if ( TTF_Init() == -1 ) {
		logError( "TTF initialization error: " + std::string( TTF_GetError() ), LogLevel::ERROR );
    	return false;
	} else {
		logError( "TTF initialization: successful", LogLevel::INFO );
	}

	m_font = TTF_OpenFont( "assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf", 24 );
	if ( !m_font ) {
		logError( "Error loading font: " + std::string( TTF_GetError() ), LogLevel::ERROR );
		cleanup();
		return false;
	} else {
		logError( "Font loading: successful", LogLevel::INFO );
	}

	return true;
}

// get window
SDL_Window* WindowManager::get_window() const { return m_window; }
// get renderer
SDL_Renderer* WindowManager::get_renderer() const { return m_renderer; }
// get window width
int WindowManager::get_screen_width() const { return m_screen_width; }
// get window height
int WindowManager::get_screen_height() const { return m_screen_height; }

// set color for clear window
void WindowManager::set_color( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha ) {
	m_r = red; m_g = green; m_b = blue; m_a = alpha;
}

// clear window
void WindowManager::clear_window() {
	SDL_SetRenderDrawColor( m_renderer, m_r, m_g, m_b, m_a ); // set color
	SDL_RenderClear( m_renderer );
}

// clean up all for close program
void WindowManager::cleanup() {
    if ( m_font != nullptr ) {
        TTF_CloseFont( m_font );
        m_font = nullptr;
        logError( "Font successfully closed", LogLevel::INFO );
    }

    TTF_Quit();
    logError( "TTF successfully quit", LogLevel::INFO );

	if( m_renderer != nullptr ) {
		SDL_DestroyRenderer( m_renderer );
		m_renderer = nullptr;
		logError( "Renderer successfully destroyed", LogLevel::INFO );
	} else {
        logError( "Renderer was already null", LogLevel::WARNING );
    }

	if( m_window != nullptr ) {
		SDL_DestroyWindow( m_window );
		m_window = nullptr;
		logError( "Window successfully destroyed", LogLevel::INFO );
	} else {
        logError( "Window was already null", LogLevel::WARNING );
    }

	SDL_Quit();
	logError( "SDL successfully quit\n", LogLevel::INFO );
}

// destructor
WindowManager::~WindowManager() { cleanup(); }