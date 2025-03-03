#include "GameManager.h"

GameManager::GameManager( WindowManager* windowManager ) : 
    windowManager( windowManager ),
    playState( std::make_unique<PlayState>( windowManager ) )
{}

void GameManager::setNextState( std::unique_ptr<GameState> newState ) {
    nextState = std::move( newState );
}

void GameManager::changeState() {
    if ( nextState ) {
        currentState = std::move( nextState );
    }
}

GameState* GameManager::getCurrentState() const { return currentState.get(); }
