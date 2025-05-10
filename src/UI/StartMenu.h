#pragma once
#include <SDL2/SDL.h>
#include <map>
#include "Menu.h"
#include "Logo.h"
#include "Button.h"
#include "../Utils/LogError.h"
#include "../Graphics/Colors.h"

class StartMenu : public Menu {
private:
    Logo m_logo;
    Button m_start_button;

public:
    StartMenu( std::pair< int, int > window_size, SDL_Renderer* renderer, std::map< int, TTF_Font* > font_map );

    void handle_input( SDL_Event& e ) override;
    bool is_active_button() override;
    void draw( SDL_Renderer* renderer ) override;
};