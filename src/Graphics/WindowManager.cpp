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
		cleanup();
    	return false;
	} else {
		logError( "TTF initialization: successful", LogLevel::INFO );
	}

	if ( !set_font() ) {
		cleanup();
		return false;
	}

	return true;
}

// get window
SDL_Window* WindowManager::get_window() const { return m_window; }
// get renderer
SDL_Renderer* WindowManager::get_renderer() const { return m_renderer; }

// Create a font map and init font with checking errors
bool WindowManager::set_font() {
	const char* path_to_font = "assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf";
	for ( int size = 8, max_size = 64; size <= max_size; size*=2 ) {
		m_font_map[ size ] = TTF_OpenFont( path_to_font, size );

		if ( !m_font_map[ size ] ) {
			logError( "Error loading font " + std::to_string( size ) + " : " + std::string( TTF_GetError() ), LogLevel::ERROR );
			return false;
		} else {
			logError( "Font " + std::to_string( size ) + " loading: successful", LogLevel::INFO );
		}
	}
	return true;
}

// get font 
TTF_Font* WindowManager::get_font( int size ) const {
    auto font = m_font_map.find( size );
    if ( font != m_font_map.end() && font->second != nullptr ) {
        return font->second;
    }
    logError( "Font size " + std::to_string( size ) + " not found or invalid!", LogLevel::ERROR );
    return nullptr; // выбросить исключение
}

// get window width
int WindowManager::get_screen_width() const { return m_screen_width; }
// get window height
int WindowManager::get_screen_height() const { return m_screen_height; }

// clear window
void WindowManager::clear_window( SDL_Color clear_color ) {
	SDL_SetRenderDrawColor( m_renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a ); // set color
	SDL_RenderClear( m_renderer );
}

// clean up all for close program
void WindowManager::cleanup() {
    // Закрыть все шрифты в карте
    for ( auto& font : m_font_map ) {
        if ( font.second != nullptr ) {
            TTF_CloseFont( font.second );
            font.second = nullptr;
			logError( "Font " + std::to_string( font.first ) + " cleaned up", LogLevel::INFO );
        } else {
			logError( "Font " + std::to_string( font.first ) + " was already nullptr", LogLevel::WARNING );
		}
    }
    m_font_map.clear();


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