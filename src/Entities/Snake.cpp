#include "Snake.h"

Snake::Snake( Grid* grid, Food* food, int start_row, int start_col ) : 
    m_grid( grid ), 
    m_food( food ), 
    m_last_move_time( 0 ), 
    m_move_delay( 200 ), 
    m_direction_x( 0 ), 
    m_direction_y( 0 ),
    is_eating( false ),
    is_alive( true )
{
    m_segments.push_back( { start_row, start_col } );
}

// Перемещает змейку в текущем направлении через заданные интервалы времени (moveDelay).
// - Проверяет, прошло ли достаточно времени с последнего перемещения.
// - Вычисляет новую позицию головы, учитывая переход через границы сетки.
// - Обновляет положение змейки, добавляя новую голову и удаляя хвост.
void Snake::move() {
    Uint32 current_time = SDL_GetTicks();
    if ( current_time - m_last_move_time < m_move_delay ) return;
    m_last_move_time = current_time;

    int rows = m_grid->get_cell_rows();
    int cols = m_grid->get_cell_cols();

    int new_row = ( m_segments.front().first + m_direction_y + rows ) % rows;
    int new_col = ( m_segments.front().second + m_direction_x + cols ) % cols;

    m_segments.push_front({ new_row, new_col });
    if ( !is_eating ) m_segments.pop_back();
    is_eating = false;
}

// Проверяет, находится ли голова змейки на позиции еды ( съела ли змейка еду ).
// - Если змейка достигла позиции еды, активирует is_eating и вызывает respawnFood() ( Перемещает еду в новую случайную позицию )
// - Флаг is_eating сообщит move(), что не нужно убирать хвост после следующего движения
void Snake::grow() {
    if ( m_segments.front().first == m_food->get_food_row() && m_segments.front().second == m_food->get_food_col() ) {
        is_eating = true;
        m_food->respawn_food();
    }
}

// Отрисовывает змейку на экране, заполняя её сегменты зелёным цветом.
// - Устанавливает цвет рисования (зелёный).
// - Кэширует часто используемые вызовы функций и объекта
// - Проходит по всем сегментам змейки, рассчитывая их положение в пикселях с учётом отступа сетки.
// - Рисует каждый сегмент в виде квадрата, соответствующего размеру клетки.
void Snake::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); // Цвет змейки: зелёный

    const int grid_border = m_grid->get_grid_border();
    const int grid_cell_size = m_grid->get_cell_size();
    SDL_Rect rect = { 0, 0, grid_cell_size, grid_cell_size };

    for ( auto& segment : m_segments ) {
        rect.x = grid_border + segment.second * grid_cell_size;
        rect.y = grid_border + segment.first * grid_cell_size;
        
        SDL_RenderFillRect( renderer, &rect );
    }
}

// Устанавливает новое направление движения змейки.  
// - Запрещает разворот на 180 градусов (змейка не может двигаться в обратном направлении).  
// - Обновляет значения dx и dy, задавая новое направление.
void Snake::set_direction( int new_dx, int new_dy ) {
    if ( new_dx == -m_direction_x && new_dy == -m_direction_y ) return; // Запрет разворота на 180 градусов
    m_direction_x = new_dx;
    m_direction_y = new_dy;
}

// Проверяем столкновение змейки с самой собой
// - Проверяем достаточно ли змейка большая для того чтобы столкнуться с хвостом
// - Запоминаем голову змейки
// - сравниваем позиции сегментов змейки не включая голову первые три сегмента так как они никак столкнуться не могут
// - Если столкновение есть, то змейка умирает меняя флаг is_alive на false и выходим из функции
void Snake::check_collision() {
    if ( m_segments.size() >= 4 ) {
        auto head = m_segments.front();
        for ( auto it = m_segments.begin() + 3; it != m_segments.end(); ++it ) {
            if ( *it == head ) {
                is_alive = false;
                return;
            }
        }
    }
}

// Получаем флаг жива змейка или нет
bool Snake::get_is_alive() const { return is_alive; }
// Получаем размер змейки
int Snake::get_number_of_segments() const { return m_segments.size(); }

Snake::~Snake() {}