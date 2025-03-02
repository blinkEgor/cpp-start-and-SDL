#include "Food.h"

Food::Food( Grid* grid ) : 
    grid( grid )
{
    respawnFood();
}

// Устанавливает еду в случайную позицию на сетке.
// - Определяет диапазон возможных координат.
// - Генерирует случайную строку и столбец в пределах сетки.
void Food::respawnFood() {
    row = rand() % grid->getCellRows();
    col = rand() % grid->getCellCols(); 
}

// Отрисовывает еду на сетке.
// - Устанавливает красный цвет для еды.
// - Вычисляет координаты на основе размера клетки и границ сетки.
// - Рисует квадрат, представляющий еду.
void Food::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 ); // Цвет еды: красный
    int grid_border = grid->getGridBorder(), grid_cell_size = grid->getCellSize();
    SDL_Rect rect = { 
        grid_border + col * grid_cell_size, 
        grid_border + row * grid_cell_size, 
        grid_cell_size, grid_cell_size };
    SDL_RenderFillRect( renderer, &rect );
}

// Возвращает строку, в которой расположена еда.
int Food::getFoodRow() const { return row; }

// Возвращает столбец, в котором расположена еда.
int Food::getFoodCol() const { return col; }

Food::~Food() {}