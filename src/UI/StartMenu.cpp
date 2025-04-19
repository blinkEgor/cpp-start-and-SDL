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

// Рисуем все элементы стартового меню
// - Устанавливаем цвет кнопки на зелёный
// - Рисуем саму кнопку в центре экрана
void StartMenu::draw( SDL_Renderer* renderer ) {
    m_start_button.draw( renderer );
}