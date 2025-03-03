#pragma once

#include <SDL2/SDL.h>

class StartMenu {
private:
    SDL_Rect button_rect;  // Границы кнопки
    bool is_clicked; // Флаг нажатия

public:
    StartMenu( int window_width, int window_height );

    void draw( SDL_Renderer* renderer );
    void setClick( int x, int y );
    bool getIsClicked() const;
};