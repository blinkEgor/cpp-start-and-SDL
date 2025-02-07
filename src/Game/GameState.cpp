#include "GameState.h"

PlayState::PlayState(WindowManager* windowManager) : windowManager(windowManager) {}

void PlayState::handleEvents( SDL_Event& e ) {
    if( e.type == SDL_KEYDOWN ) {	// Checking whether a key is pressed
        switch ( e.key.keysym.sym ) {
        case SDLK_w: player.update_velocity_y( UP ); break; // move up
        case SDLK_s: player.update_velocity_y( DOWN ); break; // move down
        case SDLK_a: player.update_velocity_x( LEFT ); break; // move left
        case SDLK_d: player.update_velocity_x( RIGHT ); break; // move right
        
        default: break;
        }
    }
}

void PlayState::update() {
    player.move();
    player.update_velocity_x(); // reset value
    player.update_velocity_y(); // reset value
}

void PlayState::render() {
    windowManager->clearWindow();
    player.draw( windowManager->getRenderer() );
}