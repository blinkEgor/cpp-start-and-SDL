#include "Snake.h"

Snake::Snake( Grid* grid, int start_row, int start_col ) : 
    grid( grid ), 
    lastMoveTime( 0 ), 
    moveDelay( 200 ), 
    dx( 0 ), 
    dy( 0 )
{
    segments.push_back( { start_row, start_col } );
}

// Перемещает змейку в текущем направлении через заданные интервалы времени (moveDelay).
// - Проверяет, прошло ли достаточно времени с последнего перемещения.
// - Вычисляет новую позицию головы, учитывая переход через границы сетки.
// - Обновляет положение змейки, добавляя новую голову и удаляя хвост.
void Snake::move() {
    Uint32 currentTime = SDL_GetTicks();
    if ( currentTime - lastMoveTime < moveDelay ) return;
    lastMoveTime = currentTime;

    int rows = grid->getCellRows();
    int cols = grid->getCellCols();

    int newRow = ( segments.front().first + dy + rows ) % rows;
    int newCol = ( segments.front().second + dx + cols ) % cols;

    segments.push_front({ newRow, newCol });
    segments.pop_back();
}

void Snake::grow() {}

// Отрисовывает змейку на экране, заполняя её сегменты зелёным цветом.
// - Устанавливает цвет рисования (зелёный).
// - Проходит по всем сегментам змейки, рассчитывая их положение в пикселях с учётом отступа сетки.
// - Рисует каждый сегмент в виде квадрата, соответствующего размеру клетки.
void Snake::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); // Цвет змейки: зелёный
    for ( auto& segment : segments ) {
        SDL_Rect rect = { 
            grid->getGridBorder() + segment.second * grid->getCellSize(), 
            grid->getGridBorder() + segment.first * grid->getCellSize(), 
            grid->getCellSize(), grid->getCellSize() };
        SDL_RenderFillRect( renderer, &rect );
    }
}

// Устанавливает новое направление движения змейки.  
// - Запрещает разворот на 180 градусов (змейка не может двигаться в обратном направлении).  
// - Обновляет значения dx и dy, задавая новое направление.
void Snake::setDirection(int newDx, int newDy) {
    if (newDx == -dx && newDy == -dy) return; // Запрет разворота на 180 градусов
    dx = newDx;
    dy = newDy;
}

Snake::~Snake() {}