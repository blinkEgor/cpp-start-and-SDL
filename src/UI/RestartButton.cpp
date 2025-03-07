#include "RestartButton.h"


RestartButton::RestartButton( int window_width, int window_height ) : 
    is_clicked( false )
{
    button_rect.w = 200;
    button_rect.h = 50;
    button_rect.x = ( window_width - button_rect.w ) / 2;
    button_rect.y = ( window_height - button_rect.h ) / 2;
}

// Рисуем кнопку рестарта
// - Устанавливаем цвет кнопки на зелёный
// - Рисуем саму кнопку в центре экрана
void RestartButton::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 0, 220, 0, 255 ); // Зелёный цвет
    SDL_RenderFillRect( renderer, &button_rect );
}

// Флаг нажатия на кнопку
// - Если координаты мышки находятся в пределах кнопки, то
// - - Меняем значение флага на true
void RestartButton::setClick( int x, int y ) {
    if ( x >= button_rect.x && x <= button_rect.x + button_rect.w /* Проверка по ширине */ && 
         y >= button_rect.y && y <= button_rect.y + button_rect.h /* Проверка по высоте */ ) {
        is_clicked = true;
    }
}

// Получаем флаг нажатия на кнопку
// - если false, то не нажата
// - если true, то нажата
bool RestartButton::getIsClicked() const { return is_clicked; }