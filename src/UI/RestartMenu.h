#pragma once
#include <SDL2/SDL.h>
#include <map>
#include "Menu.h"
#include "Button.h"
#include "Text.h"
#include "../Utils/LogError.h"
#include "../Graphics/Colors.h"

class RestartMenu : public Menu {
private:
    Button m_restart_button;
    Text m_score;

public:
    RestartMenu( std::pair< int, int > window_size, SDL_Renderer* renderer, std::map< int, TTF_Font* > font_map );

    void handle_input( SDL_Event& e ) override;
    void update( SDL_Renderer* renderer, TTF_Font* font, int score );
    bool is_active_button() override;
    void draw( SDL_Renderer* renderer ) override;
};