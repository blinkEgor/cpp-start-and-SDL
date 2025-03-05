#include "Snake.h"

Snake::Snake( Grid* grid, Food* food, int start_row, int start_col ) : 
    grid( grid ), 
    food( food ), 
    last_move_time( 0 ), 
    move_delay( 200 ), 
    dx( 0 ), 
    dy( 0 ),
    is_eating( false ),
    is_alive( true )
{
    segments.push_back( { start_row, start_col } );
}

// Перемещает змейку в текущем направлении через заданные интервалы времени (moveDelay).
// - Проверяет, прошло ли достаточно времени с последнего перемещения.
// - Вычисляет новую позицию головы, учитывая переход через границы сетки.
// - Обновляет положение змейки, добавляя новую голову и удаляя хвост.
void Snake::move() {
    Uint32 current_time = SDL_GetTicks();
    if ( current_time - last_move_time < move_delay ) return;
    last_move_time = current_time;

    int rows = grid->getCellRows();
    int cols = grid->getCellCols();

    int new_row = ( segments.front().first + dy + rows ) % rows;
    int new_col = ( segments.front().second + dx + cols ) % cols;

    segments.push_front({ new_row, new_col });
    if ( !is_eating ) segments.pop_back();
    is_eating = false;
}

// Проверяет, находится ли голова змейки на позиции еды ( съела ли змейка еду ).
// - Если змейка достигла позиции еды, активирует is_eating и вызывает respawnFood() ( Перемещает еду в новую случайную позицию )
// - Флаг is_eating сообщит move(), что не нужно убирать хвост после следующего движения
void Snake::grow() {
    if ( segments.front().first == food->getFoodRow() && segments.front().second == food->getFoodCol() ) {
        is_eating = true;
        food->respawnFood();
    }
}

// Отрисовывает змейку на экране, заполняя её сегменты зелёным цветом.
// - Устанавливает цвет рисования (зелёный).
// - Кэширует часто используемые вызовы функций и объекта
// - Проходит по всем сегментам змейки, рассчитывая их положение в пикселях с учётом отступа сетки.
// - Рисует каждый сегмент в виде квадрата, соответствующего размеру клетки.
void Snake::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); // Цвет змейки: зелёный

    const int grid_border = grid->getGridBorder();
    const int grid_cell_size = grid->getCellSize();
    SDL_Rect rect = { 0, 0, grid_cell_size, grid_cell_size };

    for ( auto& segment : segments ) {
        rect.x = grid_border + segment.second * grid_cell_size;
        rect.y = grid_border + segment.first * grid_cell_size;
        
        SDL_RenderFillRect( renderer, &rect );
    }
}

// Устанавливает новое направление движения змейки.  
// - Запрещает разворот на 180 градусов (змейка не может двигаться в обратном направлении).  
// - Обновляет значения dx и dy, задавая новое направление.
void Snake::setDirection( int new_dx, int new_dy ) {
    if ( new_dx == -dx && new_dy == -dy ) return; // Запрет разворота на 180 градусов
    dx = new_dx;
    dy = new_dy;
}

// Проверяем столкновение змейки с самой собой
// - Проверяем достаточно ли змейка большая для того чтобы столкнуться с хвостом
// - Запоминаем голову змейки
// - сравниваем позиции сегментов змейки не включая голову первые три сегмента так как они никак столкнуться не могут
// - Если столкновение есть, то змейка умирает меняя флаг is_alive на false и выходим из функции
void Snake::checkCollision() {
    if ( segments.size() >= 4 ) {
        auto head = segments.front();
        for ( auto it = segments.begin() + 3; it != segments.end(); ++it ) {
            if ( *it == head ) {
                is_alive = false;
                return;
            }
        }
    }
}

// Получаем флаг жива змейка или нет
bool Snake::getIsAlive() const { return is_alive; }

Snake::~Snake() {}