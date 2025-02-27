#include "Grid.h"

Grid::Grid( int cellSize, int cellCount ) : 
    cell_size(cellSize), cell_count(cellCount), grid_size(cellSize * cellCount),
    grid( cell_count, std::vector<int>( cell_count, 0 ) ) {}

void Grid::drawGrid( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 ); // Цвет сетки

    // Отрисовка вертикальных линий
    for (int x = 0; x <= grid_size; x += cell_size) {
        SDL_RenderDrawLine( renderer, x, 0, x, grid_size );
    }

    // Отрисовка горизонтальных линий
    for (int y = 0; y <= grid_size; y += cell_size) {
        SDL_RenderDrawLine( renderer, 0, y, grid_size, y );
    }
}

Grid::~Grid() {}
