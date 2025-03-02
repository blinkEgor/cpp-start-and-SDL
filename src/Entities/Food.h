#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "../Game/Grid.h"

class Food {
private:
    Grid* grid; // Ссылка на сетку
    int row, col; // Позиция еды на сетке строка и столбец
public:
    Food( Grid* grid );
    void respawnFood(); // Перемещает еду в случайную позицию
    void draw( SDL_Renderer* renderer ); // Отрисовка еды
    int getFoodRow() const;
    int getFoodCol() const;
    ~Food();
};