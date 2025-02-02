#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include "WindowManager.h"

class GameState {
	public:
		virtual void handleEvents( SDL_Event& e ) = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual ~GameState() {}
};

class PlayState : public GameState {
	private:
		WindowManager* windowManager;
	public: 
	PlayState(WindowManager* windowManager);
	
    void handleEvents( SDL_Event& e );
    void update();
    void render();
};