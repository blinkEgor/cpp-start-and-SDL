#include "Grid.h"

Grid::Grid() : 
    m_cell_size( 32 ), 
    m_cell_rows( 16 ),
    m_cell_cols( 24 ), 
    m_grid_border( 16 ), 
    m_grid_rows_size( m_cell_size * m_cell_rows + 2 * m_grid_border ), 
    m_grid_cols_size( m_cell_size * m_cell_cols + 2 * m_grid_border )
{
    m_grid_field.resize( m_cell_rows, std::vector< std::pair< int, int >>( m_cell_cols ) );

    for ( int r = 0; r < m_cell_rows; ++r ) {
        for ( int c = 0; c < m_cell_cols; ++c ) {
            m_grid_field[ r ][ c ] = std::make_pair( m_grid_border + m_cell_size * c, m_grid_border + m_cell_size * r );
        }
    }
}

// Рисует сетку
// Цвет сетки
// Отрисовка вертикальных линий
// Отрисовка горизонтальных линий
void Grid::draw_grid( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 
        Palette::GRID_LINE_GREY.r, 
        Palette::GRID_LINE_GREY.g, 
        Palette::GRID_LINE_GREY.b, 
        Palette::GRID_LINE_GREY.a 
    ); 
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
// Колическтво клеток по высоте
int Grid::get_cell_rows() const { return m_cell_rows; }
// Количество клеток по ширине
int Grid::get_cell_cols() const { return m_cell_cols; }
// Ссылка на двумерный вектор с парами значений координат Y, X
std::vector< std::vector< std::pair< int, int >>>& Grid::get_grid_field() { return m_grid_field; }

Grid::~Grid() {}
