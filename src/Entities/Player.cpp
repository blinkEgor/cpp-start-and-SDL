#include "Player.h"

Player::Player() {}

// Drawing Player
void Player::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a ); // set color
    SDL_Rect rect = { x, y, w, h }; // update rect to Player will corret drawing
    SDL_RenderFillRect( renderer, &rect ); // draw
}

// Moving Player
void Player::move() { 
    x += velocity_x;
    y += velocity_y;
}

// Настраивает значение для позиции во время движения по горизонтали
void Player::update_velocity_x( int _x ) { velocity_x = speed * _x; }

// Настраивает значение для позиции во время движения по вертикали
void Player::update_velocity_y( int _y ) { velocity_y = speed * _y; }

Player::~Player() {}