#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "../Graphics/WindowManager.h"
#include "Grid.h"
#include "../Entities/Snake.h"
#include "../Entities/Food.h"

class GameState {
public:
	virtual void handleEvents( SDL_Event& e ) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual ~GameState() {}
};

// __ PlayState ____________________________________________________________
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

// __ StartMenuState _______________________________________________________
class StartMenuState : public GameState {
private:
	WindowManager* windowManager;

public:
	StartMenuState( WindowManager* windowManager );

	void handleEvents( SDL_Event& e );
    void update();
    void render();
};