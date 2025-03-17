#pragma once

#include "GameState.h"
#include "../UI/StartMenu.h"
#include "PlayState.h"

class StartMenuState : public GameState {
protected:
	WindowManager* windowManager;

private:
	StartMenu startMenu;

public:
	StartMenuState( WindowManager* windowManager, GameState::StateChangeCallback callback );

	void handleEvents( SDL_Event& e );
    void update();
    void render( SDL_Renderer* renderer );
    void enter();
    void exit();
};