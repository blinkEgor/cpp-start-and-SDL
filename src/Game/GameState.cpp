#include "GameState.h"

PlayState::PlayState(WindowManager* windowManager) : windowManager(windowManager), grid() {}

void PlayState::handleEvents( SDL_Event& e ) {

}

void PlayState::update() {

}

void PlayState::render() {
    windowManager->clearWindow();
    grid.drawGrid( windowManager->getRenderer() );
}
