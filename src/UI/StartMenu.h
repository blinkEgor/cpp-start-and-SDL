#pragma once
#include <SDL2/SDL.h>
#include "Button.h"
#include "../Utils/LogError.h"

class StartMenu {
private:
    Button m_start_button;

public:
    StartMenu( std::pair< int, int > );

    void handle_input( SDL_Event& e );
    void draw( SDL_Renderer* renderer );
};