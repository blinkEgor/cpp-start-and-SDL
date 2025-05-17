#include "WindowManager.h"

// Конструктор: устанавливает заголовок и размеры окна, но не инициализирует SDL.
// Инициализация вынесена в отдельный метод init() для явного контроля над процессом.
WindowManager::WindowManager( const std::string& title, int width, int height ) : 
	m_title( title ), 
	m_screen_width( width ), 
	m_screen_height( height ) 
{}

//  - Инициализирует SDL, окно, рендерер и шрифты.
//  - Важно: порядок вызовов (SDL_Init -> SDL_CreateWindow -> SDL_CreateRenderer) критичен.
//  - Нарушение может привести к утечкам или крашу (см. документацию SDL 2.0).
//  - return false при любой критической ошибке (например, драйверы GPU не поддерживаются).
bool WindowManager::init() {
	// Инициализация SDL_VIDEO обязательна для работы с окнами и рендерером.
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		logError( "SDL could not initialize! SDL_Error: " + std::string( SDL_GetError() ), LogLevel::ERROR );
		return false;
	} else {
		logError( "SDL initialization: successful", LogLevel::INFO );
	}

	// Создание окна в позиции "не определено" — позволяет ОС самой выбрать место, что удобно для кроссплатформенности.
	m_window = SDL_CreateWindow( m_title.c_str(), W_POS_X, W_POS_Y, m_screen_width, m_screen_height, W_FLAGS );
	if( m_window == nullptr ) {
		logError( "Window could not be created! SDL_Error: " + std::string( SDL_GetError() ), LogLevel::ERROR );
		cleanup();
		return false;
	} else {
		logError( "Window initialization: successful", LogLevel::INFO );
	}

	// Ускоренный рендерер (SDL_RENDERER_ACCELERATED) использует GPU, в отличие от программного (SDL_RENDERER_SOFTWARE).
	m_renderer = SDL_CreateRenderer( m_window, D_INDEX, R_FLAGS );
	if( m_renderer == nullptr ) {
		logError( "Renderer could not be created! SDL_Error: " + std::string( SDL_GetError() ), LogLevel::ERROR );
		cleanup();
		return false;
	} else {
		logError( "Renderer initialization: successful", LogLevel::INFO );
	}

	// Инициализация TTF после SDL_Init, так как TTF зависит от SDL подсистем.
	if ( TTF_Init() == -1 ) {
		logError( "TTF initialization error: " + std::string( TTF_GetError() ), LogLevel::ERROR );
		cleanup();
    	return false;
	} else {
		logError( "TTF initialization: successful", LogLevel::INFO );
	}

	// Предзагрузка шрифтов: кратные 8 размеры (8, 16, 32, 64) покрывают большинство сценариев,
    // чтобы избежать задержек при первом обращении к get_font() во время рендеринга.
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

// - Загружает шрифты в память заранее, чтобы избежать задержек во время рендеринга.
// - Размеры кратны 8 (8 → 64) — это стандартные размеры для пиксельных шрифтов.
// - Если шрифт не загружен здесь, get_font() вернет nullptr, что приведет к крашу при рендеринге текста.
bool WindowManager::set_font() {
	const char* path_to_font = "assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf";

	// Умножаем размер шрифта на 2 для покрытия стандартных размеров (8, 16, 32, 64)
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

// Возвращает шрифт указанного размера. Если размер не найден, возвращает nullptr
TTF_Font* WindowManager::get_font( int size ) const {
    auto font = m_font_map.find( size );
    if ( font != m_font_map.end() && font->second != nullptr ) {
        return font->second;
    }
    logError( "Font size " + std::to_string( size ) + " not found or invalid!", LogLevel::ERROR );
    return nullptr;
}

// get window width
int WindowManager::get_screen_width() const { return m_screen_width; }
// get window height
int WindowManager::get_screen_height() const { return m_screen_height; }

// Очищает окно указанным цветом (по умолчанию: черный)
void WindowManager::clear_window( SDL_Color clear_color ) {
	SDL_SetRenderDrawColor( m_renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a );
	SDL_RenderClear( m_renderer );
}

// Очистка выполняется в порядке, обратном инициализации:
// 1. Шрифты -> 2. TTF -> 3. Рендерер -> 4. Окно -> 5. SDL.
// Это предотвращает утечки (например, рендерер должен быть уничтожен до окна).
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