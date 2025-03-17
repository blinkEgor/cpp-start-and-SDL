#pragma once

#include "GameState.h"
#include "GameManager.h"

#include "Grid.h"
#include "../Entities/Snake.h"
#include "../Entities/Food.h"
#include "../UI/RestartButton.h"

class PlayState : public GameState {
protected:
	WindowManager* windowManager;
    GameManager* gameManager;

private:
	Grid grid;
	Snake snake;
	Food food;
    RestartButton restartButton;

public: 
	PlayState( WindowManager* windowManager, GameManager* gameManager );
	
    void handleEvents( SDL_Event& e );
    void update();
    void render( SDL_Renderer* renderer );
    void enter();
    void exit();
};
