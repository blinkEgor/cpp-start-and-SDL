#pragma once

#include "GameState.h"
#include "StartMenuState.h"
#include "Grid.h"
#include "../Entities/Snake.h"
#include "../Entities/Food.h"
#include "../UI/RestartButton.h"

class PlayState : public GameState {
protected:
	WindowManager* window_manager;

private:
	Grid m_grid;
	Food m_food;
	Snake m_snake;
    RestartButton m_restart_button;

public: 
	PlayState( WindowManager* window_manager, GameState::StateChangeCallback callback );
	
    void handle_events( SDL_Event& e );
    void update();
    void render( SDL_Renderer* renderer );
    void enter();
    void exit();
};
