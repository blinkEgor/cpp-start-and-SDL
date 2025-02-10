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
    } else if ( e.type == SDL_KEYUP ) {
        switch ( e.key.keysym.sym ) {
        case SDLK_w:
        case SDLK_s: player.update_velocity_y(); break; // reset value
        case SDLK_a:
        case SDLK_d: player.update_velocity_x(); break; // reset value
        
        default: break;
        }
    }
}

void PlayState::update() {
    player.move( windowManager->getWidth(), windowManager->getHeight() );
}

void PlayState::render() {
    windowManager->clearWindow();
    player.draw( windowManager->getRenderer() );
}
