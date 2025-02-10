#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "../Graphics/WindowManager.h"
#include "../Entities/Player.h"

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
	enum { UP = -1, DOWN = 1, LEFT = -1, RIGHT = 1, };
	Player player;
public: 
	PlayState(WindowManager* windowManager);
	
    void handleEvents( SDL_Event& e );
    void update();
    void render();
};