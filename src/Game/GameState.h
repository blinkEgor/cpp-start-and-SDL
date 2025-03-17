#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../Graphics/WindowManager.h"
#include "../Utils/LogError.h"

class GameManager; // Предварительное объявление для компилятора

class GameState {
protected:
    GameManager* gameManager;
	WindowManager* windowManager;

public:
	virtual void handleEvents( SDL_Event& e ) = 0;
	virtual void update() = 0;
	virtual void render( SDL_Renderer* renderer ) = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
	virtual ~GameState() {}
};