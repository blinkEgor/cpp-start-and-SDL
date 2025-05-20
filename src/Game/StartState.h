#pragma once

#include "GameState.h"
#include "../UI/StartMenu.h"
#include "PlayState.h"

class StartState : public GameState {
protected:
	WindowManager* window_manager;
    // m_set_next_state_callback доступен через наследование от GameState

private:
	StartMenu m_start_menu;

public:
	StartState( WindowManager* window_manager, GameState::NextStateCallback set_next_state_callback );

	void handle_events( SDL_Event& e );
    void update();
    void render( SDL_Renderer* renderer );
    void enter();
    void exit();
};