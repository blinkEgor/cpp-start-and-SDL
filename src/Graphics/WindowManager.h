#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "../Utils/LogError.h"

class WindowManager {
private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	TTF_Font* m_font = nullptr;

	const int W_POS_X = SDL_WINDOWPOS_UNDEFINED; // Константа для позиции окна по X
	const int W_POS_Y = SDL_WINDOWPOS_UNDEFINED; // Константа для позиции окна по Y
	const int D_INDEX = -1; // Индекс драйвера рендерера
	const Uint32 R_FLAGS = SDL_RENDERER_ACCELERATED; // Флаги рендерера
	const Uint32 W_FLAGS = SDL_WINDOW_SHOWN; // Флаги рендерера
	
	std::string m_title;
	int m_screen_width;
	int m_screen_height;
	Uint8 m_r = 0, m_g = 0, m_b = 0, m_a = 255; // Цвет фона (чёрный)

public:
	// Конструктор
	WindowManager( const std::string& title = "SDL Window", int width = 640, int height = 480 );
	
	// Методы
	bool init();
	SDL_Window* get_window() const;
	SDL_Renderer* get_renderer() const;
	int get_screen_width() const;
	int get_screen_height() const;
	void set_color( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255 );
	void clear_window();
	void cleanup();

	// Деструктор
	~WindowManager();
};