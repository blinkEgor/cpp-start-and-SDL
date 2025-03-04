#pragma once

#include <SDL2/SDL.h>

#include "../Graphics/WindowManager.h"

class GameState {
public:
	virtual void handleEvents( SDL_Event& e ) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual ~GameState() {}
};