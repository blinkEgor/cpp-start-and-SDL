#include "StartMenu.h"

StartMenu::StartMenu( std::pair< int, int > window_size )
{
    // Палитра цветов
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color green = { 0, 255, 0, 255 };

    // Размеры элементов
    SDL_Rect rect;

    // Реализация одного элемента
    rect.w = 200;
    rect.h = 50;
    m_start_button = Button( 
        { 
            ( window_size.first - rect.w ) / 2, 
            ( window_size.second - rect.h ) / 2, 
            rect.w, 
            rect.h 
        }, 
        green, 
        white, 
        "Start" 
    );

    // Будет реализация другого элемента когда он разработается
    // ...
}

// Обработчик ивентов стартового меню
void StartMenu::handle_input( SDL_Event& e ) {
    if ( e.type == SDL_MOUSEBUTTONDOWN ) {
        std::pair< int, int > mouse_pos = { e.button.x, e.button.y };
        logError( "Mouse button was pressed on position x:" + std::to_string( mouse_pos.first ) + " y:" + std::to_string( mouse_pos.second ), LogLevel::INFO );
        m_start_button.check_click_button( mouse_pos );
        return;
    }
    if ( e.type == SDL_KEYDOWN ) {
        if ( e.key.keysym.sym == SDLK_SPACE ) {
            logError( "Space was pressed", LogLevel::INFO );
            m_start_button.set_click();
            return;
        }
        if ( e.key.keysym.sym == SDLK_RETURN ) {
            logError( "Enter was pressed", LogLevel::INFO );
            m_start_button.set_click();
        }
    }
}

bool StartMenu::is_active_button() { return m_start_button.get_is_clicked(); }

// Рисуем все элементы стартового меню
// - Устанавливаем цвет кнопки на зелёный
// - Рисуем саму кнопку в центре экрана
void StartMenu::draw( SDL_Renderer* renderer ) {
    m_start_button.draw( renderer );
}