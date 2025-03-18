#include "Grid.h"

Grid::Grid() : 
    m_cell_size( 32 ), 
    m_cell_rows( 16 ),
    m_cell_cols( 24 ), 
    m_grid_border( 16 ), 
    m_grid_rows_size( m_cell_size * m_cell_rows + 2 * m_grid_border ), 
    m_grid_cols_size( m_cell_size * m_cell_cols + 2 * m_grid_border ), 
    m_grid( m_cell_rows, std::vector<int>( m_cell_cols, 0 ) ) 
{}

// Рисует сетку
// Цвет сетки
// Отрисовка вертикальных линий
// Отрисовка горизонтальных линий
void Grid::draw_grid( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 50, 50, 50, 255 ); 
    for ( int x = m_grid_border; x <= m_grid_cols_size + m_cell_size - m_grid_border; x += m_cell_size ) {
        SDL_RenderDrawLine( renderer, x, m_grid_border, x, m_grid_border + m_cell_rows * m_cell_size );
    }
    for ( int y = m_grid_border; y <= m_grid_rows_size + m_cell_size - m_grid_border; y += m_cell_size ) {
        SDL_RenderDrawLine( renderer, m_grid_border, y, m_grid_border + m_cell_cols * m_cell_size, y );
    }
}

// Получаем размер одной клетки в пикселях
int Grid::get_cell_size() const { return m_cell_size; }
// Получаем толщину отступа вокруг сетки в пикселях
int Grid::get_grid_border() const { return m_grid_border; }
// Колическтво клеток по ширине
int Grid::get_cell_rows() const { return m_cell_rows; }
// Количество клеток по высоте
int Grid::get_cell_cols() const { return m_cell_cols; }

Grid::~Grid() {}
