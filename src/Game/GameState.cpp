#include "GameState.h"

// __ PlayState ____________________________________________________________
PlayState::PlayState( WindowManager* windowManager ) : 
    windowManager( windowManager ),
    grid(),
    snake( &grid, &food, 5, 5 ),
    food( &grid )
{}

void PlayState::handleEvents( SDL_Event& e ) {
    if (e.type == SDL_KEYDOWN) { // Ловим нажатие
        switch (e.key.keysym.sym) {
            case SDLK_w: snake.setDirection(0, -1); break;
            case SDLK_s: snake.setDirection(0, 1);  break;
            case SDLK_a: snake.setDirection(-1, 0); break;
            case SDLK_d: snake.setDirection(1, 0);  break;
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

// __ StartMenuState _______________________________________________________
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