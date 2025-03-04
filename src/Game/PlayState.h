#pragma once

#include "GameState.h"
#include "GameManager.h"

#include "Grid.h"
#include "../Entities/Snake.h"
#include "../Entities/Food.h"

class PlayState : public GameState {
protected:
    GameManager* gameManager; // Указатель на GameManager
	WindowManager* windowManager;

private:
	Grid grid;
	Snake snake;
	Food food;

public: 
	PlayState( WindowManager* windowManager, GameManager* gameManager );
	
    void handleEvents( SDL_Event& e );
    void update();
    void render();
    void enter();
    void exit();
};
