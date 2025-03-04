#include "StartMenuState.h"

StartMenuState::StartMenuState( WindowManager* windowManager, GameManager* gameManager ) : 
    windowManager( windowManager ),
    gameManager( gameManager ),
    startMenu( windowManager->getWidth(), windowManager->getHeight() )
{}

void StartMenuState::handleEvents( SDL_Event& e ) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x, y = e.button.y;
        startMenu.setClick( x, y );
    }
}

void StartMenuState::update() {
    if ( startMenu.getIsClicked() ) {
        // Переход в PlayState
        gameManager->setNextState( std::make_unique<PlayState>( windowManager, gameManager ));
        gameManager->changeState();
    }
}

void StartMenuState::render() {
    windowManager->clearWindow();
    startMenu.draw( windowManager->getRenderer() );
}

void StartMenuState::enter() {
    logError( "Entering StartMenuState" );
}

void StartMenuState::exit() {
    logError( "Exiting StartMenuState" );
}