#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

class WindowManager {
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		const int W_POS_X = SDL_WINDOWPOS_UNDEFINED; // Константа для позиции окна по X
		const int W_POS_Y = SDL_WINDOWPOS_UNDEFINED; // Константа для позиции окна по Y
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		int D_INDEX = -1; // Индекс драйвера рендерера
		std::string title;
		Uint8 r = 0, g = 0, b = 0, a = 255; // Цвет фона (чёрный)
		const Uint32 R_FLAGS = SDL_RENDERER_ACCELERATED; // Флаги рендерера
		const Uint32 W_FLAGS = SDL_WINDOW_SHOWN; // Флаги рендерера
	
	public:
	// Конструктор
	WindowManager(const std::string& title = "SDL Window", int width = 640, int height = 480);
	
	// Методы
	bool init();
	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;
	int getWidth() const;
	int getHeight() const;
	void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);
	void clearWindow();
	void cleanup();

	// Деструктор
	~WindowManager();
};