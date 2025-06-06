#include "StartMenu.h"

StartMenu::StartMenu( std::pair< int, int > window_size, SDL_Renderer* renderer, std::map< int, TTF_Font* > font_map )
{
    // Размеры элементов
    SDL_Rect rect;

    // Реализация Логотипа
    rect = { 0, 0, 256, 48 }; // Значения могут быть любыми, они просто указывают положение относительно окна
    m_logo = Logo(
        { 
            ( window_size.first - rect.w ) / 2, 
            ( window_size.second - rect.h - 200 ) / 2, /* 200 - это отступ от центра окна, где находится кнопка, вверх */ 
            rect.w, rect.h 
        }, 
        Palette::TEXT_WHITE, "Snake"
    );
    m_logo.update_text_texture( renderer, font_map[ 64 ] );

    // Реализация Кнопки старта
    rect = { 0, 0, 256, 48 };
    m_start_button = Button( 
        { /* Абсолютное центрирование кнопки по центру окна */
            ( window_size.first - rect.w ) / 2, 
            ( window_size.second - rect.h ) / 2, 
            rect.w, rect.h 
        }, 
        Palette::BG_BTN_GREEN, Palette::TEXT_WHITE, "Start" 
    );
    m_start_button.update_text_texture( renderer, font_map[ 32 ] );
}

// Обработчик ивентов стартового меню
void StartMenu::handle_input( SDL_Event& e ) {
    if ( e.type == SDL_MOUSEBUTTONDOWN ) {
        std::pair< int, int > mouse_pos = { e.button.x, e.button.y };
        logError( "Mouse button was pressed on position x:" + std::to_string( mouse_pos.first ) + " y:" + std::to_string( mouse_pos.second ), LogLevel::INFO );
        m_start_button.check_click_button( mouse_pos );
        return;
    } else if ( e.type == SDL_KEYDOWN ) {
        if ( e.key.keysym.sym == SDLK_SPACE ) {
            logError( "Space was pressed", LogLevel::INFO );
            m_start_button.set_click();
            return;
        } else if ( e.key.keysym.sym == SDLK_RETURN ) {
            logError( "Enter was pressed", LogLevel::INFO );
            m_start_button.set_click();
        }
    }
}

// Возвращает статус активированности/неактивированности кнопки 
bool StartMenu::is_active_button() { return m_start_button.get_is_clicked(); }

// Рисуем все элементы стартового меню
// - Устанавливаем цвет кнопки на зелёный
// - Рисуем саму кнопку в центре экрана
void StartMenu::draw( SDL_Renderer* renderer ) {
    m_start_button.draw( renderer );
    m_logo.draw ( renderer );
}