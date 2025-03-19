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
    using NextStateCallback = std::function< void( std::unique_ptr<GameState> ) >; // Определяем тип коллбэка
	virtual void handle_events( SDL_Event& e ) = 0;
	virtual void update() = 0;
	virtual void render( SDL_Renderer* renderer ) = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
	virtual ~GameState() {}

	// Метод для установки коллбэка
    void set_next_state_callback( NextStateCallback set_next_state_callback ) {
        m_set_next_state_callback = std::move( set_next_state_callback );
    }
	
protected:
    NextStateCallback m_set_next_state_callback; // Коллбэк для установки нового сотояния
};