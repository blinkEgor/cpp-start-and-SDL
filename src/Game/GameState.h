#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <functional> // Для std::function

#include "../Graphics/WindowManager.h"
#include "../Utils/LogError.h"

// class GameManager; // Предварительное объявление для компилятора

class GameState {
protected:
    // GameManager* gameManager;
	WindowManager* windowManager;

public:
    using StateChangeCallback = std::function< void( std::unique_ptr<GameState> ) >; // Определяем тип коллбэка
	virtual void handleEvents( SDL_Event& e ) = 0;
	virtual void update() = 0;
	virtual void render( SDL_Renderer* renderer ) = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
	virtual ~GameState() {}

	// Метод для установки коллбэка
    void setStateChangeCallback( StateChangeCallback callback ) {
        stateChangeCallback = std::move( callback );
    }
	
protected:
    StateChangeCallback stateChangeCallback; // Коллбэк для смены состояния
};