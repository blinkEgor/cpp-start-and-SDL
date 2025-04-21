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

Button::~Button() {
    if ( m_text_texture ) {
        SDL_DestroyTexture( m_text_texture );
        m_text_texture = nullptr;
        logError( "Text texture successfully destroyed", LogLevel::INFO );
    }
}

// Метод для установки шрифта и генерации текстуры
void Button::update_text_texture( SDL_Renderer* renderer, TTF_Font* font ) {
    if ( m_text_texture ) SDL_DestroyTexture( m_text_texture );

    SDL_Surface* surface = TTF_RenderText_Solid( font, m_text.c_str(), m_text_color );
    if ( !surface ) {
        logError( "Surface can't create TTF_RenderText_Solid: " + std::string( TTF_GetError() ), LogLevel::ERROR );
        return;
    }

    m_text_texture = SDL_CreateTextureFromSurface( renderer, surface );

    m_text_rect = {
        m_button_rect.x + ( m_button_rect.w - surface->w ) / 2,
        m_button_rect.y + ( m_button_rect.h - surface->h ) / 2,
        surface->w,
        surface->h
    };

    SDL_FreeSurface( surface );
}

// Активирует кнопку в состояние "нажата"
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

    if ( m_text_texture ) {
        SDL_RenderCopy( renderer, m_text_texture, nullptr, &m_text_rect );
    }
}