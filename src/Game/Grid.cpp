#include "Grid.h"

Grid::Grid() : 
    cell_size( 32 ), 
    cell_rows( 16 ),
    cell_cols( 24 ), 
    grid_border( 16 ), 
    grid_rows_size( cell_size * cell_rows + 2 * grid_border ), 
    grid_cols_size( cell_size * cell_cols + 2 * grid_border ), 
    grid( cell_rows, std::vector<int>( cell_cols, 0 ) ) {}

// Рисует сетку
// Цвет сетки
// Отрисовка вертикальных линий
// Отрисовка горизонтальных линий
void Grid::drawGrid( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 ); 
    for ( int x = grid_border; x <= grid_cols_size + cell_size - grid_border; x += cell_size ) {
        SDL_RenderDrawLine(renderer, x, grid_border, x, grid_border + cell_rows * cell_size);
    }
    for ( int y = grid_border; y <= grid_rows_size + cell_size - grid_border; y += cell_size ) {
        SDL_RenderDrawLine(renderer, grid_border, y, grid_border + cell_cols * cell_size, y);
    }
}

int Grid::getCellSize() const { return cell_size; }

int Grid::getGridBorder() const { return grid_border; }

int Grid::getCellRows() const { return cell_rows; }

int Grid::getCellCols() const { return cell_cols; }

Grid::~Grid() {}
