#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <deque>
#include <algorithm>
#include "../Utils/Utils.h"
#include "../Graphics/Colors.h"

class Food {
private:
    std::pair< int, int > m_position = { 0, 0 }; // Позиция еды на сетке
public:
    Food( std::pair< int, int > start_position );
    void respawn_food( std::vector< std::vector< std::pair< int, int >>>& grid_field, std::deque< std::pair< int, int >>& snake_segments ); // Перемещает еду в случайную позицию
    void draw( SDL_Renderer* renderer, int grid_cell_size, int grid_border ); // Отрисовка еды
    std::pair< int, int > get_food_position() const;
    ~Food();
};