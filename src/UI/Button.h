#pragma once
#include <SDL2/SDL.h>
#include <string>

class Button {
protected:
    SDL_Rect m_button_rect = { 0, 0, 30, 10 }; // Границы кнопки: по умолчанию квадрад 30*10 в левом верхнем углу экрана
    SDL_Color m_background_color = { 0, 255, 0, 0 }; // Цвет кнопки: по умолчанию зелёный
    SDL_Color m_text_color = { 255, 255, 255, 0 }; // Цвет текста: по умолчанию белый
    std::string m_text = "text"; // Текст кнопки: по умолчанию "text"
    
    bool is_clicked = false; // Флаг нажатия: по умолчанию "false"

public:
    virtual void draw( SDL_Renderer* renderer ) = 0;
    virtual void set_click( std::pair< int, int > click_position ) = 0;
    virtual bool get_is_clicked() const = 0;
};