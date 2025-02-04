#include "Player.h"

Player::Player() {}

// Drawing Player
void Player::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a ); // set color
    SDL_Rect rect = { x, y, w, h }; // update rect to Player will corret drawing
    SDL_RenderFillRect( renderer, &rect ); // draw
}

// Moving Player to right side
void Player::move_right() { x += speed; } // update X position

// Moving Player to left side
void Player::move_left() { x -= speed; } // update X position

// Moving Player to up side
void Player::move_up() { y -= speed; } // update Y position

// Moving Player to down side
void Player::move_down() { y += speed; } // update Y position

Player::~Player() {}