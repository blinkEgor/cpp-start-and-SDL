#pragma once
#include <SDL2/SDL.h>
#include "Button.h"
#include "../Utils/LogError.h"

class StartMenu {
private:
    Button m_start_button;

public:
    StartMenu( std::pair< int, int >, SDL_Renderer* renderer, TTF_Font* font );

    void handle_input( SDL_Event& e );
    bool is_active_button();
    void draw( SDL_Renderer* renderer );
};