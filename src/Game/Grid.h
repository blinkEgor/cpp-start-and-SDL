#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

class Grid {
private:
    const int cell_size; // Размер одной клетки в пикселях
    const int cell_rows; // Количество клеток по ширине
    const int cell_cols; // Количество клеток по высоте
    const int grid_rows_size; // Общий размер строки в пикселях
    const int grid_cols_size; // Общий размер колонки в пикселях
    const int grid_border; // Отступ вокруг сетки

    // Двумерный вектор для хранения состояния клеток
    std::vector<std::vector<int>> grid;

public:
    Grid();
    void drawGrid( SDL_Renderer* renderer );
    void printGrid();
    ~Grid();
};
