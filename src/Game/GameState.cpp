#include "GameState.h"
#include "../Entities/Player.h"

PlayState::PlayState(WindowManager* windowManager) : windowManager(windowManager) {}

void PlayState::handleEvents( SDL_Event& e ) {
    if( e.type == SDL_KEYDOWN ) {	// Checking whether a key is pressed
        // switch ( e.key.keysym.sym ) {
        // case SDLK_c: windowManager->setColor( 0, 0, 0 ); break;
        // case SDLK_r: windowManager->setColor( 255, 0, 0 ); break;
        // case SDLK_g: windowManager->setColor( 0, 255, 0 ); break;
        // case SDLK_b: windowManager->setColor( 0, 0, 255 ); break;

        // Эта механика была тестовая, для понимания работы заливки окна
        // и сейча она не нужна, поэтому метод тоже удалил. 
        // Оставил в комментарии для образка, как использовать ивенты.
        
        // default: break;
        // }
    }
}

void PlayState::update() {}

void PlayState::render() {
    Player player;
    windowManager->clearWindow();
    player.draw( windowManager->getRenderer() );
}