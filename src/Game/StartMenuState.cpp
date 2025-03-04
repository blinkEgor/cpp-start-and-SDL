#include "StartMenuState.h"

StartMenuState::StartMenuState( WindowManager* windowManager ) : 
    windowManager( windowManager ),
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
        
    }
}

void StartMenuState::render() {
    windowManager->clearWindow();
    startMenu.draw( windowManager->getRenderer() );
}