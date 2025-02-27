#include "Grid.h"

Grid::Grid( int cell_size, int cell_count, int grid_border ) : 
    cell_size( cell_size ), cell_count( cell_count ), grid_border( grid_border ), 
    grid_size( cell_size * cell_count + 2 * grid_border ), 
    grid( cell_count, std::vector<int>( cell_count, 0 ) ) {}

void Grid::drawGrid( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 ); // Цвет сетки

    // Отрисовка вертикальных линий
    for (int x = grid_border; x <= grid_size - grid_border; x += cell_size) {
        SDL_RenderDrawLine( renderer, x, grid_border, x, grid_size - grid_border );
    }

    // Отрисовка горизонтальных линий
    for (int y = grid_border; y <= grid_size - grid_border; y += cell_size) {
        SDL_RenderDrawLine( renderer, grid_border, y, grid_size - grid_border, y );
    }
}

Grid::~Grid() {}
