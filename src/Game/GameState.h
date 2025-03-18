#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <functional> // Для std::function

#include "../Graphics/WindowManager.h"
#include "../Utils/LogError.h"

class GameState {
protected:
	WindowManager* window_manager;

public:
    using StateChangeCallback = std::function< void( std::unique_ptr<GameState> ) >; // Определяем тип коллбэка
	virtual void handle_events( SDL_Event& e ) = 0;
	virtual void update() = 0;
	virtual void render( SDL_Renderer* renderer ) = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
	virtual ~GameState() {}

	// Метод для установки коллбэка
    void set_state_change_callback( StateChangeCallback callback ) {
        state_change_callback = std::move( callback );
    }
	
protected:
    StateChangeCallback state_change_callback; // Коллбэк для смены состояния
};