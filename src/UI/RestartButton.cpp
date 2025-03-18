#include "RestartButton.h"


RestartButton::RestartButton( int window_width, int window_height ) 
{
    m_button_rect.w = 200;
    m_button_rect.h = 50;
    m_button_rect.x = ( window_width - m_button_rect.w ) / 2;
    m_button_rect.y = ( window_height - m_button_rect.h ) / 2;
}

// Рисуем кнопку рестарта
// - Устанавливаем цвет кнопки на зелёный
// - Рисуем саму кнопку в центре экрана
void RestartButton::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 0, 220, 0, 255 ); // Зелёный цвет
    SDL_RenderFillRect( renderer, &m_button_rect );
}

// Флаг нажатия на кнопку
// - Если координаты мышки находятся в пределах кнопки, то
// - - Меняем значение флага на true
void RestartButton::set_click( int x, int y ) {
    if ( x >= m_button_rect.x && x <= m_button_rect.x + m_button_rect.w /* Проверка по ширине */ && 
         y >= m_button_rect.y && y <= m_button_rect.y + m_button_rect.h /* Проверка по высоте */ ) {
        is_clicked = true;
    }
}

// Получаем флаг нажатия на кнопку
// - если false, то не нажата
// - если true, то нажата
bool RestartButton::get_is_clicked() const { return is_clicked; }