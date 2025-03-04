#include "GameManager.h"

GameManager::GameManager( WindowManager* windowManager ) : 
    windowManager( windowManager )
    // playState( std::make_unique<PlayState>( windowManager ) )
{
    setNextState( std::make_unique<StartMenuState>( windowManager, this ) );
    changeState();
}

void GameManager::setNextState( std::unique_ptr<GameState> newState ) {
    nextState = std::move( newState );
}

void GameManager::changeState() {
    if ( nextState ) {
        if ( currentState ) {
            currentState->exit(); // Завершаем текущее состояние
        }
        currentState = std::move( nextState );
        currentState->enter(); // Инициализируем новое состояние
    }
}

GameState* GameManager::getCurrentState() const { return currentState.get(); }
