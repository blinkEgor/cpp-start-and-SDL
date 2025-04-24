#pragma once
#include <iostream>
#include <deque>
#include <SDL2/SDL.h>
#include "../Utils/Utils.h"
#include "../Game/Grid.h"
#include "Food.h"
#include "../Graphics/Colors.h"

class Snake {
private:
    std::deque<std::pair<int, int>> m_segments;
    Uint32 m_last_move_time; // Время последнего хода змейки
    Uint32 m_move_delay; // Задержка между ходами (мс)
    std::pair< int, int > m_direction; // Текущее направление движения
    bool is_eating; // Флаг, едим или нет?
    bool is_alive; // Флаг, змейка жива?

public:
    Snake( std::pair< int, int > start_position );
    void move( std::vector< std::vector< std::pair< int, int >>>& grid_field );
    bool grow( std::pair< int, int > food_position );
    void draw( SDL_Renderer* renderer, int grid_cell_size, int grid_border );
    void set_direction( std::pair< int, int > new_direction );
    void check_collision();
    bool get_is_alive() const;
    int get_number_of_segments() const;
    std::deque< std::pair< int, int >>& get_snake_segments();
    std::pair< int, int > get_snake_direction() const;
    ~Snake();
};