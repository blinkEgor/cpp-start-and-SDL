#pragma once
#include <SDL2/SDL.h>
#include <string>

class Button {
protected:
    SDL_Rect m_button_rect = { 0, 0, 10, 10 }; // Границы кнопки
    SDL_Color m_background_color = { 0, 255, 0, 0 }; // Цвет кнопки
    SDL_Color m_text_color = { 255, 255, 255, 0 }; // Цвет текста 
    std::string m_text = "text"; // Текси кнопки
    bool is_clicked = false; // Флаг нажатия

public:
    virtual void draw( SDL_Renderer* renderer ) = 0;
    virtual void set_click( std::pair< int, int > click_position ) = 0;
    virtual bool get_is_clicked() const = 0;
};