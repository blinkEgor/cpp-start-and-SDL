#include "Player.h"

Player::Player() {}

// Drawing Player
// set color
// update rect to Player will corret drawing
// draw
void Player::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a ); 
    SDL_Rect rect = { x, y, w, h }; 
    SDL_RenderFillRect( renderer, &rect ); 
}

// Moving Player
// update vertical position
// update horisontal position
// check for collision with window borders
void Player::move( int width, int height ) { 
    x += velocity_x; 
    y += velocity_y; 

    // check for collision with window borders (можно вынести в отдельный метод)
    if ( x + w > width ) x = width - w;
    if ( x < 0 ) x = 0;
    if ( y + h > height ) y = height - h;
    if ( y < 0 ) y = 0;
}

// Настраивает значение для позиции во время движения по горизонтали
// default = 0
void Player::update_velocity_x( int _x ) { velocity_x = speed * _x; } 

// Настраивает значение для позиции во время движения по вертикали
// default = 0
void Player::update_velocity_y( int _y ) { velocity_y = speed * _y; } 

Player::~Player() {}