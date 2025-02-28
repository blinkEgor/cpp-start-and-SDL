#pragma once
#include <iostream>
#include <deque>
#include <SDL2/SDL.h>
#include "../Game/Grid.h"

class Snake {
private:
    std::deque<std::pair<int, int>> segments;
    Grid* grid;
    Uint32 lastMoveTime;  // Время последнего хода змейки
    int moveDelay;        // Задержка между ходами (мс)
    int dx, dy;           // Текущее направление движения
public:
    Snake( Grid* grid, int start_row, int start_col );
    void move();
    void grow();
    void draw( SDL_Renderer* renderer );
    void setDirection( int newDx, int newDy );
    ~Snake();
};