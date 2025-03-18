#pragma once

#include "GameState.h"
#include "../UI/StartMenu.h"
#include "PlayState.h"

class StartMenuState : public GameState {
protected:
	WindowManager* window_manager;

private:
	StartMenu m_start_menu;

public:
	StartMenuState( WindowManager* window_manager, GameState::StateChangeCallback callback );

	void handle_events( SDL_Event& e );
    void update();
    void render( SDL_Renderer* renderer );
    void enter();
    void exit();
};