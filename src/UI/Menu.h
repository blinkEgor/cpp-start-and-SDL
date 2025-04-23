#pragma once
#include <SDL2/SDL.h>

class Menu {
public: 
    virtual void handle_input( SDL_Event& e ) = 0;
    virtual bool is_active_button() = 0;
    virtual void draw( SDL_Renderer* renderer ) = 0;
};