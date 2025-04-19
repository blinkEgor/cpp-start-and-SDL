#pragma once
#include <SDL2/SDL.h>
#include <string>

class Button {
private:
    SDL_Rect m_button_rect = { 0, 0, 30, 10 }; // Границы кнопки: по умолчанию прямоугольник 30*10 в левом верхнем углу экрана
    SDL_Color m_background_color = { 0, 255, 0, 255 }; // Цвет кнопки: по умолчанию зелёный
    SDL_Color m_text_color = { 255, 255, 255, 255 }; // Цвет текста: по умолчанию белый
    std::string m_text = "text"; // Текст кнопки: по умолчанию "text"

    bool is_clicked = false; // Флаг нажатия: по умолчанию "false"

public:
    Button(
        SDL_Rect button_rect = { 0, 0, 30, 10 },
        SDL_Color background_color = { 0, 255, 0, 255 },
        SDL_Color text_color = { 255, 255, 255, 255 },
        std::string text = "text"
    );
    void set_click();
    void reset_click();
    bool get_is_clicked() const;
    void check_click_button( std::pair< int, int > click_position );
    void draw( SDL_Renderer* renderer );
};