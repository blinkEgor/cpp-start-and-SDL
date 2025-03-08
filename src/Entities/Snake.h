#pragma once
#include <iostream>
#include <deque>
#include <SDL2/SDL.h>
#include "../Game/Grid.h"
#include "Food.h"

class Snake {
private:
    std::deque<std::pair<int, int>> segments;
    Grid* grid;
    Food* food;
    Uint32 last_move_time; // Время последнего хода змейки
    Uint32 move_delay; // Задержка между ходами (мс)
    int dx, dy; // Текущее направление движения
    bool is_eating; // Флаг, едим или нет?
    bool is_alive; // Флаг, змейка жива?

public:
    Snake( Grid* grid, Food* food, int start_row, int start_col );
    void move();
    void grow();
    void draw( SDL_Renderer* renderer );
    void setDirection( int new_dx, int new_dy );
    void checkCollision();
    bool getIsAlive() const;
    int getNumberOfSegments() const;
    ~Snake();
};