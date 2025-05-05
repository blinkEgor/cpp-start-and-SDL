#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../Utils/LogError.h"

class Logo {
private:
    SDL_Rect m_logo_rect; // Границы логотипа: по умолчанию прямоугольник 256*48 в левом верхнем углу экрана
    SDL_Color m_text_color; // Цвет текста: по умолчанию белый
    std::string m_text; // Текст кнопки: по умолчанию ""

    SDL_Texture* m_text_texture;

public:
    Logo(
        SDL_Rect logo_rect = { 0, 0, 256, 48 },
        SDL_Color text_color = { 255, 255, 255, 255 },
        std::string text = ""
    );
    ~Logo();
    void update_text_texture( SDL_Renderer* renderer, TTF_Font* font );
    void draw( SDL_Renderer* renderer );
};