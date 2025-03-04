#include "PlayState.h"

PlayState::PlayState( WindowManager* windowManager, GameManager* gameManager ) : 
    windowManager( windowManager ),
    gameManager( gameManager ),
    grid(),
    snake( &grid, &food, 5, 5 ),
    food( &grid )
{}

void PlayState::handleEvents( SDL_Event& e ) {
    if ( e.type == SDL_KEYDOWN ) {
        switch ( e.key.keysym.sym ) {
            case SDLK_w: snake.setDirection( 0, -1 ); break;
            case SDLK_s: snake.setDirection( 0, 1 );  break;
            case SDLK_a: snake.setDirection( -1, 0 ); break;
            case SDLK_d: snake.setDirection( 1, 0 );  break;
        }
    }
}

void PlayState::update() {
    snake.move();
    snake.grow();
}

void PlayState::render() {
    windowManager->clearWindow();
    grid.drawGrid( windowManager->getRenderer() );
    food.draw( windowManager->getRenderer() );
    snake.draw( windowManager->getRenderer() );
}

void PlayState::enter() {
    logError( "Entering PlayState" );
}

void PlayState::exit() {
    logError( "Exiting PlayState" );
}