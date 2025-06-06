#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include "../Utils/LogError.h"

class WindowManager {
private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	std::map< int, TTF_Font* > m_font_map;

	const int W_POS_X = SDL_WINDOWPOS_UNDEFINED; // Константа для позиции окна по X
	const int W_POS_Y = SDL_WINDOWPOS_UNDEFINED; // Константа для позиции окна по Y
	const int D_INDEX = -1; // Индекс драйвера рендерера
	const Uint32 R_FLAGS = SDL_RENDERER_ACCELERATED; // Флаги рендерера
	const Uint32 W_FLAGS = SDL_WINDOW_SHOWN; // Флаги рендерера
	
	std::string m_title;
	int m_screen_width;
	int m_screen_height;

public:
	WindowManager( const std::string& title = "SDL Window", int width = 640, int height = 480 );
	
	bool init();
	SDL_Window* get_window() const;
	SDL_Renderer* get_renderer() const;
	bool set_font();
	TTF_Font* get_font( int size = 8 ) const;
	int get_screen_width() const;
	int get_screen_height() const;
	void clear_window( SDL_Color clear_color = { 0, 0, 0, 255 } );
	void cleanup();

	// Деструктор
	~WindowManager();
};