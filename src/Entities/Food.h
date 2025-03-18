#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "../Game/Grid.h"

class Food {
private:
    Grid* m_grid; // Ссылка на сетку
    int m_row, m_col; // Позиция еды на сетке строка и столбец
public:
    Food( Grid* grid );
    void respawn_food(); // Перемещает еду в случайную позицию
    void draw( SDL_Renderer* renderer ); // Отрисовка еды
    int get_food_row() const;
    int get_food_col() const;
    ~Food();
};