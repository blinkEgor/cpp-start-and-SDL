#include "Player.h"

Player::Player() {}

// Drawing Player
void Player::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a ); // set color
    SDL_RenderFillRect( renderer, &rect ); // draw
}

// Moving Player to right side
void Player::move_right() {
    x++; // update X position
    rect = { x, y, w, h }; // update rect to Player will corret drawing
}

Player::~Player() {}