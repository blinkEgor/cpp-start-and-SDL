#pragma once

#include "GameState.h"
#include "StartMenuState.h"
#include "Grid.h"
#include "../Entities/Snake.h"
#include "../Entities/Food.h"
#include "../UI/RestartButton.h"

class PlayState : public GameState {
protected:
	WindowManager* windowManager;

private:
	Grid grid;
	Food food;
	Snake snake;
    RestartButton restartButton;

public: 
	PlayState( WindowManager* windowManager, GameState::StateChangeCallback callback );
	
    void handleEvents( SDL_Event& e );
    void update();
    void render( SDL_Renderer* renderer );
    void enter();
    void exit();
};
