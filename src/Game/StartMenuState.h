#pragma once

#include "GameState.h"
#include "GameManager.h"

#include "../UI/StartMenu.h"

class StartMenuState : public GameState {
protected:
    GameManager* gameManager;
	WindowManager* windowManager;

private:
	StartMenu startMenu;

public:
	StartMenuState( WindowManager* windowManager, GameManager* gameManager );

	void handleEvents( SDL_Event& e );
    void update();
    void render();
    void enter();
    void exit();
};