#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

class Grid {
private:
    const int cell_size; // Размер одной клетки в пикселях
    const int cell_count; // Количество клеток по ширине и высоте
    const int grid_size; // Общий размер сетки в пикселях

    // Двумерный вектор для хранения состояния клеток
    std::vector<std::vector<int>> grid;

public:
    Grid( int cellSize = 32, int cellCount = 10 );
    void drawGrid( SDL_Renderer* renderer );
    ~Grid();
};
