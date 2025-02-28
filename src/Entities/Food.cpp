#include "Food.h"

Food::Food( Grid* grid ) : 
    grid( grid )
{
    respawnFood();
}

void Food::respawnFood() {
    int start = 1;
    int end_row = grid->getCellRows(), end_col = grid->getCellCols();
    row = rand() % (end_row - start + 1) + start;
    col = rand() % (end_col - start + 1) + start;
}

void Food::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 ); // Цвет еды: красный
    SDL_Rect rect = { 
        grid->getGridBorder() + col * grid->getCellSize(), 
        grid->getGridBorder() + row * grid->getCellSize(), 
        grid->getCellSize(), grid->getCellSize() };
    SDL_RenderFillRect( renderer, &rect );
}

Food::~Food() {}