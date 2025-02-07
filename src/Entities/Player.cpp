#include "Player.h"

Player::Player() {}

// Drawing Player
void Player::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a ); // set color
    SDL_Rect rect = { x, y, w, h }; // update rect to Player will corret drawing
    SDL_RenderFillRect( renderer, &rect ); // draw
}

// Moving Player
void Player::move( int width, int height ) { 
    x += velocity_x; // update vertical position
    y += velocity_y; // update horisontal position

    // check for collision with window borders (можно вынести в отдельный метод)
    if ( x + w > width ) x = width - w;
    if ( x < 0 ) x = 0;
    if ( y + h > height ) y = height - h;
    if ( y < 0 ) y = 0;
}

// Настраивает значение для позиции во время движения по горизонтали
void Player::update_velocity_x( int _x ) { velocity_x = speed * _x; } // default = 0

// Настраивает значение для позиции во время движения по вертикали
void Player::update_velocity_y( int _y ) { velocity_y = speed * _y; } // default = 0

Player::~Player() {}