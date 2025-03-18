#pragma once

#include <SDL2/SDL.h>

class StartMenu {
private:
    SDL_Rect m_button_rect;  // Границы кнопки
    bool is_clicked = false; // Флаг нажатия

public:
    StartMenu( int window_width, int window_height );

    void draw( SDL_Renderer* renderer );
    void set_click( int x, int y );
    bool get_is_clicked() const;
};