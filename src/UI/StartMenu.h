#pragma once
#include <SDL2/SDL.h>
#include "Button.h"

class StartMenu {
private:
    Button m_start_button;

public:
    StartMenu( std::pair< int, int > );

    void draw( SDL_Renderer* renderer );
};