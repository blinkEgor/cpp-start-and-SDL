#include "GameState.h"

PlayState::PlayState( WindowManager* windowManager ) : 
    windowManager(windowManager),
    grid(),
    snake( &grid, &food, 5, 5 ),
    food( &grid )
{}

void PlayState::handleEvents( SDL_Event& e ) {
    if (e.type == SDL_KEYDOWN) { // Теперь ловим нажатие (а не отпускание)
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
