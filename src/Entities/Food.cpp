#include "Food.h"

Food::Food( Grid* grid ) : 
    m_grid( grid )
{
    respawn_food();
}

// Устанавливает еду в случайную позицию на сетке.
// - Определяет диапазон возможных координат.
// - Генерирует случайную строку и столбец в пределах сетки.
void Food::respawn_food() {
    m_row = rand() % m_grid->get_cell_rows();
    m_col = rand() % m_grid->get_cell_cols(); 
}

// Отрисовывает еду на сетке.
// - Устанавливает красный цвет для еды.
// - Вычисляет координаты на основе размера клетки и границ сетки.
// - Рисует квадрат, представляющий еду.
void Food::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 ); // Цвет еды: красный
    const int grid_border = m_grid->get_grid_border();
    const int grid_cell_size = m_grid->get_cell_size();
    SDL_Rect rect = { 
        grid_border + m_col * grid_cell_size, 
        grid_border + m_row * grid_cell_size, 
        grid_cell_size, grid_cell_size };
    SDL_RenderFillRect( renderer, &rect );
}

// Возвращает строку, в которой расположена еда.
int Food::get_food_row() const { return m_row; }

// Возвращает столбец, в котором расположена еда.
int Food::get_food_col() const { return m_col; }

Food::~Food() {}