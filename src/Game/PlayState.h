#pragma once

#include "GameState.h"

#include "Grid.h"
#include "../Entities/Snake.h"
#include "../Entities/Food.h"

class PlayState : public GameState {
private:
	WindowManager* windowManager;
	Grid grid;
	Snake snake;
	Food food;

public: 
	PlayState( WindowManager* windowManager );
	
    void handleEvents( SDL_Event& e );
    void update();
    void render();
};
