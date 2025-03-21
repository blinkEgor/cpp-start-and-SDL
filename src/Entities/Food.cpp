#include "Food.h"

Food::Food( std::pair< int, int > start_position ) {
    m_position = start_position;
}

// Устанавливает еду в случайную позицию на сетке.
// - Определяет диапазон возможных координат.
// - Генерирует случайную строку и столбец в пределах сетки.
void Food::respawn_food( std::vector< std::vector< std::pair< int, int >>>& grid_field, std::deque< std::pair< int, int >>& snake_segments ) {
    std::pair< int, int > max_value = { 
        static_cast< int >( grid_field.size() ), 
        static_cast< int >( grid_field[ 0 ].size() ) 
    };
    std::pair< int, int > new_position;
    bool position_valid = false;
    
    do {
        new_position = get_rund_pair( { 0, 0 }, max_value );
        position_valid = std::find( snake_segments.begin(), snake_segments.end(), new_position ) == snake_segments.end();
    } while ( !position_valid );

    m_position = new_position;
}

// Отрисовывает еду на сетке.
// - Устанавливает красный цвет для еды.
// - Вычисляет координаты на основе размера клетки и границ сетки.
// - Рисует квадрат, представляющий еду.
void Food::draw( SDL_Renderer* renderer, int grid_cell_size, int grid_border ) {
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 ); // Цвет еды: красный
    SDL_Rect rect = { 
        m_position.second * grid_cell_size + grid_border, 
        m_position.first * grid_cell_size + grid_border, 
        grid_cell_size, grid_cell_size 
    };

    SDL_RenderFillRect( renderer, &rect );
}

std::pair< int, int > Food::get_food_position() const { return m_position; }

Food::~Food() {}