#include "Snake.h"

Snake::Snake( std::pair< int, int > start_position ) : 
    m_last_move_time( 0 ), 
    m_move_delay( 200 ), 
    m_direction( { 0, 0 } ),
    is_eating( false ),
    is_alive( true )
{
    m_segments.push_back( start_position );
}

// Перемещает змейку в текущем направлении через заданные интервалы времени (moveDelay).
// - Проверяет, прошло ли достаточно времени с последнего перемещения.
// - Вычисляет новую позицию головы, учитывая переход через границы сетки.
// - Обновляет положение змейки, добавляя новую голову и удаляя хвост.
void Snake::move( std::vector< std::vector< std::pair< int, int >>>& grid_field ) {
    Uint32 current_time = SDL_GetTicks();
    if ( current_time - m_last_move_time < m_move_delay ) return;
    m_last_move_time = current_time;
    
    std::pair< int, int > grid_sell_position = { grid_field.size(), grid_field[0].size() };
    std::pair< int, int > new_position = ( m_segments.front() + m_direction + grid_sell_position ) % grid_sell_position;

    m_segments.push_front( new_position );
    if ( !is_eating ) m_segments.pop_back();
    is_eating = false;
}

// Проверяет, находится ли голова змейки на позиции еды ( съела ли змейка еду ).
// - Если змейка достигла позиции еды, активирует is_eating и вызывает respawnFood() ( Перемещает еду в новую случайную позицию )
// - Флаг is_eating сообщит move(), что не нужно убирать хвост после следующего движения
bool Snake::grow( std::pair< int, int > food_position ) {
    if ( m_segments.front() == food_position ) {
        is_eating = true;
        return true;
    } else {
        return false;
    }
}

// Отрисовывает змейку на экране, заполняя её сегменты зелёным цветом.
// - Устанавливает цвет рисования (зелёный).
// - Проходит по всем сегментам змейки, рассчитывая их положение в пикселях с учётом отступа сетки.
// - Рисует каждый сегмент в виде квадрата, соответствующего размеру клетки.
void Snake::draw( SDL_Renderer* renderer, int grid_cell_size, int grid_border ) {
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); // Цвет змейки: зелёный
    SDL_Rect rect = { 0, 0, grid_cell_size, grid_cell_size };

    for ( auto& segment : m_segments ) {
        rect.y = segment.first * grid_cell_size + grid_border;
        rect.x = segment.second * grid_cell_size + grid_border;
        
        SDL_RenderFillRect( renderer, &rect );
    }
}

// Устанавливает новое направление движения змейки.  
// - Запрещает разворот на 180 градусов (змейка не может двигаться в обратном направлении).  
// - Обновляет значения dx и dy, задавая новое направление.
void Snake::set_direction( std::pair< int, int > new_direction ) {
    if ( is_opposite_pair( new_direction, m_direction ) ) return; // Запрет разворота на 180 градусов
    m_direction = new_direction;
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
// Получаем ссылку на массив с позициями змейки на поле сетки
std::deque< std::pair< int, int >>& Snake::get_snake_segments() { return m_segments; }

Snake::~Snake() {}