#include "GameManager.h"

GameManager::GameManager( WindowManager* windowManager ) : 
    windowManager( windowManager )
{ // Ставим состояние игры по умолчанию
    setNextState( std::make_unique<StartMenuState>( windowManager, this ) );
    changeState();
}

// Назначаем следующее состояние игры
void GameManager::setNextState( std::unique_ptr<GameState> newState ) {
    nextState = std::move( newState );
}

// Меняем состояние игры
// - Завершаем текущее состояние
// - Инициализируем новое состояние
void GameManager::changeState() {
    if ( nextState ) {
        if ( currentState ) {
            currentState->exit();
        }
        currentState = std::move( nextState );
        currentState->enter();
    }
}

// Получаем текущее состояние игры
GameState* GameManager::getCurrentState() const { return currentState.get(); }
