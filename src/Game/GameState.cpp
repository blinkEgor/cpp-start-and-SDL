#include "GameState.h"

PlayState::PlayState(WindowManager* windowManager) : windowManager(windowManager) {}

void PlayState::handleEvents( SDL_Event& e ) {

}

void PlayState::update() {

}

void PlayState::render() {
    windowManager->clearWindow();
    
}
