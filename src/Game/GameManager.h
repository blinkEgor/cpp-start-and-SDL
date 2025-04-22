#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../Graphics/WindowManager.h"
#include "GameState.h"
#include "StartMenuState.h"
#include "PlayState.h"
#include "../Graphics/Colors.h"

class GameManager {
private:
    WindowManager* window_manager;
    std::unique_ptr<GameState> m_current_state = nullptr;
    std::unique_ptr<GameState> m_next_state = nullptr;

public:
    GameManager( WindowManager* window_manager );

    void game_loop();
    void set_next_state( std::unique_ptr<GameState> next_state );
    void change_state();

    GameState* get_current_state() const;
};