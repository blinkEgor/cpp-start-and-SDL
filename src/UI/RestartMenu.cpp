#include "RestartMenu.h"

RestartMenu::RestartMenu( std::pair< int, int > window_size, SDL_Renderer* renderer, TTF_Font* font )
{
    // Размеры элементов
    SDL_Rect rect;

    // Реализация одного элемента
    rect.w = 200;
    rect.h = 50;
    m_restart_button = Button( 
        { 
            ( window_size.first - rect.w ) / 2, 
            ( window_size.second - rect.h ) / 2, 
            rect.w, rect.h 
        }, 
        Palette::BG_BTN_GREEN, Palette::TEXT_WHITE, "Restart" 
    );
    m_restart_button.update_text_texture( renderer, font );
}

// Обработчик ивентов стартового меню
void RestartMenu::handle_input( SDL_Event& e ) {
    if ( e.type == SDL_MOUSEBUTTONDOWN ) {
        std::pair< int, int > mouse_pos = { e.button.x, e.button.y };
        logError( "Mouse button was pressed on position x:" + std::to_string( mouse_pos.first ) + " y:" + std::to_string( mouse_pos.second ), LogLevel::INFO );
        m_restart_button.check_click_button( mouse_pos );
        return;
    } else if ( e.type == SDL_KEYDOWN ) {
        if ( e.key.keysym.sym == SDLK_SPACE ) {
            logError( "Space was pressed", LogLevel::INFO );
            m_restart_button.set_click();
            return;
        } else if ( e.key.keysym.sym == SDLK_RETURN ) {
            logError( "Enter was pressed", LogLevel::INFO );
            m_restart_button.set_click();
        }
    }
}

// Возвращает статус активированности/неактивированности кнопки 
bool RestartMenu::is_active_button() { return m_restart_button.get_is_clicked(); }

// Рисуем все элементы стартового меню
// - Устанавливаем цвет кнопки на зелёный
// - Рисуем саму кнопку в центре экрана
void RestartMenu::draw( SDL_Renderer* renderer ) {
    m_restart_button.draw( renderer );
}