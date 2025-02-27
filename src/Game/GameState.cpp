#include "GameState.h"

PlayState::PlayState( WindowManager* windowManager ) : 
    windowManager(windowManager),
    grid(),
    head() {}

void PlayState::handleEvents( SDL_Event& e ) {
    // if( e.type == SDL_KEYDOWN ) {
    //     switch ( e.key.keysym.sym ) {
    //     case SDLK_g: grid.printGrid(); break;

    //     default: break;
    //     }
    // }
}

void PlayState::update() {

}

void PlayState::render() {
    windowManager->clearWindow();
    grid.drawGrid( windowManager->getRenderer() );
    head.draw( windowManager->getRenderer() );
}
