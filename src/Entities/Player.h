#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Player {
private:
    Uint8 r = 255, g = 255, b = 255, a = 255; // color 
    int x = 64, y = 64, w = 32, h = 32; // position and size
    int speed = 4; // скорость в пикселях, параметр скорости
    int velocity_x = 0, velocity_y = 0; // текущая скорость в пикселях
public:
    Player();
    void draw( SDL_Renderer* renderer );
    void move( int width, int height );
    void update_velocity_x( int _x = 0 );
    void update_velocity_y( int _y = 0 );

    ~Player();
};
