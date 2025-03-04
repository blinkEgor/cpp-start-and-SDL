#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../Graphics/WindowManager.h"

#include "GameState.h"
#include "PlayState.h"
#include "StartMenuState.h"

class GameManager {
private:
    WindowManager* windowManager;
    std::unique_ptr<GameState> currentState = nullptr;
    std::unique_ptr<GameState> nextState = nullptr;

    std::unique_ptr<PlayState> playState;
    std::unique_ptr<StartMenuState> startMenuState;

public:
    GameManager( WindowManager* windowManager );
    void setNextState( std::unique_ptr<GameState> nextState );
    void changeState();

    GameState* getCurrentState() const;
};