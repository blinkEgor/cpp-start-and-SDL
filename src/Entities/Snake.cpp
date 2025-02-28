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

// Движение змейки
// Двигаемся только через moveDelay мс
void Snake::move() {
    Uint32 currentTime = SDL_GetTicks();
    if ( currentTime - lastMoveTime < moveDelay ) return;
    lastMoveTime = currentTime;

    int newRow = segments.front().first + dy;
    int newCol = segments.front().second + dx;

    // Проверка выхода за границы
    if ( newRow < 0 || newRow >= grid->getCellRows() || newCol < 0 || newCol >= grid->getCellCols() ) return;

    segments.push_front({ newRow, newCol });
    segments.pop_back();
}

void Snake::grow() {}

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

// Здаём направление
// Запрет разворота на 180 градусов
void Snake::setDirection(int newDx, int newDy) {
    if (newDx == -dx && newDy == -dy) return;
    dx = newDx;
    dy = newDy;
}

Snake::~Snake() {}