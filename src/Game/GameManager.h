#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../Graphics/WindowManager.h"
#include "GameState.h"
#include "StartMenuState.h"
#include "PlayState.h"

class GameManager {
private:
    WindowManager* windowManager;
    std::unique_ptr<GameState> currentState = nullptr;
    std::unique_ptr<GameState> nextState = nullptr;

public:
    GameManager( WindowManager* windowManager );

    void gameLoop();
    void setNextState( std::unique_ptr<GameState> nextState );
    void changeState();

    GameState* getCurrentState() const;
};