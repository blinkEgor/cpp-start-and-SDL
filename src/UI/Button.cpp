#include "Button.h"

Button::Button( 
    SDL_Rect button_rect,
    SDL_Color background_color,
    SDL_Color text_color,
    std::string text
) : 
    m_button_rect( button_rect ), 
    m_background_color( background_color ), 
    m_text_color( text_color ), 
    m_text( text )
{}

// Флаг нажатия на кнопку
void Button::set_click() { is_clicked = true; }
// Возвращает кнопку в состояние "не нажата"
void Button::reset_click() { is_clicked = false; }

// Получаем флаг нажатия на кнопку
// - если false, то не нажата
// - если true, то нажата
bool Button::get_is_clicked() const { return is_clicked; }

// - Если координаты мышки находятся в пределах кнопки, то
// - - Меняем значение флага на true
void Button::check_click_button( std::pair< int, int > click_position ) {
    if ( click_position.first >= m_button_rect.x 
         && click_position.first <= m_button_rect.x + m_button_rect.w /* Проверка по ширине */ 
         && 
         click_position.second >= m_button_rect.y 
         && click_position.second <= m_button_rect.y + m_button_rect.h /* Проверка по высоте */ 
        ) {
        set_click();
    }
}

// Рисуем кнопку рестарта
// - Устанавливаем цвет кнопки на зелёный
// - Рисуем саму кнопку в центре экрана
void Button::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor(
        renderer, 
        m_background_color.r,    // Красный компонент
        m_background_color.g,    // Зеленый компонент
        m_background_color.b,    // Синий компонент
        m_background_color.a     // Альфа (непрозрачность)
    );
    SDL_RenderFillRect( renderer, &m_button_rect );
}