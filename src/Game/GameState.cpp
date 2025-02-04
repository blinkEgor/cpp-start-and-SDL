#include "GameState.h"
#include "../Entities/Player.h"

Player player;

PlayState::PlayState(WindowManager* windowManager) : windowManager(windowManager) {}

void PlayState::handleEvents( SDL_Event& e ) {
    if( e.type == SDL_KEYDOWN ) {	// Checking whether a key is pressed
        switch ( e.key.keysym.sym ) {
        case SDLK_w: player.move_up(); break;
        case SDLK_s: player.move_down(); break;
        case SDLK_a: player.move_left(); break;
        case SDLK_d: player.move_right(); break;
        
        default: break;
        }
    }
}

void PlayState::update() {}

void PlayState::render() {
    windowManager->clearWindow();
    player.draw( windowManager->getRenderer() );
}