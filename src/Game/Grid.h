#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

class Grid {
private:
    const int cell_size; // Размер одной клетки в пикселях
    const int cell_count; // Количество клеток по ширине и высоте
    const int grid_size; // Общий размер сетки в пикселях
    const int grid_border; // Отступ вокруг сетки

    // Двумерный вектор для хранения состояния клеток
    std::vector<std::vector<int>> grid;

public:
    Grid( int cell_size = 32, int cell_count = 10, int grid_border = 10 );
    void drawGrid( SDL_Renderer* renderer );
    ~Grid();
};
