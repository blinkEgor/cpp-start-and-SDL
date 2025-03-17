#pragma once

#include "GameState.h"
#include "GameManager.h"

#include "../UI/StartMenu.h"

class StartMenuState : public GameState {
protected:
	WindowManager* windowManager;
    GameManager* gameManager;

private:
	StartMenu startMenu;

public:
	StartMenuState( WindowManager* windowManager, GameManager* gameManager );

	void handleEvents( SDL_Event& e );
    void update();
    void render( SDL_Renderer* renderer );
    void enter();
    void exit();
};