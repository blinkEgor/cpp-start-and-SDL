#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../Utils/LogError.h"

class Text {
private:
    SDL_Rect m_text_rect; // Границы текста: по умолчанию прямоугольник 256*48 в левом верхнем углу экрана
    SDL_Color m_text_color; // Цвет текста: по умолчанию серый на 100 100 100 255 RGBA
    std::string m_text; // Текст: по умолчанию ""

    SDL_Texture* m_text_texture;

public:
    Text(
        SDL_Rect text_rect = { 0, 0, 256, 48 },
        SDL_Color text_color = { 100, 100, 100, 255 },
        std::string text = ""
    );
    ~Text();
    void update_text_score( int score = 0 );
    void update_text_texture( SDL_Renderer* renderer, TTF_Font* font );
    void draw( SDL_Renderer* renderer );
};