#pragma once
#include <iostream>
#include <deque>
#include <SDL2/SDL.h>
#include "../Game/Grid.h"
#include "Food.h"

class Snake {
private:
    std::deque<std::pair<int, int>> m_segments;
    Grid* m_grid;
    Food* m_food;
    Uint32 m_last_move_time; // Время последнего хода змейки
    Uint32 m_move_delay; // Задержка между ходами (мс)
    int m_direction_x, m_direction_y; // Текущее направление движения
    bool is_eating; // Флаг, едим или нет?
    bool is_alive; // Флаг, змейка жива?

public:
    Snake( Grid* grid, Food* food, int start_row, int start_col );
    void move();
    void grow();
    void draw( SDL_Renderer* renderer );
    void set_direction( int new_dx, int new_dy );
    void check_collision();
    bool get_is_alive() const;
    int get_number_of_segments() const;
    ~Snake();
};