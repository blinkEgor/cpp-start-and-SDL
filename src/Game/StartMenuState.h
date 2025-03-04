#pragma once

#include "GameState.h"

#include "../UI/StartMenu.h"

class StartMenuState : public GameState {
private:
	WindowManager* windowManager;
	StartMenu startMenu;

public:
	StartMenuState( WindowManager* windowManager );

	void handleEvents( SDL_Event& e );
    void update();
    void render();
};