#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "../Graphics/WindowManager.h"
#include "GameState.h"

class GameManager {
private:
    WindowManager* windowManager;
    std::unique_ptr<GameState> currentState = nullptr;
    std::unique_ptr<GameState> nextState = nullptr;

    std::unique_ptr<GameState> playState;
public:
    GameManager(WindowManager* windowManager);
    void setNextState( std::unique_ptr<GameState> nextState );
    void changeState();

    PlayState* getPlayState() const;
    GameState* getCurrentState() const;
};