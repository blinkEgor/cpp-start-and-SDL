#include "GameState.h"

PlayState::PlayState( WindowManager* windowManager ) : 
    windowManager(windowManager),
    grid(),
    head() 
{
    int index_col_of_cell = 2;
    int index_row_of_cell = 5;
    head.setPosition( grid.getCellSize() * index_col_of_cell, grid.getCellSize() * index_row_of_cell, grid.getGridBorder() );
    head.setSize( grid.getCellSize(), grid.getCellSize() );
}

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
