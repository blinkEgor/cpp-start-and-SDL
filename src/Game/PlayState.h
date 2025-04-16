#pragma once

#include "GameState.h"
#include "StartMenuState.h"
#include "Grid.h"
#include "../Entities/Snake.h"
#include "../Entities/Food.h"
#include "../UI/RestartButton.h"
#include "../Utils/Utils.h"

class PlayState : public GameState {
protected:
	WindowManager* window_manager;
    // m_set_next_state_callback доступен через наследование от GameState

private:
	Grid m_grid;
	Snake m_snake;
	Food m_food;
    // RestartButton m_restart_button;

public: 
	PlayState( WindowManager* window_manager, GameState::NextStateCallback set_next_state_callback );
	
    void handle_events( SDL_Event& e );
    void update();
    void render( SDL_Renderer* renderer );
    void enter();
    void exit();
};
