#pragma once
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "../Graphics/Colors.h"

class Grid {
private:
    const int m_cell_size; // Размер одной клетки в пикселях
    const int m_cell_rows; // Количество клеток по высоте
    const int m_cell_cols; // Количество клеток по ширине
    const int m_grid_border; // Отступ вокруг сетки
    const int m_grid_rows_size; // Общий размер строки в пикселях
    const int m_grid_cols_size; // Общий размер колонки в пикселях

    // Двумерный вектор для хранения состояния клеток
    std::vector< std::vector< std::pair< int, int >>> m_grid_field;

public:
    Grid();
    void draw_grid( SDL_Renderer* renderer );
    int get_cell_size() const;
    int get_grid_border() const;
    int get_cell_rows() const;
    int get_cell_cols() const;
    std::vector< std::vector< std::pair< int, int >>>& get_grid_field();
    ~Grid();
};
