#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../Utils/LogError.h"

class Button {
private:
    SDL_Rect m_button_rect; // Границы кнопки: по умолчанию прямоугольник 30*10 в левом верхнем углу экрана
    SDL_Color m_background_color; // Цвет кнопки: по умолчанию зелёный
    SDL_Color m_text_color; // Цвет текста: по умолчанию белый
    std::string m_text; // Текст кнопки: по умолчанию "text"

    SDL_Texture* m_text_texture = nullptr;
    SDL_Rect m_text_rect = { 0, 0, 0, 0 };
    bool is_clicked = false; // Флаг нажатия: по умолчанию "false"

public:
    Button(
        SDL_Rect button_rect = { 0, 0, 30, 10 },
        SDL_Color background_color = { 0, 255, 0, 255 },
        SDL_Color text_color = { 255, 255, 255, 255 },
        std::string text = "text"
    );
    ~Button();
    void update_text_texture( SDL_Renderer* renderer, TTF_Font* font );
    void set_click();
    void reset_click();
    bool get_is_clicked() const;
    void check_click_button( std::pair< int, int > click_position );
    void draw( SDL_Renderer* renderer );
};